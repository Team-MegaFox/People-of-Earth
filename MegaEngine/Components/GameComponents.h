// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 01-24-2016
// ***********************************************************************
// <copyright file="GameComponents.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once

#include "..\Core\Transform.h"
#include "..\Core\GameObject.h"
#include "..\Core\InputManager.h"
class RenderingEngine;
class Shader;

/// <summary>
/// A Game Component class that attaches to GameObjects to have custom funcationality.
/// </summary>
/// <example>
/// <code>
/// class MeshRenderer : public GameComponet { ... }
/// </code>
/// </example>
class GameComponent
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="GameComponent"/> class.
	/// </summary>
	GameComponent() :
		m_parent(0) {}
	/// <summary>
	/// Finalizes an instance of the <see cref="GameComponent"/> class.
	/// </summary>
	virtual ~GameComponent() {}

	/// <summary>
	/// Virtual function for custom input processing.
	/// </summary>
	/// <param name="input">The input manager.</param>
	/// <param name="delta">The frame time delta.</param>
	virtual void processInput(const InputManager& input, float delta) {}
	/// <summary>
	/// Virtual function for custom update functionality.
	/// </summary>
	/// <param name="delta">The frame time delta.</param>
	virtual void update(float delta) {}
	/// <summary>
	/// Virtual function for custom rendering functionality.
	/// </summary>
	/// <param name="shader">The shader.</param>
	/// <param name="renderingEngine">The rendering engine.</param>
	/// <param name="camera">The camera.</param>
	virtual void render(const Shader& shader, const RenderingEngine& renderingEngine, const Camera3D & camera) const {}

	/// <summary>
	/// Adds to Core Engine.
	/// </summary>
	/// <param name="engine">The Core Engine.</param>
	virtual void addToEngine(CoreEngine* engine) const { }

	/// <summary>
	/// Gets the transform from the attached GameObject.
	/// </summary>
	/// <returns>A pointer to the attached GameObject's Transform object.</returns>
	inline Transform * getTransform()             { return m_parent->getTransform(); }
	/// <summary>
	/// Gets the transform from the attached GameObject.
	/// </summary>
	/// <returns>A const refernce to the attached GameObject's Transform objet.</returns>
	inline const Transform & getTransform() const { return *m_parent->getTransform(); }
	
	/// <summary>
	/// Sets the parent GameObject..
	/// </summary>
	/// <param name="parent">The GameObject to be attached to.</param>
	virtual void setParent(GameObject* parent) { m_parent = parent; }

protected:
	CoreEngine* getCoreEngine() { return m_parent->getCoreEngine(); }

private:
	/// <summary>
	/// The parent GameObject.
	/// </summary>
	GameObject* m_parent;

	/// <summary>
	/// Initializes a new instance of the <see cref="GameComponent"/> class.
	/// </summary>
	/// <param name="other">The other.</param>
	GameComponent(const GameComponent& other) {}
	/// <summary>
	/// Operator=s the specified other.
	/// </summary>
	/// <param name="other">The other.</param>
	void operator=(const GameComponent& other) {}
};