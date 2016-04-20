
#pragma once
#include "SteeringBehaviour.h"
#include "ShipStats.h"
#include "PlayerShipMovementController.h"
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
		m_wayPoints.push_back(PxVec3(10.0f, 15.0f, 2000.0f));
		m_wayPoints.push_back(PxVec3(300.0f, 15.0f, 1500.0f));
		m_wayPoints.push_back(PxVec3(150.0f, 15.0f, 1000.0f));
		m_wayPoints.push_back(PxVec3(0.0f, 15.0f, 500.0f));
		m_delayCheckInFront = 0.0f;
		m_distanceToChangeWayPoint = 200.0f;

		//In game code:
		m_shipStats = getParent()->getGameComponent<ShipStats>();
	}

	virtual std::vector<GameObject*> getAllEnemyObject() override
	{
		std::vector<GameObject*> collisionCheckObject;
		//std::vector<GameObject*> gameObjects;
		//gameObjects = getGameObjectsByName("enemyFighter_");
		//for (size_t i = 0; i < gameObjects.size(); i++)
		//{
		//	collisionCheckObject.push_back(gameObjects[i]);
		//}
		return collisionCheckObject;
	}

	virtual void UpdateAI(float timestep) override
	{
		WayPoint(timestep);
	}

private:
	ShipStats* m_shipStats;
	float m_delayAttacking;
	int numberOfLaserShot;
	float m_delayObjectSearch;
};