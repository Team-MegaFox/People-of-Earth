// ***********************************************************************
// Author           : Pavan Jakhu, Jesse Derochie and Christopher Maeda
// Created          : 09-17-2015
//
// Last Modified By : Jesse Derochie
// Last Modified On : 02-22-2016
// ***********************************************************************
// <copyright file="FireProjectile.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
//</summary>
// ***********************************************************************

#pragma once
#include <Components\GameComponents.h>
#include <Components\Audio.h>
#include <Components\MeshRenderer.h>

struct Projectile : public GameComponent
{
	/// <summary>
	/// Initializes a new instance of the <see cref="Laser"/> class.
	/// </summary>
	Projectile() : m_lifeTime(2.0f) {}
	/// <summary>
	/// Finalizes an instance of the <see cref="Laser"/> class.
	/// </summary>
	~Projectile() { }

	/// <summary>
	/// Updates this GameComponent using delta time.
	/// </summary>
	/// <param name="delta">The delta.</param>
	virtual void update(float delta) override
	{
		m_lifeTime -= delta;
		if (m_lifeTime < 0)
		{
			destroy(getParent());
		}

	}

private:

	/// <summary>
	/// The life time of a laser projectile
	/// </summary>
	float m_lifeTime;
};

class FireProjectile : public GameComponent
{

public:

	/// <summary>
	/// Initializes a new instance of the <see cref="FireProjectile"/> class.
	/// </summary>
	FireProjectile() { }
	/// <summary>
	/// Finalizes an instance of the <see cref="FireProjectile"/> class.
	/// </summary>
	~FireProjectile() { }

	virtual void onStart() override
	{
		m_audioComponent = getParent()->getGameComponent<Audio>();
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
					(new GameObject("Laser", *getTransform()->getPosition(), *getTransform()->getRotation(), glm::vec3(0.15f, 0.15f, 4.0f)))
					->addGameComponent(new Projectile)
					->addGameComponent(new MeshRenderer(Mesh("Environment/cube.obj"), Material("plan1")))
					->addGameComponent(new RigidBody(*getTransform()->getPosition(), *getTransform()->getRotation(), 1.0f, 0.075f, 0.075f, 2.0f, Utility::getForward(*getTransform()->getRotation()) * 100.0f))
					);

				if (!m_audioComponent->isPlaying())
				m_audioComponent->play(true);

				m_delay = 0.0f;
			}
			if (input.GetLeftTrigger() != 0)
			{
				instantiate(
					(new GameObject("Laser", *getTransform()->getPosition(), *getTransform()->getRotation(), glm::vec3(0.15f, 0.15f, 4.0f)))
					->addGameComponent(new Projectile)
					->addGameComponent(new MeshRenderer(Mesh("Environment/cube.obj"), Material("plan1")))
					->addGameComponent(new RigidBody(*getTransform()->getPosition(), *getTransform()->getRotation(), 1.0f, 0.075f, 0.075f, 2.0f, Utility::getForward(*getTransform()->getRotation()) * 100.0f))
					);

				if (!m_audioComponent->isPlaying())
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
};