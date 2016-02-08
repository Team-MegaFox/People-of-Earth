// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 02-07-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 02-08-2016
// ***********************************************************************
// <copyright file="Particle.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
/*
This particle.h file is used by the particle system to create particle effects.
*/
// </summary>
// ***********************************************************************
#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>
#include "..\Rendering\Material.h"
#include "..\Components\MeshRenderer.h"
#include "..\Core\Time.h"

class Particle
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Particle"/> class.
	/// </summary>
	Particle() {}
	/// <summary>
	/// Initializes a new instance of the <see cref="Particle"/> class.
	/// </summary>
	/// <param name="gameObject">The game object.</param>
	Particle(
		std::vector<GameObject *> gameObjects, 
		glm::vec3 startPosition,
		Material * material = nullptr,
		float size = 1.0f,
		float lifeTime = 10.0f) :
		m_gameObjects(gameObjects),
		m_startPosition(startPosition),
		m_lifeTime(lifeTime)
	{
		if (material == nullptr)
		{
			m_material = new Material("default", 0.5f, 4, Texture("defaultTexture.png"), Texture("default_normal.jpg"), Texture("default_disp.png"), 0.03f, -0.5f);
		}
		for (size_t i = 0; i < gameObjects.size(); i++)
		{
			m_gameObjects[i]->addGameComponent(new MeshRenderer(Mesh("sphere.obj", size), *material));
			m_isAlive.push_back(true);
		}
	}

	/// <summary>
	/// Finalizes an instance of the <see cref="Particle"/> class.
	/// </summary>
	~Particle()
	{
		delete m_material;
	}

	/// <summary>
	/// Sets the velocity of this particle.
	/// </summary>
	/// <param name="velocity">The velocity.</param>
	inline void setVelocity(int index, glm::vec3 & velocity, glm::vec3 & acceleration, float deltaTime)
	{
		m_velocity = velocity;

		if (m_totalTime < m_lifeTime)
		{
			m_timeThisUpdate += (Time::getTime() * 0.00001);
			if (m_lastUpdate > 0)
				m_timeSinceLastUpdate = m_timeThisUpdate - m_lastUpdate;
			m_totalTime += m_timeSinceLastUpdate;
		}

		if (m_totalTime >= m_lifeTime)
		{
			//for (size_t i = 0; i < m_isAlive.size(); i++)
			//{
			//	m_isAlive[i] = false;
			//}
		}
		else
		{
			glm::vec3 currentPosition = *m_gameObjects[index]->getTransform()->getPosition();
			currentPosition.x += velocity.x * deltaTime + 0.5f * acceleration.x * deltaTime * deltaTime;
			currentPosition.y += velocity.y * deltaTime + 0.5f * acceleration.y * deltaTime * deltaTime;
			currentPosition.z += velocity.z * deltaTime + 0.5f * acceleration.z * deltaTime * deltaTime;

			glm::vec3 movedDistance = currentPosition - m_startPosition;

			float magnitude = glm::sqrt(
				(movedDistance.x * movedDistance.x) +
				(movedDistance.y * movedDistance.y) +
				(movedDistance.z * movedDistance.z));

			if (magnitude > 25.0f || magnitude < -25.0f)
			{
				currentPosition = m_startPosition;
			}
			m_gameObjects[index]->getTransform()->setPosition(currentPosition);
		}
		m_lastUpdate = m_timeThisUpdate;
	}

	/// <summary>
	/// Removes the game objects.
	/// </summary>
	/// <param name="scene">The scene.</param>
	void removeGameObjects(Scene * scene)
	{
		for (size_t i = 0; i < m_gameObjects.size(); i++)
		{
			scene->removeGameObjectByName("particle " + i);
		}
		m_gameObjects.clear();
	}

	/// <summary>
	/// Gets the is alive boolean.
	/// </summary>
	/// <returns>bool &.</returns>
	inline std::vector<bool> getIsAlive() { return m_isAlive; }

	/// <summary>
	/// Gets the game object.
	/// </summary>
	/// <returns>GameObject *.</returns>
	inline std::vector<GameObject *> getGameObjects() { return m_gameObjects; }

	/// <summary>
	/// Gets the life time.
	/// </summary>
	/// <returns>float.</returns>
	inline float getLifeTime() { return m_lifeTime; }
private:

	/// <summary>
	/// The life time of this particle
	/// </summary>
	float m_lifeTime;
	/// <summary>
	/// The m_time since last update
	/// </summary>
	double m_timeSinceLastUpdate = 0.0;
	/// <summary>
	/// The m_time this update
	/// </summary>
	double m_timeThisUpdate = 0.0;
	/// <summary>
	/// The m_last update
	/// </summary>
	double m_lastUpdate = 0.0;
	/// <summary>
	/// The m_total time
	/// </summary>
	double m_totalTime = 0.0;
	/// <summary>
	/// The direction and velocity of this particle
	/// </summary>
	glm::vec3 m_velocity;
	/// <summary>
	/// The material to use for this particle
	/// </summary>
	Material * m_material;
	/// <summary>
	/// The is alive boolean 
	/// </summary>
	std::vector<bool> m_isAlive;
	/// <summary>
	/// This particles game object
	/// </summary>
	std::vector<GameObject *> m_gameObjects;
	/// <summary>
	/// The start position of this particle
	/// </summary>
	glm::vec3 m_startPosition;

};