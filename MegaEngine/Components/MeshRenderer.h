// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Christopher Maeda
// Last Modified On : 03-17-2016
// ***********************************************************************
// <copyright file="MeshRenderer.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once
#include "GameComponents.h"
#include "..\Rendering\Material.h"
#include "..\Rendering\Mesh.h"
#include "..\Rendering\Shader.h"
#include "..\Core\Utility.h"


/// <summary>
/// Renders a Mesh based on a file given or information manually entered.
/// </summary>
/// <seealso cref="GameComponent" />
class MeshRenderer : public GameComponent
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="MeshRenderer"/> class.
	/// </summary>
	/// <param name="mesh">The mesh.</param>
	/// <param name="material">The material.</param>
	MeshRenderer(const Mesh & mesh, const Material & material) :
		m_mesh(mesh), m_material(material) { }
	/// <summary>
	/// Renders the mesh with the applied material.
	/// </summary>
	/// <param name="shader">The shader program.</param>
	/// <param name="renderingEngine">The rendering engine.</param>
	/// <param name="camera">The main active camera.</param>
	virtual void render(const Shader & shader, const RenderingEngine & renderingEngine, const Camera3D & camera) const
	{
		EnclosureType inside = camera.isInside(getTransform().getTransformedPos(), m_mesh.getBoundingRadius());
		if (inside != EnclosureType::OUTSIDE)
		{
			shader.bind();
			shader.updateUniforms(getTransform(), m_material, renderingEngine, camera);
			m_mesh.render();
		}
	}

private:
	/// <summary>
	/// The mesh.
	/// </summary>
	Mesh m_mesh;
	/// <summary>
	/// The material.
	/// </summary>
	Material m_material;
};

