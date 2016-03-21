// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Jesse Derochie
// Last Modified On : 02-08-2016
// ***********************************************************************
// <copyright file="SkyBox.cpp" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************

#include "Skybox.h"
#include "..\Core\CoreEngine.h"
#include "RenderingEngine.h"

Skybox::Skybox(const std::string& fileName) :
m_cubeShader("skybox"), 
m_cubeTexture(Utility::split(fileName, '.')[0].substr(0, Utility::split(fileName, '.')[0].length()) + "." + Utility::split(fileName, '.')[1],
GL_TEXTURE_CUBE_MAP, GL_LINEAR, GL_RGBA, GL_RGBA, true)
{
	float SIZE = 3.0f;
	// Manually creating the cube since when I was trying to use .obj's the texture
	// coordinates would have a weird effect on the bottom side of the cube.
	// You can try doing it though.
	IndexedModel cube;
	{
		cube.addVertex(-SIZE, SIZE, -SIZE);
		cube.addVertex(-SIZE, -SIZE, -SIZE);
		cube.addVertex(SIZE, -SIZE, -SIZE);
		cube.addFace(0, 1, 2);
		cube.addVertex(SIZE, -SIZE, -SIZE);
		cube.addVertex(SIZE, SIZE, -SIZE);
		cube.addVertex(-SIZE, SIZE, -SIZE);
		cube.addFace(3, 4, 5);

		cube.addVertex(-SIZE, -SIZE, SIZE);
		cube.addVertex(-SIZE, -SIZE, -SIZE);
		cube.addVertex(-SIZE, SIZE, -SIZE);
		cube.addFace(6, 7, 8);
		cube.addVertex(-SIZE, SIZE, -SIZE);
		cube.addVertex(-SIZE, SIZE, SIZE);
		cube.addVertex(-SIZE, -SIZE, SIZE);
		cube.addFace(9, 10, 11);

		cube.addVertex(SIZE, -SIZE, -SIZE);
		cube.addVertex(SIZE, -SIZE, SIZE);
		cube.addVertex(SIZE, SIZE, SIZE);
		cube.addFace(12, 13, 14);
		cube.addVertex(SIZE, SIZE, SIZE);
		cube.addVertex(SIZE, SIZE, -SIZE);
		cube.addVertex(SIZE, -SIZE, -SIZE);
		cube.addFace(15, 16, 17);
		
		cube.addVertex(-SIZE, -SIZE, SIZE);
		cube.addVertex(-SIZE, SIZE, SIZE);
		cube.addVertex(SIZE, SIZE, SIZE);
		cube.addFace(18, 19, 20);
		cube.addVertex(SIZE, SIZE, SIZE);
		cube.addVertex(SIZE, -SIZE, SIZE);
		cube.addVertex(-SIZE, -SIZE, SIZE);
		cube.addFace(21, 22, 23);

		cube.addVertex(-SIZE, SIZE, -SIZE);
		cube.addVertex(SIZE, SIZE, -SIZE);
		cube.addVertex(SIZE, SIZE, SIZE);
		cube.addFace(24, 25, 26);
		cube.addVertex(SIZE, SIZE, SIZE);
		cube.addVertex(-SIZE, SIZE, SIZE);
		cube.addVertex(-SIZE, SIZE, -SIZE);
		cube.addFace(27, 28, 29);

		cube.addVertex(-SIZE, -SIZE, -SIZE);
		cube.addVertex(-SIZE, -SIZE, SIZE);
		cube.addVertex(SIZE, -SIZE, -SIZE);
		cube.addFace(30, 31, 32);
		cube.addVertex(SIZE, -SIZE, -SIZE);
		cube.addVertex(-SIZE, -SIZE, SIZE);
		cube.addVertex(SIZE, -SIZE, SIZE);
		cube.addFace(33, 34, 35);
	}
	m_cubeMesh = new Mesh("SkyboxCube", cube.finalize());
}	

Skybox::~Skybox()
{
	delete m_cubeMesh;
}

void Skybox::render(const RenderingEngine& renderingEngine, const Camera3D & camera) const
{
	m_cubeShader.bind();
	m_cubeShader.updateUniforms(m_cubeTransform, Material("skyboxMaterial", m_cubeTexture), renderingEngine, camera);
	m_cubeMesh->render();
}

SkyboxRenderer::~SkyboxRenderer()
{
	getCoreEngine()->getRenderingEngine()->removeSkybox();
}

void SkyboxRenderer::addToEngine(CoreEngine* engine) const
{
	engine->getRenderingEngine()->setSkybox(m_skybox);
}
