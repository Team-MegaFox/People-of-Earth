// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 02-07-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 02-07-2016
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

/*
Add these lines to TestScene
if they are not alredy there.

std::vector<GameObject *> particlesGO;
for (size_t i = 0; i < 20; i++)
{
particlesGO.push_back(new GameObject("particle " + i));
}

Particle * theParticle = new Particle(particlesGO, &bricks, 0.1f);

ParticleSystem * particleSystem = new ParticleSystem(
*theParticle, 10.0f,
glm::vec3(0.0f, -5.0f, 80.0f),
glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
this,
SPHERICAL);

*/

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
	~ParticleSystem() {}

	/// <summary>
	/// Virtual function for custom update functionality.
	/// </summary>
	/// <param name="deltaTime">The delta time.</param>
	virtual void update(float deltaTime) override
	{
		m_particleEmitter->update(deltaTime);
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
		ParticleEmitter() {}
		/// <summary>
		/// Initializes a new instance of the <see cref="ParticleEmitter"/> class.
		/// </summary>
		/// <param name="type">The type.</param>
		ParticleEmitter(EmitterType type) :
			m_emitterType(type)	{}

		/// <summary>
		/// Finalizes an instance of the <see cref="ParticleEmitter"/> class.
		/// </summary>
		~ParticleEmitter() {}

		void init(
			Scene * scene,
			Particle particle,
			float emissionRate,
			glm::quat initialOrientation)
		{
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
			}
		}

		void update(float deltaTime)
		{
			m_counter += 0.001f;
			int counter = 0;

			// Create random values for the velocity and orientation for the particles
			std::mt19937 random((unsigned int)time(nullptr));
			std::mt19937 random2((unsigned int)time(nullptr));
			std::mt19937 random3((unsigned int)time(nullptr));
			std::uniform_real_distribution<float> randDirection(-10.0f, 10.0f);

			// Set each particles orientation and velocity
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

					FOR SPHERICAL SHAPED ENMISSIONS

					The particles simply need to pick any position in any direction 
					and move towards that point.


							ooooo
						 ooo     ooo
						ooo		  ooo
					   oo			oo
					  o				  o
					 o        *	       o	End Points 
					 o	Starting Point o
					  o				  o
					   oo			oo
						 ooo	 ooo
						  ooo   ooo  
						    ooooo

					*/

					if (m_emitterType == CONICAL)
					{
						//// do it this way
						//m_particles[i].setVelocity(glm::vec3(0.0f));
					}
					else if (m_emitterType == SPHERICAL)
					{
						// BASICALLY JUST FOR TESTING PURPOSES

						glm::vec3 acceleration = glm::vec3(randDirection(random), randDirection(random2), randDirection(random3));
						// do it this way
						m_particle.setVelocity(i, glm::vec3(randDirection(random), sinf(m_counter), randDirection(random3)), acceleration, deltaTime);
					}
				}
			}

			//// Determine if the particles are still alive
			//for (auto i = m_particle.getIsAlive().begin(); i != m_particle.getIsAlive().end(); i++)
			//{
			//	if (!i->getIsAlive())
			//	{
			//		counter++;
			//		// if it isn't alive it has to be removed
			//		m_particle.getIsAlive().erase(i);
			//	}
			//}
			//// replace particles that are no longer alive
			//for (counter; counter > 0; counter--)
			//{
			//	m_particles.emplace_back(m_particle);
			//}
			//counter = 0;
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

		float m_counter = 0.0f;
	};
};

