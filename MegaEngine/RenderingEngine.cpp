#include "RenderingEngine.h"
#include "Viewport.h"
#include "BaseLight.h"
#include "GameObject.h"
#include "Camera3D.h"
#include <assert.h>
#include <glm/gtc/matrix_transform.hpp>

const glm::mat4 RenderingEngine::BIAS_MATRIX = glm::scale(glm::vec3(0.5f)) * glm::translate(glm::vec3(1.0f));

RenderingEngine::RenderingEngine(Viewport viewport, GUIEngine & guiEngine) :
m_viewport(&viewport),
m_guiEngine(&guiEngine)
{

}

void RenderingEngine::render(GameObject & gameObject)
{
	getTexture("displayTexture").bindRenderTarget();


	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	gameObject.renderAll(m_defaultShader, *m_guiEngine, *this, m_mainCamera);

	for (unsigned int i = 0; i < m_lights.size(); i++)
	{
		m_activeLight = m_lights[i];
		ShadowInfo shadowInfo = m_activeLight->getShadowInfo();

		int shadowMapIndex = 0;
		if (shadowInfo.getShadowMapSizeAsPowerOf2() != 0)
			shadowMapIndex = shadowInfo.getShadowMapSizeAsPowerOf2() - 1;

		assert(shadowMapIndex >= 0 && shadowMapIndex < NUM_SHADOW_MAPS);

		setTexture("shadowMap", m_shadowMaps[shadowMapIndex]);
		m_shadowMaps[shadowMapIndex].bindRenderTarget();
		glClearColor(1.0f, 1.0f, 0.0f, 0.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		if (shadowInfo.getShadowMapSizeAsPowerOf2() != 0)
		{
			m_altCamera.setCameraProjection(shadowInfo.getProjection());
			ShadowCameraTransform shadowCameraTransform = m_activeLight->calcShadowCameraTransform(m_mainCamera.getTransform()->getTransformedPos(),
				m_mainCamera.getTransform()->getTransformedRot());
			m_altCamera.getTransform()->setPosition(shadowCameraTransform.getPos());
			m_altCamera.getTransform()->setRotation(shadowCameraTransform.getRot());

			m_lightMatrix = BIAS_MATRIX * m_altCamera.projection();

			setFloat("shadowVarianceMin", shadowInfo.getMinVariance());
			setFloat("shadowLightBleedingReduction", shadowInfo.getLightBleedReductionAmount());
			bool flipFaces = shadowInfo.getFlipFaces();

			if (flipFaces)
			{
				glCullFace(GL_FRONT);
			}

			gameObject.renderAll(m_shadowMapShader, *m_guiEngine, *this, m_altCamera);

			if (flipFaces)
			{
				glCullFace(GL_BACK);
			}

			float shadowSoftness = shadowInfo.getShadowSoftness();
			if (shadowSoftness != 0)
			{
				blurShadowMap(shadowMapIndex, shadowSoftness);
			}
		}
		else
		{
			m_lightMatrix = glm::scale(glm::vec3(0.0f));
			setFloat("shadowVarianceMin", 0.00002f);
			setFloat("shadowLightBleedingReduction", 0.0f);
		}

		getTexture("displayTexture").bindRenderTarget();

		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glDepthMask(GL_FALSE);
		glDepthFunc(GL_EQUAL);

		gameObject.renderAll(m_activeLight->getShader(), *m_guiEngine, *this, m_mainCamera);

		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LESS);
		glDisable(GL_BLEND);

	}

	setVec3("inverseFilterTextureSize", glm::vec3(1.0f / getTexture("displayTexture").getWidth(), 1.0f / getTexture("displayTexture").getHeight(), 0.0f));

	applyFilter(m_fxaaFilter, getTexture("displayTexture"), 0);

}

void RenderingEngine::setMainCamera(Camera3D & camera)
{
	m_mainCamera = camera;
}

void RenderingEngine::addLight(const BaseLight & light)
{
	m_lights.emplace_back(light);
}

void RenderingEngine::applyFilter(const Shader & filter, const TextureImage & src, const TextureImage * dst)
{
	assert(&src != dst);
	if (dst == 0)
	{
		m_viewport->bindRenderTarget();
	}
	else
	{
		dst->bindRenderTarget();
	}

	setTexture("filterTexture", src);

	m_altCamera.setCameraProjection();
	m_altCamera.lookAt(glm::vec3(0.0f, 1.0f, 0.0f));
	m_altCamera.setPosition(glm::vec3(0.0f));

	glClear(GL_DEPTH_BUFFER_BIT);
	filter.bind();

	//  TODO : What can I possibly pass through here?

	filter.updateUniforms(nullptr, nullptr, *this, m_altCamera);

	setTexture("filterTexture", 0);

}

void RenderingEngine::blurShadowMap(int shadowMapIndex, float blurAmount)
{
	setVec3("blurScale", glm::vec3(blurAmount / (m_shadowMaps[shadowMapIndex].getWidth()), 0.0f, 0.0f));
	applyFilter(m_gausBlurFilter, m_shadowMaps[shadowMapIndex], &m_shadowMapTempTargets[shadowMapIndex]);

	setVec3("blurScale", glm::vec3(0.0f, blurAmount / (m_shadowMaps[shadowMapIndex].getHeight()), 0.0f));
	applyFilter(m_gausBlurFilter, m_shadowMapTempTargets[shadowMapIndex], &m_shadowMaps[shadowMapIndex]);
}

void RenderingEngine::setSamplerSlot(std::string name, GLuint value)
{
	m_samplerMap[name] = value;
}

