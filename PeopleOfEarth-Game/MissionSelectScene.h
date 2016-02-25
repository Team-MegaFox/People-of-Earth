#pragma once
#include <MegaEngine.h>

class MissionSelectScene : public Scene
{
public:
	MissionSelectScene() : Scene("Mission Select") { }
	~MissionSelectScene() { }

	virtual void init(const Viewport& window) override
	{
		addToRoot((new GameObject("Skybox"))
			->addGameComponent(new SkyboxRenderer("Skybox/drake/drake.tga")));

		addToRoot((new GameObject("Directional Light"))
			->addGameComponent(new DirectionalLight(glm::vec3(1.0f, 1.0f, 1.0f), 0.2f, 7, 8.0f, 1.0f)));

		addToRoot((new GameObject("Camera"))
			->addGameComponent(new CameraComponent(glm::perspective(glm::radians(60.0f), window.getAspectRatio(), 0.1f, 1000.0f))));

	}

private:

};
