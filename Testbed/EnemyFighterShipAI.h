// ***********************************************************************
// Author           : Christopher Maeda
// Created          : 02-23-2016
//
// Last Modified By : Christopher Maeda
// Last Modified On : 02-25-2016
// ***********************************************************************
// <copyright file="EnemyFighterShipAI.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
//</summary>
// ***********************************************************************

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
		m_forwardDirection = glm::vec3(0);
		m_direction = glm::vec3(0);
		m_targetPoint = *getTransform()->getPosition();
		m_velocityValue = 50.0f;
	}

	virtual void UpdateAI(float timestep) override
	{
		Wander(timestep);
		
	}
};

