// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Deroiche
// Created          : 09-15-2015
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 01-24-2016
// ***********************************************************************
// <copyright file="SceneManager.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once
#include <string>
#include <unordered_map>

class Scene;
class CoreEngine;
class RenderingEngine;
class InputManager;

/// <summary>
/// Holds a map of scenes to manage.
/// </summary>
class SceneManager
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="SceneManager"/> class.
	/// </summary>
	SceneManager();
	/// <summary>
	/// Finalizes an instance of the <see cref="SceneManager"/> class.
	/// </summary>
	~SceneManager();

	/// <summary>
	/// Adds the scene to the manager.
	/// </summary>
	/// <param name="scene">The scene.</param>
	void addScene(Scene* scene);
	/// <summary>
	/// Removes the scene from the manager.
	/// </summary>
	/// <param name="scene">The scene.</param>
	/// <returns>If the scene was removed successfully.</returns>
	bool removeScene(Scene* scene);
	/// <summary>
	/// Removes the scene from the manager by name.
	/// </summary>
	/// <param name="name">The name.</param>
	/// <returns>If the scene was removed successfully.</returns>
	bool removeScene(std::string name);
	/// <summary>
	/// Switches the scene.
	/// </summary>
	/// <param name="scene">The scene.</param>
	void switchScene(Scene* scene);
	/// <summary>
	/// Switches the scene by name.
	/// </summary>
	/// <param name="name">The name.</param>
	void switchScene(std::string name);

	/// <summary>
	/// Updates the current scene.
	/// </summary>
	/// <param name="delta">The frame time delta.</param>
	void update(float delta);
	/// <summary>
	/// Renders the the current scene.
	/// </summary>
	/// <param name="renderingEngine">The rendering engine.</param>
	void render(RenderingEngine* renderingEngine);
	/// <summary>
	/// Processes the input for the current scene.
	/// </summary>
	/// <param name="input">The input.</param>
	/// <param name="delta">The frame time delta.</param>
	void processInput(const InputManager& input, float delta);

	/// <summary>
	/// Gets the current scene.
	/// </summary>
	/// <returns>A pointer to the current scene.</returns>
	Scene* getCurrentScene() { return m_scenes[m_currentScene]; }
	/// <summary>
	/// Sets the Core Engine for all scenes.
	/// </summary>
	/// <param name="engine">The engine.</param>
	void setEngine(CoreEngine* engine);

private:
	/// <summary>
	/// The current scene.
	/// </summary>
	std::string m_currentScene;
	/// <summary>
	/// The map of scenes.
	/// </summary>
	std::unordered_map<std::string, Scene*> m_scenes;

	/// <summary>
	/// A pointer to the Core Engine.
	/// </summary>
	CoreEngine* m_coreEngine;

};

