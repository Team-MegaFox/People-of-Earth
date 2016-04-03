#include "ParticleSystem.h"
#include <glew\glew.h>
#include <glm\gtx\norm.hpp>
#include <algorithm>
#include <random>
#include "..\Core\CoreEngine.h"
#include "Camera3D.h"
#include "RenderingEngine.h"

// Ambient Emitter

AmbientEmitter::AmbientEmitter(glm::vec4 & colour, float lifeTime, int maxParticles /*= 10000.0f*/, float spawnRate /*= 5.0f*/)
{
	m_maxParticles = maxParticles;
	m_spawnRate = spawnRate;
	m_updateEmitter = true;
	m_colour = colour;
	m_lifeTime = lifeTime;

	m_particles.resize(m_maxParticles, Particle());
	m_positionData.resize(m_maxParticles);
	m_colourData.resize(m_maxParticles);

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
	std::cout << sizeof(g_vertex_buffer_data) << std::endl;

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, m_positionData.size() * sizeof(m_positionData[0]), NULL, GL_STREAM_DRAW);
	std::cout << m_positionData.size() * sizeof(m_positionData[0]) << std::endl;

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[COLOUR_VB]);
	glBufferData(GL_ARRAY_BUFFER, m_colourData.size() * sizeof(m_colourData[0]), NULL, GL_STREAM_DRAW);
	std::cout << m_colourData.size() * sizeof(m_colourData[0]) << std::endl;
}

AmbientEmitter::~AmbientEmitter()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void AmbientEmitter::update(float deltaTime)
{
	if (m_updateEmitter)
	{
		int newparticles = (int)(deltaTime * 100.0);

		for (int i = 0; i < newparticles; i++)
		{
			int particleIndex = findUnusedParticle();
			m_particles[particleIndex].life = m_lifeTime;

			glm::vec3 randomPos = glm::vec3(
				(rand() % 20000 - 10000.0f) / 10.0f,
				(rand() % 20000 - 10000.0f) / 10.0f,
				(rand() % 20000 - 10000.0f) / 10.0f
				);

			m_particles[particleIndex].pos = randomPos;

			float spread = 1.5f;
			glm::vec3 maindir = glm::vec3(0.0f, 0.0f, 0.0f);
			glm::vec3 randomdir = glm::vec3(
				(rand() % 2000 - 1000.0f) / 1000.0f,
				(rand() % 2000 - 1000.0f) / 1000.0f,
				(rand() % 2000 - 1000.0f) / 1000.0f
				);

			m_particles[particleIndex].speed = maindir + randomdir*spread;

			//if (m_colour.w == 0.0f)
			//{
			//	// Very bad way to generate a random color
			//	m_particles[particleIndex].colour.r = 1.0f/*(float)(rand() % 256)*/;
			//	m_particles[particleIndex].colour.g = 1.0f/*(float)(rand() % 256)*/;
			//	m_particles[particleIndex].colour.b = 1.0f/*(float)(rand() % 256)*/;
			//	m_particles[particleIndex].colour.a = 1.0f/*(rand() % 256) / 3.0f*/;

			//	m_particles[particleIndex].size = 1.0f/*(rand() % 1000) / 2000.0f + 0.1f*/;
			//}
			//else
			//{
			//	m_particles[particleIndex].colour = m_colour;
			//}

		}

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
					p->speed += glm::vec3(0.0f, 0.0f, 0.0f) * deltaTime * 0.5f;
					p->pos += p->speed * deltaTime;
					//p->cameraDistance = glm::length2(p->pos - CameraPosition);
					//ParticlesContainer[i].pos += glm::vec3(0.0f,10.0f, 0.0f) * (float)delta;

					m_positionData[i] = glm::vec4(p->pos, p->size);
					m_colourData[i] = p->colour;
				}

				m_particleCount++;

			}
		}

		m_updateEmitter = false;
	}
}

void AmbientEmitter::render(const Camera3D & camera)
{
	//glDepthMask(GL_FALSE);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_updateEmitter = true;

	for (size_t i = 0; i < m_particles.size(); i++)
	{
		Particle* p = &m_particles[i];

		if (p->life > 0.0f)
		{
			p->cameraDistance = glm::length2(p->pos - camera.getTransform().getPosition());
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

int AmbientEmitter::findUnusedParticle()
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

void AmbientEmitter::sortParticles()
{
	std::sort(&m_particles[0], &m_particles[m_particles.size() - 1]);
}


// Explosion Emitter

ExplosionEmitter::ExplosionEmitter(glm::vec4 & colour, float lifeTime, int maxParticles /*= 10000.0f*/, float spawnRate /*= 5.0f*/)
{
	m_maxParticles = maxParticles;
	m_spawnRate = spawnRate;
	m_updateEmitter = true;
	m_colour = colour;
	m_lifeTime = lifeTime;

	m_particles.resize(m_maxParticles, Particle());
	m_positionData.resize(m_maxParticles);
	m_colourData.resize(m_maxParticles);

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
	std::cout << sizeof(g_vertex_buffer_data) << std::endl;

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, m_positionData.size() * sizeof(m_positionData[0]), NULL, GL_STREAM_DRAW);
	std::cout << m_positionData.size() * sizeof(m_positionData[0]) << std::endl;

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[COLOUR_VB]);
	glBufferData(GL_ARRAY_BUFFER, m_colourData.size() * sizeof(m_colourData[0]), NULL, GL_STREAM_DRAW);
	std::cout << m_colourData.size() * sizeof(m_colourData[0]) << std::endl;
}

ExplosionEmitter::~ExplosionEmitter()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void ExplosionEmitter::update(float deltaTime)
{
	if (m_updateEmitter)
	{
		if (!m_runOnce)
		{
			if (m_timesThrough >= 250.0f)
			{
				m_runOnce = true;
			}

			for (int i = 0; i < (int)(deltaTime * 100.0); i++)
			{
				int particleIndex = findUnusedParticle();
				m_particles[particleIndex].life = m_lifeTime;
				m_particles[particleIndex].pos = glm::vec3(0.0f, 0.0f, 0.0f);

				float spread = 1.5f;
				glm::vec3 randomdir = glm::vec3(
					(rand() % 2000 - 1000.0f) / 1000.0f,
					(rand() % 2000 - 1000.0f) / 1000.0f,
					(rand() % 2000 - 1000.0f) / 1000.0f
					);

				m_particles[particleIndex].speed = randomdir * spread;

				//if (m_colour.w == 0.0f)
				//{
				//	// Very bad way to generate a random color
				//	m_particles[particleIndex].colour.r = 1.0f/*(float)(rand() % 256)*/;
				//	m_particles[particleIndex].colour.g = 1.0f/*(float)(rand() % 256)*/;
				//	m_particles[particleIndex].colour.b = 1.0f/*(float)(rand() % 256)*/;
				//	m_particles[particleIndex].colour.a = 1.0f/*(rand() % 256) / 3.0f*/;

				//	m_particles[particleIndex].size = 1.0f/*(rand() % 1000) / 2000.0f + 0.1f*/;
				//}
				//else
				//{
				//	m_particles[particleIndex].colour = m_colour;
				//}

				m_particles[particleIndex].size = 1.0f/*(rand() % 1000) / 2000.0f + 0.1f*/;

			}
		}

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
					p->speed += glm::vec3(0.0f, 0.0f, 0.0f) * deltaTime * 0.5f;
					p->pos += p->speed * 5.0f * deltaTime;
					//p->cameraDistance = glm::length2(p->pos - CameraPosition);
					//ParticlesContainer[i].pos += glm::vec3(0.0f,10.0f, 0.0f) * (float)delta;

					m_positionData[i] = glm::vec4(p->pos, p->size);
					m_colourData[i] = p->colour;
				}

				m_particleCount++;

			}
		}

		m_updateEmitter = false;
	}
	m_timesThrough++;
}

void ExplosionEmitter::render(const Camera3D & camera)
{
	//glDepthMask(GL_FALSE);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_updateEmitter = true;

	for (size_t i = 0; i < m_particles.size(); i++)
	{
		Particle* p = &m_particles[i];

		if (p->life > 0.0f)
		{
			p->cameraDistance = glm::length2(p->pos - camera.getTransform().getPosition());
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

int ExplosionEmitter::findUnusedParticle()
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

void ExplosionEmitter::sortParticles()
{
	std::sort(&m_particles[0], &m_particles[m_particles.size() - 1]);
}


// Fountain Emitter

FountainEmitter::FountainEmitter(glm::vec4 & colour, float lifeTime, int maxParticles /*= 10000.0f*/, float spawnRate /*= 5.0f*/)
{
	m_maxParticles = maxParticles;
	m_spawnRate = spawnRate;
	m_updateEmitter = true;
	m_colour = colour;
	m_lifeTime = lifeTime;

	m_particles.resize(m_maxParticles, Particle());
	m_positionData.resize(m_maxParticles);
	m_colourData.resize(m_maxParticles);

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
	std::cout << sizeof(g_vertex_buffer_data) << std::endl;

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, m_positionData.size() * sizeof(m_positionData[0]), NULL, GL_STREAM_DRAW);
	std::cout << m_positionData.size() * sizeof(m_positionData[0]) << std::endl;

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[COLOUR_VB]);
	glBufferData(GL_ARRAY_BUFFER, m_colourData.size() * sizeof(m_colourData[0]), NULL, GL_STREAM_DRAW);
	std::cout << m_colourData.size() * sizeof(m_colourData[0]) << std::endl;
}

FountainEmitter::~FountainEmitter()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void FountainEmitter::update(float deltaTime)
{
	if (m_updateEmitter)
	{
		int newparticles = (int)(deltaTime * 100.0);

		for (int i = 0; i < newparticles; i++)
		{
			int particleIndex = findUnusedParticle();
			m_particles[particleIndex].life = m_lifeTime;
			m_particles[particleIndex].pos = glm::vec3(0.0f, 0.0f, 0.0f);

			float spread = 1.5f;
			glm::vec3 maindir = glm::vec3(0.0f, 0.0f, -10.0f);
			glm::vec3 randomdir = glm::vec3(
				(rand() % 2000 - 1000.0f) / 1000.0f,
				(rand() % 2000 - 1000.0f) / 1000.0f,
				(rand() % 2000 - 1000.0f) / 1000.0f
				);

			m_particles[particleIndex].speed = maindir + randomdir*spread;

			//if (m_colour.w == 0.0f)
			//{
			//	// Very bad way to generate a random color
			//	m_particles[particleIndex].colour.r = 1.0f/*(float)(rand() % 256)*/;
			//	m_particles[particleIndex].colour.g = 1.0f/*(float)(rand() % 256)*/;
			//	m_particles[particleIndex].colour.b = 1.0f/*(float)(rand() % 256)*/;
			//	m_particles[particleIndex].colour.a = 1.0f/*(rand() % 256) / 3.0f*/;

			//	m_particles[particleIndex].size = 1.0f/*(rand() % 1000) / 2000.0f + 0.1f*/;
			//}
			//else
			//{
			//	m_particles[particleIndex].colour = m_colour;
			//}

		}

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
					p->speed += glm::vec3(0.0f, 0.0f, 0.0f) * deltaTime * 0.5f;
					p->pos += p->speed * deltaTime;
					//p->cameraDistance = glm::length2(p->pos - CameraPosition);
					//ParticlesContainer[i].pos += glm::vec3(0.0f,10.0f, 0.0f) * (float)delta;

					m_positionData[i] = glm::vec4(p->pos, p->size);
					m_colourData[i] = p->colour;
				}

				m_particleCount++;

			}
		}

		m_updateEmitter = false;
	}
}

void FountainEmitter::render(const Camera3D & camera)
{
	//glDepthMask(GL_FALSE);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_updateEmitter = true;

	for (size_t i = 0; i < m_particles.size(); i++)
	{
		Particle* p = &m_particles[i];

		if (p->life > 0.0f)
		{
			p->cameraDistance = glm::length2(p->pos - camera.getTransform().getPosition());
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

int FountainEmitter::findUnusedParticle()
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

void FountainEmitter::sortParticles()
{
	std::sort(&m_particles[0], &m_particles[m_particles.size() - 1]);
}


// Cone Emitter

ConeEmitter::ConeEmitter(glm::vec3 & endPoint, glm::vec4 & colour, float radius, float lifeTime, int maxParticles /*= 10000.0f*/, float spawnRate /*= 5.0f*/)
{
	m_maxParticles = maxParticles;
	m_spawnRate = spawnRate;
	m_updateEmitter = true;
	m_colour = colour;
	m_lifeTime = lifeTime;
	m_radius = radius;
	m_endPoint = endPoint;

	m_particles.resize(m_maxParticles, Particle());
	m_positionData.resize(m_maxParticles);
	m_colourData.resize(m_maxParticles);

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
	std::cout << sizeof(g_vertex_buffer_data) << std::endl;

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, m_positionData.size() * sizeof(m_positionData[0]), NULL, GL_STREAM_DRAW);
	std::cout << m_positionData.size() * sizeof(m_positionData[0]) << std::endl;

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[COLOUR_VB]);
	glBufferData(GL_ARRAY_BUFFER, m_colourData.size() * sizeof(m_colourData[0]), NULL, GL_STREAM_DRAW);
	std::cout << m_colourData.size() * sizeof(m_colourData[0]) << std::endl;
}

ConeEmitter::~ConeEmitter()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void ConeEmitter::update(float deltaTime)
{
	if (m_updateEmitter)
	{
		int newparticles = 360;

		for (int i = 0; i < newparticles; i++)
		{
			int particleIndex = findUnusedParticle();
			m_particles[particleIndex].life = m_lifeTime;

			// pick a location along the circumference of a circle
			m_particles[particleIndex].pos = glm::vec3(m_radius * cos(i), m_radius * sin(i), 0.0f);

			// move towards the cone's end point
			glm::vec3 direction = m_endPoint - m_particles[particleIndex].pos;

			m_particles[particleIndex].speed = direction;

			//if (m_colour.w == 0.0f)
			//{
			//	// Very bad way to generate a random color
			//	m_particles[particleIndex].colour.r = 1.0f/*(float)(rand() % 256)*/;
			//	m_particles[particleIndex].colour.g = 1.0f/*(float)(rand() % 256)*/;
			//	m_particles[particleIndex].colour.b = 1.0f/*(float)(rand() % 256)*/;
			//	m_particles[particleIndex].colour.a = 1.0f/*(rand() % 256) / 3.0f*/;

			//	m_particles[particleIndex].size = 1.0f/*(rand() % 1000) / 2000.0f + 0.1f*/;
			//}
			//else
			//{
			//	m_particles[particleIndex].colour = m_colour;
			//}

			m_particles[particleIndex].size = 1.0f/*(rand() % 1000) / 2000.0f + 0.1f*/;

		}

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
					p->speed += glm::vec3(0.0f, 0.0f, 0.0f) * deltaTime * 0.5f;
					p->pos += p->speed * deltaTime;
					//p->cameraDistance = glm::length2(p->pos - CameraPosition);
					//ParticlesContainer[i].pos += glm::vec3(0.0f,10.0f, 0.0f) * (float)delta;

					m_positionData[i] = glm::vec4(p->pos, p->size);
					m_colourData[i] = p->colour;
				}

				m_particleCount++;

			}
		}

		m_updateEmitter = false;
	}
}

void ConeEmitter::render(const Camera3D & camera)
{
	//glDepthMask(GL_FALSE);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_updateEmitter = true;

	for (size_t i = 0; i < m_particles.size(); i++)
	{
		Particle* p = &m_particles[i];

		if (p->life > 0.0f)
		{
			p->cameraDistance = glm::length2(p->pos - camera.getTransform().getPosition());
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

int ConeEmitter::findUnusedParticle()
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

void ConeEmitter::sortParticles()
{
	std::sort(&m_particles[0], &m_particles[m_particles.size() - 1]);
}


// Ray Emitter

RayEmitter::RayEmitter(glm::vec3 & endPoint, glm::vec4 & colour, float lifeTime, int maxParticles /*= 10000.0f*/, float spawnRate /*= 5.0f*/)
{
	m_maxParticles = maxParticles;
	m_spawnRate = spawnRate;
	m_updateEmitter = true;
	m_colour = colour;
	m_lifeTime = lifeTime;

	m_particles.resize(m_maxParticles, Particle());
	m_positionData.resize(m_maxParticles);
	m_colourData.resize(m_maxParticles);

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
	std::cout << sizeof(g_vertex_buffer_data) << std::endl;

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, m_positionData.size() * sizeof(m_positionData[0]), NULL, GL_STREAM_DRAW);
	std::cout << m_positionData.size() * sizeof(m_positionData[0]) << std::endl;

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[COLOUR_VB]);
	glBufferData(GL_ARRAY_BUFFER, m_colourData.size() * sizeof(m_colourData[0]), NULL, GL_STREAM_DRAW);
	std::cout << m_colourData.size() * sizeof(m_colourData[0]) << std::endl;
}

RayEmitter::~RayEmitter()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void RayEmitter::update(float deltaTime)
{
	if (m_updateEmitter)
	{
		int newparticles = (int)(deltaTime * 100.0);

		for (int i = 0; i < newparticles; i++)
		{
			int particleIndex = findUnusedParticle();
			m_particles[particleIndex].life = m_lifeTime;
			m_particles[particleIndex].pos = glm::vec3(0.0f, 0.0f, 0.0f);

			float spread = 1.5f;
			glm::vec3 randomdir = glm::vec3(
				(rand() % 2000 - 1000.0f) / 1000.0f,
				(rand() % 2000 - 1000.0f) / 1000.0f,
				(rand() % 2000 - 1000.0f) / 1000.0f
				);

			m_particles[particleIndex].speed = randomdir * spread;

			//if (m_colour.w == 0.0f)
			//{
			//	// Very bad way to generate a random color
			//	m_particles[particleIndex].colour.r = 1.0f/*(float)(rand() % 256)*/;
			//	m_particles[particleIndex].colour.g = 1.0f/*(float)(rand() % 256)*/;
			//	m_particles[particleIndex].colour.b = 1.0f/*(float)(rand() % 256)*/;
			//	m_particles[particleIndex].colour.a = 1.0f/*(rand() % 256) / 3.0f*/;

			//	m_particles[particleIndex].size = 1.0f/*(rand() % 1000) / 2000.0f + 0.1f*/;
			//}
			//else
			//{
			//	m_particles[particleIndex].colour = m_colour;
			//}

			m_particles[particleIndex].size = 1.0f/*(rand() % 1000) / 2000.0f + 0.1f*/;

		}

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
					p->speed += glm::vec3(0.0f, 0.0f, 0.0f) * deltaTime * 0.5f;
					p->pos += p->speed * deltaTime;
					//p->cameraDistance = glm::length2(p->pos - CameraPosition);
					//ParticlesContainer[i].pos += glm::vec3(0.0f,10.0f, 0.0f) * (float)delta;

					m_positionData[i] = glm::vec4(p->pos, p->size);
					m_colourData[i] = p->colour;
				}

				m_particleCount++;

			}
		}

		m_updateEmitter = false;
	}
}

void RayEmitter::render(const Camera3D & camera)
{
	//glDepthMask(GL_FALSE);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_updateEmitter = true;

	for (size_t i = 0; i < m_particles.size(); i++)
	{
		Particle* p = &m_particles[i];

		if (p->life > 0.0f)
		{
			p->cameraDistance = glm::length2(p->pos - camera.getTransform().getPosition());
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

int RayEmitter::findUnusedParticle()
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

void RayEmitter::sortParticles()
{
	std::sort(&m_particles[0], &m_particles[m_particles.size() - 1]);
}


//Particle System

ParticleSystem::ParticleSystem(
	Material material, 
	EmitterType eType/* = EmitterType::AMBIENT */, 
	glm::vec4 & colour/*  = glm::vec4(0.0f) */, 
	float lifeTime/* = 4.0f*/, 
	float spawnRate /*= 5.0f*/, 
	int maxParticles /*= 10000.0f*/) :
m_particleMat(material),
m_emitterType(eType)
{
	switch (eType)
	{
	case AMBIENT:
		m_particleEmitter = new AmbientEmitter(colour, lifeTime, maxParticles, spawnRate);
		break;
	case EXPLOSION:
		m_particleEmitter = new ExplosionEmitter(colour, lifeTime, maxParticles, spawnRate);
		break;
	case FOUNTAIN:
		m_particleEmitter = new FountainEmitter(colour, lifeTime, maxParticles, spawnRate);
		break;
	default:
		throw "ParticleSystem instantiation with wrong constructor.\nAmbient Emitter, Explosion emitter or Fountain Emitter only.\n";
		break;
	}
}

ParticleSystem::ParticleSystem(
	Material material, 
	glm::vec3 & endPoint, 
	EmitterType eType/* = EmitterType::CONE */, 
	float radius/* = 1.0f */,
	glm::vec4 & colour/*  = glm::vec4(0.0f) */, 
	float lifeTime/* = 1.0f*/, 
	float spawnRate/* = 5.0f */, 
	int maxParticles/* = 10000.0f */) :
m_particleMat(material),
m_emitterType(eType)
{
	switch (eType)
	{
	case CONE:
		m_particleEmitter = new ConeEmitter(endPoint, colour, radius, lifeTime, maxParticles, spawnRate);
		break;
	case RAY:
		m_particleEmitter = new RayEmitter(endPoint, colour, lifeTime, maxParticles, spawnRate);
		break;
	default:
		throw "ParticleSystem instantiation with wrong constructor.\nJet Emitter or Ray Emitter only.\n";
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