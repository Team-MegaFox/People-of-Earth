// ***********************************************************************
// Author           : Pavan Jakhu & Jesse Derochie
// Created          : 03-02-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 04-02-2016
// ***********************************************************************
// <copyright file="ParticleSystem.cpp" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
// </summary>
// ***********************************************************************

#include "ParticleSystem.h"
#include <glew\glew.h>
#include <algorithm>
#include <functional>
#include <chrono>
#include <random>
#include "..\Core\CoreEngine.h"
#include "Camera3D.h"
#include "RenderingEngine.h"

// Particle Emitter Methods

ParticleEmitter::ParticleEmitter(bool updateEmitter /*= true*/, float initalSpeed /*= 10.0f*/, int maxParticles /*= 10000*/, float spawnRate /*= 5.0f*/, float lifeTime /*= 5.0f*/) :
m_updateEmitter(updateEmitter), m_initalSpeed(initalSpeed), m_maxParticles(maxParticles), m_spawnRate(spawnRate), m_lifeTime(lifeTime)
{
	m_particles.resize(maxParticles, Particle());
	m_positionData.resize(maxParticles);
	m_colourData.resize(maxParticles);

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);
	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

	static const GLfloat g_vertex_buffer_data[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[BILLBOARD_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, m_positionData.size() * sizeof(m_positionData[0]), NULL, GL_STREAM_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[COLOUR_VB]);
	glBufferData(GL_ARRAY_BUFFER, m_colourData.size() * sizeof(m_colourData[0]), NULL, GL_STREAM_DRAW);
}

ParticleEmitter::~ParticleEmitter()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void ParticleEmitter::update(float deltaTime)
{
	if (m_updateEmitter)
	{
		updateParticles(deltaTime);

		m_particleCount = 0;
		for (size_t i = 0; i < m_particles.size(); i++)
		{
			//m_positionData[i] = glm::vec4(0.0f);
			//m_colourData[i] = glm::vec4(0.0f);
			Particle* p = &m_particles[i];

			if (p->life > 0.0f)
			{
				// Decrease life
				p->life -= deltaTime;
				if (p->life > 0.0f)
				{
					// Simulate simple physics : gravity only, no collisions
					//p->speed += glm::vec3(0.0f, 0.0f, 0.0f) * deltaTime * 0.5f;
					p->pos += p->speed * deltaTime;
					//p->cameraDistance = glm::length2(p->pos - CameraPosition);
					//ParticlesContainer[i].pos += glm::vec3(0.0f,10.0f, 0.0f) * (float)delta;

					m_positionData[i] = PxVec4(p->pos, p->size);
					m_colourData[i] = p->colour;
				}

				m_particleCount++;

			}
		}

		m_updateEmitter = false;
	}
}

void ParticleEmitter::render(const Camera3D & camera)
{
	//glDepthMask(GL_FALSE);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_updateEmitter = true;

	for (size_t i = 0; i < m_particles.size(); i++)
	{
		Particle* p = &m_particles[i];

		if (p->life >= 0.0f)
		{
			p->cameraDistance = (p->pos - camera.getTransform().getPosition()).magnitudeSquared();
		}
		else
		{
			p->cameraDistance = -1.0f;
		}
	}
	sortParticles();

	glBindVertexArray(m_vertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, m_positionData.size() * sizeof(m_positionData[0]), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_particleCount * sizeof(m_positionData[0]), &m_positionData[0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[COLOUR_VB]);
	glBufferData(GL_ARRAY_BUFFER, m_colourData.size() * sizeof(m_colourData[0]), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_particleCount * sizeof(m_colourData[0]), &m_colourData[0]);

	//The actually rendering
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[BILLBOARD_VB]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// 2nd attribute buffer : positions of particles' centers
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	// 3rd attribute buffer : particles' colors
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[COLOUR_VB]);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, 0);

	// These functions are specific to glDrawArrays*Instanced*.
	// The first parameter is the attribute buffer we're talking about.
	// The second parameter is the "rate at which generic vertex attributes advance when rendering multiple instances"
	// http://www.opengl.org/sdk/docs/man/xhtml/glVertexAttribDivisor.xml
	glVertexAttribDivisor(0, 0); // particles vertices : always reuse the same 4 vertices -> 0
	glVertexAttribDivisor(1, 1); // positions : one per quad (its center)                 -> 1
	glVertexAttribDivisor(2, 1); // color : one per quad                                  -> 1

	// Draw the particles !
	// This draws many times a small triangle_strip (which looks like a quad).
	// This is equivalent to :
	// for(i in ParticlesCount) : glDrawArrays(GL_TRIANGLE_STRIP, 0, 4), 
	// but faster.
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, m_particleCount);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	//glDepthMask(GL_TRUE);
	//glBlendFunc(GL_ONE, GL_ONE);
	//glDisable(GL_BLEND);
}

int ParticleEmitter::findUnusedParticle()
{
	for (size_t i = m_lastUsedParticle; i < m_particles.size(); i++)
	{
		if (m_particles[i].life <= 0.0f)
		{
			m_lastUsedParticle = i;
			return i;
		}
	}

	for (int i = 0; i < m_lastUsedParticle; i++)
	{
		if (m_particles[i].life <= 0.0f)
		{
			m_lastUsedParticle = i;
			return i;
		}
	}

	return 0;
}

void ParticleEmitter::sortParticles()
{
	std::sort(&m_particles[0], &m_particles[m_particles.size() - 1]);
}


// Ambient Emitter Constructors and Methods

AmbientEmitter::AmbientEmitter(float lifeTime, float initalSpeed /*= 0.0f*/, int maxParticles /*= 10000.0f*/, float spawnRate /*= 5.0f*/) :
ParticleEmitter(true, initalSpeed, maxParticles, spawnRate, lifeTime)
{
}

AmbientEmitter::~AmbientEmitter()
{	
}

void AmbientEmitter::updateParticles(float deltaTime)
{
	for (int i = 0; i < (int)(deltaTime * 100.0); i++)
	{
		int particleIndex = findUnusedParticle();
		m_particles[particleIndex].life = (float)m_lifeTime;

		//TODO: Should supply a value for density here from the constructor

		PxVec3 randomPos(
			(rand() % 10000 - 5000) / 10.0f,
			(rand() % 10000 - 5000) / 10.0f,
			(rand() % 10000 - 5000) / 10.0f
			);

		m_particles[particleIndex].pos = randomPos;

		float spread = 1.5f;
		PxVec3 maindir(0.0f, 0.0f, 0.0f);
		PxVec3 randomdir(
			(rand() % 2000 - 1000.0f) / 1000.0f,
			(rand() % 2000 - 1000.0f) / 1000.0f,
			(rand() % 2000 - 1000.0f) / 1000.0f
			);

		m_particles[particleIndex].speed = maindir + randomdir * spread * m_initalSpeed;

		m_particles[particleIndex].size = ((((rand() % ((int)(0.9f * 2000.0f))) / 2000.0f) + 0.1f) * 100.0f);

	}
}


// Explosion Emitter Constructors and Methods

ExplosionEmitter::ExplosionEmitter(float lifeTime, float initalSpeed /*= 100.0f*/, int maxParticles /*= 10000.0f*/, float spawnRate /*= 5.0f*/) :
ParticleEmitter(true, initalSpeed, maxParticles, spawnRate, lifeTime)
{
}

ExplosionEmitter::~ExplosionEmitter()
{
}

void ExplosionEmitter::updateParticles(float deltaTime)
{
	if (!m_runOnce)
	{
		if (m_timesThrough >= 250.0f)
		{
			m_runOnce = true;
		}

		for (int i = 0; i < (int)(deltaTime * m_spawnRate); i++)
		{
			int particleIndex = findUnusedParticle();
			m_particles[particleIndex].life = m_lifeTime;
			m_particles[particleIndex].pos = PxVec3(0.0f, 0.0f, 0.0f);

			float spread = 1.5f;
			PxVec3 randomdir(
				(rand() % 2000 - 1000.0f) / 1000.0f,
				(rand() % 2000 - 1000.0f) / 1000.0f,
				(rand() % 2000 - 1000.0f) / 1000.0f
				);

			m_particles[particleIndex].speed = randomdir * spread * m_initalSpeed;

			m_particles[particleIndex].size = (rand() % ((int)(0.9f * 2000.0f))) / 2000.0f + 0.1f;

		}
	}
	m_timesThrough++;
}


// Fountain Emitter Constructors and Methods

FountainEmitter::FountainEmitter(float lifeTime, float initalSpeed /*= 10.0f*/, int maxParticles /*= 10000.0f*/, float spawnRate /*= 5.0f*/) :
ParticleEmitter(true, initalSpeed, maxParticles, spawnRate, lifeTime)
{
}

FountainEmitter::~FountainEmitter()
{
}

void FountainEmitter::updateParticles(float deltaTime)
{
	int newparticles = (int)(deltaTime * m_spawnRate);

	for (int i = 0; i < newparticles; i++)
	{
		int particleIndex = findUnusedParticle();
		m_particles[particleIndex].life = m_lifeTime;
		m_particles[particleIndex].pos = PxVec3(0.0f, 0.0f, 0.0f);

		float spread = 1.5f;
		PxVec3 maindir(0.0f, 0.0f, -10.0f);
		PxVec3 randomdir(
			(rand() % 2000 - 1000.0f) / 1000.0f,
			(rand() % 2000 - 1000.0f) / 1000.0f,
			(rand() % 2000 - 1000.0f) / 1000.0f
			);

		m_particles[particleIndex].speed = maindir + randomdir * spread * m_initalSpeed;

	}
}


// Cone Emitter Constructors and Methods

ConeEmitter::ConeEmitter(float lifeTime, float initalSpeed /*= 10.0f*/, float angle /*= glm::radians(25.0f)*/, float radius /*= 1.0f*/, int maxParticles /*= 10000.0f*/, float spawnRate /*= 5.0f*/) :
ParticleEmitter(true, initalSpeed, maxParticles, spawnRate, lifeTime), m_angle(angle), m_radius(radius)
{
}

ConeEmitter::~ConeEmitter()
{
}

void ConeEmitter::updateParticles(float deltaTime)
{
	for (int i = 0; i < (int)(deltaTime * m_spawnRate); i++)
	{
		int particleIndex = findUnusedParticle();
		m_particles[particleIndex].life = m_lifeTime;

		// pick a random location inside the base circle
		auto angleRand = std::bind(std::uniform_real_distribution<float>(0.0f, PxHalfPi),
			std::mt19937((unsigned int)std::chrono::high_resolution_clock::now().time_since_epoch().count()));
		auto radiusRand = std::bind(std::uniform_real_distribution<float>(0.0f, 1.0f),
			std::mt19937((unsigned int)std::chrono::high_resolution_clock::now().time_since_epoch().count()));
		float randomAngle = angleRand();
		m_particles[particleIndex].pos = PxVec3(radiusRand() * m_radius * cosf(randomAngle), 0.0f, radiusRand() * m_radius * sinf(randomAngle));

		//MATH HELP
		float angleToRotate = PxAcos(PxVec3(1.0f, 0.0f, 0.0f).dot(m_particles[particleIndex].pos) / (PxVec3(1.0f, 0.0f, 0.0f).magnitude() * m_particles[particleIndex].pos.magnitude()));
		if ((m_particles[particleIndex].pos.x > 0.0f && m_particles[particleIndex].pos.z > 0.0f) || 
			(m_particles[particleIndex].pos.x < 0.0f && m_particles[particleIndex].pos.z > 0.0f))
		{
			angleToRotate = ToRadians(360.0f) - angleToRotate;
		}
		float distance = m_particles[particleIndex].pos.magnitude() / m_radius;
		PxVec3 initDirection = (PxVec3(PxSin(distance * m_angle), PxCos(distance * m_angle), 0.0f)).getNormalized();
		PxVec3 direction = PxQuat(angleToRotate, PxVec3(0.0f, 1.0f, 0.0f)).rotate(initDirection);

		m_particles[particleIndex].speed = direction * m_initalSpeed;

		m_particles[particleIndex].size = 1.0f/*(rand() % 1000) / 2000.0f + 0.1f*/;

	}
}

//Particle System Constructors and Methods

ParticleSystem::ParticleSystem(
	Material material, 
	EmitterType eType/* = EmitterType::AMBIENT */,
	float initalSpeed/* = 0.0f*/,
	float lifeTime/* = 4.0f*/, 
	float spawnRate /*= 5.0f*/, 
	int maxParticles /*= 10000.0f*/) :
m_particleMat(material),
m_emitterType(eType)
{
	switch (eType)
	{
	case AMBIENT:
		m_particleEmitter = new AmbientEmitter(lifeTime, initalSpeed, maxParticles, spawnRate);
		break;
	case EXPLOSION:
		m_particleEmitter = new ExplosionEmitter(lifeTime, initalSpeed, maxParticles, spawnRate);
		break;
	case FOUNTAIN:
		m_particleEmitter = new FountainEmitter(lifeTime, initalSpeed, maxParticles, spawnRate);
		break;
	default:
		throw "ParticleSystem instantiation with wrong constructor.\nAmbient Emitter, Explosion emitter or Fountain Emitter only.\n";
		break;
	}
}

ParticleSystem::ParticleSystem(
	Material material, 
	float initalSpeed /*= 0.0f*/,
	float angle /*= glm::radians(25.0f)*/, 
	EmitterType eType /*= EmitterType::CONE*/, 
	float radius /*= 1.0f*/, 
	float lifeTime /*= 1.0f*/, 
	float spawnRate /*= 10.0f*/, 
	int maxParticles /*= 10000.0f*/) :
m_particleMat(material),
m_emitterType(eType)
{
	switch (eType)
	{
	case CONE:
		m_particleEmitter = new ConeEmitter(lifeTime, initalSpeed, angle, radius, maxParticles, spawnRate);
		break;
	default:
		throw "ParticleSystem instantiation with wrong constructor.\nCone Emitter.\n";
		break;
	}
}

ParticleSystem::~ParticleSystem()
{
	delete m_particleEmitter;
}

void ParticleSystem::update(float delta)
{
	m_particleEmitter->update(delta);
}

void ParticleSystem::renderParticles(const Shader& shader, const RenderingEngine& renderingEngine, const Camera3D & camera) const
{
	//shader.bind();
	//shader.updateUniforms(getTransform(), m_particleMat, renderingEngine, camera);
	shader.bind();
	shader.updateUniforms(getTransform(), m_particleMat, renderingEngine, camera);
	m_particleEmitter->render(camera);
}

void ParticleSystem::addToEngine(CoreEngine* engine) const
{
	engine->getRenderingEngine()->addParticleSystem(*this);
}