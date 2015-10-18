#pragma once
#include <string>
#include <vector>

#include "GameObject.h"
class CoreEngine;
class RenderingEngine;
class InputManager;

class Scene
{
public:
	Scene(const std::string& name);
	virtual ~Scene();

	virtual void init() { }
	void update(float delta);
	void render(RenderingEngine* renderingEngine);
	void processInput(const InputManager& input, float delta);

	bool addToRoot(GameObject* gameobject) { m_root.addChild(gameobject); }
	bool removeGameObject(GameObject* gameobject);
	bool removeGameObjectByName(const std::string& name);

	std::vector<GameObject*> getAllGameObjects() { return m_root.getAllAttached(); }
	GameObject* getGameObjectByName(const std::string& name);
	std::string getName() { return m_name; }

	void setEngine(CoreEngine* engine) { m_root.setEngine(engine); }

private:
	std::string m_name;
	GameObject m_root;
};

