// ***********************************************************************
// Author           : Pavan Jakhu, Jesse Derochie and Christopher Maeda
// Created          : 02-18-2015
//
// Last Modified By : Christopher Maeda
// Last Modified On : 02-25-2016
// ***********************************************************************
// <copyright file="FireProjectile.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
//</summary>
// ***********************************************************************

#pragma once
#include <Components\GameComponents.h>
#include <Components\Audio.h>
#include <Components\MeshRenderer.h>
#include "ShipStats.h"

struct Projectile : public GameComponent
{
	/// <summary>
	/// Initializes a new instance of the <see cref="Laser"/> class.
	/// </summary>
	Projectile() : m_lifeTime(2.0f) {}
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
			std::vector<GameObject*> collisionCheckObject;
			GameObject* gameObject;
			int counter = 1;
			//Add all the fighter ship
			do
			{
				gameObject = getGameObjectByName("Fighter Ship" + std::to_string(counter));
				if (gameObject != nullptr)
				{
					//collisionCheckObject.push_back(gameObject);
				}
				counter++;
			} while (gameObject != nullptr);
			counter = 1;
			//Add all the enemy fighter ship
			do
			{
				gameObject = getGameObjectByName("enemyFighter" + std::to_string(counter));
				if (gameObject != nullptr)
				{
					collisionCheckObject.push_back(gameObject);
				}
				counter++;
			} while (gameObject != nullptr);

			//Check collision
			std::vector<GameObject*> collidedGameObjects;
			collidedGameObjects = m_rigidBody->checkCollision(collisionCheckObject);
			for (size_t i = 0; i < collidedGameObjects.size(); i++)
			{
				//collidedGameObjects[i]->getGameComponent<ShipStats>()->updateHealth(-20);
				printf("Collided with ship\n");
			}
			if (collidedGameObjects.size() > 0)
			{
				destroy(getParent());
			}
		}
		else if (m_lifeTime < 0)
		{
			destroy(getParent());
		}

		
	}

private:

	/// <summary>
	/// The life time of a laser projectile
	/// </summary>
	float m_lifeTime;

	RigidBody* m_rigidBody;
};

class FireProjectile : public GameComponent
{

public:

	/// <summary>
	/// Initializes a new instance of the <see cref="FireProjectile"/> class.
	/// </summary>
	FireProjectile() { }
	/// <summary>
	/// Finalizes an instance of the <see cref="FireProjectile"/> class.
	/// </summary>
	~FireProjectile() { }

	virtual void onStart() override
	{
		//m_audioComponent = getParent()->getGameComponent<Audio>();
		//m_audioComponent = new Audio("268168__shaun105__laser.wav", AudioType::SOUND);
	}

	/// <summary>
	/// Processes the input.
	/// </summary>
	/// <param name="input">The input.</param>
	/// <param name="delta">The delta.</param>
	virtual void processInput(const InputManager& input, float delta)
	{
		if (m_delay >= 0.2f)
		{
			
			m_audioComponent = nullptr;
			delete m_audioComponent;

			if (input.GetRightTrigger() != 0)
			{
				m_audioComponent = new Audio("268168__shaun105__laser.wav", AudioType::SOUND);

				instantiate(
					(new GameObject("Laser", *getTransform()->getPosition(), *getTransform()->getRotation(), glm::vec3(0.15f, 0.15f, 4.0f)))
					->addGameComponent(new Projectile)
					->addGameComponent(new MeshRenderer(Mesh("Environment/cube.obj"), Material("plan1")))
					->addGameComponent(new RigidBody(*getTransform()->getPosition(), *getTransform()->getRotation(), 1.0f, 0.075f, 0.075f, 2.0f, Utility::getForward(*getTransform()->getRotation()) * 100.0f))
					->addGameComponent(std::move(m_audioComponent))
					);

				m_audioComponent->play(true);

				m_delay = 0.0f;
			}
			if (input.GetLeftTrigger() != 0)
			{

				m_audioComponent = new Audio("268168__shaun105__laser.wav", AudioType::SOUND);

				instantiate(
					(new GameObject("Laser", *getTransform()->getPosition(), *getTransform()->getRotation(), glm::vec3(0.15f, 0.15f, 4.0f)))
					->addGameComponent(new Projectile)
					->addGameComponent(new MeshRenderer(Mesh("Environment/cube.obj"), Material("plan1")))
					->addGameComponent(new RigidBody(*getTransform()->getPosition(), *getTransform()->getRotation(), 1.0f, 0.075f, 0.075f, 2.0f, Utility::getForward(*getTransform()->getRotation()) * 100.0f))
					->addGameComponent(std::move(m_audioComponent))
					);

				m_audioComponent->play(true);

				m_delay = 0.0f;
			}


		}
		else
		{
			m_delay += delta;
		}
	}

private:
	/// <summary>
	/// The delay between shots
	/// </summary>
	float m_delay = 0.2f;
	Audio * m_audioComponent;
};