// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 02-01-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 02-03-2016
// ***********************************************************************
// <copyright file="Sound.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
// </summary>
// ***********************************************************************

#pragma once
#include "..\Audio\AudioEngine.h"

static const int NUM_SOUND_CHANNELS = 45;

class Sound
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="SoundSource"/> class.
	/// </summary>
	Sound() {}
	/// <summary>
	/// Initializes a new instance of the <see cref="SoundSource"/> class.
	/// </summary>
	/// <param name="fileName">Name of the file.</param>
	Sound(const std::string& fileName) :
		m_parent(nullptr),
		m_fileName(fileName) { }
	/// <summary>
	/// Finalizes an instance of the <see cref="SoundSource"/> class.
	/// </summary>
	~Sound() {}

	/// <summary>
	/// Initializes a new instance of the <see cref="Sound"/> class.
	/// Nullify the copy constructor
	/// </summary>
	/// <param name="">The .</param>
	Sound(const Sound&) = delete;

	void dispose()
	{
		//Clean up the SoundEffects and Stream Effects
		if (!m_soundList->empty())
		{
			for (size_t i = 0; i < m_soundList->size(); i++)
			{
				m_soundEffects[i]->release();
			}
		}

		if (m_soundEffects != nullptr)
		{
			//delete [] m_soundEffects;
		}

		//Clean up the Channel Lists
		if (m_soundChannels != nullptr)
		{
			//delete [] m_soundChannels;
		}

		//Clean up the Channel Groups
		if (m_soundEffectChannels != nullptr)
		{
			m_soundEffectChannels->release();
		}
	}

	void setSound(std::string filepath)
	{
		// TODO: stream needs to work like below
		// make m_sounds a member variable
		// fix load sounds and streams to work with this.

		m_soundEffects[m_soundMap[filepath].second]->release();
		AudioEngine::getSystem()->createSound(filepath.c_str(), FMOD_3D | FMOD_DEFAULT, 0, &m_soundMap[filepath].first);
		AudioEngine::getSystem()->playSound(FMOD_CHANNELINDEX(m_soundMap[filepath].second), m_soundMap[filepath].first, true, &m_soundChannels[m_soundMap[filepath].second]);
		m_soundChannels[m_soundMap[filepath].second]->setChannelGroup(m_soundEffectChannels);
	}

	void playSound(std::string filepath)
	{
		m_soundChannels[m_soundMap[filepath].second]->setPaused(false);
	}

	void pauseSound(bool pause, std::string filepath)
	{
		m_soundChannels[m_soundMap[filepath].second]->setPaused(pause);
	}

	void stopAllSoundEffects()
	{
		for (int i = 0; i < NUM_SOUND_CHANNELS; i++)
		{
			if (m_soundChannels[i] != NULL)
			{
				m_soundChannels[i]->stop();
			}
		}
	}

	bool isSoundPlaying(std::string filepath)
	{
		bool result;

		m_soundChannels[m_soundMap[filepath].second]->isPlaying(&result);

		return result;
	}

	void setSoundEffectVolume(float volumeLevel)
	{
		m_soundEffectChannels->setVolume(volumeLevel);
	}

	void setSoundEffectVolume(std::string filepath, float volumeLevel)
	{
		m_soundChannels[m_soundMap[filepath].second]->setVolume(volumeLevel);
	}

	float & getSoundVolume()
	{
		m_soundEffectChannels->getVolume(&m_soundVolume);
		return m_soundVolume;
	}

	void setSoundPosVel(std::string filepath, glm::vec3 pos, glm::vec3 vel)
	{
		m_soundChannels[m_soundMap[filepath].second]->set3DAttributes(&glmToFMOD(pos), &glmToFMOD(vel));
	}

	void setSoundPan(std::string filepath, float pan)
	{
		m_soundChannels[m_soundMap[filepath].second]->setPan(pan);
	}

	void setSoundDopplerLevel(std::string filepath, float dopplerLevel)
	{
		m_soundChannels[m_soundMap[filepath].second]->set3DDopplerLevel(dopplerLevel);
	}

	void setSoundConeOrientation(std::string filepath, glm::vec3 orientation)
	{
		m_soundChannels[m_soundMap[filepath].second]->set3DConeOrientation(&glmToFMOD(orientation));
	}

	void setSoundConeSettings(std::string filepath, float insideConeAngle, float outsideConeAngle, float outsideVolume)
	{
		m_soundChannels[m_soundMap[filepath].second]->set3DConeSettings(insideConeAngle, outsideConeAngle, outsideVolume);
	}

	void setSoundDistanceFilter(std::string filepath, bool custom, bool customLevel, float centerFreq)
	{
		m_soundChannels[m_soundMap[filepath].second]->set3DDistanceFilter(custom, customLevel, centerFreq);
	}

	void setSound3DMinMaxDistance(std::string filepath, float min, float max)
	{
		m_soundChannels[m_soundMap[filepath].second]->set3DMinMaxDistance(min, max);
	}

	void setSoundOcclusion(std::string filepath, float attenuation, float reverberation)
	{
		m_soundChannels[m_soundMap[filepath].second]->set3DOcclusion(attenuation, reverberation);
	}

	bool loadSounds(std::vector<std::string> soundList)
	{
		bool result;
		int numChannels;
		m_soundList = &soundList;

		for (size_t i = 0; i < soundList.size(); i++)
		{
			setSound(soundList[i]);
		}

		m_soundEffectChannels->getNumChannels(&numChannels);

		if (numChannels != soundList.size())
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
	/// The FMOD result.
	/// </summary>
	FMOD_RESULT m_result;
	
	/// <summary>
	/// The file name of this audiosource file
	/// </summary>
	std::string m_fileName;

	/// <summary>
	/// The parent Game Object
	/// </summary>
	GameObject * m_parent;

	/// <summary>
	/// The file path of this SoundSource file
	/// </summary>
	std::string m_filePath = "";

	/// <summary>
	/// The sound's volume.
	/// </summary>
	float m_soundVolume;

	/// <summary>
	/// The sound effects list.
	/// </summary>
	FMOD::Sound * m_soundEffects[NUM_SOUND_CHANNELS];
	/// <summary>
	/// The sound channels.
	/// </summary>
	FMOD::Channel * m_soundChannels[NUM_SOUND_CHANNELS];
	/// <summary>
	/// The sound effect channels.
	/// </summary>
	FMOD::ChannelGroup * m_soundEffectChannels;
	/// <summary>
	/// The sound list.
	/// </summary>
	const std::vector<std::string> * m_soundList = new std::vector<std::string>();

	/// <summary>
	/// The m_sound map
	/// </summary>
	std::unordered_map<std::string, std::pair<FMOD::Sound*, int>> m_soundMap;
};

