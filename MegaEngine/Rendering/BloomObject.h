// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 03-31-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 03-31-2016
// ***********************************************************************
// <copyright file="BloomObject.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************

#pragma once
#include <string>
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "..\Components\MeshRenderer.h"
#include "..\Core\Transform.h"
#include "..\Components\GameComponents.h"

class BloomObject
{
public:
	BloomObject(const Mesh & mesh, const Texture & diffuse);
	~BloomObject();

	/// <summary>
	/// Renders the bloomObject by binding the shader, updating the uniforms and 
	/// rendering the mesh.
	/// </summary>
	/// <param name="renderingEngine">The rendering engine.</param>
	/// <param name="camera">The camera to render the bloomObject to.</param>
	void render(const RenderingEngine& renderingEngine, const Camera3D & camera) const;

private:
	/// <summary>
	/// The bloomObject's shader.
	/// </summary>
	Shader m_objectShader;

	/// <summary>
	/// The bloomObject's texture.
	/// </summary>
	Texture m_objectTexture;

	/// <summary>
	/// The bloomObject's cube mesh.
	/// </summary>
	const Mesh* m_objectMesh;

	/// <summary>
	/// The bloomObject's transform. Which is just the default Transform.
	/// </summary>
	Transform m_objectTransform;
};

/// <summary>
/// A <see cref="GameComponent"/> that adds a bloomObject to the Rendering Engine.
/// </summary>
/// <seealso cref="GameComponent" />
class BloomObjectRenderer : public GameComponent
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="BloomObjectRenderer"/> class.
	/// </summary>
	BloomObjectRenderer(const Mesh mesh, const Texture & diffuse) :
		m_bloomObject(mesh, diffuse) { }
	/// <summary>
	/// Finalizes an instance of the <see cref="BloomObjectRenderer"/> class.
	/// </summary>
	~BloomObjectRenderer();

	/// <summary>
	/// Adds the BloomObject to the Rendering Engine.
	/// </summary>
	/// <param name="engine">A pointer to the Core Engine.</param>
	virtual void addToEngine(CoreEngine* engine) const;

	/// <summary>
	/// Gets a reference to the BloomObject object.
	/// </summary>
	/// <returns>A reference to the BloomObject object.</returns>
	BloomObject* getBloomObject() { return &m_bloomObject; }

private:
	/// <summary>
	/// The BloomObject.
	/// </summary>
	BloomObject m_bloomObject;
};
