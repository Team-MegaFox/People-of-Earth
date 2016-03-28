// ***********************************************************************
// Author           : Christopher Maeda & Jesse Derochie
// Created          : 03-25-2016
//
// Last Modified By : Jesse Derochie
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
#include <MegaEngine.h>

class MotherShipAI : public SteeringBehaviour
{
public:

	MotherShipAI() : 
		m_laserMaterial("enemyMotherlaser", 10.0f, 100, 
		Texture("qutank_DifusseMapPurps.png"),
		Texture("qutank_NormalMap.png"),
		Texture("qutank_SpecularMap.png")){}

	~MotherShipAI() {}

	virtual void init() override
	{
		m_targetObject = getGameObjectByName("passengerShip");
		m_forwardDirection = Utility::getForward(m_rigidBody->getRotation());
		m_direction = PxVec3(0.0f, 0.0f, 0.0f);
		m_shipStats = getParent()->getGameComponent<ShipStats>();
	}

	virtual std::vector<GameObject*> getAllEnemyObject() override
	{
		//Return nothing
		return std::vector<GameObject*>();
	}

	virtual void UpdateAI(float timestep) override
	{
		//Add Mother Ship AI here:
		// get direction to passenger ship
		m_direction = (*m_targetObject->getTransform()->getPosition() - *getTransform()->getPosition()).getNormalized();

		// Rotate MotherShip to face the passenger ship
		float angle = PxAcos(m_forwardDirection.dot(m_direction) / (m_forwardDirection.magnitude() * m_direction.magnitude()));

		getTransform()->setRotation(PxQuat(angle, PxVec3(0.0f, 1.0f, 0.0f)));

		// the passenger ship is less than x distance away 
		// from the mother ship the mother ship can fire
		if (m_direction.magnitude() <= 2500.0f)
		{
			if (m_delayAttacking <= 0.0f && m_shipStats->getHealth() > 0.0f)
			{
				shootLaserCannons();
				m_delayAttacking = 10.0f;
			}
		}

		if (m_delayAttacking > 0.0f)
		{
			m_delayAttacking -= 0.033f;
		}
	}

	void shootLaserCannons()
	{
		//Right side
		instantiate(
			(new GameObject("Laser", *getTransform()->getPosition()
			, *getTransform()->getRotation(), m_scaleOfProjectile))
			->addGameComponent(new Projectile(m_damageValue, AGENT::ENEMY_SIDE))
			->addGameComponent(new MeshRenderer(Mesh("Ships/Missiles/qutank_Mesh.obj"), Material("enemyMotherlaser")))
			->addGameComponent(new RigidBody(*getTransform()->getPosition() +
			Utility::getForward(*getTransform()->getRotation()) * 30.0f
			, *getTransform()->getRotation(), 1.0f, 
			m_scaleOfProjectile.x / 2.0f, 
			m_scaleOfProjectile.y / 2.0f, 
			m_scaleOfProjectile.z / 2.0f, Utility::getForward(*getTransform()->getRotation()) * 800.0f))
			);
	}

	float m_delayAttacking = 10.0f;
	Material m_laserMaterial;
	ShipStats * m_shipStats;
	float m_damageValue = 0.4f;
	PxVec3 m_scaleOfProjectile = PxVec3(4.0f);
};