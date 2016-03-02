// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 02-01-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 03-01-2016
// ***********************************************************************
// <copyright file="Stream.cpp" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
// </summary>
// ***********************************************************************

#include "Stream.h"

Stream::Stream(const std::string& fileName, bool TwoD /* = false*/) :
m_twoDimensionalSound(TwoD)
{
	m_fileName = "Assets/Music/" + fileName;

	m_streamPair.first = nullptr;
	m_streamPair.second = nullptr;

	setStream();
}

void Stream::setStream()
{
	if (m_twoDimensionalSound)
	{
		AudioEngine::FMODVerifyResult(AudioEngine::getSystem()->createSound(m_fileName.c_str(), m_twoDimensional, 0, &m_streamPair.first));
		AudioEngine::FMODVerifyResult(AudioEngine::getSystem()->playSound(FMOD_CHANNELINDEX::FMOD_CHANNEL_REUSE, m_streamPair.first, true, &m_streamPair.second));
	}
	else
	{
		AudioEngine::FMODVerifyResult(AudioEngine::getSystem()->createSound(m_fileName.c_str(), m_threeDimensional, 0, &m_streamPair.first));
		AudioEngine::FMODVerifyResult(AudioEngine::getSystem()->playSound(FMOD_CHANNELINDEX::FMOD_CHANNEL_REUSE, m_streamPair.first, true, &m_streamPair.second));
	}
}

void Stream::playStream(bool looping)
{
	if (looping)
	{
		AudioEngine::FMODVerifyResult(m_streamPair.second->setMode(FMOD_LOOP_NORMAL));
		AudioEngine::FMODVerifyResult(m_streamPair.second->setLoopCount(-1));
	}
	AudioEngine::FMODVerifyResult(m_streamPair.second->setPaused(false));
}

void Stream::pauseStream(bool pause)
{
	AudioEngine::FMODVerifyResult(m_streamPair.second->setPaused(pause));
}

void Stream::stop()
{
	AudioEngine::FMODVerifyResult(m_streamPair.second->stop());
}

bool Stream::isStreamPlaying()
{
	bool result;

	AudioEngine::FMODVerifyResult(m_streamPair.second->isPlaying(&result));

	return result;
}

void Stream::setStreamEffectVolume(float volumeLevel)
{
	AudioEngine::FMODVerifyResult(m_streamPair.second->setVolume(volumeLevel));
}

float & Stream::getStreamVolume()
{
	AudioEngine::FMODVerifyResult(m_streamPair.second->getVolume(&m_streamVolume));
	return m_streamVolume;
}

void Stream::setStreamPosVel(physx::PxVec3 pos, physx::PxVec3 vel/* = physx::PxVec3(0.0f, 0.0f, 0.0f)*/)
{
	AudioEngine::FMODVerifyResult(m_streamPair.second->set3DAttributes(&AudioEngine::physxToFMOD(pos), &AudioEngine::physxToFMOD(vel)));
}

void Stream::setStreamPan(float pan)
{
	AudioEngine::FMODVerifyResult(m_streamPair.second->setPan(pan));
}

void Stream::setStreamDopplerLevel(float dopplerLevel)
{
	AudioEngine::FMODVerifyResult(m_streamPair.second->set3DDopplerLevel(dopplerLevel));
}

void Stream::setStreamDistanceFilter(bool custom, bool customLevel, float centerFreq)
{
	AudioEngine::FMODVerifyResult(m_streamPair.second->set3DDistanceFilter(custom, customLevel, centerFreq));
}

void Stream::setStream3DMinMaxDistance(float min, float max/* = NULL */)
{
	AudioEngine::FMODVerifyResult(m_streamPair.second->set3DMinMaxDistance(min, max));
}
