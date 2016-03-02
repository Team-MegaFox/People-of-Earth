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
	void setAsListener(physx::PxVec3 pos, physx::PxVec3 vel, physx::PxVec3 forward, physx::PxVec3 up)
	{
		AudioEngine::FMODVerifyResult(AudioEngine::getSystem()->set3DListenerAttributes(
			0,
			&AudioEngine::physxToFMOD(pos),
			&AudioEngine::physxToFMOD(vel),
			&AudioEngine::physxToFMOD(forward),
			&AudioEngine::physxToFMOD(up)));
	}
};

