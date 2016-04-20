// ***********************************************************************
// Author           : Christopher Maeda & Jesse Derochie
// Created          : 03-23-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 04-204-2016
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

	MissileAI() : 
		m_lifeTime(30.0f),
		m_particleMat("explosionMat2", 0.5f, 4.0f, Texture("fireTexture.png"))
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
	Material m_particleMat;
};