#pragma once
#include <string>
#include <unordered_map>

class Scene;
class CoreEngine;
class RenderingEngine;
class InputManager;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void addScene(Scene* scene);
	bool removeScene(Scene* scene);
	bool removeScene(std::string name);
	void switchScene(Scene* scene);
	void switchScene(std::string name);

	void update(float delta);
	void render(RenderingEngine* renderingEngine);
	void processInput(const InputManager& input, float delta);

	Scene* getCurrentScene() { return m_scenes[m_currentScene]; }
	void setEngine(CoreEngine* engine);

private:
	std::string m_currentScene;
	std::unordered_map<std::string, Scene*> m_scenes;

	CoreEngine* m_coreEngine;

};

