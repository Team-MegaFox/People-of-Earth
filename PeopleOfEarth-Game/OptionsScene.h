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
		GameObject* effectsLabel = (new GameObject("Effects Volume Label"))
			->addGUIComponent(new GUILabel(PxVec4(0.165f, 0.1f, 0.1f, 0.09f), PxVec4(0.0f, 1.0f, 0.0f, 0.0f), "Effects", 16));

		GameObject* effectsSlider = (new GameObject("Effects Volume Slider"))
			->addGUIComponent(new GUISlider(PxVec4(0.2f, 0.2f, 0.0f, 0.5f), PxVec4(0.0f, 0.0f, 25.0f, 0.0f)));

		GameObject* effectsVolume = (new GameObject("Effects Volume Label"))
			->addGUIComponent(new GUILabel(PxVec4(0.165f, 0.7f, 0.1f, 0.09f), PxVec4(0.0f, 1.0f, 0.0f, 0.0f), "100", 16));

		GameObject* bgmLabel = (new GameObject("BGM Volume Label"))
			->addGUIComponent(new GUILabel(PxVec4(0.365f, 0.1f, 0.1f, 0.09f), PxVec4(0.0f, 1.0f, 0.0f, 0.0f), "BGM", 16));

		GameObject* bgmSlider = (new GameObject("BGM Volume Slider"))
			->addGUIComponent(new GUISlider(PxVec4(0.4f, 0.2f, 0.0f, 0.5f), PxVec4(0.0f, 0.0f, 25.0f, 0.0f)));

		GameObject* bgmVolume = (new GameObject("BGM Volume Label"))
			->addGUIComponent(new GUILabel(PxVec4(0.365f, 0.7f, 0.1f, 0.09f), PxVec4(0.0f, 1.0f, 0.0f, 0.0f), "100", 16));

		GameObject* backButton = (new GameObject("Back Button"))
			->addGUIComponent(new GUIButton(PxVec4(0.2f, 0.85f, 0.25f, 0.08f), PxVec4(0.0f), "Back",
			std::bind(&OptionsScene::onBackClick, this, std::placeholders::_1), 14));

		GameObject* controlsButton = (new GameObject("Controls Button"))
			->addGUIComponent(new GUIButton(PxVec4(0.5f, 0.85f, 0.25f, 0.08f), PxVec4(0.0f), "Controls",
			std::bind(&OptionsScene::onControlsClick, this, std::placeholders::_1), 14));

		addToRoot((new GameObject("Options Menu"))
			->addGUIComponent(new GUIContainer(PxVec4(0.1f, 0.1f, 0.8f, 0.8f), PxVec4(0.0f), "Options"))
			->addChild(effectsLabel)
			->addChild(effectsSlider)
			->addChild(effectsVolume)
			->addChild(bgmLabel)
			->addChild(bgmSlider)
			->addChild(bgmVolume)
			->addChild(backButton)
			->addChild(controlsButton));

		addToRoot((new GameObject("Options Menu Manager"))
			->addGameComponent(new OptionsMenuManager(effectsSlider, effectsVolume, bgmSlider, bgmVolume, backButton, controlsButton)));
	
		// TODO: Add sound effects for hovering
		// TODO: Add Sound effect for buttons selected
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
