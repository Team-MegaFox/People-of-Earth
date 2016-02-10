#include "ParticleSystem.h"
#include <glew\glew.h>
#include <glm\gtx\norm.hpp>
#include <algorithm>
#include "Camera3D.h"

ParticleEmitter::ParticleEmitter(float maxParticles /*= 10000.0f*/, float spawnRate /*= 5.0f*/) :
m_maxParticles(maxParticles),
m_spawnRate(spawnRate)
{
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
		0.5f, 0.5f, 0.0f,
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
	int newparticles = (int)(deltaTime*m_spawnRate);

	for (int i = 0; i < newparticles; i++)
	{
		int particleIndex = findUnusedParticle();
		m_particles[particleIndex].life = 5.0f; // This particle will live 5 seconds.
		m_particles[particleIndex].pos = glm::vec3(0, 0, -20.0f);

		float spread = 1.5f;
		glm::vec3 maindir = glm::vec3(0.0f, 10.0f, 0.0f);
		glm::vec3 randomdir = glm::vec3(
			(rand() % 2000 - 1000.0f) / 1000.0f,
			(rand() % 2000 - 1000.0f) / 1000.0f,
			(rand() % 2000 - 1000.0f) / 1000.0f
			);

		m_particles[particleIndex].speed = maindir + randomdir*spread;

		// Very bad way to generate a random color
		m_particles[particleIndex].colour.x = rand() % 256;
		m_particles[particleIndex].colour.y = rand() % 256;
		m_particles[particleIndex].colour.z = rand() % 256;
		m_particles[particleIndex].colour.w = (rand() % 256) / 3;

		m_particles[particleIndex].size = (rand() % 1000) / 2000.0f + 0.1f;

	}

	m_particleCount = 0;
	for (int i = 0; i < m_particles.size(); i++)
	{
		Particle* p = &m_particles[i]; 

		if (p->life > 0.0f)
		{
			// Decrease life
			p->life -= deltaTime;
			if (p->life > 0.0f)
			{
				// Simulate simple physics : gravity only, no collisions
				p->speed += glm::vec3(0.0f, -9.81f, 0.0f) * (float)deltaTime * 0.5f;
				p->pos += p->speed * (float)deltaTime;
				//p->cameraDistance = glm::length2(p->pos - CameraPosition);
				//ParticlesContainer[i].pos += glm::vec3(0.0f,10.0f, 0.0f) * (float)delta;

				m_positionData[i] = glm::vec4(p->pos, p->size);
				m_colourData[i] = p->colour;
			}

			m_particleCount++;

		}
	}
}

void ParticleEmitter::render(const Camera3D & camera)
{
	for (int i = 0; i < m_particles.size(); i++)
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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[BILLBOARD_VB]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// 2nd attribute buffer : positions of particles' centers
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// 3rd attribute buffer : particles' colors
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[COLOUR_VB]);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_TRUE, 0, (void*)0);

	// These functions are specific to glDrawArrays*Instanced*.
	// The first parameter is the attribute buffer we're talking about.
	// The second parameter is the "rate at which generic vertex attributes advance when rendering multiple instances"
	// http://www.opengl.org/sdk/docs/man/xhtml/glVertexAttribDivisor.xml
	glVertexAttribDivisor(0, 0); // particles vertices : always reuse the same 4 vertices -> 0
	glVertexAttribDivisor(1, 1); // positions : one per quad (its center)                 -> 1
	glVertexAttribDivisor(2, 1); // color : one per quad                                  -> 1

	// Draw the particules !
	// This draws many times a small triangle_strip (which looks like a quad).
	// This is equivalent to :
	// for(i in ParticlesCount) : glDrawArrays(GL_TRIANGLE_STRIP, 0, 4), 
	// but faster.
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, m_particleCount);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glDisable(GL_BLEND);
}

int ParticleEmitter::findUnusedParticle()
{
	for (int i = m_lastUsedParticle; i < m_particles.size(); i++)
	{
		if (m_particles[i].life < 0)
		{
			m_lastUsedParticle = i;
			return i;
		}
	}

	for (int i = 0; i < m_lastUsedParticle; i++)
	{
		if (m_particles[i].life < 0)
		{
			m_lastUsedParticle = i;
			return i;
		}
	}

	return 0;
}

void ParticleEmitter::sortParticles()
{
	std::sort(&m_particles[0], &m_particles[m_particles.size()]);
}

ParticleSystem::ParticleSystem(float spawnRate /*= 5.0f*/, Texture m_particleTex /*= Texture("defaultTexture.png")*/, float maxParticles /*= 10000.0f*/) :
m_particleShader("particle"),
m_particleMat("particleMat", 1.0f, 1.0f, m_particleTex)
{
	m_particleEmitter = new ParticleEmitter;
}

ParticleSystem::~ParticleSystem()
{
	delete m_particleEmitter;
}

void ParticleSystem::update(float delta)
{
	m_particleEmitter->update(delta);
}

void ParticleSystem::render(const Shader& shader, const RenderingEngine& renderingEngine, const Camera3D & camera) const
{
	m_particleShader.bind();
	m_particleShader.updateUniforms(getTransform(), m_particleMat, renderingEngine, camera);
	m_particleEmitter->render(camera);
}