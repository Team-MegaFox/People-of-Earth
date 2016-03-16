// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 02-01-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 03-01-2016
// ***********************************************************************
// <copyright file="Listener.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************

#pragma once
#include "../Components/GameComponents.h"
#include "../Audio/AudioListener.h"
#include "../Core/Utility.h"

class Listener : public GameComponent
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Listener"/> class.
	/// </summary>
	Listener()
	{
		m_theListener = new AudioListener();
	}
	/// <summary>
	/// Finalizes an instance of the <see cref="Listener"/> class.
	/// </summary>
	~Listener()
	{
		delete m_theListener;
	}

	/// <summary>
	/// Updates the specified delta time.
	/// </summary>
	/// <param name="deltaTime">The delta time.</param>
	virtual void update(float deltaTime) override
	{
		m_pos = *getTransform()->getPosition();
		m_vel = PxVec3(0.0f);
		m_forward = Utility::getForward(*getTransform()->getRotation());
		m_up = Utility::getUp(*getTransform()->getRotation());

		m_theListener->setAsListener(m_pos, m_vel, m_forward, m_up);
	}

protected:
	/// <summary>
	/// The audio listener
	/// </summary>
	AudioListener * m_theListener;

private:

	/// <summary>
	/// The position of the listener
	/// </summary>
	PxVec3 m_pos;
	/// <summary>
	/// The velocity of the listener
	/// </summary>
	PxVec3 m_vel;
	/// <summary>
	/// The forward vector of the listener
	/// </summary>
	PxVec3 m_forward;
	/// <summary>
	/// The up vector of the listener
	/// </summary>
	PxVec3 m_up;
};
