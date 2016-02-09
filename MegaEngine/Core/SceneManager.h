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

enum class Modality
{
	Exclusive,
	Popup
};

class SceneManager
{
public:
	SceneManager(Viewport* viewport);
	~SceneManager();

	Scene* peek();

	void push(Scene* scene, Modality modality = Modality::Exclusive);

	void pop();

	Scene* switchScene(Scene* scene, Modality modality = Modality::Exclusive);

	void update(float delta);

	void render(RenderingEngine* renderingEngine);

	void processInput(const InputManager& input, float delta);

	void setEngine(CoreEngine* engine);

private:
	void updateExclusiveScene();

	typedef std::pair<Scene*, Modality> SceneModalityPair;

	std::vector<SceneModalityPair> m_activeList;

	size_t m_exclusiveScene;

	Viewport* m_viewport;

	CoreEngine* m_coreEngine;

};
