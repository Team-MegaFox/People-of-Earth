#pragma once
#include <vector>
#include <string>
#include "Transform.h"
#include "InputManager.h"
class Camera;
class CoreEngine;
class GameComponent;
class GUIComponent;
class Shader;
class RenderingEngine;
class GUIEngine;

class GameObject
{
public:
	GameObject();
	~GameObject();

	void updateAll(float delta);
	void renderAll(const Shader& shader, const GUIEngine& guiEngine, const RenderingEngine& renderingEngine, const Camera& camera);
	void processAll(const InputManager& input, float delta);

	GameObject* addChild(GameObject* child);
	GameObject* addGameComponent(GameComponent* component);
	GameObject* addGUIComponent(GUIComponent* component);

	bool removeChild(GameObject* child);
	bool removeGameComponent(GameComponent* component);
	bool removeGUIComponent(GUIComponent* component);

	std::vector<GameObject*> getAllAttached();
	std::vector<GameObject*> getAllChildren();

	Transform* getTransform() { return &m_transform; }
	std::string getName() { return name; }
	void setEngine(CoreEngine* engine);

private:
	void updateGameComponents(float delta);
	void renderGameComponents(const Shader& shader, const RenderingEngine& renderingEngine, const Camera& camera);
	void processInputGameComponents(const InputManager& input, float delta);

	void updateGUIComponents(float delta);
	void renderGUIComponents(const GUIEngine& guiEngine, const Camera& camera);

	std::string name;
	std::vector<GameObject*> m_children;
	std::vector<GameComponent*> m_gameComponents;
	std::vector<GUIComponent*> m_guiComponents;
	Transform m_transform;
	CoreEngine* m_coreEngine;
};

