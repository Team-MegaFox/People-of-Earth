// ***********************************************************************
// Author           : Christopher Maeda
// Created          : 03-25-2016
//
// Last Modified By : Christopher Maeda
// Last Modified On : 03-25-2016
// ***********************************************************************
// <copyright file="MotherShipAI.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
//</summary>
// ***********************************************************************

#pragma once
#include "SteeringBehaviour.h"

class MotherShipAI : public SteeringBehaviour
{
public:

	MotherShipAI()
	{
	}

	~MotherShipAI() {}

	virtual void init() override
	{
		m_targetObject = getGameObjectByName("passengerShip");
		m_forwardDirection = Utility::getForward(m_rigidBody->getRotation());
		m_direction = PxVec3(0.0f, 0.0f, 0.0f);
	}

	virtual std::vector<GameObject*> getAllEnemyObject() override
	{
		//Return nothing
		return std::vector<GameObject*>();
	}

	virtual void UpdateAI(float timestep) override
	{
		//Add Mother Ship AI here:


	}

};