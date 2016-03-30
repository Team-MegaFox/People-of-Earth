// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 03-30-2016
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 03-30-2016
// ***********************************************************************
// <copyright file="MegaEngine.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#include "AudioEngine.h"
#include <iostream>
#include <FMOD\fmod_errors.h>

AudioEngine::AudioEngine()
{
	ERRCHECK_OK(FMOD::System_Create(&m_system));

	unsigned int version;
	m_system->getVersion(&version);

	if (version < FMOD_VERSION)
	{
		printf("FMOD lib version %08x doesn't match header version %08x", version, FMOD_VERSION);
	}

	void* extradriverdata = 0;
	ERRCHECK_OK(m_system->init(32, FMOD_INIT_NORMAL, extradriverdata));

	ERRCHECK_OK(m_system->createChannelGroup("Sounds", &m_sounds));
	ERRCHECK_OK(m_system->createChannelGroup("Streams", &m_streams));

	ERRCHECK_OK(m_system->getMasterChannelGroup(&m_masterGroup));

	ERRCHECK_OK(m_masterGroup->addGroup(m_sounds));
	ERRCHECK_OK(m_masterGroup->addGroup(m_streams));

	ERRCHECK_OK(m_system->set3DSettings(1.0, 100.0f, 1.0f));
}

AudioEngine::~AudioEngine()
{
	m_system->close();
	m_system->release();
}

void AudioEngine::update()
{
	m_system->update();
}

float AudioEngine::getSoundVolume() const
{
	float volume = -1.0f;
	ERRCHECK_OK(m_sounds->getVolume(&volume));
	return volume;
}

float AudioEngine::getStreamVolume() const
{
	float volume = -1.0f;
	ERRCHECK_OK(m_streams->getVolume(&volume));
	return volume;
}

void AudioEngine::setSoundVolume(float volume)
{
	ERRCHECK_OK(m_sounds->setVolume(volume));
}

void AudioEngine::setStreamVolume(float volume)
{
	ERRCHECK_OK(m_streams->setVolume(volume));
}

void ERRCHECK_ok(FMOD_RESULT result, const char *file, int line)
{
	if (result != FMOD_OK)
	{
		printf("%s(%d): FMOD error %d - %s\n", file, line, result, FMOD_ErrorString(result));
	}
}

void ERRCHECK_invalid(FMOD_RESULT result, const char *file, int line)
{
	if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
	{
		printf("%s(%d): FMOD error %d - %s\n", file, line, result, FMOD_ErrorString(result));
	}
}