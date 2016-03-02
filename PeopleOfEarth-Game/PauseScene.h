#pragma once
#include <MegaEngine.h>
#include "OptionsScene.h"

class PauseScene : public Scene
{
public:
	PauseScene() : Scene("Pause") { }
	~PauseScene() { }

	virtual void init(const Viewport& window) override
	{
		addToRoot((new GameObject("Pause Menu"))
			->addGUIComponent(new GUIContainer(PxVec4(0.1f, 0.1f, 0.8f, 0.8f), PxVec4(0.0f)))
			->addChild((new GameObject("Resume Button"))
			->addGUIComponent(new GUIButton(PxVec4(0.35f, 0.2f, 0.3f, 0.08f), PxVec4(0.0f), "Resume",
			std::bind(&PauseScene::onResumeClick, this, std::placeholders::_1), 14)))
			->addChild((new GameObject("Options Button"))
			->addGUIComponent(new GUIButton(PxVec4(0.35f, 0.4f, 0.3f, 0.08f), PxVec4(0.0f), "Options",
			std::bind(&PauseScene::onOptionsClick, this, std::placeholders::_1), 14)))
			->addChild((new GameObject("Mission Select Button"))
			->addGUIComponent(new GUIButton(PxVec4(0.3f, 0.6f, 0.4f, 0.08f), PxVec4(0.0f), "Mission Select",
			std::bind(&PauseScene::onMissionSelectClick, this, std::placeholders::_1), 14)))
			->addChild((new GameObject("Exit Button"))
			->addGUIComponent(new GUIButton(PxVec4(0.4f, 0.8f, 0.2f, 0.08f), PxVec4(0.0f), "Exit",
			std::bind(&PauseScene::onExitClick, this, std::placeholders::_1), 14))));


	}

private:
	bool onResumeClick(const GameObject& gameobject)
	{
		getCoreEngine()->getSceneManager()->pop();
		return true;
	}

	bool onOptionsClick(const GameObject& gameobject)
	{
		getCoreEngine()->getSceneManager()->push(new OptionsScene, Modality::Popup);
		return true;
	}

	bool onMissionSelectClick(const GameObject& gameobject)
	{
		getCoreEngine()->getSceneManager()->popTo(1);
		return true;
	}

	bool onExitClick(const GameObject& gameobject)
	{
		getCoreEngine()->stop();
		return true;
	}

};
