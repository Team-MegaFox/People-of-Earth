#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>
#include <vector>
#include "..\Components\GameComponents.h"
#include "Shader.h"

struct Particle
{
	glm::vec3 pos;
	glm::vec4 colour;
	glm::vec3 speed;
	float size;
	float angle;
	float life;
	float cameraDistance;

	bool operator<(const Particle& part) const {
		// Sort in reverse order : far particles drawn first.
		return this->cameraDistance > part.cameraDistance;
	}
};
typedef std::vector<Particle> Particles;

class ParticleEmitter
{
public:
	ParticleEmitter(int maxParticles = 10000.0f, float spawnRate = 5.0f);
	~ParticleEmitter();

	void update(float deltaTime);
	void render(const Camera3D & camera);

private:
	Particles m_particles;

	int m_maxParticles;

	float m_spawnRate;

	int m_lastUsedParticle = 0;

	int m_particleCount;

	std::vector<glm::vec4> m_positionData;

	std::vector<glm::vec4> m_colourData;

	enum
	{
		BILLBOARD_VB,
		POSITION_VB,
		COLOUR_VB,

		NUM_BUFFERS
	};

	/// <summary>
	/// The vertex array object.
	/// </summary>
	GLuint m_vertexArrayObject;
	/// <summary>
	/// The number of buffers to have to send to the graphics card.
	/// </summary>
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];

	int findUnusedParticle();

	void sortParticles();

};

class ParticleSystem : public GameComponent
{
public:
	ParticleSystem(Material material, float spawnRate = 5.0f, int maxParticles = 10000.0f);
	~ParticleSystem();

	/// <summary>
	/// Virtual function for custom update functionality.
	/// </summary>
	/// <param name="delta">The frame time delta.</param>
	virtual void update(float delta);
	/// <summary>
	/// Virtual function for custom rendering functionality.
	/// </summary>
	/// <param name="shader">The shader.</param>
	/// <param name="renderingEngine">The rendering engine.</param>
	/// <param name="camera">The camera.</param>
	virtual void render(const Shader& shader, const RenderingEngine& renderingEngine, const Camera3D & camera) const;

private:
	ParticleEmitter* m_particleEmitter;

	Shader m_particleShader;

	Material m_particleMat;

};
