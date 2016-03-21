// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 03-21-2016
// ***********************************************************************
// <copyright file="AudioSource->cpp" company="Team MegaFox">
//     Copyright (c) Team MegaFox-> All rights reserved->
// </copyright>
// <summary>
/*
This AudioSource->h file was created to allow users to interface with
the AudioEngine in MegaEngine, the methods available within this class
make it so that anything we could foresee being useful was obtainable->
*/
// </summary>
// ***********************************************************************

#include "AudioSource.h"

AudioSource::AudioSource(const std::string & fileName, AudioType type, bool TwoD /*= false*/)
{
	if (type == SOUND)
	{
		m_soundSource = new Sound(fileName, TwoD);
	}
	else if (type == STREAM)
	{
		m_streamSource = new Stream(fileName, TwoD);
	}
}

AudioSource::~AudioSource()
{
	if (m_soundSource != nullptr)
	{
		delete m_soundSource;
	}
	else
	{
		delete m_streamSource;
	}
}

bool AudioSource::isStream()
{
	if (m_soundSource != nullptr)
	{
		return false;
	}
	else if (m_streamSource != nullptr)
	{
		return true;
	}
}

void AudioSource::play(bool looping /*= false*/) 
{ 
	if (m_soundSource != nullptr)
	{
		m_soundSource->playSound();
	}
	else
	{
		m_streamSource->playStream(looping);
	}
}

void AudioSource::stop() 
{
	if (m_soundSource != nullptr)
	{
		m_soundSource->stop();
	}
	else
	{
		m_streamSource->stop();
	}
}

void AudioSource::pause(bool paused) 
{ 
	if (m_soundSource != nullptr)
	{
		m_soundSource->pauseSound(paused);
	}
	else
	{
		m_streamSource->pauseStream(paused);
	}
}

bool AudioSource::isPlaying()
{
	if (m_soundSource != nullptr)
	{
		if (m_soundSource->isSoundPlaying())
			return true;
		else
			return false;
	}
	else
	{
		if (m_streamSource->isStreamPlaying())
			return true;
		else
			return false;
	}
}

float AudioSource::getVolume() 
{ 
	if (m_soundSource != nullptr)
	{
		return m_soundSource->getSoundVolume();
	}
	else
	{
		return m_streamSource->getStreamVolume();
	}
}

void AudioSource::setVolume(float volume) 
{ 
	m_volumeRatioValue = volume;
	if (m_soundSource != nullptr)
	{
		m_soundSource->setSoundEffectVolume(
			m_volumeRatioValue * getCoreEngine()->getAudioEngine()->getSoundVolume());
	}
	else
	{
		m_streamSource->setStreamEffectVolume(
			m_volumeRatioValue * getCoreEngine()->getAudioEngine()->getStreamVolume());
	}
}

void AudioSource::setNewVolume()
{
	if (m_soundSource != nullptr)
	{
		m_soundSource->setSoundEffectVolume(
			m_volumeRatioValue * getCoreEngine()->getAudioEngine()->getStreamVolume());
	}
	else
	{
		m_streamSource->setStreamEffectVolume(
			m_volumeRatioValue * getCoreEngine()->getAudioEngine()->getSoundVolume());
	}
}

void AudioSource::setPosition(PxVec3 pos) 
{ 
	if (m_soundSource != nullptr)
	{
		m_soundSource->setSoundPosVel(pos);
	}
	else
	{
		m_streamSource->setStreamPosVel(pos);
	}
}

void AudioSource::setPan(float pan) 
{ 
	if (m_soundSource != nullptr)
	{
		m_soundSource->setSoundPan(pan);
	}
	else
	{
		m_streamSource->setStreamPan(pan);
	}
}

void AudioSource::setDoppler(float dop) 
{ 
	if (m_soundSource != nullptr)
	{
		m_soundSource->setSoundDopplerLevel(dop);
	}
	else
	{
		m_streamSource->setStreamDopplerLevel(dop);
	}
}

void AudioSource::setupCone(PxVec3 orient, float iCA, float oCA, float oVol)
{
	if (m_soundSource != nullptr)
	{
		m_soundSource->setSoundConeOrientation(orient);
		m_soundSource->setSoundConeSettings(iCA, oCA, oVol);
	}
}

void AudioSource::setDistanceFilter(bool custom, bool customLevel, float centerFreq)
{
	if (m_soundSource != nullptr)
	{
		m_soundSource->setSoundDistanceFilter(custom, customLevel, centerFreq);
	}
	else
	{
		m_streamSource->setStreamDistanceFilter(custom, customLevel, centerFreq);
	}
}

void AudioSource::set3DMinDist(float min, float max/* = NULL */) 
{ 
	if (m_soundSource != nullptr)
	{
		m_soundSource->setSound3DMinMaxDistance(min, max);
	}
	else
	{
		m_streamSource->setStream3DMinMaxDistance(min, max);
	}
}
