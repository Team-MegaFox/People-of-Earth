#pragma once
#include "World.h"

class PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();

	void updatePhysicsEngine(float timeStep);

	World* getPhysicsWorld()
	{
		return m_physicsWorld;
	}

private:
	World *m_physicsWorld;
};

