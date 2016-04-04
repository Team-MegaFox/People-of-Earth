// ***********************************************************************
// Author           : Pavan Jakhu & Jesse Derochie
// Created          : 03-02-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 04-02-2016
// ***********************************************************************
// <copyright file="ParticleSystem.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
// </summary>
// ***********************************************************************

#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>
#include <vector>
#include "..\Components\GameComponents.h"
#include "Shader.h"

/// <summary>
/// What type of emitter to use for this particle system
/// </summary>
enum EmitterType
{
	AMBIENT,
	EXPLOSION,
	FOUNTAIN,
	CONE,
	RAY
};

/// <summary>
/// The Particles properties
/// </summary>
struct Particle
{
	/// <summary>
	/// The position of the particle
	/// </summary>
	glm::vec3 pos;
	/// <summary>
	/// The colour of the particle
	/// </summary>
	glm::vec4 colour;
	/// <summary>
	/// The speed of the particle
	/// </summary>
	glm::vec3 speed;
	/// <summary>
	/// The size of the particle
	/// </summary>
	float size;
	/// <summary>
	/// The angle of the particle
	/// </summary>
	float angle;
	/// <summary>
	/// The life of the particle
	/// </summary>
	float life;
	/// <summary>
	/// The camera distance of the particle
	/// </summary>
	float cameraDistance;

	/// <summary>
	/// Overload of the less than operator
	/// </summary>
	/// <param name="part">the other particle</param>
	/// <returns></returns>
	bool operator<(const Particle& part) const {
		// Sort in reverse order : far particles drawn first.
		return this->cameraDistance > part.cameraDistance;
	}
};
typedef std::vector<Particle> Particles;

/// <summary>
/// Base class for all particle emitters
/// </summary>
class ParticleEmitter
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="ParticleEmitter"/> class.
	/// </summary>
	ParticleEmitter(bool updateEmitter = true, float maxParticles = 10000.0f, float spawnRate = 5.0f, float lifeTime = 5.0f);
	/// <summary>
	/// Finalizes an instance of the <see cref="ParticleEmitter"/> class.
	/// </summary>
	~ParticleEmitter();

	/// <summary>
	/// Virtual function for custom update functionality.
	/// </summary>
	/// <param name="deltaTime">The delta time.</param>
	void update(float deltaTime);

	virtual void updateParticles(float deltaTime) = 0;

	/// <summary>
	/// Renders the particles
	/// </summary>
	/// <param name="camera">The camera.</param>
	void render(const Camera3D & camera);

protected:

	/// <summary>
	/// The particles
	/// </summary>
	Particles m_particles;
	/// <summary>
	/// boolean used to determine when to update the emitter
	/// </summary>
	bool m_updateEmitter;
	/// <summary>
	/// The max number of particles
	/// </summary>
	int m_maxParticles;
	/// <summary>
	/// The spawn rate of particles
	/// </summary>
	float m_spawnRate;
	/// <summary>
	/// The last used particle
	/// </summary>
	int m_lastUsedParticle = 0;
	/// <summary>
	/// The particle count
	/// </summary>
	int m_particleCount;
	/// <summary>
	/// The life time of the particle
	/// </summary>
	int m_lifeTime;
	/// <summary>
	/// The position data for particles
	/// </summary>
	std::vector<glm::vec4> m_positionData;
	/// <summary>
	/// The colour data of particles
	/// </summary>
	std::vector<glm::vec4> m_colourData;
	/// <summary>
	/// The colour set to the particles
	/// </summary>
	glm::vec4 m_colour;

	/// <summary>
	/// Finds an unused particle.
	/// </summary>
	/// <returns></returns>
	int findUnusedParticle();

private:
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

	/// <summary>
	/// Sorts all the particles drawing the furthest particle first
	/// </summary>
	void sortParticles();

};

/// <summary>
/// This emitter is used to create an effect of particles surrounding the scene
/// for instance a snowing effect, or falling leaves
/// </summary>
/// <seealso cref="ParticleEmitter" />
class AmbientEmitter : public ParticleEmitter
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="AmbientEmitter"/> class.
	/// </summary>
	/// <param name="lifeTime">The life time.</param>
	/// <param name="maxParticles">The maximum particles.</param>
	/// <param name="spawnRate">The spawn rate.</param>
	AmbientEmitter(float lifeTime, int maxParticles = 10000.0f, float spawnRate = 5.0f);
	/// <summary>
	/// Finalizes an instance of the <see cref="AmbientEmitter"/> class.
	/// </summary>
	virtual ~AmbientEmitter();

	/// <summary>
	/// Updates the specified delta time.
	/// </summary>
	/// <param name="deltaTime">The delta time.</param>
	virtual void updateParticles(float deltaTime) override;
};


/// <summary>
/// This emitter is used to create an explosion like effect
/// </summary>
/// <seealso cref="ParticleEmitter" />
class ExplosionEmitter : public ParticleEmitter
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="ExplosionEmitter"/> class.
	/// </summary>
	/// <param name="lifeTime">The life time.</param>
	/// <param name="maxParticles">The maximum particles.</param>
	/// <param name="spawnRate">The spawn rate.</param>
	ExplosionEmitter(float lifeTime, int maxParticles = 10000.0f, float spawnRate = 5.0f);
	/// <summary>
	/// Finalizes an instance of the <see cref="ExplosionEmitter"/> class.
	/// </summary>
	virtual ~ExplosionEmitter();

	/// <summary>
	/// Updates the specified delta time.
	/// </summary>
	/// <param name="deltaTime">The delta time.</param>
	virtual void updateParticles(float deltaTime) override;

protected:

	/// <summary>
	/// RunOnce is used to stop particles from continuous spawning
	/// if it is used in conjunction with a timer
	/// </summary>
	bool m_runOnce = false;
	/// <summary>
	/// The timer used with the runOnce boolean to stop continuous spawning
	/// of particles
	/// </summary>
	int m_timesThrough = 0;
};

/// <summary>
/// This emitter creates a fountain like effect using simulated gravity
/// </summary>
/// <seealso cref="ParticleEmitter" />
class FountainEmitter : public ParticleEmitter
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="FountainEmitter"/> class.
	/// </summary>
	/// <param name="lifeTime">The life time.</param>
	/// <param name="maxParticles">The maximum particles.</param>
	/// <param name="spawnRate">The spawn rate.</param>
	FountainEmitter(float lifeTime, int maxParticles = 10000.0f, float spawnRate = 5.0f);
	/// <summary>
	/// Finalizes an instance of the <see cref="FountainEmitter"/> class.
	/// </summary>
	virtual ~FountainEmitter();

	/// <summary>
	/// Updates the specified delta time.
	/// </summary>
	/// <param name="deltaTime">The delta time.</param>
	virtual void updateParticles(float deltaTime) override;
};

/// <summary>
/// This emitter is used to create a conical fountain effect, this emitter
/// can be used for things like jet propulsion effects, or ray gun effects
/// </summary>
/// <seealso cref="ParticleEmitter" />
class ConeEmitter : public ParticleEmitter
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="ConeEmitter"/> class.
	/// </summary>
	/// <param name="endPoint">The end point.</param>
	/// <param name="radius">The radius.</param>
	/// <param name="lifeTime">The life time.</param>
	/// <param name="maxParticles">The maximum particles.</param>
	/// <param name="spawnRate">The spawn rate.</param>
	ConeEmitter(glm::vec3& endPoint, float radius, float lifeTime, int maxParticles = 10000.0f, float spawnRate = 5.0f);
	/// <summary>
	/// Finalizes an instance of the <see cref="ConeEmitter"/> class.
	/// </summary>
	virtual ~ConeEmitter();

	/// <summary>
	/// Updates the specified delta time.
	/// </summary>
	/// <param name="deltaTime">The delta time.</param>
	virtual void updateParticles(float deltaTime) override;

protected:

	/// <summary>
	/// The end point that this particle will move towards
	/// the tip of the cone
	/// </summary>
	glm::vec3 m_endPoint;
	/// <summary>
	/// The radius of the base of the cone
	/// </summary>
	float m_radius;
};

/// <summary>
/// This emitter is used to create shooting star like effects, it can be used
/// to create trails behind objects or streamers in a scene
/// </summary>
/// <seealso cref="ParticleEmitter" />
class RayEmitter : public ParticleEmitter
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="RayEmitter"/> class.
	/// </summary>
	/// <param name="endPoint">The end point.</param>
	/// <param name="lifeTime">The life time.</param>
	/// <param name="maxParticles">The maximum particles.</param>
	/// <param name="spawnRate">The spawn rate.</param>
	RayEmitter(glm::vec3& endPoint, float lifeTime, int maxParticles = 10000.0f, float spawnRate = 5.0f);
	/// <summary>
	/// Finalizes an instance of the <see cref="RayEmitter"/> class.
	/// </summary>
	virtual ~RayEmitter();

	/// <summary>
	/// Updates the specified delta time.
	/// </summary>
	/// <param name="deltaTime">The delta time.</param>
	virtual void updateParticles(float deltaTime) override;

protected:
	glm::vec3 m_endPoint;
};

/// <summary>
/// The particle System is the GameComponent added to a GameObject in the scene
/// the particle system sets up the emitter that will be used 
/// </summary>
/// <seealso cref="GameComponent" />
class ParticleSystem : public GameComponent
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="ParticleSystem"/> class.
	/// Only use with FountainEmitter, AmbientEmitter, ExplosionEmitter
	/// </summary>
	/// <param name="material">The material.</param>
	/// <param name="eType">Type of the e.</param>
	/// <param name="colour">The colour.</param>
	/// <param name="lifeTime">The life time.</param>
	/// <param name="spawnRate">The spawn rate.</param>
	/// <param name="maxParticles">The maximum particles.</param>
	ParticleSystem(Material material, EmitterType eType = EmitterType::AMBIENT, float lifeTime = 4.0f, float spawnRate = 5.0f, int maxParticles = 10000.0f);
	/// <summary>
	/// Initializes a new instance of the <see cref="ParticleSystem"/> class.
	/// Only use with ConeEmitter, RayEmitter
	/// </summary>
	/// <param name="material">The material.</param>
	/// <param name="endPoint">The end point.</param>
	/// <param name="eType">Type of the e.</param>
	/// <param name="radius">The radius.</param>
	/// <param name="colour">The colour.</param>
	/// <param name="lifeTime">The life time.</param>
	/// <param name="spawnRate">The spawn rate.</param>
	/// <param name="maxParticles">The maximum particles.</param>
	ParticleSystem(Material material, glm::vec3 & endPoint, EmitterType eType = EmitterType::CONE, float radius = 1.0f, float lifeTime = 1.0f, float spawnRate = 10.0f, int maxParticles = 10000.0f);
	/// <summary>
	/// Finalizes an instance of the <see cref="ParticleSystem"/> class.
	/// </summary>
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
	/// <summary>
	/// The particle emitter
	/// </summary>
	ParticleEmitter* m_particleEmitter;
	/// <summary>
	/// The particle material
	/// </summary>
	Material m_particleMat;
	/// <summary>
	/// The emitter type
	/// </summary>
	EmitterType m_emitterType;
};
