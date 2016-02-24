// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 02-01-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 02-24-2016
// ***********************************************************************
// <copyright file="StreamSource.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
// </summary>
// ***********************************************************************


#pragma once
#include "..\Audio\AudioEngine.h"

class Stream
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="StreamSource"/> class.
	/// </summary>
	Stream() {}
	/// <summary>
	/// Initializes a new instance of the <see cref="StreamSource"/> class.
	/// </summary>
	/// <param name="fileName">Name of the file.</param>
	Stream(const std::string& fileName)
	{ 
		m_fileName = "Assets/Music/" + fileName;

		m_streamPair.first = nullptr;
		m_streamPair.second = nullptr;

		setStream();
	}
	/// <summary>
	/// Finalizes an instance of the <see cref="StreamSource"/> class.
	/// </summary>
	~Stream() { }

	/// <summary>
	/// Sets the stream.
	/// </summary>
	void setStream()
	{
		AudioEngine::FMODVerifyResult(AudioEngine::getSystem()->createSound(m_fileName.c_str(), FMOD_3D | FMOD_DEFAULT, 0, &m_streamPair.first));
		AudioEngine::FMODVerifyResult(AudioEngine::getSystem()->playSound(FMOD_CHANNELINDEX::FMOD_CHANNEL_REUSE, m_streamPair.first, true, &m_streamPair.second));
	}

	/// <summary>
	/// Plays the stream.
	/// </summary>
	/// <param name="looping">if set to <c>true</c> [looping].</param>
	void playStream(bool looping)
	{
		if (looping)
		{
			m_streamPair.second->setMode(FMOD_LOOP_NORMAL);
			m_streamPair.second->setLoopCount(-1);
		}
		m_streamPair.second->setPaused(false);
	}

	/// <summary>
	/// Pauses the stream.
	/// </summary>
	/// <param name="pause">if set to <c>true</c> [pause].</param>
	void pauseStream(bool pause)
	{
		m_streamPair.second->setPaused(pause);
	}

	/// <summary>
	/// Stops all streams.
	/// </summary>
	void stop()
	{
		m_streamPair.second->stop();
	}

	/// <summary>
	/// Determines whether this stream is playing.
	/// </summary>
	/// <returns></returns>
	bool isStreamPlaying()
	{
		bool result;

		m_streamPair.second->isPlaying(&result);

		return result;
	}

	/// <summary>
	/// Sets the stream effect volume.
	/// </summary>
	/// <param name="volumeLevel">The volume level.</param>
	void setStreamEffectVolume(float volumeLevel)
	{
		m_streamPair.second->setVolume(volumeLevel);
	}

	/// <summary>
	/// Gets the stream volume.
	/// </summary>
	/// <returns></returns>
	float & getStreamVolume()
	{
		m_streamPair.second->getVolume(&m_streamVolume);
		return m_streamVolume;
	}

	/// <summary>
	/// Sets the stream position vel.
	/// </summary>
	/// <param name="pos">The position.</param>
	/// <param name="vel">The vel.</param>
	void setStreamPosVel(glm::vec3 pos, glm::vec3 vel = glm::vec3(0.0f))
	{
		m_streamPair.second->set3DAttributes(&glmToFMOD(pos), &glmToFMOD(vel));
	}

	/// <summary>
	/// Pan level, from -1.0 (left) to 1.0 (right), default = 0 (center).
	/// </summary>
	/// <param name="pan">The pan.</param>
	void setStreamPan(float pan)
	{
		m_streamPair.second->setPan(pan);
	}

	/// <summary>
	/// Sets the stream doppler level.
	/// Use with (but before) setStreamDistanceFilter for proper effect
	/// </summary>
	/// <param name="dopplerLevel">The doppler level.</param>
	void setStreamDopplerLevel(float dopplerLevel)
	{
		m_streamPair.second->set3DDopplerLevel(dopplerLevel);
	}

	/// <summary>
	/// Sets the sound distance filter.
	/// use with (but after) setStreamDopplerLevel for proper effect
	/// </summary>
	/// <param name="custom">if set to <c>true</c> [custom].</param>
	/// <param name="customLevel">if set to <c>true</c> [custom level].</param>
	/// <param name="centerFreq">The center freq.</param>
	void setStreamDistanceFilter(bool custom, bool customLevel, float centerFreq)
	{
		m_streamPair.second->set3DDistanceFilter(custom, customLevel, centerFreq);
	}

	/// <summary>
	/// In summary, increase the mindistance of a stream to make it 'louder' in a 3D world, 
	/// and decrease it to make it 'quieter' in a 3D world.
	/// Maxdistance is effectively obsolete unless you need the stream to stop fading out at 
	/// a certain point.Do not adjust this from the default if you dont need to.
	///	Some people have the confusion that maxdistance is the point the stream will fade out to, 
	/// this is not the case.
	/// </summary>
	/// <param name="min">The minimum.</param>
	/// <param name="max">The maximum.</param>
	void setStream3DMinMaxDistance(float min, float max = NULL)
	{
		m_streamPair.second->set3DMinMaxDistance(min, max);
	}


private:

	/// <summary>
	/// Converts glm::vec3's to FMOD_VECTOR *'s
	/// for use in FMOD's positioning of the listener
	/// and sound / stream positioning
	/// </summary>
	/// <param name="vector">The glm vector to convert.</param>
	/// <returns>The resulting FMOD vector conversion.</returns>
	FMOD_VECTOR glmToFMOD(glm::vec3 vector)
	{
		FMOD_VECTOR Temp;

		Temp.x = vector.x;
		Temp.y = vector.y;
		Temp.z = vector.z;

		return Temp;
	}

	/// <summary>
	/// The file name of this audiosource file
	/// </summary>
	std::string m_fileName;

	/// <summary>
	/// The stream's volume.
	/// </summary>
	float m_streamVolume;

	/// <summary>
	/// The stream pair
	/// Pair is made up of the FMOD:Sound * and the FMOD::Channel* that stream needs to be playable
	/// </summary>
	std::pair<FMOD::Sound*, FMOD::Channel*> m_streamPair;

};
