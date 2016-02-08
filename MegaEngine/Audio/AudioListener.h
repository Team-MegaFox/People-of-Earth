// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 02-01-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 02-03-2016
// ***********************************************************************
// <copyright file="AudioListener.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
// </summary>
// ***********************************************************************

#pragma once
#include "..\Audio\AudioEngine.h"
#include "..\Core\Utility.h"

class AudioListener
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="AudioListener"/> class.
	/// </summary>
	AudioListener() { }
	/// <summary>
	/// Finalizes an instance of the <see cref="AudioListener"/> class.
	/// </summary>
	~AudioListener() {}

	/// <summary>
	/// Sets as the scene audio listener.
	/// </summary>
	void setAsListener(GameObject * parent)
	{
		glm::vec3 forward = Utility::getForward(*parent->getTransform()->getRotation());
		glm::vec3 up = Utility::getUp(*parent->getTransform()->getRotation());

		AudioEngine::getSystem()->set3DListenerAttributes(
			0, 
			&glmToFMOD(*parent->getTransform()->getPosition()),
			&glmToFMOD(glm::vec3(0.5f)), 
			&glmToFMOD(forward), 
			&glmToFMOD(up));
	}

	/// <summary>
	/// Sets as the scene audio listener.
	/// </summary>
	void setAsListener(glm::vec3 pos, glm::vec3 vel, glm::vec3 forward, glm::vec3 up)
	{
		AudioEngine::getSystem()->set3DListenerAttributes(
			0,
			&glmToFMOD(pos),
			&glmToFMOD(vel),
			&glmToFMOD(forward),
			&glmToFMOD(up));
	}

private:

	/// <summary>
	/// Converts glm::vec3's to FMOD_VECTOR *'s
	/// for use in FMOD's positioning of the listener
	/// and sound / stream positioning
	/// </summary>
	/// <param name="vector">The glm vector to convert.</param>
	/// <returns>The resulting FMOD vector conversion.</returns>
	FMOD_VECTOR glmToFMOD(glm::vec3 vector)
	{
		FMOD_VECTOR Temp;

		Temp.x = vector.x;
		Temp.y = vector.y;
		Temp.z = vector.z;

		return Temp;
	}
};

