// ***********************************************************************
// Author           : Pavan Jakhu, Jesse Derochie and Christopher Maeda
// Created          : 02-18-2015
//
// Last Modified By : Christopher Maeda
// Last Modified On : 04-04-2016
// ***********************************************************************
// <copyright file="FireProjectile.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
//</summary>
// ***********************************************************************

#pragma once
#include <Components\AudioSource.h>
#include <Components\MeshRenderer.h>
#include "ShipStats.h"
#include "Projectile.h"
#include "MissileAI.h"
#include <PhysX/PxPhysicsAPI.h>
#include "DialogueBox.h"
using namespace physx;

class FireProjectile : public GameComponent
{

public:

	/// <summary>
	/// Initializes a new instance of the <see cref="FireProjectile"/> class.
	/// </summary>
	FireProjectile() : 
		m_laserMaterial("laser", 10.0f, 100, Texture("laserGreen.png")),
		m_missileMaterial("missile", 10.0f, 100, Texture("missileGreen.png")){ }
	/// <summary>
	/// Finalizes an instance of the <see cref="FireProjectile"/> class.
	/// </summary>
	~FireProjectile() { }

	/// <summary>
	/// Is called when this game component is created
	/// </summary>
	virtual void onStart() override
	{
		m_shipStats = getGameObjectByName("player")->getGameComponent<ShipStats>();
	}

	/// <summary>
	/// Processes the input.
	/// </summary>
	/// <param name="input">The input.</param>
	/// <param name="delta">The delta.</param>
	virtual void processInput(const InputManager& input, float delta)
	{
		if (m_shipStats->getEnergy() > 0.0f)
		{
			if (m_delay >= 0.2f)
			{
				if (input.GetRightTrigger() != 0)
				{
					instantiate(
						(new GameObject("Laser", *getTransform()->getPosition()
						, *getTransform()->getRotation(), m_laserScale))
						->addGameComponent(new Projectile(0.1f, AGENT::PLAYER_SIDE))
						->addGameComponent(new MeshRenderer(Mesh("Ships/Missiles/qutank_Mesh.obj"), Material("laser")))
						->addGameComponent(new RigidBody(*getTransform()->getPosition() +
						Utility::getForward(*getTransform()->getRotation()) * 15.0f +
						Utility::getRight(*getTransform()->getRotation()) * 2.5f
						, *getTransform()->getRotation(), 1.0f, 0.075f, 0.075f, 2.0f,
						Utility::getForward(*getTransform()->getRotation()) * 200.0f))
						);

					instantiate((new GameObject("Laser Sound"))
						->addGameComponent(new AudioSource("Music/sci-fi_weapon_laser_small_03.WAV", AudioType::SOUND, true, 0.2f, true)));

					m_delay = 0.0f;
					m_shipStats->updateEnergy(-0.001f);
				}
				if (input.GetLeftTrigger() != 0)
				{
					instantiate(
						(new GameObject("Laser", *getTransform()->getPosition()
						, *getTransform()->getRotation(), m_laserScale))
						->addGameComponent(new Projectile(0.1f, AGENT::PLAYER_SIDE))
						->addGameComponent(new MeshRenderer(Mesh("Ships/Missiles/qutank_Mesh.obj"), Material("laser")))
						->addGameComponent(new RigidBody(*getTransform()->getPosition() +
						Utility::getForward(*getTransform()->getRotation()) * 15.0f +
						Utility::getLeft(*getTransform()->getRotation()) * 3.5f,
						*getTransform()->getRotation(), 1.0f, 0.075f, 0.075f, 2.0f,
						Utility::getForward(*getTransform()->getRotation()) * 200.0f))
						);

					instantiate((new GameObject("Laser Sound"))
						->addGameComponent(new AudioSource("Music/sci-fi_weapon_laser_small_03.WAV", AudioType::SOUND, true, 0.2f, true)));

					m_delay = 0.0f;
					m_shipStats->updateEnergy(-0.001f);
				}
				if (input.PadButtonPress(SDL_CONTROLLER_BUTTON_B))
				{
					if (m_missileCount > 0)
					{
						//Shoot missile
						instantiate(
							(new GameObject("Missile", *getTransform()->getPosition()
							, *getTransform()->getRotation(), m_missileScale))
							->addGameComponent(new MissileAI())
							->addGameComponent(new MeshRenderer(Mesh("Ships/Missiles/missile.obj"), Material("missile")))
							->addGameComponent(new RigidBody(*getTransform()->getPosition() +
							Utility::getForward(*getTransform()->getRotation()) * 15.0f +
							Utility::getLeft(*getTransform()->getRotation()) * 3.5f,
							*getTransform()->getRotation(), 1.0f, 0.075f, 0.075f, 2.0f,
							Utility::getForward(*getTransform()->getRotation()) * 200.0f))
							);
						m_delay = 0.0f;
						m_shipStats->updateEnergy(-0.001f);
						m_missileCount--;
					}
				}
			}
			
			else
			{
				m_delay += delta;
			}
		}
	}

	int getMissileCount()
	{
		return m_missileCount;
	}

private:
	/// <summary>
	/// The delay between shots
	/// </summary>
	float m_delay = 0.2f;
	Material m_laserMaterial;
	Material m_missileMaterial;
	PxVec3 m_missileScale = PxVec3(0.0025f);
	PxVec3 m_laserScale = PxVec3(1.0f);
	ShipStats * m_shipStats;
	int m_missileCount = 10;

};