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
#include "Audio.h"

Audio::Audio(AudioEngine* audioEngine) :
m_audioEngine(audioEngine)
{
}

Audio::~Audio()
{
	stop();
	//ERRCHECK_OK(m_sound->release());
}

void Audio::stop() const
{
	if (m_channel) ERRCHECK_OK(m_channel->stop());
}

void Audio::set3DDistance(float min, float max)
{
	if (m_channel) ERRCHECK_OK(m_sound->set3DMinMaxDistance(min, max));
}

void Audio::setPaused(bool paused)
{
	if (m_channel) ERRCHECK_OK(m_channel->setPaused(paused));
}

void Audio::setPosition(const PxVec3& pos, const PxVec3& vel)
{
	FMOD_VECTOR posF = { pos.x, pos.y, pos.z };
	FMOD_VECTOR velF = { vel.x, vel.y, vel.z };

	if (m_channel) ERRCHECK_OK(m_channel->set3DAttributes(&posF, &velF));
}

void Audio::setVolume(float volume)
{
	if (m_channel) ERRCHECK_OK(m_channel->setVolume(volume));
}

void Audio::setLooping(bool looping, int amount)
{
	if (looping)
	{
		if (m_channel)
		{
			ERRCHECK_OK(m_channel->setMode(FMOD_LOOP_NORMAL));
			ERRCHECK_OK(m_channel->setLoopCount(amount));
		}
	}
	else
	{
		if (m_channel) ERRCHECK_OK(m_channel->setMode(FMOD_LOOP_OFF));
	}
}

bool Audio::isPaused() const
{
	bool paused = false;
	if (m_channel) ERRCHECK_INVALID(m_channel->getPaused(&paused));
	return paused;
}

bool Audio::isPlaying() const
{
	bool playing = false;
	if (m_channel) ERRCHECK_INVALID(m_channel->isPlaying(&playing));
	return playing;
}

float Audio::getVolume() const
{
	float volume = -1.0f;
	if (m_channel) ERRCHECK_INVALID(m_channel->getVolume(&volume));
	return volume;
}

bool Audio::getLooping() const
{
	bool result = false;
	FMOD_MODE mode;
	if (m_channel) ERRCHECK_INVALID(m_channel->getMode(&mode));
	if (mode & FMOD_LOOP_NORMAL)
	{
		result = true;
	}
	return result;
}

void Sound::createAudio(const std::string& fileName, AudioDimension audioDim)
{
	FMOD_MODE mode = FMOD_LOOP_OFF | FMOD_3D_WORLDRELATIVE | FMOD_3D_INVERSEROLLOFF;
	if (audioDim == AudioDimension::TWOD)
	{
		mode |= FMOD_2D;
	}
	else if (audioDim == AudioDimension::THREED)
	{
		mode |= FMOD_3D;
	}
	ERRCHECK_OK(m_audioEngine->getSystem()->createSound(fileName.c_str(), mode, nullptr, &m_sound));

	//ERRCHECK(m_audioEngine->getSystem()->playSound(m_sound, m_audioEngine->getSoundGroup(), true, &m_channel));
}

void Sound::play()
{
	ERRCHECK_OK(m_audioEngine->getSystem()->playSound(m_sound, m_audioEngine->getSoundGroup(), false, &m_channel));
}

void Stream::createAudio(const std::string& fileName, AudioDimension audioDim)
{
	FMOD_MODE mode = FMOD_LOOP_OFF | FMOD_3D_WORLDRELATIVE | FMOD_3D_INVERSEROLLOFF;
	if (audioDim == AudioDimension::TWOD)
	{
		mode |= FMOD_2D;
	}
	else if (audioDim == AudioDimension::THREED)
	{
		mode |= FMOD_3D;
	}
	ERRCHECK_OK(m_audioEngine->getSystem()->createStream(fileName.c_str(), mode, nullptr, &m_sound));

	//ERRCHECK(m_audioEngine->getSystem()->playSound(m_sound, m_audioEngine->getStreamGroup(), false, &m_channel));
}

void Stream::play()
{
	ERRCHECK_OK(m_audioEngine->getSystem()->playSound(m_sound, m_audioEngine->getStreamGroup(), false, &m_channel));
}
