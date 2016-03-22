// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 02-01-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 03-01-2016
// ***********************************************************************
// <copyright file="Sound.cpp" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
// </summary>
// ***********************************************************************

#include "Sound.h"

Sound::Sound(const std::string& fileName, bool TwoD /* = false */) :
m_twoDimensionalSound(TwoD)
{
	m_fileName = "Assets/Music/" + fileName;

	m_soundPair.first = nullptr;
	m_soundPair.second = nullptr;

	setSound();
}

void Sound::setSound()
{
	if (m_twoDimensionalSound)
	{
		AudioEngine::FMODVerifyResult(AudioEngine::getSystem()->createSound(m_fileName.c_str(), m_twoDimensional, 0, &m_soundPair.first));
		AudioEngine::FMODVerifyResult(AudioEngine::getSystem()->playSound(FMOD_CHANNELINDEX::FMOD_CHANNEL_REUSE, m_soundPair.first, false, &m_soundPair.second));
	}
	else
	{
		AudioEngine::FMODVerifyResult(AudioEngine::getSystem()->createSound(m_fileName.c_str(), m_threeDimensional, 0, &m_soundPair.first));
		AudioEngine::FMODVerifyResult(AudioEngine::getSystem()->playSound(FMOD_CHANNELINDEX::FMOD_CHANNEL_REUSE, m_soundPair.first, false, &m_soundPair.second));
	}
	setSoundEffectVolume(AudioEngine::getSoundVolume());
}

void Sound::playSound()
{
	AudioEngine::FMODVerifyResult(AudioEngine::getSystem()->playSound(FMOD_CHANNELINDEX::FMOD_CHANNEL_REUSE, m_soundPair.first, true, &m_soundPair.second));
	AudioEngine::FMODVerifyResult(m_soundPair.second->setPaused(false));
}

void Sound::pauseSound(bool pause)
{
	AudioEngine::FMODVerifyResult(m_soundPair.second->setPaused(pause));
}

void Sound::stop()
{
	AudioEngine::FMODVerifyResult(m_soundPair.second->stop());
}

bool Sound::isSoundPlaying()
{
	bool result;

	AudioEngine::FMODVerifyResult(m_soundPair.second->isPlaying(&result));

	return result;
}

void Sound::setSoundEffectVolume(float volumeLevel)
{
	AudioEngine::FMODVerifyResult(m_soundPair.second->setVolume(volumeLevel));
}

float & Sound::getSoundVolume()
{
	AudioEngine::FMODVerifyResult(m_soundPair.second->getVolume(&m_soundVolume));
	return m_soundVolume;
}

void Sound::setSoundPosVel(PxVec3 pos, PxVec3 vel/* = PxVec3(0.0f, 0.0f, 0.0f)*/)
{
	AudioEngine::FMODVerifyResult(m_soundPair.second->set3DAttributes(&AudioEngine::physxToFMOD(pos), &AudioEngine::physxToFMOD(vel)));
}

void Sound::setSoundPan(float pan)
{
	AudioEngine::FMODVerifyResult(m_soundPair.second->setPan(pan));
}

void Sound::setSoundDopplerLevel(float dopplerLevel)
{
	AudioEngine::FMODVerifyResult(m_soundPair.second->set3DDopplerLevel(dopplerLevel));
}

void Sound::setSoundConeOrientation(PxVec3 orientation)
{
	AudioEngine::FMODVerifyResult(m_soundPair.second->set3DConeOrientation(&AudioEngine::physxToFMOD(orientation)));
}

void Sound::setSoundConeSettings(float insideConeAngle, float outsideConeAngle, float outsideVolume)
{
	AudioEngine::FMODVerifyResult(m_soundPair.second->set3DConeSettings(insideConeAngle, outsideConeAngle, outsideVolume));
}

void Sound::setSoundDistanceFilter(bool custom, bool customLevel, float centerFreq)
{
	AudioEngine::FMODVerifyResult(m_soundPair.second->set3DDistanceFilter(custom, customLevel, centerFreq));
}

void Sound::setSound3DMinMaxDistance(float min, float max/* = NULL */)
{
	AudioEngine::FMODVerifyResult(m_soundPair.second->set3DMinMaxDistance(min, max));
}
