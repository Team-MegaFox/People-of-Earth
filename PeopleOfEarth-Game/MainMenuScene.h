#pragma once
#include <MegaEngine.h>
#include <glm\glm.hpp>
#include <iostream>

#include "FreeLook.h"
#include "FreeMove.h"
#include "TextLerpAlpha.h"
#include "MainMenuManager.h"
#include "MissionSelectScene.h"
#include "OptionsScene.h"

class MainMenuScene : public Scene
{
public:
	MainMenuScene() : Scene("Main Menu") { }
	~MainMenuScene() { }

	virtual void init(const Viewport& window) override
	{
		//Material earth("earth", 0.4f, 4.0f, Texture("Planets/earth_diffuse.jpg"), Texture("default_normal.jpg"), Texture("Planets/earth_disp.jpg"), 0.0f, 0.0f);

		addToRoot((new GameObject("Skybox"))
			->addGameComponent(new SkyboxRenderer("Skybox/orbital/orbital.tga")));

		addToRoot((new GameObject("Directional Light"))
			->addGameComponent(new DirectionalLight(PxVec3(1.0f, 1.0f, 1.0f), 0.2f, 7, 8.0f, 1.0f)));

		addToRoot((new GameObject("Camera"))
			->addGameComponent(new CameraComponent(Utility::initPerspective(glm::radians(60.0f), window.getAspectRatio(), 0.1f, 1000.0f)))
			//->addGameComponent(new FreeLook(window.getCenter()))
			//->addGameComponent(new FreeMove)
			);

		addToRoot((new GameObject("Splash"))
			->addGUIComponent(new GUILabel(PxVec4(0.4f, 0.6f, 0.2f, 0.05f), PxVec4(0.0f), "Press start...", 16))
			->addGameComponent(new TextLerpAlpha));

		addToRoot((new GameObject("Logo"))
			->addGUIComponent(new GUIImage(PxVec4(0.1f, 0.2f, 0.8f, 0.2f), 
			PxVec4(0.0f), "Images/Logos/TPOE_LOGO_Trans.png")));

		GameObject* mainMenuObject = new GameObject("Main Menu");
		mainMenuObject->addChild((new GameObject("Play Button"))
			->addGUIComponent(new GUIButton(PxVec4(0.425f, 0.6f, 0.15f, 0.07f), PxVec4(0.0f), "Play",
			std::bind(&MainMenuScene::clickPlayButton, this, std::placeholders::_1), 16)));
		mainMenuObject->addChild((new GameObject("Options Button"))
			->addGUIComponent(new GUIButton(PxVec4(0.425f, 0.7f, 0.15f, 0.07f), PxVec4(0.0f), "Options",
			std::bind(&MainMenuScene::clickOptionsButton, this, std::placeholders::_1), 16)));
		mainMenuObject->addChild((new GameObject("Exit Button"))
			->addGUIComponent(new GUIButton(PxVec4(0.425f, 0.8f, 0.15f, 0.07f), PxVec4(0.0f), "Exit",
			std::bind(&MainMenuScene::clickExitButton, this, std::placeholders::_1), 16)));
		addToRoot(mainMenuObject);

		addToRoot((new GameObject("Main Menu Manager"))
			->addGameComponent(new MainMenuManager));

		//addToRoot((new GameObject("Earth", PxVec3(0.0f), glm::angleAxis(glm::radians(-90.0f), PxVec3(1.0f, 0.0f, 0.0f))))
		//	->addGameComponent(new MeshRenderer(Mesh("Environment/sphere.obj"), Material("earth"))));
	}

	bool clickPlayButton(const GameObject& game)
	{
		getCoreEngine()->getSceneManager()->push(new MissionSelectScene);
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
};
