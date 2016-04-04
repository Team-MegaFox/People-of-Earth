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

BloomObject::BloomObject(const Mesh & mesh, const Texture & diffuse) :
m_objectShader("bloomShader"),
m_objectTexture(diffuse),
m_objectMesh(&mesh)
{
	float size = 1.0f;

	IndexedModel cube;
	{
		cube.addVertex(-size, size, -size);
		cube.addVertex(-size, -size, -size);
		cube.addVertex(size, -size, -size);
		cube.addFace(0, 1, 2);
		cube.addVertex(size, -size, -size);
		cube.addVertex(size, size, -size);
		cube.addVertex(-size, size, -size);
		cube.addFace(3, 4, 5);

		cube.addVertex(-size, -size, size);
		cube.addVertex(-size, -size, -size);
		cube.addVertex(-size, size, -size);
		cube.addFace(6, 7, 8);
		cube.addVertex(-size, size, -size);
		cube.addVertex(-size, size, size);
		cube.addVertex(-size, -size, size);
		cube.addFace(9, 10, 11);

		cube.addVertex(size, -size, -size);
		cube.addVertex(size, -size, size);
		cube.addVertex(size, size, size);
		cube.addFace(12, 13, 14);
		cube.addVertex(size, size, size);
		cube.addVertex(size, size, -size);
		cube.addVertex(size, -size, -size);
		cube.addFace(15, 16, 17);

		cube.addVertex(-size, -size, size);
		cube.addVertex(-size, size, size);
		cube.addVertex(size, size, size);
		cube.addFace(18, 19, 20);
		cube.addVertex(size, size, size);
		cube.addVertex(size, -size, size);
		cube.addVertex(-size, -size, size);
		cube.addFace(21, 22, 23);

		cube.addVertex(-size, size, -size);
		cube.addVertex(size, size, -size);
		cube.addVertex(size, size, size);
		cube.addFace(24, 25, 26);
		cube.addVertex(size, size, size);
		cube.addVertex(-size, size, size);
		cube.addVertex(-size, size, -size);
		cube.addFace(27, 28, 29);

		cube.addVertex(-size, -size, -size);
		cube.addVertex(-size, -size, size);
		cube.addVertex(size, -size, -size);
		cube.addFace(30, 31, 32);
		cube.addVertex(size, -size, -size);
		cube.addVertex(-size, -size, size);
		cube.addVertex(size, -size, size);
		cube.addFace(33, 34, 35);
	}
	m_objectMesh = new Mesh("bob_mesh", cube.finalize());
}

BloomObject::~BloomObject()
{
	delete m_objectMesh;
}

void BloomObject::render(const RenderingEngine& renderingEngine, const Camera3D & camera) const
{
	m_objectShader.bind();
	m_objectShader.updateUniforms(m_objectTransform, Material("m_objectTexture", 0.5f, 4, Texture("Planets/sun.jpg")), renderingEngine, camera);
	m_objectMesh->render();
}

BloomObjectRenderer::~BloomObjectRenderer()
{
	getCoreEngine()->getRenderingEngine()->removeBloomObject();
}

void BloomObjectRenderer::addToEngine(CoreEngine* engine) const
{
	engine->getRenderingEngine()->setBloomObject(m_bloomObject);
}

