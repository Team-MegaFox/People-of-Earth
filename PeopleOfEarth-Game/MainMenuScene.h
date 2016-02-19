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
		Material humanShip("human_ship", 1.0f, 10, Texture("Ships/Eric/HumanShip.png"));

		addToRoot((new GameObject("skybox"))
			->addGameComponent(new SkyboxRenderer("Skybox/drake/drake.tga")));

		addToRoot((new GameObject("Fighter Ship", glm::vec3(0.0f, 0.0f, 0.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Ships/HumanFighter_Final.obj", 0.1f), Material("human_ship"))));

		addToRoot((new GameObject("camera"))
			->addGameComponent(new CameraComponent(glm::perspective(glm::radians(60.0f), window.getAspectRatio(), 0.1f, 1000.0f)))
			->addGameComponent(new FreeLook(window.getCenter()))
			->addGameComponent(new FreeMove));

	}
};

