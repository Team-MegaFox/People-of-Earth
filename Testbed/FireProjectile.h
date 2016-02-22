
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
		if (m_delay >= 0.2f)
		{
			if (input.GetRightTrigger() != 0)
			{
				instantiate(
					(new GameObject("Laser", *getTransform()->getPosition(), *getTransform()->getRotation(), glm::vec3(0.15f, 0.15f, 4.0f)))
					->addGameComponent(new Laser)
					->addGameComponent(new MeshRenderer(Mesh("Environment/cube.obj"), Material("plan1")))
					);
				m_delay = 0.0f;
			}
			if (input.GetLeftTrigger() != 0)
			{
				instantiate(
					(new GameObject("Laser", *getTransform()->getPosition(), *getTransform()->getRotation(), glm::vec3(0.15f, 0.15f, 4.0f)))
					->addGameComponent(new Laser)
					->addGameComponent(new MeshRenderer(Mesh("Environment/cube.obj"), Material("plan1")))
					);
				m_delay = 0.0f;
			}
		}
		else
		{
			m_delay += delta;
		}

	}

private:
	float m_delay = 0.2f;

};