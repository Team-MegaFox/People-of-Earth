#pragma once
#include <MegaEngine.h>
#include <glm\glm.hpp>
#include <iostream>

#include "FreeLook.h"
#include "FreeMove.h"

class MainMenuScene : public Scene
{
public:
	MainMenuScene() : Scene("Main Menu") { }
	~MainMenuScene() { }

	virtual void init(const Viewport& window) override
	{
		addToRoot((new GameObject("skybox"))
			->addGameComponent(new SkyboxRenderer("Skybox/drake/drake.tga")));

		addToRoot((new GameObject("Directional Light"))
			->addGameComponent(new DirectionalLight(glm::vec3(1.0f, 1.0f, 1.0f), 0.2f, 7, 8.0f, 1.0f)));

		addToRoot((new GameObject("camera"))
			->addGameComponent(new CameraComponent(glm::perspective(glm::radians(60.0f), window.getAspectRatio(), 0.1f, 1000.0f)))
			->addGameComponent(new FreeLook(window.getCenter()))
			->addGameComponent(new FreeMove));

		addToRoot((new GameObject("Press start"))
			->addGUIComponent(new GUILabel(glm::vec4(0.45f, 0.5f, 0.1f, 0.02f), glm::vec4(0.0f), "Press start...")));

		addToRoot((new GameObject("Loading"))
			->addGUIComponent(new GUILabel(glm::vec4(0.4f, 0.1f, 0.2f, 0.1f), glm::vec4(0.0f), "Loading", 24)));

		addToRoot((new GameObject("Press"))
			->addGUIComponent(new GUILabel(glm::vec4(0.45f, 0.3f, 0.1f, 0.05f), glm::vec4(0.0f), "Press...", 16)));

	}
};

