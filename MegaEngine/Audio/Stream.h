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

	void dispose()
	{
		if (!m_streamList->empty())
		{
			for (size_t i = 0; i < m_streamList->size(); i++)
			{
				AudioEngine::getStreams()[i]->release();
			}
		}

		if (AudioEngine::getStreams() != nullptr)
		{
			//delete [] m_streams;
		}

		if (AudioEngine::getStreamChannels() != nullptr)
		{
			//delete [] m_streamChannels;
		}

		if (AudioEngine::getStreamChannelGroup() != nullptr)
		{
			AudioEngine::getStreamChannelGroup()->release();
		}

	}

	void setStream()
	{
		AudioEngine::getStreams()[m_streamMap[m_fileName].second]->release();
		AudioEngine::getSystem()->createSound(m_fileName.c_str(), FMOD_3D | FMOD_DEFAULT, 0, &m_streamMap[m_fileName].first);
		AudioEngine::getSystem()->playSound(FMOD_CHANNELINDEX(m_streamMap[m_fileName].second), m_streamMap[m_fileName].first, true, &AudioEngine::getStreamChannels()[m_streamMap[m_fileName].second]);
		AudioEngine::getStreamChannels()[m_streamMap[m_fileName].second]->setChannelGroup(AudioEngine::getStreamChannelGroup());
	}

	void setStream(std::string filepath)
	{
		AudioEngine::getStreams()[m_streamMap[filepath].second]->release();
		AudioEngine::getSystem()->createSound(filepath.c_str(), FMOD_3D | FMOD_DEFAULT, 0, &m_streamMap[filepath].first);
		AudioEngine::getSystem()->playSound(FMOD_CHANNELINDEX(m_streamMap[filepath].second), m_streamMap[filepath].first, true, &AudioEngine::getStreamChannels()[m_streamMap[filepath].second]);
		AudioEngine::getStreamChannels()[m_streamMap[filepath].second]->setChannelGroup(AudioEngine::getStreamChannelGroup());
	}

	void playStream(bool looping)
	{
		if (looping)
		{
			AudioEngine::getStreamChannels()[m_streamMap[m_fileName].second]->setMode(FMOD_LOOP_NORMAL);
			AudioEngine::getStreamChannels()[m_streamMap[m_fileName].second]->setLoopCount(-1);
		}
		AudioEngine::getStreamChannels()[m_streamMap[m_fileName].second]->setPaused(false);
	}

	void pauseStream(bool pause)
	{
		AudioEngine::getStreamChannels()[m_streamMap[m_fileName].second]->setPaused(pause);
	}

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

	bool isStreamPlaying()
	{
		bool result;

		AudioEngine::getStreamChannels()[m_streamMap[m_fileName].second]->isPlaying(&result);

		return result;
	}

	void setStreamEffectVolume(float volumeLevel)
	{
		AudioEngine::getStreamChannels()[m_streamMap[m_fileName].second]->setVolume(volumeLevel);
	}

	void setStreamEffectVolumeAll(float volumeLevel)
	{
		AudioEngine::getStreamChannelGroup()->setVolume(volumeLevel);
	}

	float & getStreamVolume()
	{
		AudioEngine::getStreamChannelGroup()->getVolume(&m_streamVolume);
		return m_streamVolume;
	}

	void setStreamPosVel(glm::vec3 pos, glm::vec3 vel = glm::vec3(0.0f))
	{
		AudioEngine::getStreamChannels()[m_streamMap[m_fileName].second]->set3DAttributes(&glmToFMOD(pos), &glmToFMOD(vel));
	}

	void setStreamPan(float pan)
	{
		AudioEngine::getStreamChannels()[m_streamMap[m_fileName].second]->setPan(pan);
	}

	void setStreamDopplerLevel(float dopplerLevel)
	{
		AudioEngine::getStreamChannels()[m_streamMap[m_fileName].second]->set3DDopplerLevel(dopplerLevel);
	}

	void setSoundDistanceFilter(bool custom, bool customLevel, float centerFreq)
	{
		AudioEngine::getStreamChannels()[m_streamMap[m_fileName].second]->set3DDistanceFilter(custom, customLevel, centerFreq);
	}

	void setStream3DMinMaxDistance(float min, float max = NULL)
	{
		AudioEngine::getStreamChannels()[m_streamMap[m_fileName].second]->set3DMinMaxDistance(min, max);
	}

	void setStreamOcclusion(float attenuation, float reverberation = NULL)
	{
		AudioEngine::getStreamChannelGroup()[m_streamMap[m_fileName].second].set3DOcclusion(attenuation, reverberation);
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

		AudioEngine::getStreamChannelGroup()->getNumChannels(&numChannels);

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