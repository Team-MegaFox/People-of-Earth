#include "GameObject.h"
#include "GameComponents.h"
#include <algorithm>

void GameObject::updateAll(float delta)
{
	updateGameComponents(delta);
	updateGUIComponents(delta);

	for (size_t go = 0; go < m_children.size(); go++)
	{
		m_children[go]->updateAll(delta);
	}
}

void GameObject::renderAll(const Shader& shader, const GUIEngine& guiEngine, const RenderingEngine& renderingEngine, const Camera3D& camera)
{
	renderGameComponents(shader, renderingEngine, camera);
	renderGUIComponents(guiEngine, camera);

	for (size_t go = 0; go < m_children.size(); go++)
	{
		m_children[go]->renderAll(shader, guiEngine, renderingEngine, camera);
	}
}

void GameObject::processAll(const InputManager& input, float delta)
{
	processInputGameComponents(input, delta);

	for (size_t go = 0; go < m_children.size(); go++)
	{
		m_children[go]->processAll(input, delta);
	}
}

GameObject* GameObject::addChild(GameObject* child)
{
	m_children.push_back(child);
	child->getTransform()->setParent(&m_transform);
	child->setEngine(m_coreEngine);
	return this;
}

GameObject* GameObject::addGameComponent(GameComponent* component)
{
	m_gameComponents.push_back(component);
	component->setParent(this);
	return this;
}

GameObject* GameObject::addGUIComponent(GUIComponent* component)
{
	return this;
}

bool GameObject::removeChild(GameObject* child)
{
	bool removed = false;
	
	for (size_t go = 0; go < m_children.size(); go++)
	{
		if (m_children[go] == child)
		{
			child->setEngine(nullptr);
			child->getTransform()->setParent(nullptr);
			m_children.erase(std::remove(m_children.begin(), m_children.end(), m_children[go]), m_children.end());
			removed = true;
		}
	}

	return removed;
}

bool GameObject::removeGameComponent(GameComponent* component)
{
	bool removed = false;

	for (size_t gc = 0; gc < m_gameComponents.size(); gc++)
	{
		if (m_gameComponents[gc] == component)
		{
			component->setParent(nullptr);
			m_gameComponents.erase(std::remove(m_gameComponents.begin(), m_gameComponents.end(), m_gameComponents[gc]), m_gameComponents.end());
			removed = true;
		}
	}

	return removed;
}

bool GameObject::removeGUIComponent(GUIComponent* component)
{
	return false;
}

std::vector<GameObject*> GameObject::getAllAttached()
{
	std::vector<GameObject*> result;

	for (size_t i = 0; i < m_children.size(); i++)
	{
		std::vector<GameObject*> childObjects = m_children[i]->getAllAttached();
		result.insert(result.end(), childObjects.begin(), childObjects.end());
	}

	result.push_back(this);
	return result;
}

std::vector<GameObject*> GameObject::getAllChildren()
{
	return m_children;
}

void GameObject::setEngine(CoreEngine* engine)
{
	if (engine != m_coreEngine)
	{
		m_coreEngine = engine;

		for (size_t i = 0; i < m_gameComponents.size(); i++)
		{
			m_gameComponents[i]->addToEngine(engine);
		}

		for (size_t i = 0; i < m_children.size(); i++)
		{
			m_children[i]->setEngine(engine);
		}
	}
}

void GameObject::updateGameComponents(float delta)
{
	for (size_t gc = 0; gc < m_gameComponents.size(); gc++)
	{
		m_gameComponents[gc]->update(delta);
	}
}

void GameObject::renderGameComponents(const Shader& shader, const RenderingEngine& renderingEngine, const Camera3D& camera)
{
	for (size_t gc = 0; gc < m_gameComponents.size(); gc++)
	{
		m_gameComponents[gc]->render(shader, renderingEngine, camera);
	}
}

void GameObject::processInputGameComponents(const InputManager& input, float delta)
{
	m_transform.update();

	for (size_t gc = 0; gc < m_gameComponents.size(); gc++)
	{
		m_gameComponents[gc]->processInput(input, delta);
	}
}

void GameObject::updateGUIComponents(float delta)
{

}

void GameObject::renderGUIComponents(const GUIEngine& guiEngine, const Camera3D& camera)
{

}
