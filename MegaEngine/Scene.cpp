#include "Scene.h"
#include <algorithm>


Scene::Scene(const std::string& name) : m_name(name)
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
	//Hello world
	//renderingEngine->render(m_root);
}

void Scene::processInput(const InputManager& input, float delta)
{
	m_root.processAll(input, delta);
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

bool Scene::removeGameObjectByName(const std::string& name)
{
	bool removed = false;

	std::vector<GameObject*> attached = m_root.getAllAttached();
	for (size_t i = 0; i < attached.size() && !removed; i++)
	{
		if (attached[i]->getName() == name)
		{
			GameObject* parent = attached[i]->getTransform()->getParent()->getAttachedGameObject();
			for (size_t j = 0; j < attached[i]->getAllChildren().size(); j++)
			{
				attached[i]->getAllChildren()[j]->getTransform()->setParent(parent->getTransform());
				attached[i]->getAllChildren()[j]->getTransform()->setAttachedGameObject(parent);
			}
			attached[i]->setEngine(nullptr);
			attached.erase(std::remove(attached.begin(), attached.end(), attached[i]), attached.end());

			removed = true;
		}
	}

	return removed;
}

GameObject* Scene::getGameObjectByName(const std::string& name)
{
	GameObject* result = nullptr;

	std::vector<GameObject*> attached = m_root.getAllAttached();
	for (size_t i = 0; i < attached.size(); i++)
	{
		if (attached[i]->getName() == name)
		{
			result = attached[i];
		}
	}

	return result;
}