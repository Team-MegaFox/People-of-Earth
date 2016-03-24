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
		m_fighterShip = getGameObjectByName("Fighter Ship");
		//getTransform()->setPosition(
		//	m_fighterShip->getGameComponent<RigidBody>()->getPosition() +
		//	PxVec3(0, 0, m_distanceOfCrossHair)
		//	);

		//getTransform()->setRotation(
		//	*getTransform()->getRotation() *
		//	PxQuat(
		//	1 * PxSin(0.5f * 200.0f),
		//	0,
		//	0,
		//	1 * PxCos(0.5f * 200.0f))
		//	);

		m_mainCamera = getGameObjectByName("camera")->getGameComponent<CameraComponent>();
		
		m_label = new GUILabel(PxVec4(0.0f, 0.0f, 0.1f, 0.05f), PxVec4(0.0f), "Hellow wolrd");
		instantiate((new GameObject("hello button"))
			->addGUIComponent(m_label));
	}

	virtual void update(float delta) override
	{
		PxVec3 screen = m_mainCamera->worldToScreenPoint(m_fighterShip->getGameComponent<RigidBody>()->getPosition() +
			PxVec3(0, 0, m_distanceOfCrossHair));
		m_label->setPixelPosition(PxVec2(screen.x, screen.y));
	}

	

private:
	float m_distanceOfCrossHair = 0.0f;

	GameObject* m_fighterShip;

	CameraComponent* m_mainCamera;

	GUILabel* m_label;
};