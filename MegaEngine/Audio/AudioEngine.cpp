// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Jesse Derochie
// Last Modified On : 02-24-2016
// ***********************************************************************
// <copyright file="AudioEngine.cpp" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
/*
	This AudioEngine class is a wrapper around some of FMOD's methods and abilities,
	The goal of this engine was simply to allow for 3D sound and music to
	be used in any game built with MegaEngine. On behalf of TeamMegaFox I
	would like to thank the developers of FMOD for their engine, and for
	making it available to students like us.
	You can learn more about FMOD by going to there website here : http://www.fmod.org/
	or if the link is for some reason dead feel free to look them up
	using "The Great and Powerful God" Google.
*/
// </summary>
// ***********************************************************************
#include "AudioEngine.h"

FMOD::System * AudioEngine::m_system = nullptr;

AudioEngine::AudioEngine()
{
	// Create FMOD system object
	m_result = FMOD::System_Create(&m_system);
	FMODVerifyResult(m_result);

	init();
}

void AudioEngine::init()
{
	unsigned int version;
	int numDrivers;
	FMOD_SPEAKERMODE speakerMode;
	FMOD_CAPS caps;
	char name[256];

	// Get version of FMOD
	m_result = m_system->getVersion(&version);
	FMODVerifyResult(m_result);

	if (version < FMOD_VERSION)
	{
		std::cout << "You're using an old version of FMOD." << std::endl;
		return;
	}

	m_result = m_system->getNumDrivers(&numDrivers);
	FMODVerifyResult(m_result);

	if (numDrivers == 0)
	{
		m_result = m_system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
		FMODVerifyResult(m_result);
	}
	else
	{
		m_result = m_system->getDriverCaps(0, &caps, 0, &speakerMode);
		FMODVerifyResult(m_result);

		/*

		Set the user selected speaker mode

		*/
		m_result = m_system->setSpeakerMode(speakerMode);
		FMODVerifyResult(m_result);

		if (caps & FMOD_CAPS_HARDWARE_EMULATED)
		{
			/*

			The user has the 'Acceleration slider set to off!
			This is really bad for latency, warn the user about this.

			*/
			std::cout << "Acceleration is not activated, please activate accleration\nto reduce latency." << std::endl;

			m_result = m_system->setDSPBufferSize(1024, 10);
			FMODVerifyResult(m_result);
		}

		if (strstr(name, "SigmaTel"))
		{
			/*

			SigmaTel sound devices crackle for some reason if the format is PCM 16bit
			PCM floating point output seems to solve it

			*/
			m_result = m_system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0, 0, FMOD_DSP_RESAMPLER_LINEAR);
			FMODVerifyResult(m_result);
		}
	}

	m_result = m_system->init(MAX_NUM_CHANNELS, FMOD_INIT_NORMAL, 0);

	if (m_result == FMOD_ERR_OUTPUT_CREATEBUFFER)
	{
		/*

		If the speaker mode selected isn't compatible with
		this sound card, switch the speaker mode to stereo instead

		*/

		m_result = m_system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
		FMODVerifyResult(m_result);

		m_result = m_system->init(MAX_NUM_CHANNELS, FMOD_INIT_NORMAL, 0);
	}

	FMODVerifyResult(m_result);
}

void AudioEngine::dispose()
{
	// Clean up the System Object
	if (m_system != nullptr)
	{
		m_system->release();
	}
}

void AudioEngine::update()
{
	FMODVerifyResult(m_system->update());
}