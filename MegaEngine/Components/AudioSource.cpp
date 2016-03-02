// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Jesse Derochie
// Last Modified On : 02-25-2016
// ***********************************************************************
// <copyright file="AudioSource.cpp" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
/*
This AudioSource.h file was created to allow users to interface with
the AudioEngine in MegaEngine, the methods available within this class
make it so that anything we could foresee being useful was obtainable.
*/
// </summary>
// ***********************************************************************

#include "AudioSource.h"

AudioSource::AudioSource(const Sound & sound) :
m_soundSource(sound) 
{}

AudioSource::AudioSource(const Stream & stream) :
m_streamSource(stream)
{}

void AudioSource::playSound() { m_soundSource.playSound(); }

void AudioSource::playStream(bool looping) { m_streamSource.playStream(looping); }

void AudioSource::stopSound() { m_soundSource.stop(); }

void AudioSource::stopStream() { m_streamSource.stop(); }

void AudioSource::pauseSound(bool paused) { m_soundSource.pauseSound(paused); }

void AudioSource::pauseStream(bool paused) { m_streamSource.pauseStream(paused); }

bool AudioSource::isSoundPlaying()
{
	if (m_soundSource.isSoundPlaying())
		return true;
	else
		return false;
}

bool AudioSource::isStreamPlaying()
{
	if (m_streamSource.isStreamPlaying())
		return true;
	else
		return false;
}

float AudioSource::getSoundVolume() { return m_soundSource.getSoundVolume(); }

float AudioSource::getStreamVolume() { return m_streamSource.getStreamVolume(); }

void AudioSource::setSoundVolume(float volume) { m_soundSource.setSoundEffectVolume(volume); }

void AudioSource::setStreamVolume(float volume) { m_streamSource.setStreamEffectVolume(volume); }

void AudioSource::setSoundPosition(physx::PxVec3 pos) { m_soundSource.setSoundPosVel(pos); }

void AudioSource::setStreamPosition(physx::PxVec3 pos) { m_streamSource.setStreamPosVel(pos); }

void AudioSource::setSoundPan(float pan) { m_soundSource.setSoundPan(pan); }

void AudioSource::setStreamPan(float pan) { m_streamSource.setStreamPan(pan); }

void AudioSource::setSoundDoppler(float dop) { m_soundSource.setSoundDopplerLevel(dop); }

void AudioSource::setStreamDoppler(float dop) { m_streamSource.setStreamDopplerLevel(dop); }

void AudioSource::setupSoundCone(physx::PxVec3 orient, float iCA, float oCA, float oVol)
{
	m_soundSource.setSoundConeOrientation(orient);
	m_soundSource.setSoundConeSettings(iCA, oCA, oVol);
}

void AudioSource::setSoundDistanceFilter(bool custom, bool customLevel, float centerFreq)
{
	m_soundSource.setSoundDistanceFilter(custom, customLevel, centerFreq);
}

void AudioSource::setStreamDistanceFilter(bool custom, bool customLevel, float centerFreq)
{
	m_streamSource.setStreamDistanceFilter(custom, customLevel, centerFreq);
}

void AudioSource::setSound3DMinDist(float min, float max/* = NULL */) { m_soundSource.setSound3DMinMaxDistance(min, max); }

void AudioSource::setStream3DMinDist(float min, float max/* = NULL */) { m_streamSource.setStream3DMinMaxDistance(min, max); }
