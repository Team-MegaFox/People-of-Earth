#pragma once
#include <MegaEngine.h>
#include "OptionsScene.h"
#include "GameWonManager.h"

class GameWonScene : public Scene
{
public:
	GameWonScene() : Scene("GameWon") { }
	~GameWonScene() { }

	virtual void init(const Viewport& window) override
	{
		std::string formatting = "[colour='FFFFFFFF'][font='SaucerBB-20'][padding='l:5 t:0 r:5 b:0']";
		std::string objectives = "Congratulations you Win!!";

		addToRoot((new GameObject("Game Won Container"))
			->addGUIComponent(new GUIContainer(PxVec4(0.1f, 0.1f, 0.8f, 0.8f), PxVec4(0.0f), "You Win!"))
			->addChild((new GameObject("Label"))
			->addGUIComponent(new GUILabel(PxVec4(0.25f, 0.35f, 0.5f, 0.2f), PxVec4(0.0f), formatting + objectives)))
			->addChild((new GameObject("Exit Button"))
			->addGUIComponent(new GUIButton(PxVec4(0.4f, 0.7f, 0.2f, 0.09f), PxVec4(0.0f), "Exit",
			std::bind(&GameWonScene::onExitClick, this, std::placeholders::_1), 14))));

		//addToRoot((new GameObject("Game Won Menu"))
		//	->addGUIComponent(new GUIContainer(PxVec4(0.1f, 0.1f, 0.8f, 0.8f), PxVec4(0.0f), "You Win!"))
		//	->addChild((new GameObject("Exit Button"))
		//	->addGUIComponent(new GUIButton(PxVec4(0.4f, 0.5f, 0.2f, 0.08f), PxVec4(0.0f), "Exit",
		//	std::bind(&GameWonScene::onExitClick, this, std::placeholders::_1), 14)))
		//	);

		addToRoot((new GameObject("Game Won Manager"))
			->addGameComponent(new GameWonManager));
	}

private:

	bool onExitClick(const GameObject& gameobject)
	{
		getCoreEngine()->stop();
		return true;
	}

};