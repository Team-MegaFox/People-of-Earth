// ***********************************************************************
// Author           : Pavan Jakhu, Jesse Derochie and Christopher Maeda
// Created          : 02-18-2015
//
// Last Modified By : Christopher Maeda
// Last Modified On : 02-29-2016
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
#include <PhysX/PxPhysicsAPI.h>
using namespace physx;

class FireProjectile : public GameComponent
{

public:

	/// <summary>
	/// Initializes a new instance of the <see cref="FireProjectile"/> class.
	/// </summary>
	FireProjectile(const std::string fileName) : 
		m_material(
		"laser", 10.0f, 100, Texture("defaultTexture.png")),
		m_fileName(fileName){}
	/// <summary>
	/// Finalizes an instance of the <see cref="FireProjectile"/> class.
	/// </summary>
	~FireProjectile() { }

	/// <summary>
	/// Is called when this game component is created
	/// </summary>
	virtual void onStart() override
	{
		m_audioComponent = new Audio(m_fileName, AudioType::SOUND, true);
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
			if (input.GetRightTrigger() != 0)
			{
				instantiate(
					(new GameObject("Laser", *getTransform()->getPosition()
					, *getTransform()->getRotation(), PxVec3(0.15f, 0.15f, 4.0f)))
					->addGameComponent(new Projectile)
					->addGameComponent(new MeshRenderer(Mesh("Environment/cube.obj"), Material("laser")))
					->addGameComponent(new RigidBody(*getTransform()->getPosition() +
					Utility::getForward(*getTransform()->getRotation()) * 15.0f +
					Utility::getRight(*getTransform()->getRotation()) * 2.5f					
					, *getTransform()->getRotation(), 1.0f, 0.075f, 0.075f, 2.0f, Utility::getForward(*getTransform()->getRotation()) * 200.0f))
					);

				m_audioComponent->play();

				m_delay = 0.0f;
			}
			if (input.GetLeftTrigger() != 0)
			{
				instantiate(
					(new GameObject("Laser", *getTransform()->getPosition()
					, *getTransform()->getRotation(), PxVec3(0.15f, 0.15f, 4.0f)))
					->addGameComponent(new Projectile)
					->addGameComponent(new MeshRenderer(Mesh("Environment/cube.obj"), Material("laser")))
					->addGameComponent(new RigidBody(*getTransform()->getPosition() +
					Utility::getForward(*getTransform()->getRotation()) * 15.0f +
					Utility::getLeft(*getTransform()->getRotation()) * 3.5f, *getTransform()->getRotation(), 1.0f, 0.075f, 0.075f, 2.0f, Utility::getForward(*getTransform()->getRotation()) * 200.0f))
					);

				m_audioComponent->play();

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
	/// <summary>
	/// The file name of the sound to use
	/// </summary>
	std::string m_fileName;
	/// <summary>
	/// The audio component this game component will use for sound
	/// </summary>
	Audio * m_audioComponent;
	Material m_material;
};