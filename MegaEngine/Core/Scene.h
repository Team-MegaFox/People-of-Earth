// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 01-24-2016
// ***********************************************************************
// <copyright file="Scene.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once
#include <string>
#include <vector>

#include "GameObject.h"
#include "..\Rendering\Viewport.h"
class CoreEngine;
class RenderingEngine;
class InputManager;


/// <summary>
/// Holds a root GameObject for the scene graph.
/// </summary>
class Scene
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Scene"/> class.
	/// </summary>
	/// <param name="name">The name.</param>
	Scene(const std::string& name);
	/// <summary>
	/// Finalizes an instance of the <see cref="Scene"/> class.
	/// </summary>
	virtual ~Scene();

	/// <summary>
	/// Initializes the scene with GameObjects.
	/// </summary>
	/// <param name="window">The window.</param>
	virtual void init(const Viewport& window) { }
	/// <summary>
	/// Updates the scene calling GameObject's update.
	/// </summary>
	/// <param name="delta">The frame time delta.</param>
	void update(float delta);
	/// <summary>
	/// Renders the scene calling GameObject's render.
	/// </summary>
	/// <param name="renderingEngine">The rendering engine.</param>
	void render(RenderingEngine* renderingEngine);
	/// <summary>
	/// Processes the input by calling GameObject's processInput.
	/// </summary>
	/// <param name="input">The input.</param>
	/// <param name="delta">The frame time delta.</param>
	void processInput(const InputManager& input, float delta);

	/// <summary>
	/// Adds a GameObject to the root GameObject.
	/// </summary>
	/// <param name="gameobject">The gameobject.</param>
	void addToRoot(GameObject* gameobject) { m_root.addChild(gameobject); }
	/// <summary>
	/// Removes the GameOject from the root.
	/// </summary>
	/// <param name="gameobject">The gameobject.</param>
	/// <returns>If the GameObject was removed.</returns>
	bool removeGameObject(GameObject* gameobject);
	/// <summary>
	/// Removes the GameObject by name.
	/// </summary>
	/// <param name="name">The name.</param>
	/// <returns>if the GameObject was removed.</returns>
	bool removeGameObjectByName(const std::string& name);

	/// <summary>
	/// Gets all game objects.
	/// </summary>
	/// <returns>All attached Objects to the root.</returns>
	std::vector<GameObject*> getAllGameObjects() { return m_root.getAllAttached(); }
	/// <summary>
	/// Gets the GameObject by name.
	/// </summary>
	/// <param name="name">The name.</param>
	/// <returns>A pointer to the GameObject.</returns>
	GameObject* getGameObjectByName(const std::string& name);
	/// <summary>
	/// Gets the name.
	/// </summary>
	/// <returns>The string value.</returns>
	std::string getName() { return m_name; }

	/// <summary>
	/// Sets the Core Engine.
	/// </summary>
	/// <param name="engine">The engine.</param>
	void setEngine(CoreEngine* engine) { m_root.setEngine(engine); }

private:
	/// <summary>
	/// The name of the Scene.
	/// </summary>
	std::string m_name;
	/// <summary>
	/// The root GameObject.
	/// </summary>
	GameObject m_root;
};

