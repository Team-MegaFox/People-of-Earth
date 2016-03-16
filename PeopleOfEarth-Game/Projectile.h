// ***********************************************************************
// Author           : Christopher Maeda
// Created          : 02-28-2016
//
// Last Modified By : Christopher Maeda
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

struct Projectile : public GameComponent
{
	/// <summary>
	/// Initializes a new instance of the <see cref="Laser"/> class.
	/// </summary>
	Projectile() : m_lifeTime(2.0f), m_delay(0.0f), m_damageValue(0.1f) {}
	/// <summary>
	/// Finalizes an instance of the <see cref="Laser"/> class.
	/// </summary>
	~Projectile() { }

	virtual void onStart()
	{
		m_rigidBody = getParent()->getGameComponent<RigidBody>();
	}

	/// <summary>
	/// Updates this GameComponent using delta time.
	/// </summary>
	/// <param name="delta">The delta.</param>
	virtual void update(float delta) override
	{
		m_lifeTime -= delta;

		if (m_rigidBody->getCollided())
		{
			//Check collision
			std::vector<GameObject*> collidedGameObjects;
			collidedGameObjects = m_rigidBody->checkCollision(getAllFigherShipsGameObjects());
			for (size_t i = 0; i < collidedGameObjects.size(); i++)
			{
				collidedGameObjects[i]->getGameComponent<ShipStats>()->updateHealth(-m_damageValue);
				m_damageValue = 0.0f;
				m_lifeTime = -1.0f;
				break;
			}
		}
		else if (!m_rigidBody->getCollided())
		{
			if (m_delay < 0)
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
				//No collision along its path so delay this collision check by 0.25 sec
				if (m_lifeTime > 0)
				{
					m_delay = 0.5f;
				}
			}
			else
			{
				m_delay -= delta;
			}
		}
		else if (!PhysicsEngine::getPhysicsWorld()->checkInsideWorld(m_rigidBody->getCollider()))
		{
			m_lifeTime = -1.0f;
		}

		if (m_lifeTime < 0)
		{
			destroy(getParent());
		}

	}

	std::vector<GameObject*> getAllFigherShipsGameObjects()
	{
		std::vector<GameObject*> collisionCheckObject;
		std::vector<GameObject*> gameObjects;
		gameObjects = getGameObjectsByName("Fighter Ship");
		for (size_t i = 0; i < gameObjects.size(); i++)
		{
			collisionCheckObject.push_back(gameObjects[i]);
		}
		gameObjects = getGameObjectsByName("enemyFighter");
		for (size_t i = 0; i < gameObjects.size(); i++)
		{
			collisionCheckObject.push_back(gameObjects[i]);
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
};