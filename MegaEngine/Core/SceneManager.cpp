// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 01-24-2016
// ***********************************************************************
// <copyright file="SceneManager.cpp" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "CoreEngine.h"

SceneManager::SceneManager() : m_currentScene("")
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::addScene(Scene* scene)
{
	m_scenes.insert(std::make_pair(scene->getName(), scene));
}

bool SceneManager::removeScene(Scene* scene)
{
	return removeScene(scene->getName());
}

bool SceneManager::removeScene(std::string name)
{
	bool removed = false;
	auto it = m_scenes.find(name);

	if (it != m_scenes.end())
	{
		m_scenes.erase(it);
		removed = true;
	}

	return removed;
}

void SceneManager::switchScene(Scene* scene)
{
	switchScene(scene->getName());
}

void SceneManager::switchScene(std::string name)
{
	auto it = m_scenes.find(name);

	if (it != m_scenes.end())
	{
		m_currentScene = name;
		//m_scenes[m_currentScene]->init(*m_coreEngine->getViewport());
	}
}

void SceneManager::update(float delta)
{
	m_scenes[m_currentScene]->update(delta);
}

void SceneManager::render(RenderingEngine* renderingEngine)
{
	m_scenes[m_currentScene]->render(renderingEngine);
}

void SceneManager::processInput(const InputManager& input, float delta)
{
	m_scenes[m_currentScene]->processInput(input, delta);
}

void SceneManager::setEngine(CoreEngine* engine)
{
	m_coreEngine = engine;

	for (auto it = m_scenes.begin(); it != m_scenes.end(); it++)
	{
		it->second->setEngine(engine);
	}
}
