#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"

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
	for (auto it = m_scenes.begin(); it != m_scenes.end(); it++)
	{
		it->second->setEngine(engine);
	}
}
