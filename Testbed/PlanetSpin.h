#pragma once
#include <Components\GameComponents.h>
#include <PhysX/PxPhysicsAPI.h>
using namespace physx;

class PlanetSpin : public GameComponent
{
public:
	PlanetSpin() { }
	~PlanetSpin() { }

	virtual void onStart() override
	{
		//getParent()->getGameComponent<RigidBody>()->setDebugDraw(true);
	}

	virtual void update(float delta) override
	{
		m_angle += 0.001f;

		getTransform()->setRotation(PxQuat(0.0f, 0.0f, 1.0f, m_angle));
	}

private:
	float m_angle;
	bool goAhead = false;
};