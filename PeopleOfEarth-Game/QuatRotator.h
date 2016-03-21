#pragma once

#include <Components\GameComponents.h>
#include <SDL2\SDL.h>
#include <PhysX\PxPhysicsAPI.h>
using namespace physx;

class QuatRotator : public GameComponent
{
public:
	QuatRotator(PxVec3 center) : m_center(center) {}
	~QuatRotator() {}

	virtual void update(float deltaTime) override
	{
		if (angle < 360.0f)
		{
			angle += 1.0f;
		}
		else if (angle >= 360.0f)
		{
			angle = 0.0f;
		}

		getTransform()->setPosition(PxVec3(m_center.x, PxCos(angle) + m_center.y, m_center.z));
	}

private:

	PxVec3 m_center;
	float angle = 0.0f;
};