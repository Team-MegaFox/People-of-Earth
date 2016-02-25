#pragma once
#include <MegaEngine.h>

#include "FreeLook.h"
#include "FreeMove.h"

class MissionOneScene : public Scene
{
public:
	MissionOneScene() : Scene("Misson 1") { }
	~MissionOneScene() { }

	virtual void init(const Viewport& window) override
	{
		Material humanShip("human_ship", 1.0f, 10, Texture("Ships/Eric/HumanShip.png"));

		addToRoot((new GameObject("Skybox"))
			->addGameComponent(new SkyboxRenderer("Skybox/drake/drake.tga")));

		addToRoot((new GameObject("Directional Light"))
			->addGameComponent(new DirectionalLight(glm::vec3(1.0f, 1.0f, 1.0f), 0.2f, 7, 8.0f, 1.0f)));

		addToRoot((new GameObject("Camera"))
			->addGameComponent(new CameraComponent(glm::perspective(glm::radians(60.0f), window.getAspectRatio(), 0.1f, 1000.0f)))
			->addGameComponent(new FreeLook(window.getCenter()))
			->addGameComponent(new FreeMove));

		addToRoot((new GameObject("Fighter Ship"))
			->addGameComponent(new MeshRenderer(Mesh("Ships/HumanFighter_Final.obj", 0.1f), Material("human_ship"))));
	}

private:

};
