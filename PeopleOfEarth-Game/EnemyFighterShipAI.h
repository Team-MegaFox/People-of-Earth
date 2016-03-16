// ***********************************************************************
// Author           : Christopher Maeda
// Created          : 02-23-2016
//
// Last Modified By : Christopher Maeda
// Last Modified On : 03-15-2016
// ***********************************************************************
// <copyright file="EnemyFighterShipAI.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
//</summary>
// ***********************************************************************

#pragma once
#include "SteeringBehaviour.h"
#include "Projectile.h"
#include "ShipStats.h"
#include "PlayerShipMovementController.h"
#include <PhysX/PxPhysicsAPI.h>
using namespace physx;

enum SHIP_CLASS
{
	FIGHTER_SHIP,
	PASSENGER_SHIP,
	ALL_ENEMY_SHIP
};

class EnemyFighterShipAI : public SteeringBehaviour
{

public:
	EnemyFighterShipAI()
	{}

	~EnemyFighterShipAI() { }

	virtual void init() override
	{
		m_forwardDirection = PxVec3(0.0f, 0.0f, 0.0f);
		m_direction = PxVec3(0.0f, 0.0f, 0.0f);
		m_targetPoint = *getTransform()->getPosition();
		m_velocityValue = 100.0f; 
		//In game code:
		m_shipStats = getParent()->getGameComponent<ShipStats>();
		m_delayObjectSearch = -1.0f;
		getClosestObject(SHIP_CLASS::ALL_ENEMY_SHIP);
		m_passengerShip = getGameObjectByName("passengerShip");
	}

	virtual std::vector<GameObject*> getAllEnemyObject() override
	{
		std::vector<GameObject*> collisionCheckObject;
		std::vector<GameObject*> gameObjects;
		gameObjects = getGameObjectsByName("Fighter Ship");
		for (size_t i = 0; i < gameObjects.size(); i++)
		{
			collisionCheckObject.push_back(gameObjects[i]);
		}
		gameObjects = getGameObjectsByName("Passenger Ship");
		for (size_t i = 0; i < gameObjects.size(); i++)
		{
			collisionCheckObject.push_back(gameObjects[i]);
		}
		return collisionCheckObject;

	}

	virtual void UpdateAI(float timestep) override
	{
		//If it is close enough then
		if (Utility::getDistance(*getTransform()->getPosition(), *m_targetObject->getTransform()->getPosition()) < 2000.0f)
		{
			//Pursue the passenger ship if hp is above 80%
			if (m_delayAttacking < 0.0f && m_shipStats->getHealth() > 0.8f)
			{
				getClosestObject(SHIP_CLASS::PASSENGER_SHIP);
				float timeOfCollision;
				if (Utility::getDistance(*getTransform()->getPosition(), *m_targetObject->getTransform()->getPosition()) < 600.0f
					&& m_targetObject->getGameComponent<RigidBody>()->getCollider()->checkCollision(
					*getTransform()->getPosition(), Utility::getForward(*getTransform()->getRotation()) /*getParent()->getGameComponent<RigidBody>()->getVelocity()*/, timeOfCollision))
				{
					timeOfCollision /= 60.0f;
					if (timeOfCollision < 2.0f)
					{
						shootLaser();
					}
				}
				Pursue(*m_targetObject, timestep);
			}
			//Pursue the fighter ship
			else if (m_delayAttacking < 0.0f && m_shipStats->getHealth() > 0.4f)
			{
				getClosestObject(SHIP_CLASS::FIGHTER_SHIP);
				float timeOfCollision;
				if (Utility::getDistance(*getTransform()->getPosition(), *m_targetObject->getTransform()->getPosition()) < 150.0f
					&& m_targetObject->getGameComponent<RigidBody>()->getCollider()->checkCollision(
					*getTransform()->getPosition(), getParent()->getGameComponent<RigidBody>()->getVelocity(), timeOfCollision))
				{
					shootLaser();
				}
				Pursue(*m_targetObject, timestep);
			}
			//Evade
			else if (m_shipStats->getHealth() <= 0.4f)
			{
				getClosestObject(SHIP_CLASS::ALL_ENEMY_SHIP);
				Evade(*m_targetObject, timestep);
				m_shipStats->updateHealth(0.01f);
			}
			//Wander
			else
			{
				Evade(*m_passengerShip, timestep);
				Wander(timestep);
				m_delayAttacking -= timestep;
			}
		}
		else
		{
			Wander(timestep);
		}

		m_delayObjectSearch -= timestep;
		
		//WayPoint(timestep);
	}

	void getClosestObject(SHIP_CLASS shipType)
	{
		if (m_delayObjectSearch < 0.0f)
		{
			std::vector<GameObject*> allEnemyObject;
			float closestDistance = 999999.0f;
			std::vector<GameObject*> gameObjects;
			int counter = 1;
			if (shipType == SHIP_CLASS::ALL_ENEMY_SHIP || shipType == SHIP_CLASS::FIGHTER_SHIP)
			{
				gameObjects = getGameObjectsByName("Fighter Ship");
				for (size_t i = 0; i < gameObjects.size(); i++)
				{
					allEnemyObject.push_back(gameObjects[i]);
				}
			}
			if (shipType == SHIP_CLASS::ALL_ENEMY_SHIP || shipType == SHIP_CLASS::PASSENGER_SHIP)
			{
				gameObjects = getGameObjectsByName("passengerShip");
				for (size_t i = 0; i < gameObjects.size(); i++)
				{
					allEnemyObject.push_back(gameObjects[i]);
				}

			}

			for (size_t i = 0; i < allEnemyObject.size(); i++)
			{

				if (closestDistance > Utility::getDistance(*getTransform()->getPosition(), *allEnemyObject[i]->getTransform()->getPosition()))
				{
					closestDistance = Utility::getDistance(*getTransform()->getPosition(), *allEnemyObject[i]->getTransform()->getPosition());
					m_targetObject = allEnemyObject[i];
				}
			}
			m_delayObjectSearch = 2.0f;
		}
	}

	void shootLaser()
	{
		Material bob("enemyLaser", 10.0f, 100, Texture("laserGreen.png"));
		//Right side
		instantiate(
			(new GameObject("Laser", *getTransform()->getPosition()
			, *getTransform()->getRotation(), PxVec3(0.15f, 0.15f, 4.0f)))
			->addGameComponent(new Projectile(0.1f, AGENT::ENEMY_SIDE))
			->addGameComponent(new MeshRenderer(Mesh("Environment/cube.obj"), Material("enemyLaser")))
			->addGameComponent(new RigidBody(*getTransform()->getPosition() +
			Utility::getForward(*getTransform()->getRotation()) * 50.0f +//30.0f +
			Utility::getRight(*getTransform()->getRotation()) * 8.0f
			, *getTransform()->getRotation(), 1.0f, 0.075f, 0.075f, 2.0f, Utility::getForward(*getTransform()->getRotation()) * 200.0f))
			);
		//Left Side
		instantiate(
			(new GameObject("Laser", *getTransform()->getPosition(), *getTransform()->getRotation(), PxVec3(0.15f, 0.15f, 4.0f)))
			->addGameComponent(new Projectile(0.1f, AGENT::ENEMY_SIDE))
			->addGameComponent(new MeshRenderer(Mesh("Environment/cube.obj"), Material("enemyLaser")))
			->addGameComponent(new RigidBody(*getTransform()->getPosition() +
			Utility::getForward(*getTransform()->getRotation()) * 50.0f + //30.0f +
			Utility::getLeft(*getTransform()->getRotation()) * 10.0f
			, *getTransform()->getRotation(), 1.0f, 0.075f, 0.075f, 2.0f, Utility::getForward(*getTransform()->getRotation()) * 200.0f))
			);

		numberOfLaserShot++;
		if (numberOfLaserShot >= 3)
		{
			//5 Sec delay 
			m_delayAttacking = 5.0f;
			numberOfLaserShot = 0;
			m_targetPoint = *getTransform()->getPosition();
		}
		else
		{
			m_delayAttacking = 0.2f;
		}
	}

private:

	ShipStats* m_shipStats;
	float m_delayAttacking;
	int numberOfLaserShot;
	float m_delayObjectSearch;
	GameObject* m_passengerShip;
};

