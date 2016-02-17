// ***********************************************************************
// Author           : Pavan Jakhu, Jesse Derochie and Christopher Maeda
// Created          : 09-15-2015
//
// Last Modified By : Christopher Maeda
// Last Modified On : 02-17-2016
// ***********************************************************************
// <copyright file="SceneManager.cpp" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************

#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"

#include <stdexcept>
#include <algorithm>

SceneManager::SceneManager(Viewport* viewport) :
m_viewport(viewport)
{
}

SceneManager::~SceneManager()
{
	while (!m_activeList.empty())
	{
		pop();
	}
}

Scene* SceneManager::peek()
{
	if (m_activeList.empty())
	{
		return nullptr;
	}
	else
	{
		return m_activeList.back().first;
	}
}

void SceneManager::push(Scene* scene, Modality modality /*= Modality::Exclusive*/)
{
	if (!m_activeList.empty())
	{
		auto go = m_activeList.back().first->getAllGameObjects();
		for (size_t i = 0; i < go.size(); i++)
		{
			go[i]->deactivate();
		}
	}

	m_activeList.push_back(std::make_pair(scene, modality));
	updateExclusiveScene();

	scene->init(*m_viewport);
	scene->setEngine(m_coreEngine);
}

void SceneManager::pop()
{
	if (m_activeList.empty()) 
	{
		throw std::runtime_error("Attempted to pop from an empty game state stack");
	}

	delete m_activeList.back().first;
	m_activeList.pop_back();

	if (!m_activeList.empty())
	{
		updateExclusiveScene();

		auto go = m_activeList.back().first->getAllGameObjects();
		for (size_t i = 0; i < go.size(); i++)
		{
			go[i]->activate();
		}
	}
}

Scene* SceneManager::switchScene(Scene* scene, Modality modality /*= Modality::Exclusive*/)
{
	Scene* currentScene = peek();

	if (currentScene)
	{
		pop();
	}

	push(scene, modality);

	return currentScene;
}

void SceneManager::update(float delta)
{
	for (size_t i = m_exclusiveScene; i < m_activeList.size(); i++)
	{
		m_activeList[i].first->update(delta);
	}
}

void SceneManager::render(RenderingEngine* renderingEngine)
{
	for (size_t i = m_exclusiveScene; i < m_activeList.size(); i++)
	{
		m_activeList[i].first->render(renderingEngine);
	}
}

void SceneManager::processInput(const InputManager& input, float delta)
{
	m_activeList.back().first->processInput(input, delta);
}

void SceneManager::setEngine(CoreEngine* engine)
{
	m_coreEngine = engine;

	for (size_t i = 0; i < m_activeList.size(); i++)
	{
		m_activeList[i].first->setEngine(engine);
	}
}

bool SceneManager::removeGameObjectByName(const std::string& name)
{
	//Gets all gameobject in the scene
	std::vector<GameObject*> attached = peek()->getRoot()->getAllAttached();
	
	//Loop through all the gameobject
	for (size_t i = 0; i < attached.size(); i++)
	{
		//if the gameobject name is the same as the name you are looking for then
		if (attached[i]->getName() == name)
		{
			//Delete gameobject from the parent
			attached[i]->getTransform()->getParent()->getAttachedGameObject()->removeChild(attached[i]);
			return true;
		}
	}
	return false;
}

GameObject* SceneManager::getGameObjectByName(const std::string& name)
{
	GameObject* result = nullptr;

	std::vector<GameObject*> attached = peek()->getRoot()->getAllAttached();
	for (size_t i = 0; i < attached.size(); i++)
	{
		if (attached[i]->getName() == name)
		{
			result = attached[i];
		}
	}

	return result;
}

void SceneManager::updateExclusiveScene()
{
	for (size_t i = m_activeList.size() - 1; i >= 0; i--)
	{
		if (m_activeList[i].second == Modality::Exclusive)
		{
			m_exclusiveScene = i;
			break;
		}
	}
}
