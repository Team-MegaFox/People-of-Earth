// ***********************************************************************
// Author           : Christopher Maeda
// Created          : 03-18-2016
//
// Last Modified By : Christopher Maeda
// Last Modified On : 03-20-2016
// ***********************************************************************
// <copyright file="CrossHair.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
//</summary>
// ***********************************************************************

#pragma once
#include <MegaEngine.h>

class CrossHair : public GameComponent
{
public:
	CrossHair(float distanceOfCrossHair = 25.0f) : m_distanceOfCrossHair(distanceOfCrossHair)
	{}

	~CrossHair()
	{}

	virtual void onStart() override
	{
		GameObject* playerFighterShip = getGameObjectByName("Fighter Ship");
		getTransform()->setPosition(
			playerFighterShip->getGameComponent<RigidBody>()->getPosition() +
			PxVec3(0, 0, m_distanceOfCrossHair)
			);

		getTransform()->setRotation(
			*getTransform()->getRotation() *
			PxQuat(
			1 * PxSin(0.5f * 200.0f),
			0,
			0,
			1 * PxCos(0.5f * 200.0f))
			);
	}

private:
	float m_distanceOfCrossHair = 0.0f;
};