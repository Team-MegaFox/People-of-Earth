// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 02-01-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 02-25-2016
// ***********************************************************************
// <copyright file="Sound.cpp" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
// </summary>
// ***********************************************************************

#include "Sound.h"

Sound::Sound(const std::string& fileName)
{
	m_fileName = "Assets/Music/" + fileName;

	m_soundPair.first = nullptr;
	m_soundPair.second = nullptr;

	setSound();
}

void Sound::setSound()
{
	AudioEngine::FMODVerifyResult(AudioEngine::getSystem()->createSound(m_fileName.c_str(), FMOD_3D | FMOD_DEFAULT, 0, &m_soundPair.first));
	AudioEngine::FMODVerifyResult(AudioEngine::getSystem()->playSound(FMOD_CHANNELINDEX::FMOD_CHANNEL_REUSE, m_soundPair.first, true, &m_soundPair.second));
}

void Sound::playSound()
{
	AudioEngine::FMODVerifyResult(AudioEngine::getSystem()->playSound(FMOD_CHANNELINDEX::FMOD_CHANNEL_REUSE, m_soundPair.first, true, &m_soundPair.second));
	m_soundPair.second->setPaused(false);
}

void Sound::pauseSound(bool pause)
{
	m_soundPair.second->setPaused(pause);
}

void Sound::stop()
{
	m_soundPair.second->stop();
}

bool Sound::isSoundPlaying()
{
	bool result;

	m_soundPair.second->isPlaying(&result);

	return result;
}

void Sound::setSoundEffectVolume(float volumeLevel)
{
	m_soundPair.second->setVolume(volumeLevel);
}

float & Sound::getSoundVolume()
{
	m_soundPair.second->getVolume(&m_soundVolume);
	return m_soundVolume;
}

void Sound::setSoundPosVel(glm::vec3 pos, glm::vec3 vel/* = glm::vec3(0.0f)*/)
{
	m_soundPair.second->set3DAttributes(&glmToFMOD(pos), &glmToFMOD(vel));
}

void Sound::setSoundPan(float pan)
{
	m_soundPair.second->setPan(pan);
}

void Sound::setSoundDopplerLevel(float dopplerLevel)
{
	m_soundPair.second->set3DDopplerLevel(dopplerLevel);
}

void Sound::setSoundConeOrientation(glm::vec3 orientation)
{
	m_soundPair.second->set3DConeOrientation(&glmToFMOD(orientation));
}

void Sound::setSoundConeSettings(float insideConeAngle, float outsideConeAngle, float outsideVolume)
{
	m_soundPair.second->set3DConeSettings(insideConeAngle, outsideConeAngle, outsideVolume);
}

void Sound::setSoundDistanceFilter(bool custom, bool customLevel, float centerFreq)
{
	m_soundPair.second->set3DDistanceFilter(custom, customLevel, centerFreq);
}

void Sound::setSound3DMinMaxDistance(float min, float max/* = NULL */)
{
	m_soundPair.second->set3DMinMaxDistance(min, max);
}

FMOD_VECTOR Sound::glmToFMOD(glm::vec3 vector)
{
	FMOD_VECTOR Temp;

	Temp.x = vector.x;
	Temp.y = vector.y;
	Temp.z = vector.z;

	return Temp;
}