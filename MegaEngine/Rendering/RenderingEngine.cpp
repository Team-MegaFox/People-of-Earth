 //***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Jesse Derochie
// Last Modified On : 03-31-2016
// ***********************************************************************
// <copyright file="RenderingEngine.cpp" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#include "RenderingEngine.h"
#include "Shader.h"
#include "Mesh.h"
#include "ParticleSystem.h"
#include "..\Core\GameObject.h"
#include <cassert>
#include <glew\glew.h>

/// <summary>
/// Should construct a Matrix like this:
///     x   y   z   w
/// x [ 0.5 0.0 0.0 0.5 ]
/// y [ 0.0 0.5 0.0 0.5 ]
/// z [ 0.0 0.0 0.5 0.5 ]
/// w [ 0.0 0.0 0.0 1.0 ]
/// 
/// Note the 'w' column in this representation should be
/// the translation column!
/// 
/// This matrix will convert 3D coordinates from the range (-1, 1) to the range (0, 1).
/// </summary>
const PxMat44 RenderingEngine::BIAS_MATRIX = Utility::initScale(PxVec3(0.5, 0.5, 0.5)) * Utility::initTranslation(PxVec3(1.0, 1.0, 1.0));

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
m_particleShader("particle"),
m_altCameraTransform(PxVec3(0, 0, 0), PxQuat(ToRadians(180.0f), PxVec3(0, 1, 0))),
m_altCamera(PxMat44(PxIdentity), &m_altCameraTransform)
{
	setSamplerSlot("diffuse", 0);
	setSamplerSlot("normalMap", 1);
	setSamplerSlot("dispMap", 2);
	setSamplerSlot("shadowMap", 3);
	setSamplerSlot("blurTex", 1);

	setSamplerSlot("filterTexture", 0);

	setVec3("ambient", PxVec3(0.5f, 0.5f, 0.5f));

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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_MULTISAMPLE);

	m_planeTransform.setScale(PxVec3(1.0f));
	m_planeTransform.rotate(PxQuat(ToRadians(90.0f), PxVec3(1, 0, 0)));
	m_planeTransform.rotate(PxQuat(ToRadians(180.0f), PxVec3(0, 0, 1)));

	for (int i = 0; i < NUM_SHADOW_MAPS; i++)
	{
		int shadowMapSize = 1 << (i + 1);
		m_shadowMaps[i] = Texture(shadowMapSize, shadowMapSize, 0, GL_TEXTURE_2D, GL_LINEAR, GL_RG32F, GL_RGBA, true, GL_COLOR_ATTACHMENT0);
		m_shadowMapTempTargets[i] = Texture(shadowMapSize, shadowMapSize, 0, GL_TEXTURE_2D, GL_LINEAR, GL_RG32F, GL_RGBA, true, GL_COLOR_ATTACHMENT0);
	}

	m_lightMatrix = Utility::initScale(PxVec3(0, 0, 0));
}

void RenderingEngine::blurShadowMap(int shadowMapIndex, float blurAmount)
{
	setVec3("blurScale", PxVec3(blurAmount / (m_shadowMaps[shadowMapIndex].getWidth()), 0.0f, 0.0f));
	applyFilter(m_gausBlurFilter, m_shadowMaps[shadowMapIndex], &m_shadowMapTempTargets[shadowMapIndex]);

	setVec3("blurScale", PxVec3(0.0f, blurAmount / (m_shadowMaps[shadowMapIndex].getHeight()), 0.0f));
	applyFilter(m_gausBlurFilter, m_shadowMapTempTargets[shadowMapIndex], &m_shadowMaps[shadowMapIndex]);
}

void RenderingEngine::applyFilter(const Shader& filter, const Texture& source, const Texture* dest)
{
	assert(&source != dest);
	if (dest == 0)
	{
		m_window->bindAsRenderTarget();
	}
	else
	{
		dest->bindAsRenderTarget();
	}

	setTexture("filterTexture", source);

	m_altCamera.setProjection(PxMat44(PxIdentity));
	m_altCamera.getTransform()->setPosition(PxVec3(0, 0, 0));
	m_altCamera.getTransform()->setRotation(PxQuat(ToRadians(180.0f), PxVec3(0, 1, 0)));

	glClear(GL_DEPTH_BUFFER_BIT);
	filter.bind();
	filter.updateUniforms(m_planeTransform, m_planeMaterial, *this, m_altCamera);
	m_plane.render();

	setTexture("filterTexture", 0);
}

void RenderingEngine::render(const GameObject& object)
{
	getTexture("displayTexture").bindAsRenderTarget();
	//m_window->bindAsRenderTarget();
	//m_tempTarget->bindAsRenderTarget();

	m_window->clearScreen();
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
			m_altCamera.getTransform()->setPosition(shadowCameraTransform.getPosition());
			m_altCamera.getTransform()->setRotation(shadowCameraTransform.GetRotation());

			m_lightMatrix = BIAS_MATRIX * m_altCamera.getViewProjection();

			setFloat("shadowVarianceMin", shadowInfo.getMinVariance());
			setFloat("shadowLightBleedingReduction", shadowInfo.getLightBleedReductionAmount());
			bool flipFaces = shadowInfo.getFlipFaces();

			if (flipFaces)
			{
				glCullFace(GL_FRONT);
			}

			object.renderAll(m_shadowMapShader, *this, m_altCamera);

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
			m_lightMatrix = Utility::initScale(PxVec3(0, 0, 0));
			setFloat("shadowVarianceMin", 0.00002f);
			setFloat("shadowLightBleedingReduction", 0.0f);
		}

		getTexture("displayTexture").bindAsRenderTarget();
		//m_window->bindAsRenderTarget();

		//glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glDepthMask(GL_FALSE);
		glDepthFunc(GL_EQUAL);

		object.renderAll(m_activeLight->getShader(), *this, *m_mainCamera);

		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LESS);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	if (m_skybox != nullptr)
	{
		glDepthFunc(GL_LEQUAL);

		m_skybox->render(*this, *m_mainCamera);

		glDepthFunc(GL_LESS);
	}

	//if (m_bloomObjects.size() >= 1)
	//{
	//	for (size_t i = 0; i < m_bloomObjects.size(); i++)
	//	{
	//		m_bloomObjects[i]->render(*this, *m_mainCamera);
	//	}
	//}

	for (size_t i = 0; i < m_particleSystems.size(); i++)
	{
		if (m_particleSystems[i] != nullptr)
		{
			m_particleSystems[i]->renderParticles(m_particleShader, *this, *m_mainCamera);
		}
	}

	if (m_bloomObject != nullptr)
	{
		glDepthFunc(GL_LEQUAL);

		m_bloomObject->render(*this, *m_mainCamera);

		glDepthFunc(GL_LESS);
	}

	setVec3("inverseFilterTextureSize", PxVec3(1.0f / getTexture("displayTexture").getWidth(), 1.0f / getTexture("displayTexture").getHeight(), 0.0f));

	applyFilter(m_fxaaFilter, getTexture("displayTexture"), 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
	glActiveTexture(GL_TEXTURE0);
}