// ***********************************************************************
// Author           : Christopher Maeda
// Created          : 03-23-2016
//
// Last Modified By : Christopher Maeda
// Last Modified On : 03-24-2016
// ***********************************************************************
// <copyright file="MissileAI.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
//</summary>
// ***********************************************************************

#pragma once
#include "SteeringBehaviour.h"

class MissileAI : public SteeringBehaviour
{
public:

	MissileAI() : m_lifeTime(30.0f)
	{
	}

	~MissileAI() {}

	virtual void init() override;

	virtual std::vector<GameObject*> getAllEnemyObject() override;

	virtual void UpdateAI(float timestep) override;

	void removeTarget(const std::string & name);

private:
	float m_lifeTime;
	RigidBody* m_targetRigidBody;
};