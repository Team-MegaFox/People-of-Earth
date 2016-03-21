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
	void setAsListener(PxVec3 pos, PxVec3 vel, PxVec3 forward, PxVec3 up)
	{
		AudioEngine::FMODVerifyResult(AudioEngine::getSystem()->set3DListenerAttributes(
			0,
			&AudioEngine::physxToFMOD(pos),
			&AudioEngine::physxToFMOD(vel),
			&AudioEngine::physxToFMOD(forward),
			&AudioEngine::physxToFMOD(up)));
	}
};

