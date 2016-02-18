
#pragma once
#include <Components\GameComponents.h>
#include <Components\MeshRenderer.h>
#include "Laser.h"

class FireProjectile : public GameComponent
{

public:

	FireProjectile() {}
	~FireProjectile() {}

	virtual void processInput(const InputManager& input, float delta)
	{
		if (input.PadButtonPress(SDL_CONTROLLER_BUTTON_A))
		{
			instantiate(
				(new GameObject("Laser", *getTransform()->getPosition(), *getTransform()->getRotation(), glm::vec3(1.0f, 1.0f, 10.0f)))
				->addGameComponent(new Laser)
				->addGameComponent(new MeshRenderer(Mesh("Environment/cube.obj"), Material("plan1")))
				);
		}

		/*if (input.MouseButtonPress(SDL_BUTTON_LEFT))
		{
			instantiate(
				(new GameObject("Laser", *getTransform()->getPosition(), *getTransform()->getRotation(), glm::vec3(1.0f, 1.0f, 10.0f)))
				->addGameComponent(new Laser)
				->addGameComponent(new MeshRenderer(Mesh("Environment/cube.obj"), Material("plan1")))
				);
		}*/
	}

};