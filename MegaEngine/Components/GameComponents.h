// ***********************************************************************
// Author           : Pavan Jakhu, Jesse Derochie and Christopher Maeda
// Created          : 09-15-2015
//
// Last Modified By : Christopher Maeda
// Last Modified On : 02-17-2016
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
#include "..\Core\CoreEngine.h"
#include "..\Core\SceneManager.h"
#include "..\Core\Scene.h"
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
	/// <summary>
	/// Gets the core engine.
	/// </summary>
	/// <returns></returns>
	CoreEngine * getCoreEngine() { return m_parent->getCoreEngine(); }
	/// <summary>
	/// Gets the parent.
	/// </summary>
	/// <returns></returns>
	GameObject * getParent() { return m_parent; }

	/// <summary>
	/// Gets the game object from the top most scene by name.
	/// </summary>
	/// <param name="gameObjectName">Name of the game object to get.</param>
	/// <returns></returns>
	GameObject * getGameObjectByName(const std::string & gameObjectName) { return getCoreEngine()->getSceneManager()->getGameObjectByName(gameObjectName); }

	/// <summary>
	/// Removes the game object by finding it in the top most scene by name.
	/// </summary>
	/// <param name="gameObjectName">Name of the game object to remove.</param>
	/// <returns></returns>
	bool removeGameObjectByName(const std::string & gameObjectName) { return getCoreEngine()->getSceneManager()->removeGameObjectByName(gameObjectName); }

	/// <summary>
	/// Removes the game object by finding it in the top most scene.
	/// </summary>
	/// <param name="gameObjectName">The game object to remove.</param>
	/// <returns></returns>
	bool destroy(GameObject* gameObject) {	return removeGameObjectByName(gameObject->getName()); }

	//TODO:: Comment
	void instantiate(GameObject* gameObject)
	{
		getCoreEngine()->getSceneManager()->peek()->addToRoot(gameObject);
	}

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