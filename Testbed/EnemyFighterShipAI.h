
#pragma once
#include "SteeringBehaviour.h"

class EnemyFighterShipAI : public SteeringBehaviour
{

public:
	EnemyFighterShipAI() 
	{}

	~EnemyFighterShipAI()
	{}

	virtual void init() override
	{
		forwardDirection = glm::vec3(0);
		direction = glm::vec3(0);
		SPEED_REDUCTION = 1000.0f;
		targetPoint = glm::vec3(0);
	}

	virtual void UpdateAI(float timestep) override
	{
		Wander(timestep);
	}
};

