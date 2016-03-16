// ***********************************************************************
// Author           : Christopher Maeda
// Created          : 09-15-2015
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 01-24-2016
// ***********************************************************************
// <copyright file="PhysicsEngine.cpp" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
// </summary>
// ***********************************************************************
#include "PhysicsEngine.h"
#include "../Rendering/Camera3D.h"

World * PhysicsEngine::m_physicsWorld = nullptr;

PhysicsEngine::PhysicsEngine()
{
	m_physicsWorld = new World();
}


PhysicsEngine::~PhysicsEngine()
{
	delete m_physicsWorld;
}

void PhysicsEngine::setMainCamera(const Camera3D& camera)
{
	m_mainCamera = &camera;
}

void PhysicsEngine::updatePhysicsEngine(float timeStep)
{
	m_physicsWorld->setPosition(m_mainCamera->getTransform().getTransformedPos());
	m_physicsWorld->update(timeStep);
}
