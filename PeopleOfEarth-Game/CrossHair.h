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
		m_fighterShip = getGameObjectByName("Fighter Ship")->getGameComponent<RigidBody>();

		m_mainCamera = getGameObjectByName("camera")->getGameComponent<CameraComponent>();
		
		m_crosshairImage = new GUIImage(PxVec4(0.0f, 0.0f, 0.1f, 0.1f), PxVec4(0.0f), "Images/crosshair.png");
		instantiate((new GameObject("hello button"))->addGUIComponent(m_crosshairImage));
	}

	virtual void update(float delta) override
	{
		PxVec2 viewport(getCoreEngine()->getViewport()->getScreenWidth() * 0.1f, getCoreEngine()->getViewport()->getScreenHeight() * 0.1f);

		PxVec3 screen = m_mainCamera->worldToScreenPoint(m_fighterShip->getPosition() + (Utility::getForward(m_fighterShip->getRotation()).getNormalized() * m_distanceOfCrossHair));

		m_crosshairImage->setPixelPosition(PxVec2(screen.x - viewport.x / 4.0f, screen.y - viewport.y / 4.0f));
	}

private:
	float m_distanceOfCrossHair = 0.0f;

	RigidBody* m_fighterShip;

	CameraComponent* m_mainCamera;

	GUIImage* m_crosshairImage;
};