#pragma once
#include <MegaEngine.h>

#include "MissionSelectManager.h"

class MissionSelectScene : public Scene
{
public:
	MissionSelectScene() : Scene("Mission Select") { }
	~MissionSelectScene() { }

	virtual void init(const Viewport& window) override
	{
		Audio * BGM = new Audio("music.mp3", AudioType::STREAM, true);

		addToRoot((new GameObject("Skybox"))
			->addGameComponent(new SkyboxRenderer("Skybox/drake/drake.tga")));

		addToRoot((new GameObject("Directional Light"))
			->addGameComponent(new DirectionalLight(PxVec3(1.0f, 1.0f, 1.0f), 0.2f, 7, 8.0f, 1.0f)));

		addToRoot((new GameObject("Camera"))
			->addGameComponent(new CameraComponent(ToRadians(60.0f), window.getAspectRatio(), 0.1f, 1000.0f))
			->addGameComponent(BGM));

		addToRoot((new GameObject("Mission 1"))
			->addGUIComponent(new GUIContainer(PxVec4(0.1f, 0.1f, 0.8f, 0.8f), PxVec4(0.0f)))
			->addChild((new GameObject("Mission 1 Button"))
			->addGUIComponent(new GUIButton(PxVec4(0.425f, 0.95f, 0.15f, 0.05f), PxVec4(0.0f), "Mission 1",
			std::bind(&MissionSelectScene::clickMissonOne, this, std::placeholders::_1), 16)))
			->addChild((new GameObject("Mission 1 Image"))
			->addGUIComponent(new GUIImage(PxVec4(0.05f, 0.1f, 0.9f, 0.8f), PxVec4(0.0f), "Images/MissionOneImage.png"))));

		addToRoot((new GameObject("Mission 2"))
			->addGUIComponent(new GUIContainer(PxVec4(1.1f, 0.1f, 0.8f, 0.8f), PxVec4(0.0f)))
			->addChild((new GameObject("Mission 2 Button"))
			->addGUIComponent(new GUIButton(PxVec4(0.425f, 0.95f, 0.15f, 0.05f), PxVec4(0.0f), "Mission 2",
			std::bind(&MissionSelectScene::clickMissonTwo, this, std::placeholders::_1), 16)))
			->addChild((new GameObject("Mission 2 Image"))
			->addGUIComponent(new GUIImage(PxVec4(0.05f, 0.1f, 0.9f, 0.8f), PxVec4(0.0f), "Images/MissionTwoImage.png"))));

		addToRoot((new GameObject("Mission 3"))
			->addGUIComponent(new GUIContainer(PxVec4(2.1f, 0.1f, 0.8f, 0.8f), PxVec4(0.0f)))
			->addChild((new GameObject("Mission 3 Button"))
			->addGUIComponent(new GUIButton(PxVec4(0.425f, 0.95f, 0.15f, 0.05f), PxVec4(0.0f), "Mission 3",
			std::bind(&MissionSelectScene::clickMissonThree, this, std::placeholders::_1), 16)))
			->addChild((new GameObject("Mission 3 Image"))
			->addGUIComponent(new GUIImage(PxVec4(0.05f, 0.1f, 0.9f, 0.8f), PxVec4(0.0f), "Images/MissionThreeImage.png"))));

		addToRoot((new GameObject("Back Button"))
			->addGUIComponent(new GUIButton(PxVec4(0.45f, 0.95f, 0.1f, 0.05f), PxVec4(0.0f), "Back",
			std::bind(&MissionSelectScene::clickBackButton, this, std::placeholders::_1))));

		addToRoot((new GameObject("Mission Select Manager"))
			->addGameComponent(new MissionSelectManager(3)));

		BGM->pause(true);
	}

private:
	bool clickBackButton(const GameObject& gameobject)
	{
		getCoreEngine()->getSceneManager()->popTo(0);
		return true;
	}

	bool clickMissonOne(const GameObject& gameobject)
	{
		getCoreEngine()->getSceneManager()->push(new MissionOneScene);
		return true;
	}

	bool clickMissonTwo(const GameObject& gameobject)
	{
		return true;
	}

	bool clickMissonThree(const GameObject& gameobject)
	{
		return true;
	}
};
