// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 03-31-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 03-31-2016
// ***********************************************************************
// <copyright file="BloomObject.cpp" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************

#include "BloomObject.h"
#include "..\Core\CoreEngine.h"
#include "RenderingEngine.h"

BloomObject::BloomObject(const std::string& fileName, const Texture & diffuse) :
m_objectShader("bloomShader"),
m_objectTexture(diffuse)
{
	float SIZE = 3.0f;

	/*
	
	There is a bloom shader but it needs to be edited to work with our shader system.
	
	*/
	
	Mesh * mesh = new Mesh("sphere.obj");
	m_objectMesh = mesh;
}

BloomObject::~BloomObject()
{
	delete m_objectMesh;
}

void BloomObject::render(const RenderingEngine& renderingEngine, const Camera3D & camera) const
{
	m_objectShader.bind();
	m_objectShader.updateUniforms(m_objectTransform, Material("m_objectTexture", m_objectTexture), renderingEngine, camera);
	m_objectMesh->render();
}

BloomObjectRenderer::~BloomObjectRenderer()
{
	getCoreEngine()->getRenderingEngine()->removeSkybox();
}

void BloomObjectRenderer::addToEngine(CoreEngine* engine) const
{
	engine->getRenderingEngine()->setBloomObjects(m_bloomObject);
}

