// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 02-07-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 02-08-2016
// ***********************************************************************
// <copyright file="ParticleSystem.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
/*
This ParticleSystem.h file is a GameComponent that is used to create
Particle Emitters for MegaEngine
*/
// </summary>
// ***********************************************************************

#pragma once
#include "Particle.h"
#include "../Components/GameComponents.h"
#include <vector>
#include <ctime>
#include <random>

enum EmitterType
{
	CONICAL,
	SPHERICAL,
	NONE
};

/// <summary>
/// The Maximum Supported Density
/// </summary>
const int MAX_DENSITY = 100;

/// <summary>
/// Class ParticleSystem.
/// </summary>
/// <seealso cref="GameComponent" />
class ParticleSystem : public GameComponent
{
	// Forward declaration required for nesting the Particleemitter class
	// inside the ParticleSystem class. 
	// See http://en.cppreference.com/w/cpp/language/nested_types for further information

	class ParticleEmitter;

public:
	/// <summary>
	/// Initializes a new instance of the <see cref="ParticleSystem"/> class.
	/// </summary>
	ParticleSystem() {}
	/// <summary>
	/// Initializes a new instance of the <see cref="ParticleSystem"/> class.
	/// </summary>
	/// <param name="particle">The particle.</param>
	/// <param name="particleDensity">The particle density if less than MAX_DENSITY(100).</param>
	/// <param name="initialPosition">The initial position.</param>
	/// <param name="initialOrientation">The initial orientation.</param>
	ParticleSystem(
		Particle particle,
		float emissionRate,
		glm::vec3 initialPosition, 
		glm::quat initialOrientation,
		Scene * scene,
		EmitterType type = NONE) :
	m_position(initialPosition)	
	{
		m_particleEmitter = new ParticleEmitter(type);
		m_particleEmitter->init(scene, particle, emissionRate, initialOrientation);
	}

	/// <summary>
	/// Finalizes an instance of the <see cref="ParticleSystem"/> class.
	/// </summary>
	~ParticleSystem() 
	{
		delete m_particleEmitter;
	}

	/// <summary>
	/// Virtual function for custom update functionality.
	/// </summary>
	/// <param name="deltaTime">The delta time.</param>
	virtual void update(float deltaTime) override
	{
		m_particleEmitter->update(deltaTime);
	}

	/// <summary>
	/// Renders the specified shader.
	/// </summary>
	/// <param name="shader">The shader.</param>
	/// <param name="renderingEngine">The rendering engine.</param>
	/// <param name="camera">The camera.</param>
	virtual void render(const Shader& shader, const RenderingEngine& renderingEngine, const Camera3D & camera) const override
	{
		m_particleEmitter->render();
	}

private:
	/// <summary>
	/// The particle emitter
	/// </summary>
	ParticleEmitter * m_particleEmitter;
	/// <summary>
	/// The position of the particle emitter
	/// </summary>
	glm::vec3 m_position;


	//Class is nested to make is so that users can not just create a Particle Emitter
	/// <summary>
	/// Class ParticleEmitter.
	/// </summary>
	class ParticleEmitter
	{
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="ParticleEmitter"/> class.
		/// </summary>
		ParticleEmitter() {	}
		/// <summary>
		/// Initializes a new instance of the <see cref="ParticleEmitter"/> class.
		/// </summary>
		/// <param name="type">The type.</param>
		ParticleEmitter(EmitterType type) :
			m_emitterType(type)	{	}

		/// <summary>
		/// Finalizes an instance of the <see cref="ParticleEmitter"/> class.
		/// </summary>
		~ParticleEmitter() {	}

		/// <summary>
		/// Initializes the specified emitter.
		/// </summary>
		/// <param name="scene">The scene.</param>
		/// <param name="particle">The particle.</param>
		/// <param name="emissionRate">The emission rate.</param>
		/// <param name="initialOrientation">The initial orientation.</param>
		void init(
			Scene * scene,
			Particle particle,
			float emissionRate,
			glm::quat initialOrientation)
		{
			m_scene = scene;
			m_particle = particle;
			m_emissionRate = emissionRate;
			m_orientation = initialOrientation;
			// Ensure there is no way the particle density
			// can accidentally be used to crash the Engine
			if (m_particle.getGameObjects().size() < MAX_DENSITY)
			{
				m_particleDensity = m_particle.getGameObjects().size();
			}
			else
			{
				m_particleDensity = MAX_DENSITY;
			}

			// Create a vector of particles that is density length
			for (size_t i = 0; i < m_particleDensity; i++)
			{
				scene->addToRoot(m_particle.getGameObjects()[i]);
				m_velocities.push_back(glm::vec3(getRandomValue(), getRandomValue(), getRandomValue()));
				m_accelerations.push_back(glm::vec3(getRandomValue(), getRandomValue(), getRandomValue()));
			}
		}

		/// <summary>
		/// Gets the random value.
		/// </summary>
		/// <returns>float.</returns>
		float getRandomValue()
		{
			float returnValue;
			static std::mt19937 random((unsigned int)time(nullptr));
			std::uniform_real_distribution<float> randDirection(-1.0f, 1.0f);

			returnValue = randDirection(random);

			return returnValue;
		}

		/// <summary>
		/// Updates the specified delta time.
		/// </summary>
		/// <param name="deltaTime">The delta time.</param>
		void update(float deltaTime)
		{
			for (size_t i = 0; i < m_particle.getGameObjects().size(); i++)
			{
				if (m_particle.getIsAlive()[i])
				{
					/*
					
					Here I need to create the logic for creating a cone shaped emission
					allowing me to set the orientation and the velocity of each individual particle.
					
					Also need to update these particles based on the type of emission that was chosen by the user
							
					FOR CONE SHAPED EMISSIONS

					Circular Circumference where particles should move towards
					There are 360 points on that circumference the particles 
					could choose from to move to

							End Points
							_______
						   (_______)
					        \      /
							 \    /
							  \  /
						       \/
							    * Starting point of the particles

					*/

					if (m_emitterType == CONICAL)
					{
						//// do something here
					}
					else if (m_emitterType == SPHERICAL)
					{
						m_particle.setVelocity(i, m_velocities[i], m_accelerations[i], deltaTime);
					}
				}
				else
				{
					//m_particle.removeGameObjects(m_scene);
				}
			}
		}

		/// <summary>
		/// Renders this instance.
		/// </summary>
		void render()
		{
			// do stuff
		
		}

	protected:
		/// <summary>
		/// The emitter type
		/// </summary>
		EmitterType m_emitterType;
		/// <summary>
		/// The particle type
		/// </summary>
		Particle m_particle;
		/// <summary>
		/// The particle density (maximum number of particles)
		/// </summary>
		int m_particleDensity;
		/// <summary>
		/// The emission rate of the particles
		/// </summary>
		float m_emissionRate;
		/// <summary>
		/// The orientation of the particle emitter
		/// </summary>
		glm::quat m_orientation;
		/// <summary>
		/// The m_accelerations
		/// </summary>
		std::vector<glm::vec3> m_accelerations;
		/// <summary>
		/// The m_velocities
		/// </summary>
		std::vector<glm::vec3> m_velocities;
		/// <summary>
		/// The m_scene
		/// </summary>
		Scene * m_scene;
	};
};

