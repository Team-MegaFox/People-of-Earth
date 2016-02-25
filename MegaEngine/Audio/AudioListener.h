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
	void setAsListener(glm::vec3 pos, glm::vec3 vel, glm::vec3 forward, glm::vec3 up)
	{
		AudioEngine::FMODVerifyResult(AudioEngine::getSystem()->set3DListenerAttributes(
			0,
			&AudioEngine::glmToFMOD(pos),
			&AudioEngine::glmToFMOD(vel),
			&AudioEngine::glmToFMOD(forward),
			&AudioEngine::glmToFMOD(up)));
	}
};

