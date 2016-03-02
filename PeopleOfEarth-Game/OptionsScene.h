#pragma once
#include <MegaEngine.h>
#include "OptionsMenuManager.h"
#include "ControlsScene.h"

class OptionsScene : public Scene
{
public:
	OptionsScene() : Scene("Options") { }
	~OptionsScene() { }

	virtual void init(const Viewport& window) override
	{
		GameObject* effectsSlider = (new GameObject("Effects Volume Slider"))
			->addGUIComponent(new GUISlider(PxVec4(0.2f, 0.2f, 0.05f, 0.5f), PxVec4(0.0f)));

		GameObject* effectsBox = (new GameObject("Effects Volume Text Box"))
			->addGUIComponent(new GUITextBox(PxVec4(0.17f, 0.7f, 0.11f, 0.09f), PxVec4(0.0f, 8.0f, 0.0f, 0.0f), "0", 3));

		GameObject* bgmSlider = (new GameObject("BGM Volume Slider"))
			->addGUIComponent(new GUISlider(PxVec4(0.4f, 0.2f, 0.05f, 0.5f), PxVec4(0.0f)));

		GameObject* bgmBox = (new GameObject("BGM Volume Text Box"))
			->addGUIComponent(new GUITextBox(PxVec4(0.37f, 0.7f, 0.11f, 0.09f), PxVec4(0.0f, 8.0f, 0.0f, 0.0f), "0", 3));

		addToRoot((new GameObject("Options Menu"))
			->addGUIComponent(new GUIContainer(PxVec4(0.1f, 0.1f, 0.8f, 0.8f), PxVec4(0.0f), "Options"))
			->addChild(effectsSlider)
			->addChild(effectsBox)
			->addChild(bgmSlider)
			->addChild(bgmBox)
			->addChild((new GameObject("Back Button"))
			->addGUIComponent(new GUIButton(PxVec4(0.2f, 0.85f, 0.25f, 0.08f), PxVec4(0.0f), "Back",
			std::bind(&OptionsScene::onBackClick, this, std::placeholders::_1), 14)))
			->addChild((new GameObject("Controls Button"))
			->addGUIComponent(new GUIButton(PxVec4(0.5f, 0.85f, 0.25f, 0.08f), PxVec4(0.0f), "Controls",
			std::bind(&OptionsScene::onControlsClick, this, std::placeholders::_1), 14))));

		addToRoot((new GameObject("Options Menu Manager"))
			->addGameComponent(new OptionsMenuManager(effectsSlider, effectsBox, bgmSlider, bgmBox)));
	}

private:
	bool onBackClick(const GameObject& gameobject)
	{
		getCoreEngine()->getSceneManager()->pop();
		return true;
	}

	bool onControlsClick(const GameObject& gameobject)
	{
		getCoreEngine()->getSceneManager()->push(new ControlsScene, Modality::Popup);
		return true;
	}

};
