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

static const int NUM_STREAM_CHANNELS = 15;

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
		m_parent(nullptr),
		m_fileName(fileName) { }
	/// <summary>
	/// Finalizes an instance of the <see cref="StreamSource"/> class.
	/// </summary>
	~Stream() {}

	/// <summary>
	/// Initializes a new instance of the <see cref="Stream"/> class.
	/// Nullify the copy constructor
	/// </summary>
	/// <param name="">The .</param>
	Stream(const Stream&) = delete;

	void dispose()
	{
		if (!m_streamList->empty())
		{
			for (size_t i = 0; i < m_streamList->size(); i++)
			{
				m_streams[i]->release();
			}
		}

		if (m_streams != nullptr)
		{
			//delete [] m_streams;
		}

		if (m_streamChannels != nullptr)
		{
			//delete [] m_streamChannels;
		}

		if (m_streamEffectChannels != nullptr)
		{
			m_streamEffectChannels->release();
		}

	}

	void setStream(std::string filepath)
	{
		m_streams[m_streamMap[filepath].second]->release();
		AudioEngine::getSystem()->createSound(filepath.c_str(), FMOD_3D | FMOD_DEFAULT, 0, &m_streamMap[filepath].first);
		AudioEngine::getSystem()->playSound(FMOD_CHANNELINDEX(m_streamMap[filepath].second), m_streamMap[filepath].first, true, &m_streamChannels[m_streamMap[filepath].second]);
		m_streamChannels[m_streamMap[filepath].second]->setChannelGroup(m_streamEffectChannels);
	}

	void playStream(std::string filepath, bool looping)
	{
		if (looping)
		{
			m_streamChannels[m_streamMap[filepath].second]->setMode(FMOD_LOOP_NORMAL);
			m_streamChannels[m_streamMap[filepath].second]->setLoopCount(-1);
		}
		m_streamChannels[m_streamMap[filepath].second]->setPaused(false);
	}

	void pauseStream(bool pause, std::string filepath)
	{
		m_streamChannels[m_streamMap[filepath].second]->setPaused(pause);
	}

	void stopAllStreams()
	{
		for (int i = 0; i < NUM_STREAM_CHANNELS; i++)
		{
			if (m_streamChannels[i] != NULL)
			{
				m_streamChannels[i]->stop();
			}
		}
	}

	bool isStreamPlaying(std::string filepath)
	{
		bool result;

		m_streamChannels[m_streamMap[filepath].second]->isPlaying(&result);

		return result;
	}

	void setStreamEffectVolume(std::string filepath, float volumeLevel)
	{
		m_streamChannels[m_streamMap[filepath].second]->setVolume(volumeLevel);
	}

	void setStreamEffectVolume(float volumeLevel)
	{
		m_streamEffectChannels->setVolume(volumeLevel);
	}

	float & getStreamVolume()
	{
		m_streamEffectChannels->getVolume(&m_streamVolume);
		return m_streamVolume;
	}

	void setStreamPosVel(std::string filepath, glm::vec3 pos, glm::vec3 vel)
	{
		m_streamChannels[m_streamMap[filepath].second]->set3DAttributes(&glmToFMOD(pos), &glmToFMOD(vel));
	}

	void setStreamPan(std::string filepath, float pan)
	{
		m_streamChannels[m_streamMap[filepath].second]->setPan(pan);
	}

	void setStreamDopplerLevel(std::string filepath, float dopplerLevel)
	{
		m_streamChannels[m_streamMap[filepath].second]->set3DDopplerLevel(dopplerLevel);
	}

	void setSoundDistanceFilter(std::string filepath, bool custom, bool customLevel, float centerFreq)
	{
		m_streamChannels[m_streamMap[filepath].second]->set3DDistanceFilter(custom, customLevel, centerFreq);
	}

	void setStream3DMinMaxDistance(std::string filepath, float min, float max)
	{
		m_streamChannels[m_streamMap[filepath].second]->set3DMinMaxDistance(min, max);
	}

	void setStreamOcclusion(std::string filepath, float attenuation, float reverberation)
	{
		m_streamEffectChannels[m_streamMap[filepath].second].set3DOcclusion(attenuation, reverberation);
	}


	bool loadStreams(std::vector<std::string> streamList)
	{
		bool result;
		int numChannels;
		m_streamList = &streamList;

		for (size_t i = 0; i < streamList.size(); i++)
		{
			setStream(streamList[i]);
		}

		m_streamEffectChannels->getNumChannels(&numChannels);

		if (numChannels != streamList.size())
		{
			result = false;
		}
		else
		{
			result = true;
		}

		return result;
	}

	/// <summary>
	/// Sets the file path.
	/// </summary>
	/// <param name="filePath">The file path.</param>
	void setFilePath(std::string filePath)
	{
		m_filePath = filePath;
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
	/// The parent Game Object
	/// </summary>
	GameObject * m_parent;

	/// <summary>
	/// The file path of this StreamSource file
	/// </summary>
	std::string m_filePath = "";

	/// <summary>
	/// The FMOD result.
	/// </summary>
	FMOD_RESULT m_result;

	/// <summary>
	/// The stream's volume.
	/// </summary>
	float m_streamVolume;

	// Stream Effects (Music)
	/// <summary>
	/// The streams.
	/// </summary>
	FMOD::Sound * m_streams[NUM_STREAM_CHANNELS];
	/// <summary>
	/// The stream channels.
	/// </summary>
	FMOD::Channel * m_streamChannels[NUM_STREAM_CHANNELS];
	/// <summary>
	/// The stream effect channels.
	/// </summary>
	FMOD::ChannelGroup * m_streamEffectChannels;
	/// <summary>
	/// The stream list.
	/// </summary>
	const std::vector<std::string> * m_streamList = new std::vector<std::string>();

	/// <summary>
	/// The m_stream map
	/// </summary>
	std::unordered_map<std::string, std::pair<FMOD::Sound*, int>> m_streamMap;
};

/*


*/