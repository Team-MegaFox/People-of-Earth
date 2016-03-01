#include "renderingEngine.h"
#include "..\Core\GameObject.h"
#include "Shader.h"
#include "Mesh.h"
#include <glew\glew.h>
#include <cassert>

const glm::mat4 RenderingEngine::BIAS_MATRIX = Utility::initScale(glm::vec3(0.5, 0.5, 0.5)) * Utility::initTranslation(glm::vec3(1.0, 1.0, 1.0));
//Should construct a Matrix like this:
//     x   y   z   w
//x [ 0.5 0.0 0.0 0.5 ]
//y [ 0.0 0.5 0.0 0.5 ]
//z [ 0.0 0.0 0.5 0.5 ]
//w [ 0.0 0.0 0.0 1.0 ]
//
//Note the 'w' column in this representation should be
//the translation column!
//
//This matrix will convert 3D coordinates from the range (-1, 1) to the range (0, 1).

RenderingEngine::RenderingEngine(const Viewport& window) :
m_plane(Mesh("Environment/plane.obj")),
m_window(&window),
m_tempTarget(window.getScreenWidth(), window.getScreenHeight(), 0, GL_TEXTURE_2D, GL_NEAREST, GL_RGBA, GL_RGBA, false, GL_COLOR_ATTACHMENT0),
m_planeMaterial("renderingEngine_filterPlane", 1, 8, m_tempTarget),
m_defaultShader("forward-ambient"),
m_shadowMapShader("shadowMapGenerator"),
m_nullFilter("filter-null"),
m_gausBlurFilter("filter-gausBlur7x1"),
m_fxaaFilter("filter-fxaa"),
m_altCameraTransform(glm::vec3(0, 0, 0), glm::angleAxis(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f))),
m_altCamera(glm::mat4(1.0f), &m_altCameraTransform)
{
	setSamplerSlot("diffuse", 0);
	setSamplerSlot("normalMap", 1);
	setSamplerSlot("dispMap", 2);
	setSamplerSlot("shadowMap", 3);

	setSamplerSlot("filterTexture", 0);

	setVec3("ambient", glm::vec3(0.2f, 0.2f, 0.2f));

	setFloat("fxaaSpanMax", 8.0f);
	setFloat("fxaaReduceMin", 1.0f / 128.0f);
	setFloat("fxaaReduceMul", 1.0f / 8.0f);

	setTexture("displayTexture", Texture(m_window->getScreenWidth(), m_window->getScreenHeight(), 0, GL_TEXTURE_2D, GL_LINEAR, GL_RGBA, GL_RGBA, true, GL_COLOR_ATTACHMENT0));

	setSamplerSlot("S_skybox", 0);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);
	//glEnable(GL_MULTISAMPLE);

	//m_planeMaterial("renderingEngine_filterPlane", m_tempTarget, 1, 8);
	m_planeTransform.setScale(glm::vec3(1.0f));
	m_planeTransform.rotate(glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
	m_planeTransform.rotate(glm::angleAxis(glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f)));

	for (int i = 0; i < NUM_SHADOW_MAPS; i++)
	{
		int shadowMapSize = 1 << (i + 1);
		m_shadowMaps[i] = Texture(shadowMapSize, shadowMapSize, 0, GL_TEXTURE_2D, GL_LINEAR, GL_RG32F, GL_RGBA, true, GL_COLOR_ATTACHMENT0);
		m_shadowMapTempTargets[i] = Texture(shadowMapSize, shadowMapSize, 0, GL_TEXTURE_2D, GL_LINEAR, GL_RG32F, GL_RGBA, true, GL_COLOR_ATTACHMENT0);
	}

	m_lightMatrix = Utility::initScale(glm::vec3(0, 0, 0));
}

void RenderingEngine::blurShadowMap(int shadowMapIndex, float blurAmount)
{
	setVec3("blurScale", glm::vec3(blurAmount / (m_shadowMaps[shadowMapIndex].getWidth()), 0.0f, 0.0f));
	applyFilter(m_gausBlurFilter, m_shadowMaps[shadowMapIndex], &m_shadowMapTempTargets[shadowMapIndex]);

	setVec3("blurScale", glm::vec3(0.0f, blurAmount / (m_shadowMaps[shadowMapIndex].getHeight()), 0.0f));
	applyFilter(m_gausBlurFilter, m_shadowMapTempTargets[shadowMapIndex], &m_shadowMaps[shadowMapIndex]);

	//	SetPxVec3("inverseFilterTextureSize", PxVec3(blurAmount/m_shadowMaps[shadowMapIndex].GetWidth(), blurAmount/m_shadowMaps[shadowMapIndex].GetHeight(), 0.0f));
	//	ApplyFilter(m_fxaaFilter, m_shadowMaps[shadowMapIndex], &m_shadowMapTempTargets[shadowMapIndex]);
	//	
	//	ApplyFilter(m_nullFilter, m_shadowMapTempTargets[shadowMapIndex], &m_shadowMaps[shadowMapIndex]);
}

void RenderingEngine::applyFilter(const Shader& filter, const Texture& source, const Texture* dest)
{
	assert(&source != dest);
	if (dest == 0)
	{
		m_window->bindRenderTarget();
	}
	else
	{
		dest->bindAsRenderTarget();
	}

	setTexture("filterTexture", source);

	m_altCamera.setProjection(glm::mat4(1.0f));
	m_altCamera.getTransform()->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	m_altCamera.getTransform()->setRotation(glm::angleAxis(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)));

	//	const Camera* temp = m_mainCamera;
	//	m_mainCamera = m_altCamera;

	glClear(GL_DEPTH_BUFFER_BIT);
	filter.bind();
	filter.updateUniforms(m_planeTransform, m_planeMaterial, *this, m_altCamera);
	m_plane.render();

	//	m_mainCamera = temp;
	setTexture("filterTexture", 0);
}

void RenderingEngine::render(const GameObject& object)
{
	getTexture("displayTexture").bindAsRenderTarget();
	//m_window->BindAsRenderTarget();
	//m_tempTarget->BindAsRenderTarget();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	object.renderAll(m_defaultShader, *this, *m_mainCamera);

	for (unsigned int i = 0; i < m_lights.size(); i++)
	{
		m_activeLight = m_lights[i];
		ShadowInfo shadowInfo = m_activeLight->getShadowInfo();

		int shadowMapIndex = 0;
		if (shadowInfo.getShadowMapSizeAsPowerOf2() != 0)
			shadowMapIndex = shadowInfo.getShadowMapSizeAsPowerOf2() - 1;

		assert(shadowMapIndex >= 0 && shadowMapIndex < NUM_SHADOW_MAPS);

		setTexture("shadowMap", m_shadowMaps[shadowMapIndex]);
		m_shadowMaps[shadowMapIndex].bindAsRenderTarget();
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

			//			const Camera* temp = m_mainCamera;
			//			m_mainCamera = m_altCamera;

			if (flipFaces)
			{
				glCullFace(GL_FRONT);
			}

			object.renderAll(m_shadowMapShader, *this, m_altCamera);

			if (flipFaces)
			{
				glCullFace(GL_BACK);
			}

			//			m_mainCamera = temp;

			float shadowSoftness = shadowInfo.getShadowSoftness();
			if (shadowSoftness != 0)
			{
				blurShadowMap(shadowMapIndex, shadowSoftness);
			}
		}
		else
		{
			m_lightMatrix = Utility::initScale(glm::vec3(0.0f, 0.0f, 0.0f));
			setFloat("shadowVarianceMin", 0.00002f);
			setFloat("shadowLightBleedingReduction", 0.0f);
		}

		getTexture("displayTexture").bindAsRenderTarget();
		//m_window->BindAsRenderTarget();

		//		glEnable(GL_SCISSOR_TEST);
		//		TODO: Make use of scissor test to limit light area
		//		glScissor(0, 0, 100, 100);

		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glDepthMask(GL_FALSE);
		glDepthFunc(GL_EQUAL);

		object.renderAll(m_activeLight->getShader(), *this, *m_mainCamera);

		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LESS);
		glDisable(GL_BLEND);

		//		glDisable(GL_SCISSOR_TEST);
	}

	if (m_skybox != nullptr)
	{
		glDepthFunc(GL_LEQUAL);

		m_skybox->render(*this, *m_mainCamera);

		glDepthFunc(GL_LESS);
	}

	setVec3("inverseFilterTextureSize", glm::vec3(1.0f / getTexture("displayTexture").getWidth(), 1.0f / getTexture("displayTexture").getHeight(), 0.0f));

	applyFilter(m_fxaaFilter, getTexture("displayTexture"), 0);
}