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
		Audio * BGM = new Audio("In Game Music 2.wav", AudioType::STREAM, true);
		//BGM->pause(true);

		addToRoot((new GameObject("Skybox"))
			->addGameComponent(new SkyboxRenderer("Skybox/drake/drake.tga")));

		addToRoot((new GameObject("Directional Light"))
			->addGameComponent(new DirectionalLight(PxVec3(1.0f, 1.0f, 1.0f), 0.2f, 7, 8.0f, 1.0f)));

		addToRoot((new GameObject("Camera"))
			->addGameComponent(new CameraComponent(ToRadians(60.0f), window.getAspectRatio(), 0.1f, 1000.0f))
			->addGameComponent(BGM));
	}

private:
};
