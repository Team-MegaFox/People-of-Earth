// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 02-01-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 02-25-2016
// ***********************************************************************
// <copyright file="Stream.cpp" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
// </summary>
// ***********************************************************************

#include "Stream.h"

Stream::Stream(const std::string& fileName)
{
	m_fileName = "Assets/Music/" + fileName;

	m_streamPair.first = nullptr;
	m_streamPair.second = nullptr;

	setStream();
}

void Stream::setStream()
{
	AudioEngine::FMODVerifyResult(AudioEngine::getSystem()->createSound(m_fileName.c_str(), FMOD_DEFAULT, 0, &m_streamPair.first));
	AudioEngine::FMODVerifyResult(AudioEngine::getSystem()->playSound(FMOD_CHANNELINDEX::FMOD_CHANNEL_REUSE, m_streamPair.first, true, &m_streamPair.second));
}

void Stream::playStream(bool looping)
{
	if (looping)
	{
		m_streamPair.second->setMode(FMOD_LOOP_NORMAL);
		m_streamPair.second->setLoopCount(-1);
	}
	m_streamPair.second->setPaused(false);
}

void Stream::pauseStream(bool pause)
{
	m_streamPair.second->setPaused(pause);
}

void Stream::stop()
{
	m_streamPair.second->stop();
}

bool Stream::isStreamPlaying()
{
	bool result;

	m_streamPair.second->isPlaying(&result);

	return result;
}

void Stream::setStreamEffectVolume(float volumeLevel)
{
	m_streamPair.second->setVolume(volumeLevel);
}

float & Stream::getStreamVolume()
{
	m_streamPair.second->getVolume(&m_streamVolume);
	return m_streamVolume;
}

void Stream::setStreamPosVel(glm::vec3 pos, glm::vec3 vel/* = glm::vec3(0.0f)*/)
{
	m_streamPair.second->set3DAttributes(&glmToFMOD(pos), &glmToFMOD(vel));
}

void Stream::setStreamPan(float pan)
{
	m_streamPair.second->setPan(pan);
}

void Stream::setStreamDopplerLevel(float dopplerLevel)
{
	m_streamPair.second->set3DDopplerLevel(dopplerLevel);
}

void Stream::setStreamDistanceFilter(bool custom, bool customLevel, float centerFreq)
{
	m_streamPair.second->set3DDistanceFilter(custom, customLevel, centerFreq);
}

void Stream::setStream3DMinMaxDistance(float min, float max/* = NULL */)
{
	m_streamPair.second->set3DMinMaxDistance(min, max);
}

FMOD_VECTOR Stream::glmToFMOD(glm::vec3 vector)
{
	FMOD_VECTOR Temp;

	Temp.x = vector.x;
	Temp.y = vector.y;
	Temp.z = vector.z;

	return Temp;
}