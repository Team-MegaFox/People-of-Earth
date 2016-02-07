// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 02-07-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 02-07-2016
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

class Particle
{
public:
	/*
	
	Perhaps create a list of gameobjects and pass them in to the particle class,
	each one is now a gameObject and a particle, adding methods from particle to the game objects

	now pass the list of particles into particle system, and work the magic
	
	*/


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
		Material * material = nullptr,
		float size = 1.0f,
		float lifeTime = 3.0f) :
		m_gameObjects(gameObjects)
	{
		if (material == nullptr)
		{
			m_material = new Material("default", 0.5f, 4, Texture("defaultTexture.png"), Texture("default_normal.jpg"), Texture("default_disp.png"), 0.03f, -0.5f);
		}
		for (size_t i = 0; i < gameObjects.size(); i++)
		{
			m_gameObjects[i]->addGameComponent(new MeshRenderer(Mesh("cube.obj", size), *material));
			m_isAlive.push_back(true);
		}
	}

	/// <summary>
	/// Finalizes an instance of the <see cref="Particle"/> class.
	/// </summary>
	~Particle(){}

	/// <summary>
	/// Sets the velocity of this particle.
	/// </summary>
	/// <param name="velocity">The velocity.</param>
	inline void setVelocity(int index, glm::vec3 & velocity, glm::vec3 & acceleration, float deltaTime)
	{ 
		m_velocity = velocity; 
		glm::vec3 pos;
		pos.x = velocity.x * deltaTime + 0.5f * acceleration.x * deltaTime * deltaTime;
		pos.y = velocity.y * deltaTime + 0.5f * acceleration.y * deltaTime * deltaTime;
		pos.z = velocity.z * deltaTime + 0.5f * acceleration.z * deltaTime * deltaTime;
		m_gameObjects[index]->getTransform()->setPosition(pos);
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

};
