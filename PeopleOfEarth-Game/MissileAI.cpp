// ***********************************************************************
// Author           : Christopher Maeda & Jesse Derochie
// Created          : 03-30-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 04-20-2016
// ***********************************************************************
// <copyright file="MissileAI.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
//</summary>
// ***********************************************************************

#include "MissileAI.h"
#include "ShipStats.h"

void MissileAI::init()
{
	m_targetObject = nullptr;
	m_forwardDirection = Utility::getForward(m_rigidBody->getRotation());
	m_direction = PxVec3(0.0f, 0.0f, 0.0f);
	float shortestDistance = 999999999.0f;
	float distance;
	std::vector<GameObject*> enemyGameObjects = getAllEnemyObject();

	for (size_t i = 0; i < enemyGameObjects.size(); i++)
	{
		//If in front
		if ((enemyGameObjects[i]->getGameComponent<RigidBody>()->getPosition() - m_rigidBody->getPosition()).dot(
			m_forwardDirection) > 0.0f)
		{
			//Get the distance
			distance = Utility::getDistance(
				enemyGameObjects[i]->getGameComponent<RigidBody>()->getPosition(), m_rigidBody->getPosition());
			//if it is the closest
			if (shortestDistance > distance)
			{
				m_targetObject = enemyGameObjects[i];
				m_targetRigidBody = m_targetObject->getGameComponent<RigidBody>();
				shortestDistance = distance;
			}
		}
	}
	
	m_velocityValue = 100.0f;
	
}

std::vector<GameObject*> MissileAI::getAllEnemyObject()
{
	return getGameObjectsByName("enemyFighter_");
}

void MissileAI::UpdateAI(float timestep)
{
	//No target
	if (m_targetObject != nullptr)
	{
		//if missile collided with target then
		if (m_rigidBody->getCollider()->checkCollision(m_targetRigidBody->getCollider()))
		{
			instantiate((new GameObject("explosionA", *m_targetObject->getTransform()->getPosition()))
				->addGameComponent(new ParticleSystem(Material("explosionMat"), EXPLOSION, 10.0f, 5.0f, 500.0f)));
			instantiate((new GameObject("explosionB", *m_targetObject->getTransform()->getPosition()))
				->addGameComponent(new ParticleSystem(Material("explosionMat"), EXPLOSION, 10.0f, 5.0f, 500.0f)));
			m_targetObject->getGameComponent<ShipStats>()->setHealth(0.0f);
			m_alive = false;
		}
		else
		{
			//if (Utility::getDistance(m_targetRigidBody->getPosition(), m_rigidBody->getPosition()) < 100.0f)
			//{
				float timeOfCollision = 0.0f;
				//In front
				if (m_targetRigidBody->getCollider()->checkCollision(m_rigidBody->getPosition(), m_rigidBody->getVelocity(), timeOfCollision))
				{
					m_velocityValue = 100.0f;
				}
				//Slow it down to turn
				else
				{
					m_velocityValue = 50.0f;
					RotateShip(timestep * 2);
				}
			//}
			////Just need to move fast to its target
			//else
			//{
			//	m_velocityValue = 100.0f;
			//}
			SeekToPoint(m_targetRigidBody->getPosition() + (m_targetRigidBody->getVelocity() * timestep), timestep);
		}
	}
	m_lifeTime -= timestep;

	if (m_lifeTime < 0.0f)
	{
		m_alive = false;
	}
}

void MissileAI::removeTarget(const std::string & name)
{
	if (m_targetObject!= nullptr && name == m_targetObject->getName())
	{
		m_targetObject = nullptr;
	}
}