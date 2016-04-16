// ***********************************************************************
// Author           : Christopher Maeda & Jesse Derochie
// Created          : 02-28-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 03-11-2016
// ***********************************************************************
// <copyright file="Projectile.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
//</summary>
// ***********************************************************************

#pragma once
#include <Components\GameComponents.h>

enum AGENT{
	PLAYER_SIDE,
	ENEMY_SIDE
};

struct Projectile : public GameComponent
{
	/// <summary>
	/// Initializes a new instance of the <see cref="Laser"/> class.
	/// </summary>
	Projectile(float damageValue, AGENT agentType) : m_lifeTime(7.0f), m_delay(0.0f), m_damageValue(damageValue), m_agentType(agentType) {}
	/// <summary>
	/// Finalizes an instance of the <see cref="Laser"/> class.
	/// </summary>
	~Projectile() { }

	virtual void onStart()
	{
		m_rigidBody = getParent()->getGameComponent<RigidBody>();
	}

	void runOnce()
	{
		std::vector<GameObject*> collidableGameObjects;
		collidableGameObjects = getAllFigherShipsGameObjects();
		float m_collisionTime;
		for (size_t i = 0; i < collidableGameObjects.size(); i++)
		{
			if (collidableGameObjects[i]->getGameComponent<RigidBody>()->getCollider()->checkCollision(
				*getTransform()->getPosition(), m_rigidBody->getVelocity().getNormalized(),
				m_collisionTime)
				)
			{
				m_collisionTime /= 60.0f;
				//Within the lasers life time
				if (m_collisionTime < m_lifeTime)
				{
					collidableGameObjects[i]->getGameComponent<ShipStats>()->updateHealth(-m_damageValue);
					m_damageValue = 0.0f;
					m_lifeTime = m_collisionTime;
					m_delay = 2.0f;
					break;
				}
			}
		}
		m_velocity = m_rigidBody->getVelocity();
		getTransform()->setPosition(m_rigidBody->getPosition());
		getParent()->removeGameComponent(m_rigidBody);
	}

	/// <summary>
	/// Updates this GameComponent using delta time.
	/// </summary>
	/// <param name="delta">The delta.</param>
	virtual void update(float delta) override
	{
		PxVec3 displacement;

		m_lifeTime -= delta;

		if (onlyOnce)
		{
			runOnce();
			onlyOnce = false;
		}

		// Determine Displacement
		displacement = m_velocity * delta;

		//if (m_rigidBody->getCollided())
		//{
		//	//Check collision
		//	std::vector<GameObject*> collidedGameObjects;
		//	collidedGameObjects = m_rigidBody->checkCollision(getAllFigherShipsGameObjects());
		//	for (size_t i = 0; i < collidedGameObjects.size(); i++)
		//	{
		//		collidedGameObjects[i]->getGameComponent<ShipStats>()->updateHealth(-m_damageValue);
		//		m_damageValue = 0.0f;
		//		m_lifeTime = -1.0f;
		//		break;
		//	}
		//}
		//else if (!m_rigidBody->getCollided())
		//{
		//	if (m_delay < 0)
		//	{
		//		std::vector<GameObject*> collidableGameObjects;
		//		collidableGameObjects = getAllFigherShipsGameObjects();
		//		float m_collisionTime;
		//		for (size_t i = 0; i < collidableGameObjects.size(); i++)
		//		{
		//			if (collidableGameObjects[i]->getGameComponent<RigidBody>()->getCollider()->checkCollision(
		//				*getTransform()->getPosition(), m_rigidBody->getVelocity().getNormalized(),
		//				m_collisionTime)
		//				)
		//			{
		//				m_collisionTime /= 60.0f;
		//				//Within the lasers life time
		//				if (m_collisionTime < m_lifeTime)
		//				{
		//					collidableGameObjects[i]->getGameComponent<ShipStats>()->updateHealth(-m_damageValue);
		//					m_damageValue = 0.0f;
		//					m_lifeTime = m_collisionTime;
		//					m_delay = 2.0f;
		//					break;
		//				}
		//			}
		//		}
		//		//No collision along its path so delay this collision check by 0.25 sec
		//		if (m_lifeTime > 0)
		//		{
		//			m_delay = 0.5f;
		//		}
		//	}
		//	else
		//	{
		//		m_delay -= delta;
		//	}
		//}
		//else if (!PhysicsEngine::getPhysicsWorld()->checkInsideWorld(m_rigidBody->getCollider()))
		//{
		//	m_lifeTime = -1.0f;
		//}

		//Update the position
		getTransform()->setPosition(*getTransform()->getPosition() + displacement);

		if (m_lifeTime < 0)
		{
			destroy(getParent());
		}

	}

	std::vector<GameObject*> getAllFigherShipsGameObjects()
	{
		std::vector<GameObject*> collisionCheckObject;
		std::vector<GameObject*> gameObjects;
		if (m_agentType == ENEMY_SIDE)
		{
			gameObjects = getGameObjectsByName("player");
			for (size_t i = 0; i < gameObjects.size(); i++)
			{
				collisionCheckObject.push_back(gameObjects[i]);
			}
		}
		if (m_agentType == ENEMY_SIDE)
		{
			gameObjects = getGameObjectsByName("passengerShip");
			for (size_t i = 0; i < gameObjects.size(); i++)
			{
				collisionCheckObject.push_back(gameObjects[i]);
			}
		}
		if (m_agentType == PLAYER_SIDE)
		{
			gameObjects = getGameObjectsByName("enemyFighter");
			for (size_t i = 0; i < gameObjects.size(); i++)
			{
				collisionCheckObject.push_back(gameObjects[i]);
			}
		}
		if (m_agentType == PLAYER_SIDE)
		{
			gameObjects = getGameObjectsByName("EnemyMother");
			for (size_t i = 0; i < gameObjects.size(); i++)
			{
				collisionCheckObject.push_back(gameObjects[i]);
			}
		}
		return collisionCheckObject;
	}

private:

	/// <summary>
	/// The life time of a laser projectile
	/// </summary>
	float m_lifeTime;

	RigidBody* m_rigidBody;

	float m_delay;

	float m_damageValue;

	PxVec3 m_velocity;

	bool onlyOnce = true;

	AGENT m_agentType;
};