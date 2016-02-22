// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 02-01-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 02-03-2016
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
	Stream(const std::string& fileName) :
		m_fileName(fileName) { }
	/// <summary>
	/// Finalizes an instance of the <see cref="StreamSource"/> class.
	/// </summary>
	~Stream() {}

	/// <summary>
	/// Disposes this instance.
	/// </summary>
	void dispose()
	{
		if (AudioEngine::getStreamChannelGroup() != nullptr)
		{
			AudioEngine::getStreamChannelGroup()->release();
		}
	}

	/// <summary>
	/// Sets the stream.
	/// </summary>
	void setStream()
	{
		AudioEngine::getStreams()[m_streamPair.second]->release();
		AudioEngine::getSystem()->createSound(m_fileName.c_str(), FMOD_3D | FMOD_DEFAULT, 0, &m_streamPair.first);
		AudioEngine::getSystem()->playSound(FMOD_CHANNELINDEX(m_streamPair.second), m_streamPair.first, true, &AudioEngine::getStreamChannels()[m_streamPair.second]);
		AudioEngine::getStreamChannels()[m_streamPair.second]->setChannelGroup(AudioEngine::getStreamChannelGroup());
	}

	/// <summary>
	/// Plays the stream.
	/// </summary>
	/// <param name="looping">if set to <c>true</c> [looping].</param>
	void playStream(bool looping)
	{
		if (looping)
		{
			AudioEngine::getStreamChannels()[m_streamPair.second]->setMode(FMOD_LOOP_NORMAL);
			AudioEngine::getStreamChannels()[m_streamPair.second]->setLoopCount(-1);
		}
		AudioEngine::getStreamChannels()[m_streamPair.second]->setPaused(false);
	}

	/// <summary>
	/// Pauses the stream.
	/// </summary>
	/// <param name="pause">if set to <c>true</c> [pause].</param>
	void pauseStream(bool pause)
	{
		AudioEngine::getStreamChannels()[m_streamPair.second]->setPaused(pause);
	}

	/// <summary>
	/// Stops all streams.
	/// </summary>
	void stopAllStreams()
	{
		for (int i = 0; i < NUM_STREAM_CHANNELS; i++)
		{
			if (AudioEngine::getStreamChannels()[i] != NULL)
			{
				AudioEngine::getStreamChannels()[i]->stop();
			}
		}
	}

	/// <summary>
	/// Determines whether [is stream playing].
	/// </summary>
	/// <returns></returns>
	bool isStreamPlaying()
	{
		bool result;

		AudioEngine::getStreamChannels()[m_streamPair.second]->isPlaying(&result);

		return result;
	}

	/// <summary>
	/// Sets the stream effect volume.
	/// </summary>
	/// <param name="volumeLevel">The volume level.</param>
	void setStreamEffectVolume(float volumeLevel)
	{
		AudioEngine::getStreamChannels()[m_streamPair.second]->setVolume(volumeLevel);
	}

	/// <summary>
	/// Sets the stream effect volume all.
	/// </summary>
	/// <param name="volumeLevel">The volume level.</param>
	void setStreamEffectVolumeAll(float volumeLevel)
	{
		AudioEngine::getStreamChannelGroup()->setVolume(volumeLevel);
	}

	/// <summary>
	/// Gets the stream volume.
	/// </summary>
	/// <returns></returns>
	float & getStreamVolume()
	{
		AudioEngine::getStreamChannelGroup()->getVolume(&m_streamVolume);
		return m_streamVolume;
	}

	/// <summary>
	/// Sets the stream position vel.
	/// </summary>
	/// <param name="pos">The position.</param>
	/// <param name="vel">The vel.</param>
	void setStreamPosVel(glm::vec3 pos, glm::vec3 vel = glm::vec3(0.0f))
	{
		AudioEngine::getStreamChannels()[m_streamPair.second]->set3DAttributes(&glmToFMOD(pos), &glmToFMOD(vel));
	}

	/// <summary>
	/// Pan level, from -1.0 (left) to 1.0 (right), default = 0 (center).
	/// </summary>
	/// <param name="pan">The pan.</param>
	void setStreamPan(float pan)
	{
		AudioEngine::getStreamChannels()[m_streamPair.second]->setPan(pan);
	}

	/// <summary>
	/// Sets the stream doppler level.
	/// Use with (but before) setStreamDistanceFilter for proper effect
	/// </summary>
	/// <param name="dopplerLevel">The doppler level.</param>
	void setStreamDopplerLevel(float dopplerLevel)
	{
		AudioEngine::getStreamChannels()[m_streamPair.second]->set3DDopplerLevel(dopplerLevel);
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
		AudioEngine::getStreamChannels()[m_streamPair.second]->set3DDistanceFilter(custom, customLevel, centerFreq);
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
		AudioEngine::getStreamChannels()[m_streamPair.second]->set3DMinMaxDistance(min, max);
	}

	/// <summary>
	/// Sets the stream occlusion.
	/// </summary>
	/// <param name="attenuation">The attenuation.</param>
	/// <param name="reverberation">The reverberation.</param>
	void setStreamOcclusion(float attenuation, float reverberation = NULL)
	{
		AudioEngine::getStreamChannelGroup()[m_streamPair.second].set3DOcclusion(attenuation, reverberation);
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
	/// The file path of this StreamSource file
	/// </summary>
	std::string m_filePath = "";

	/// <summary>
	/// The stream's volume.
	/// </summary>
	float m_streamVolume;

	/// <summary>
	/// The m_stream map
	/// </summary>
	std::pair<FMOD::Sound*, int> m_streamPair;

};

/*


*/