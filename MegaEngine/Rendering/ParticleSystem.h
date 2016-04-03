#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>
#include <vector>
#include "..\Components\GameComponents.h"
#include "Shader.h"

enum EmitterType
{
	AMBIENT,
	EXPLOSION,
	FOUNTAIN,
	CONE,
	RAY
};

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
	ParticleEmitter() {}
	virtual ~ParticleEmitter() {}

	virtual void update(float deltaTime) = 0;
	virtual void render(const Camera3D & camera) = 0;

protected:

	Particles m_particles;

	bool m_updateEmitter;

	int m_maxParticles;

	float m_spawnRate;

	int m_lastUsedParticle = 0;

	int m_particleCount;

	int m_lifeTime;

	std::vector<glm::vec4> m_positionData;

	std::vector<glm::vec4> m_colourData;

	glm::vec4 m_colour;

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

	virtual int findUnusedParticle() = 0;

	virtual void sortParticles() = 0;

};

class AmbientEmitter : public ParticleEmitter
{
public:
	AmbientEmitter(glm::vec4 & colour, float lifeTime, int maxParticles = 10000.0f, float spawnRate = 5.0f);
	~AmbientEmitter();

	virtual void update(float deltaTime) override;
	virtual void render(const Camera3D & camera) override;

protected:

	virtual int findUnusedParticle() override;

	virtual void sortParticles() override;
};

class ExplosionEmitter : public ParticleEmitter
{
public:
	ExplosionEmitter(glm::vec4 & colour, float lifeTime, int maxParticles = 10000.0f, float spawnRate = 5.0f);
	~ExplosionEmitter();

	virtual void update(float deltaTime) override;
	virtual void render(const Camera3D & camera) override;

protected:

	virtual int findUnusedParticle() override;

	virtual void sortParticles() override;

	bool m_runOnce = false;
	int m_timesThrough = 0;
};

class FountainEmitter : public ParticleEmitter
{
public:
	FountainEmitter(glm::vec4 & colour, float lifeTime, int maxParticles = 10000.0f, float spawnRate = 5.0f);
	~FountainEmitter();

	virtual void update(float deltaTime) override;
	virtual void render(const Camera3D & camera) override;

protected:

	virtual int findUnusedParticle() override;

	virtual void sortParticles() override;

};

class ConeEmitter : public ParticleEmitter
{
public:
	ConeEmitter(glm::vec3& endPoint, glm::vec4 & colour, float radius, float lifeTime, int maxParticles = 10000.0f, float spawnRate = 5.0f);
	~ConeEmitter();

	virtual void update(float deltaTime) override;
	virtual void render(const Camera3D & camera) override;

protected:

	virtual int findUnusedParticle() override;

	virtual void sortParticles() override;

	glm::vec3 m_endPoint;
	float m_radius;
};

class RayEmitter : public ParticleEmitter
{
public:
	RayEmitter(glm::vec3& endPoint, glm::vec4 & colour, float lifeTime, int maxParticles = 10000.0f, float spawnRate = 5.0f);
	~RayEmitter();

	virtual void update(float deltaTime) override;
	virtual void render(const Camera3D & camera) override;

protected:

	virtual int findUnusedParticle() override;

	virtual void sortParticles() override;
};

class ParticleSystem : public GameComponent
{
public:
	// FountainEmitter, AmbientEmitter, ExplosionEmitter
	ParticleSystem(Material material, EmitterType eType = EmitterType::AMBIENT, glm::vec4 & colour = glm::vec4(0.0f), float lifeTime = 4.0f, float spawnRate = 5.0f, int maxParticles = 10000.0f);
	// ConeEmitter, RayEmitter
	ParticleSystem(Material material, glm::vec3 & endPoint, EmitterType eType = EmitterType::CONE, float radius = 1.0f, glm::vec4 & colour = glm::vec4(0.0f), float lifeTime = 1.0f, float spawnRate = 10.0f, int maxParticles = 10000.0f);
	~ParticleSystem();

	/// <summary>
	/// Virtual function for custom update functionality.
	/// </summary>
	/// <param name="delta">The frame time delta.</param>
	virtual void update(float delta) override;
	/// <summary>
	/// Virtual function for custom rendering functionality.
	/// </summary>
	/// <param name="shader">The shader.</param>
	/// <param name="renderingEngine">The rendering engine.</param>
	/// <param name="camera">The camera.</param>
	void renderParticles(const Shader& shader, const RenderingEngine& renderingEngine, const Camera3D & camera) const;

	/// <summary>
	/// Adds the particle system to the Rendering Engine so it can be rendered.
	/// </summary>
	/// <param name="engine">The Core Engine.</param>
	virtual void addToEngine(CoreEngine* engine) const override;

private:
	ParticleEmitter* m_particleEmitter;

	Material m_particleMat;

	EmitterType m_emitterType;
};
