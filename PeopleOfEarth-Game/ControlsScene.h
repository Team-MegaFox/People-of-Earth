#pragma once
#include <MegaEngine.h>

class ControlsMenuManager : public GameComponent
{
public:
	virtual void processInput(const InputManager& input, float delta) 
	{
		if (input.PadButtonPress(SDL_CONTROLLER_BUTTON_B))
		{
			getCoreEngine()->getSceneManager()->pop();
		}
	}
};

class ControlsScene : public Scene
{
public:
	ControlsScene() : Scene("Controls") { }
	~ControlsScene() { }

	virtual void init(const Viewport& window) override
	{
		addToRoot((new GameObject("Options Menu"))
			->addGUIComponent(new GUIContainer(PxVec4(0.1f, 0.1f, 0.8f, 0.8f), PxVec4(0.0f), "Controls"))
			->addChild((new GameObject("Controls Image"))
			->addGUIComponent(new GUIImage(PxVec4(0.1f, 0.03f, 0.8f, 8.8f), PxVec4(0.0f), "Images/GameControls.png", 2500.0f / 1440.0f)))
			->addChild((new GameObject("Back Button"))
			->addGUIComponent(new GUIButton(PxVec4(0.375f, 0.9f, 0.25f, 0.08f), PxVec4(0.0f), "Back",
			std::bind(&ControlsScene::onBackClick, this, std::placeholders::_1), 14))));

		addToRoot((new GameObject("Options Menu Manager"))
			->addGameComponent(new ControlsMenuManager));
	}

private:
	bool onBackClick(const GameObject& gameobject)
	{
		getCoreEngine()->getSceneManager()->pop();
		return true;
	}

};