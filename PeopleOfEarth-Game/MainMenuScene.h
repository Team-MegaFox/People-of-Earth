#pragma once
#include <MegaEngine.h>
#include <glm\glm.hpp>
#include <iostream>

#include "FreeLook.h"
#include "FreeMove.h"
#include "TextLerpAlpha.h"
#include "MainMenuManager.h"
#include "MissionOneScene.h"
#include "OptionsScene.h"

class MainMenuScene : public Scene
{
public:
	MainMenuScene() : Scene("Main Menu") { }
	~MainMenuScene() { }

	virtual void init(const Viewport& window) override
	{
		AudioSource * BGM = new AudioSource("Title Music.wav", AudioType::STREAM, true);
		//BGM->pause(true);

		addToRoot((new GameObject("Skybox"))
			->addGameComponent(new SkyboxRenderer("Skybox/orbital/orbital.tga")));

		addToRoot((new GameObject("Camera"))
			->addGameComponent(new CameraComponent(ToRadians(60.0f), window.getAspectRatio(), 0.1f, 1000.0f))
			->addGameComponent(new FreeLook(window.getCenter()))
			->addGameComponent(BGM)
			//->addGameComponent(new FreeMove)
			);

		addToRoot((new GameObject("Splash"))
			->addGUIComponent(new GUILabel(PxVec4(0.4f, 0.6f, 0.2f, 0.05f), PxVec4(0.0f), "Press start...", 16))
			->addGameComponent(new TextLerpAlpha));

		m_logo = (new GameObject("Logo"))
			->addGUIComponent(new GUIImage(PxVec4(0.1f, 0.1f, 0.8f, 0.3f),
			PxVec4(0.0f), "Images/Logos/TPOE_LOGO_Trans.png", 2500.0f / 500.0f));
		addToRoot(m_logo);

		m_mainMenuObject = new GameObject("Main Menu");
		m_mainMenuObject->addChild((new GameObject("Play Button"))
			->addGUIComponent(new GUIButton(PxVec4(0.425f, 0.6f, 0.15f, 0.07f), PxVec4(0.0f), "Play",
			std::bind(&MainMenuScene::clickPlayButton, this, std::placeholders::_1), 16)));
		m_mainMenuObject->addChild((new GameObject("Options Button"))
			->addGUIComponent(new GUIButton(PxVec4(0.425f, 0.7f, 0.15f, 0.07f), PxVec4(0.0f), "Options",
			std::bind(&MainMenuScene::clickOptionsButton, this, std::placeholders::_1), 16)));
		m_mainMenuObject->addChild((new GameObject("Exit Button"))
			->addGUIComponent(new GUIButton(PxVec4(0.425f, 0.8f, 0.15f, 0.07f), PxVec4(0.0f), "Exit",
			std::bind(&MainMenuScene::clickExitButton, this, std::placeholders::_1), 16)));
		addToRoot(m_mainMenuObject);

		m_missionSelectMenuObject = new GameObject("Mission Select Menu");
		m_missionSelectMenuObject->addChild((new GameObject("Mission 1"))
			->addGUIComponent(new GUIContainer(PxVec4(0.1f, 0.1f, 0.8f, 0.8f), PxVec4(0.0f)))
			->addChild((new GameObject("Mission 1 Button"))
			->addGUIComponent(new GUIButton(PxVec4(0.425f, 0.95f, 0.15f, 0.05f), PxVec4(0.0f), "Mission 1",
			std::bind(&MainMenuScene::clickMissionOne, this, std::placeholders::_1), 16)))
			->addChild((new GameObject("Mission 1 Image"))
			->addGUIComponent(new GUIImage(PxVec4(0.05f, 0.1f, 0.9f, 0.8f), PxVec4(0.0f), "Images/MissionOneImage.png"))));
		m_missionSelectMenuObject->addChild((new GameObject("Mission 2"))
			->addGUIComponent(new GUIContainer(PxVec4(1.1f, 0.1f, 0.8f, 0.8f), PxVec4(0.0f)))
			->addChild((new GameObject("Mission 2 Button"))
			->addGUIComponent(new GUIButton(PxVec4(0.425f, 0.95f, 0.15f, 0.05f), PxVec4(0.0f), "Mission 2",
			std::bind(&MainMenuScene::clickMissionTwo, this, std::placeholders::_1), 16)))
			->addChild((new GameObject("Mission 2 Image"))
			->addGUIComponent(new GUIImage(PxVec4(0.05f, 0.1f, 0.9f, 0.8f), PxVec4(0.0f), "Images/MissionTwoImage.png"))));
		m_missionSelectMenuObject->addChild((new GameObject("Mission 3"))
			->addGUIComponent(new GUIContainer(PxVec4(2.1f, 0.1f, 0.8f, 0.8f), PxVec4(0.0f)))
			->addChild((new GameObject("Mission 3 Button"))
			->addGUIComponent(new GUIButton(PxVec4(0.425f, 0.95f, 0.15f, 0.05f), PxVec4(0.0f), "Mission 3",
			std::bind(&MainMenuScene::clickMissionThree, this, std::placeholders::_1), 16)))
			->addChild((new GameObject("Mission 3 Image"))
			->addGUIComponent(new GUIImage(PxVec4(0.05f, 0.1f, 0.9f, 0.8f), PxVec4(0.0f), "Images/MissionThreeImage.png"))));
		m_missionSelectMenuObject->addChild((new GameObject("Back Button"))
			->addGUIComponent(new GUIButton(PxVec4(0.45f, 0.95f, 0.1f, 0.05f), PxVec4(0.0f), "Back",
			std::bind(&MainMenuScene::clickBackButton, this, std::placeholders::_1))));
		addToRoot(m_missionSelectMenuObject);

		addToRoot((new GameObject("Moved button sound"))
			->addGameComponent(new AudioSource("(hover_beep)185828__lloydevans09__little-thing.wav", AudioType::SOUND, true)));
		addToRoot((new GameObject("Selected button sound"))
			->addGameComponent(new AudioSource("(select_beep)319200__18hiltc__pixel-game-beep.wav", AudioType::SOUND, true)));

		addToRoot((new GameObject("Main Menu Manager"))
			->addGameComponent(new MainMenuManager(3)));

		// TODO: Add sound effects for hovering
		// TODO: Add Sound effect for buttons selected
	}

private:
	GameObject* m_logo;
	GameObject* m_mainMenuObject;
	GameObject* m_missionSelectMenuObject;
	GameObject* m_missionSelectManagerObject;

	bool clickPlayButton(const GameObject& game)
	{
		m_logo->setEnabled(false);
		m_mainMenuObject->setEnabled(false);
		m_missionSelectMenuObject->setEnabled(true);
		//m_missionSelectManagerObject->getGameComponent<MissionSelectManager>()->setCheckInput(false);
		return true;
	}

	bool clickOptionsButton(const GameObject& game)
	{
		getCoreEngine()->getSceneManager()->push(new OptionsScene, Modality::Popup);
		return true;
	}

	bool clickExitButton(const GameObject& game)
	{
		getCoreEngine()->stop();
		return true;
	}

	//Mission Select
	bool clickBackButton(const GameObject& gameobject)
	{
		m_logo->setEnabled(true);
		m_mainMenuObject->setEnabled(true);
		m_missionSelectMenuObject->setEnabled(false);
		//m_missionSelectManagerObject->getGameComponent<MissionSelectManager>()->setCheckInput(false);
		return true;
	}

	bool clickMissionOne(const GameObject& gameobject)
	{
		getCoreEngine()->getSceneManager()->push(new MissionOneScene);
		return true;
	}

	bool clickMissionTwo(const GameObject& gameobject)
	{
		return true;
	}

	bool clickMissionThree(const GameObject& gameobject)
	{
		return true;
	}
};
