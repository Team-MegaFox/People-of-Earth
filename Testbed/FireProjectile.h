// ***********************************************************************
// Author           : Pavan Jakhu, Jesse Derochie and Christopher Maeda
// Created          : 02-18-2015
//
// Last Modified By : Christopher Maeda
// Last Modified On : 02-25-2016
// ***********************************************************************
// <copyright file="FireProjectile.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
//</summary>
// ***********************************************************************

#pragma once
#include <Components\Audio.h>
#include <Components\MeshRenderer.h>
#include "ShipStats.h"
#include "Projectile.h"

class FireProjectile : public GameComponent
{

public:

	/// <summary>
	/// Initializes a new instance of the <see cref="FireProjectile"/> class.
	/// </summary>
	FireProjectile() : m_material(
		"plan1", 1.0f, 10, Texture("Planets/Planet_A.png"), Texture("Planets/Planet_A_NORM.png")) {}
	/// <summary>
	/// Finalizes an instance of the <see cref="FireProjectile"/> class.
	/// </summary>
	~FireProjectile() { }

	virtual void onStart() override
	{
		//m_audioComponent = getParent()->getGameComponent<Audio>();
		//m_audioComponent = new Audio("268168__shaun105__laser.wav", AudioType::SOUND);
		//getParent()->getGameComponent<RigidBody>()->setDebugDraw(true);
	}

	/// <summary>
	/// Processes the input.
	/// </summary>
	/// <param name="input">The input.</param>
	/// <param name="delta">The delta.</param>
	virtual void processInput(const InputManager& input, float delta)
	{
		if (m_delay >= 0.2f)
		{
			
			m_audioComponent = nullptr;
			delete m_audioComponent;

			if (input.GetRightTrigger() != 0)
			{
				m_audioComponent = new Audio("268168__shaun105__laser.wav", AudioType::SOUND);
				
				instantiate(
					(new GameObject("Laser", *getTransform()->getPosition(), *getTransform()->getRotation(), glm::vec3(0.15f, 0.15f, 4.0f)))
					->addGameComponent(new Projectile)
					->addGameComponent(new MeshRenderer(Mesh("Environment/cube.obj"), Material("plan1")))
					->addGameComponent(new RigidBody(*getTransform()->getPosition(), *getTransform()->getRotation(), 1.0f, 0.075f, 0.075f, 2.0f, Utility::getForward(*getTransform()->getRotation()) * 200.0f))
					->addGameComponent(std::move(m_audioComponent))
					);

				m_audioComponent->play(true);

				m_delay = 0.0f;
			}
			if (input.GetLeftTrigger() != 0)
			{

				m_audioComponent = new Audio("268168__shaun105__laser.wav", AudioType::SOUND);

				instantiate(
					(new GameObject("Laser", *getTransform()->getPosition(), *getTransform()->getRotation(), glm::vec3(0.15f, 0.15f, 4.0f)))
					->addGameComponent(new Projectile)
					->addGameComponent(new MeshRenderer(Mesh("Environment/cube.obj"), Material("plan1")))
					->addGameComponent(new RigidBody(*getTransform()->getPosition(), *getTransform()->getRotation(), 1.0f, 0.075f, 0.075f, 2.0f, Utility::getForward(*getTransform()->getRotation()) * 200.0f))
					->addGameComponent(std::move(m_audioComponent))
					);

				m_audioComponent->play(true);

				m_delay = 0.0f;
			}


		}
		else
		{
			m_delay += delta;
		}
	}

private:
	/// <summary>
	/// The delay between shots
	/// </summary>
	float m_delay = 0.2f;
	Audio * m_audioComponent;
	Material m_material;
};