#pragma once
#include <MegaEngine.h>
#include <glm\glm.hpp>
#include <iostream>

#include "FreeLook.h"
#include "FreeMove.h"
#include "TextLerpAlpha.h"
#include "MainMenuManager.h"

class MainMenuScene : public Scene
{
public:
	MainMenuScene() : Scene("Main Menu") { }
	~MainMenuScene() { }

	virtual void init(const Viewport& window) override
	{
		addToRoot((new GameObject("Skybox"))
			->addGameComponent(new SkyboxRenderer("Skybox/drake/drake.tga")));

		addToRoot((new GameObject("Directional Light"))
			->addGameComponent(new DirectionalLight(glm::vec3(1.0f, 1.0f, 1.0f), 0.2f, 7, 8.0f, 1.0f)));

		addToRoot((new GameObject("Camera"))
			->addGameComponent(new CameraComponent(glm::perspective(glm::radians(60.0f), window.getAspectRatio(), 0.1f, 1000.0f))));

		addToRoot((new GameObject("Splash"))
			->addGUIComponent(new GUILabel(glm::vec4(0.4f, 0.6f, 0.2f, 0.05f), glm::vec4(0.0f), "Press any button...", 16))
			->addGameComponent(new TextLerpAlpha));

		addToRoot((new GameObject("Main Menu"))
			->addGUIComponent(new GUILabel(glm::vec4(0.4f, 0.2f, 0.2f, 0.05f), glm::vec4(0.0f), "Main Menu", 16)));

		addToRoot((new GameObject("Main Menu Manager"))
			->addGameComponent(new MainMenuManager));

	}
};
