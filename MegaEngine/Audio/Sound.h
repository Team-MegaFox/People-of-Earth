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
		if (AudioEngine::getSoundChannelGroup() != nullptr)
		{
			AudioEngine::getSoundChannelGroup()->release();
		}
	}

	void setSound()
	{
		// TODO: stream needs to work like below
		// make m_sounds a member variable
		// fix load sounds and streams to work with this.

		m_soundEffects[m_soundMap[m_fileName].second]->release();
		AudioEngine::getSystem()->createSound(m_fileName.c_str(), FMOD_3D | FMOD_DEFAULT, 0, &m_soundMap[m_fileName].first);
		AudioEngine::getSystem()->playSound(FMOD_CHANNELINDEX(m_soundMap[m_fileName].second), m_soundMap[m_fileName].first, true, &m_soundChannels[m_soundMap[m_fileName].second]);
		m_soundChannels[m_soundMap[m_fileName].second]->setChannelGroup(AudioEngine::getSoundChannelGroup());
	}

	void setSound(std::string fileName)
	{
		// TODO: stream needs to work like below
		// make m_sounds a member variable
		// fix load sounds and streams to work with this.
		m_soundEffects[m_soundMap[fileName].second]->release();
		AudioEngine::getSystem()->createSound(fileName.c_str(), FMOD_3D | FMOD_DEFAULT, 0, &m_soundMap[fileName].first);
		AudioEngine::getSystem()->playSound(FMOD_CHANNELINDEX(m_soundMap[fileName].second), m_soundMap[fileName].first, true, &m_soundChannels[m_soundMap[fileName].second]);
		m_soundChannels[m_soundMap[fileName].second]->setChannelGroup(AudioEngine::getSoundChannelGroup());
	}

	void playSound()
	{
		m_soundChannels[m_soundMap[m_fileName].second]->setPaused(false);
	}

	void pauseSound(bool pause)
	{
		m_soundChannels[m_soundMap[m_fileName].second]->setPaused(pause);
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

	bool isSoundPlaying()
	{
		bool result;

		m_soundChannels[m_soundMap[m_fileName].second]->isPlaying(&result);

		return result;
	}

	void setSoundEffectVolume(float volumeLevel)
	{
		AudioEngine::getSoundChannelGroup()->setVolume(volumeLevel);
	}

	void setSoundEffectVolumeAll(float volumeLevel)
	{
		m_soundChannels[m_soundMap[m_fileName].second]->setVolume(volumeLevel);
	}

	float & getSoundVolume()
	{
		AudioEngine::getSoundChannelGroup()->getVolume(&m_soundVolume);
		return m_soundVolume;
	}

	void setSoundPosVel(glm::vec3 pos, glm::vec3 vel = glm::vec3(0.0f))
	{
		m_soundChannels[m_soundMap[m_fileName].second]->set3DAttributes(&glmToFMOD(pos), &glmToFMOD(vel));
	}

	void setSoundPan(float pan)
	{
		m_soundChannels[m_soundMap[m_fileName].second]->setPan(pan);
	}

	void setSoundDopplerLevel(float dopplerLevel)
	{
		m_soundChannels[m_soundMap[m_fileName].second]->set3DDopplerLevel(dopplerLevel);
	}

	void setSoundConeOrientation(glm::vec3 orientation)
	{
		m_soundChannels[m_soundMap[m_fileName].second]->set3DConeOrientation(&glmToFMOD(orientation));
	}

	void setSoundConeSettings(float insideConeAngle, float outsideConeAngle, float outsideVolume)
	{
		m_soundChannels[m_soundMap[m_fileName].second]->set3DConeSettings(insideConeAngle, outsideConeAngle, outsideVolume);
	}

	void setSoundDistanceFilter(bool custom, bool customLevel, float centerFreq)
	{
		m_soundChannels[m_soundMap[m_fileName].second]->set3DDistanceFilter(custom, customLevel, centerFreq);
	}

	void setSound3DMinMaxDistance(float min, float max = NULL)
	{
		m_soundChannels[m_soundMap[m_fileName].second]->set3DMinMaxDistance(min, max);
	}

	void setSoundOcclusion(float attenuation, float reverberation = NULL)
	{
		m_soundChannels[m_soundMap[m_fileName].second]->set3DOcclusion(attenuation, reverberation);
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

		AudioEngine::getSoundChannelGroup()->getNumChannels(&numChannels);

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
	/// The sound list.
	/// </summary>
	const std::vector<std::string> * m_soundList = new std::vector<std::string>();

	/// <summary>
	/// The m_sound map
	/// </summary>
	std::unordered_map<std::string, std::pair<FMOD::Sound*, int>> m_soundMap;
};

