#include "PhysicsEngine.h"


PhysicsEngine::PhysicsEngine() : m_physicsWorld(new World())
{
}


PhysicsEngine::~PhysicsEngine()
{
}


void PhysicsEngine::updatePhysicsEngine(float timeStep)
{
	m_physicsWorld->update(timeStep);
}
