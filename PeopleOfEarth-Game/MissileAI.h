// ***********************************************************************
// Author           : Christopher Maeda
// Created          : 03-23-2016
//
// Last Modified By : Christopher Maeda
// Last Modified On : 03-24-2016
// ***********************************************************************
// <copyright file="MissileAI.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
//</summary>
// ***********************************************************************

#pragma once
#include "SteeringBehaviour.h"

class MissileAI : public SteeringBehaviour
{
public:

	MissileAI() : m_lifeTime(30.0f)
	{
	}

	~MissileAI() {}

	virtual void init() override
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

	virtual std::vector<GameObject*> getAllEnemyObject() override
	{
		return getGameObjectsByName("enemyFighter");
	}

	virtual void UpdateAI(float timestep) override
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

	void removeTarget(std::string name)
	{
		if (name == getParent()->getName())
		{
			m_targetObject = nullptr;
		}
	}

private:
	float m_lifeTime;
	RigidBody* m_targetRigidBody;
};