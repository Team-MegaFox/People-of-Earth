// ***********************************************************************
// Author           : Pavan Jakhu
// Created          : 02-04-2016
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 02-05-2016
// ***********************************************************************
// <copyright file="Skybox.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once
#include <string>
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "..\Core\Transform.h"
#include "..\Components\GameComponents.h"

/*
Order of skybox textures:
right, left, top, bottom, back, front
*/

/// <summary>
/// Creates a skybox in the current scene. There should only be one.
/// It is attached to the RenderingEngine's Skybox and calls render once everything
/// else is done rendering in the scene (except the GUI).
/// The order to input the skybox textures are right, left, top, bottom, back and front.
/// </summary>
class Skybox
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Skybox"/> class.
	/// </summary>
	/// <param name="fileName">Name of the skybox (without the 
	/// numerical number at the end) file.</param>
	Skybox(const std::string& fileName);
	/// <summary>
	/// Finalizes an instance of the <see cref="Skybox"/> class.
	/// </summary>
	~Skybox();

	/// <summary>
	/// Renders the skybox by binding the shader, updating the uniforms and 
	/// rendering the mesh.
	/// </summary>
	/// <param name="renderingEngine">The rendering engine.</param>
	/// <param name="camera">The camera to render the skybox to.</param>
	void render(const RenderingEngine& renderingEngine, const Camera3D & camera) const;

private:
	/// <summary>
	/// The skybox shader.
	/// </summary>
	Shader m_cubeShader;

	/// <summary>
	/// The skybox texture.
	/// </summary>
	Texture m_cubeTexture;

	/// <summary>
	/// The skybox's cube mesh.
	/// </summary>
	Mesh* m_cubeMesh;

	/// <summary>
	/// The cube's transform. Which is just the default Transform.
	/// </summary>
	Transform m_cubeTransform;

};

/// <summary>
/// A <see cref="GameComponent"/> that adds a skybox to the Rendering Engine.
/// </summary>
/// <seealso cref="GameComponent" />
class SkyboxRenderer : public GameComponent
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="SkyboxRenderer"/> class.
	/// </summary>
	/// <param name="fileName">>Name of the skybox (without the 
	/// numerical number at the end) file.</param>
	SkyboxRenderer(const std::string& fileName) :
		m_skybox(fileName) { }
	/// <summary>
	/// Finalizes an instance of the <see cref="SkyboxRenderer"/> class.
	/// </summary>
	~SkyboxRenderer();

	/// <summary>
	/// Adds the skybox to the Rendering Engine.
	/// </summary>
	/// <param name="engine">A pointer to the Core Engine.</param>
	virtual void addToEngine(CoreEngine* engine) const;
	
	/// <summary>
	/// Gets a reference to the skybox object.
	/// </summary>
	/// <returns>A reference to the skybox object.</returns>
	Skybox* getSkybox() { return &m_skybox; }

private:
	/// <summary>
	/// The skybox.
	/// </summary>
	Skybox m_skybox;
};

