// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
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
#include <vector>

class Scene;
class Viewport;
class RenderingEngine;
class InputManager;
class CoreEngine;
class GameObject;

/// <summary>
/// Enum used to determine what scene it is.
/// </summary>
enum class Modality
{
	Exclusive,
	Popup
};

class SceneManager
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="SceneManager"/> class.
	/// </summary>
	/// <param name="viewport">The viewport.</param>
	SceneManager(Viewport* viewport);
	/// <summary>
	/// Finalizes an instance of the <see cref="SceneManager"/> class.
	/// </summary>
	~SceneManager();

	/// <summary>
	/// Returns the top most scene from the scene manager
	/// </summary>
	/// <returns></returns>
	Scene* peek();

	/// <summary>
	/// Pushes the specified scene onto the scene stack.
	/// </summary>
	/// <param name="scene">The scene.</param>
	/// <param name="modality">The modality.</param>
	void push(Scene* scene, Modality modality = Modality::Exclusive);

	/// <summary>
	/// Pops the top most scene off the scene stack.
	/// </summary>
	void pop();

	/// <summary>
	/// Removes the top most scene and replaces it with the a new scene
	/// </summary>
	/// <param name="scene">The scene.</param>
	/// <param name="modality">The modality.</param>
	/// <returns></returns>
	Scene* switchScene(Scene* scene, Modality modality = Modality::Exclusive);

	/// <summary>
	/// Updates the scene stack up to the top most exclusive scene.
	/// </summary>
	/// <param name="delta">The delta.</param>
	void update(float delta);

	/// <summary>
	/// Renders the scene stack up to the top most exclusive scene.
	/// </summary>
	/// <param name="renderingEngine">The rendering engine.</param>
	void render(RenderingEngine* renderingEngine);

	/// <summary>
	/// Process the input for the top most scene
	/// </summary>
	/// <param name="input">The input.</param>
	/// <param name="delta">The delta.</param>
	void processInput(const InputManager& input, float delta);

	/// <summary>
	/// Sets the scene for all the scenes in the stack
	/// </summary>
	/// <param name="engine">The engine.</param>
	void setEngine(CoreEngine* engine);

	/// <summary>
	/// Removes a gameobject from the top most scene using its name to find it in the scene graph
	/// </summary>
	/// <param name="name">The name.</param>
	/// <returns>if the GameObject was removed.</returns>
	bool removeGameObjectByName(const std::string& name);

	/// <summary>
	/// Gets a gameobject from the top most scene using its name to find it in the scene graph
	/// </summary>
	/// <param name="name">The name.</param>
	/// <returns>A pointer to the GameObject.</returns>
	GameObject* getGameObjectByName(const std::string& name);

	/// <summary>
	/// Gets a gameobjects from the top most scene using its name to find it in the scene graph
	/// </summary>
	/// <param name="name">The name.</param>
	/// <returns>A vector of the GameObjects.</returns>
	std::vector<GameObject*> getGameObjectsByName(const std::string& name);

private:
	/// <summary>
	/// Updates the exclusive scene.
	/// </summary>
	void updateExclusiveScene();

	typedef std::pair<Scene*, Modality> SceneModalityPair;

	/// <summary>
	/// The scene stack
	/// </summary>
	std::vector<SceneModalityPair> m_activeList;

	/// <summary>
	/// The exclusive scene
	/// </summary>
	size_t m_exclusiveScene;

	/// <summary>
	/// The viewport
	/// </summary>
	Viewport* m_viewport;

	/// <summary>
	/// The core engine
	/// </summary>
	CoreEngine* m_coreEngine;

};
