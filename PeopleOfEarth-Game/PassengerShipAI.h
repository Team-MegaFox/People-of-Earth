// ***********************************************************************
// Author           : Christopher Maeda
// Created          : 03-03-2016
//
// Last Modified By : Christopher Maeda
// Last Modified On : 03-04-2016
// ***********************************************************************
// <copyright file="PassengerShipAI.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
//</summary>
// ***********************************************************************

#pragma once
#include "SteeringBehaviour.h"
#include "ShipStats.h"
#include "PlayerShipMovementController.h"
#include "GameWonScene.h"
#include <PhysX/PxPhysicsAPI.h>
using namespace physx;

class PassengerShipAI : public SteeringBehaviour
{

public:
	PassengerShipAI()
	{}

	~PassengerShipAI()
	{}

	virtual void init() override
	{
		m_forwardDirection = PxVec3(0.0f, 0.0f, 0.0f);
		m_direction = PxVec3(0.0f, 0.0f, 0.0f);
		m_velocityValue = 25.0f;
		m_wayPoints.push_back(PxVec3(0.0f, 0.0f, 15000.0f));
		m_wayPoints.push_back(PxVec3(0.0f, 0.0f, 12000.0f));
		m_wayPoints.push_back(PxVec3(0.0f, 0.0f, 10000.0f));
		m_wayPoints.push_back(PxVec3(0.0f, 0.0f, 7500.0f));
		m_wayPoints.push_back(PxVec3(0.0f, 0.0f, 1000.0f));
		m_delayCheckInFront = 0.0f;
		m_distanceToChangeWayPoint = 200.0f;

		//In game code:
		m_shipStats = getParent()->getGameComponent<ShipStats>();
	}

	virtual std::vector<GameObject*> getAllEnemyObject() override
	{
		std::vector<GameObject*> collisionCheckObject;
		std::vector<GameObject*> gameObjects;
		//gameObjects = getGameObjectsByName("enemyFighter_");
		//for (size_t i = 0; i < gameObjects.size(); i++)
		//{
		//	collisionCheckObject.push_back(gameObjects[i]);
		//}
		//No Collider at the moment
		/*gameObjects = getGameObjectsByName("Asteroid Field");
		for (size_t i = 0; i < gameObjects.size(); i++)
		{
			collisionCheckObject.push_back(gameObjects[i]);
		}*/
		return collisionCheckObject;
	}

	virtual void UpdateAI(float timestep) override
	{
		WayPoint(timestep);

		PxReal zPos = m_rigidBody->getPosition().z;
		if (zPos >= 25000.0f)
		{
			getCoreEngine()->getSceneManager()->push(new GameWonScene, Modality::Popup);
		}
	}

private:
	ShipStats* m_shipStats;
	float m_delayAttacking;
	int numberOfLaserShot;
	float m_delayObjectSearch;
};