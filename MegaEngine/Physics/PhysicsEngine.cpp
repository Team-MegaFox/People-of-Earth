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

World * PhysicsEngine::m_physicsWorld = nullptr;

PhysicsEngine::PhysicsEngine()
{
	m_physicsWorld = new World();
}


PhysicsEngine::~PhysicsEngine()
{
}


void PhysicsEngine::updatePhysicsEngine(float timeStep)
{
	m_physicsWorld->update(timeStep);
}
