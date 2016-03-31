// ***********************************************************************
// Author           : Christopher Maeda & Jesse Derochie
// Created          : 03-30-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 03-24-2016
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
			}
		}
	}

	if (m_targetObject != nullptr)
	{
		m_velocityValue = 100.0f;
	}
}

std::vector<GameObject*> MissileAI::getAllEnemyObject()
{
	return getGameObjectsByName("enemyFighter");
}

void MissileAI::UpdateAI(float timestep)
{
	//No target
	if (m_targetObject != nullptr)
	{
		//if missile collided with target then
		if (m_rigidBody->getCollider()->checkCollision(m_targetRigidBody->getCollider()))
		{
			m_targetObject->getGameComponent<ShipStats>()->setHealth(0.0f);
			m_alive = false;
		}
		else
		{
			SeekToTarget(timestep);
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