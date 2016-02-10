#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>
#include <vector>
#include "..\Components\GameComponents.h"

struct Particle
{
	glm::vec3 pos;
	float size;
	float angle;
	float age;	
	float lifeTime;
};
typedef std::vector<Particle> Particles;

class ParticleEmitter
{
public:
	ParticleEmitter();
	~ParticleEmitter();

	virtual void update(float deltaTime);
	void render();

private:
	Particles m_particles;

};

class ParticleSystem : public GameComponent
{
public:
	ParticleSystem();
	~ParticleSystem();

private:
	float m_spawnRate;

};
