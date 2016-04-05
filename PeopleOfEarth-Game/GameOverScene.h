#pragma once
#include <MegaEngine.h>
#include "OptionsScene.h"
#include "GameOverManager.h"

class GameOverScene : public Scene
{
public:
	GameOverScene() : Scene("GameOver") { }
	~GameOverScene() { }

	virtual void init(const Viewport& window) override
	{
		addToRoot((new GameObject("Game Over Menu"))
			->addGUIComponent(new GUIContainer(PxVec4(0.1f, 0.1f, 0.8f, 0.8f), PxVec4(0.0f), "Pause"))
			->addChild((new GameObject("Mission Select Button"))
			->addGUIComponent(new GUIButton(PxVec4(0.3f, 0.6f, 0.4f, 0.08f), PxVec4(0.0f), "Mission Select",
			std::bind(&GameOverScene::onMissionSelectClick, this, std::placeholders::_1), 14)))
			->addChild((new GameObject("Exit Button"))
			->addGUIComponent(new GUIButton(PxVec4(0.4f, 0.8f, 0.2f, 0.08f), PxVec4(0.0f), "Exit",
			std::bind(&GameOverScene::onExitClick, this, std::placeholders::_1), 14))));

		addToRoot((new GameObject("Game Over Manager"))
			->addGameComponent(new GameOverManager));

		addToRoot((new GameObject("Moved button sound"))
			->addGameComponent(new AudioSource("Music/(hover_beep)185828__lloydevans09__little-thing.wav", AudioType::SOUND, false)));
		addToRoot((new GameObject("Selected button sound"))
			->addGameComponent(new AudioSource("Music/(select_beep)319200__18hiltc__pixel-game-beep.wav", AudioType::SOUND, false)));
	}

private:

	bool onMissionSelectClick(const GameObject& gameobject)
	{
		getCoreEngine()->getSceneManager()->popTo(0);
		return true;
	}

	bool onExitClick(const GameObject& gameobject)
	{
		getCoreEngine()->stop();
		return true;
	}

};
