#include "RenderingEngine.h"

#include <assert.h>
#include <glm/gtc/matrix_transform.hpp>

#include "..\Core\GameObject.h"
#include "..\Core\Utility.h"
#include "Viewport.h"
#include "Lighting.h"
#include "Camera3D.h"

/// <summary>
/// Adds the light.
/// </summary>
/// <param name="light">The light.</param>
const glm::mat4 RenderingEngine::BIAS_MATRIX = initScale(glm::vec3(0.5f)) * initTranslation(glm::vec3(1.0f));

RenderingEngine::RenderingEngine(Viewport& viewport, GUIEngine& guiEngine) :
m_filterPlane(Mesh("plane.obj")),
m_viewport(&viewport),
m_guiEngine(&guiEngine),
m_tempTarget(viewport.getScreenWidth(), viewport.getScreenHeight(), 0, GL_TEXTURE_2D, GL_NEAREST, GL_RGBA, GL_RGBA, false, GL_COLOR_ATTACHMENT0),
m_filterPlaneMaterial("renderingEngine_filterPlane", 1, 8, m_tempTarget),
m_defaultShader("forward-ambient"),
m_shadowMapShader("shadowMapGenerator"),
m_nullFilter("filter-null"),
m_gausBlurFilter("filter-gausBlur7x1"),
m_fxaaFilter("filter-fxaa"),
m_altCameraTransform(glm::vec3(0.0f), glm::quat(glm::angleAxis(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)))),
m_altCamera(glm::mat4(1.0f), &m_altCameraTransform)
{
	setSamplerSlot("diffuse", 0);
	setSamplerSlot("normalMap", 1);
	setSamplerSlot("dispMap", 2);
	setSamplerSlot("shadowMap", 3);

	setSamplerSlot("filterTexture", 0);

	setVec3("ambient", glm::vec3(0.4f, 0.4f, 0.4f));

	setFloat("fxaaSpanMax", 8.0f);
	setFloat("fxaaReduceMin", 1.0f / 128.0f);
	setFloat("fxaaReduceMul", 1.0f / 8.0f);

	setTexture("displayTexture", Texture(m_viewport->getScreenWidth(), m_viewport->getScreenHeight(), 0, GL_TEXTURE_2D, GL_LINEAR, GL_RGBA, GL_RGBA, true, GL_COLOR_ATTACHMENT0));

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);

	m_filterPlaneTransform.setScale(glm::vec3(1.0f));
	m_filterPlaneTransform.rotate(glm::quat(glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f))));
	m_filterPlaneTransform.rotate(glm::quat(glm::angleAxis(glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f))));

	for (int i = 0; i < NUM_SHADOW_MAPS; i++)
	{
		int shadowMapSize = 1 << (i + 1);
		m_shadowMaps[i] = Texture(shadowMapSize, shadowMapSize, 0, GL_TEXTURE_2D, GL_LINEAR, GL_RG32F, GL_RGBA, true, GL_COLOR_ATTACHMENT0);
		m_shadowMapTempTargets[i] = Texture(shadowMapSize, shadowMapSize, 0, GL_TEXTURE_2D, GL_LINEAR, GL_RG32F, GL_RGBA, true, GL_COLOR_ATTACHMENT0);
	}

	m_lightMatrix = glm::mat4(
		glm::vec4(0.0f),
		glm::vec4(0.0f),
		glm::vec4(0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
}

void RenderingEngine::render(GameObject & gameObject)
{
	//getTexture("displayTexture").bindRenderTarget();
	m_viewport->bindRenderTarget();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	gameObject.renderAll(m_defaultShader, *m_guiEngine, *this, *m_mainCamera);

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
			m_altCamera.setProjection(shadowInfo.getProjection());
			ShadowCameraTransform shadowCameraTransform = m_activeLight->calcShadowCameraTransform(m_mainCamera->getTransform().getTransformedPos(),
				m_mainCamera->getTransform().getTransformedRot());
			m_altCamera.getTransform()->setPosition(shadowCameraTransform.getPos());
			m_altCamera.getTransform()->setRotation(shadowCameraTransform.getRot());

			m_lightMatrix = BIAS_MATRIX * m_altCamera.getViewProjection();

			setFloat("shadowVarianceMin", shadowInfo.getMinVariance());
			setFloat("shadowLightBleedingReduction", shadowInfo.getLightBleedReductionAmount());
			bool flipFaces = shadowInfo.getFlipFaces();

			if (flipFaces)
			{
				glCullFace(GL_FRONT);
			}

			gameObject.renderAll(m_shadowMapShader, *m_guiEngine, *this, m_altCamera);

			if (!flipFaces)
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
			m_lightMatrix = initScale(glm::vec3(0.0f));
			setFloat("shadowVarianceMin", 0.00002f);
			setFloat("shadowLightBleedingReduction", 0.0f);
		}

		//getTexture("displayTexture").bindRenderTarget();
		m_viewport->bindRenderTarget();

		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glDepthMask(GL_FALSE);
		glDepthFunc(GL_EQUAL);

		gameObject.renderAll(m_activeLight->getShader(), *m_guiEngine, *this, *m_mainCamera);

		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LESS);
		glDisable(GL_BLEND);

	}

	setVec3("inverseFilterTextureSize", glm::vec3(1.0f / getTexture("displayTexture").getWidth(), 1.0f / getTexture("displayTexture").getHeight(), 0.0f));

	//applyFilter(m_fxaaFilter, getTexture("displayTexture"), 0);

}

void RenderingEngine::applyFilter(const Shader & filter, const Texture & src, const Texture * dst)
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

	m_altCamera.setProjection(glm::mat4(1.0f));
	m_altCamera.getTransform()->setPosition(glm::vec3(0.0f));
	m_altCamera.getTransform()->setRotation(glm::quat(glm::angleAxis(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f))));

	glClear(GL_DEPTH_BUFFER_BIT);
	filter.bind();
	filter.updateUniforms(m_filterPlaneTransform, m_filterPlaneMaterial, *this, m_altCamera);
	m_filterPlane.render();

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

