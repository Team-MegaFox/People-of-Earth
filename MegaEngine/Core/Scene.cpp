// ***********************************************************************
// Author           : Pavan Jakhu, Jesse Derochie and Christopher Maeda
// Created          : 09-15-2015
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 03-21-2016
// ***********************************************************************
// <copyright file="Scene.cpp" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************

#include "Scene.h"
#include "..\Rendering\RenderingEngine.h"

#include <algorithm>

Scene::Scene(const std::string& name) : 
m_name(name), m_root("Root")
{
}

Scene::~Scene()
{
}

void Scene::update(float delta)
{
	m_root.updateAll(delta);
}

void Scene::render(RenderingEngine* renderingEngine)
{
	renderingEngine->render(m_root);
}

void Scene::processInput(const InputManager& input, float delta)
{
	m_root.processAll(input, delta);
}

void Scene::addToRoot(GameObject* gameobject)
{
	auto it =  m_GONameCounter.find(gameobject->getName());
	Uint16 tempCounter = 0;

	//It exists
	if (it != m_GONameCounter.end())
	{
		it->second++;
		gameobject->setName(gameobject->getName() + std::to_string(it->second));
	}
	else
	{
		auto children = gameobject->getAllAttached();
		for (size_t i = 0; i < children.size(); i++)
		{
			m_GONameCounter.insert(std::make_pair(children[i]->getName(), 1));
			children[i]->setName(children[i]->getName() + std::to_string(1));
		}
	}

	m_root.addChild(gameobject);
}

bool Scene::removeGameObject(GameObject* gameobject)
{
	bool removed = false;

	std::vector<GameObject*> attached = m_root.getAllAttached();
	for (size_t i = 0; i < attached.size() && !removed; i++)
	{
		if (attached[i] == gameobject)
		{
			GameObject* parent = gameobject->getTransform()->getParent()->getAttachedGameObject();
			for (size_t j = 0; j < gameobject->getAllChildren().size(); j++)
			{
				gameobject->getAllChildren()[j]->getTransform()->setParent(parent->getTransform());
			}
			gameobject->setEngine(nullptr);
			attached.erase(std::remove(attached.begin(), attached.end(), gameobject), attached.end());

			removed = true;
		}
	}

	return removed;
}

Uint16 Scene::getNameCounter(const std::string& name)
{
	auto it = m_GONameCounter.find(name);
	if (it != m_GONameCounter.end())
	{
		return it->second;
	}
	return 0;
}

void Scene::instantiate(GameObject* gameObject)
{
	addToRoot(gameObject);
	auto gameComponents = gameObject->getAllGameComponents();
	for (size_t j = 0; j < gameComponents.size(); j++)
	{
		gameComponents[j]->onStart();
	}
}