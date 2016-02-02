// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Jesse Derochie
// Last Modified On : 01-28-2016
// ***********************************************************************
// <copyright file="AudioEngine.cpp" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
/*
	This AudioEngine class is a wrapper around some of FMOD's methods and abilities,
	The goal of this engine was simply to allow for 3D sound and music to
	be used in any game built with MegaEngine. On behalf of TeamMegaFox I
	would like to thank the developers of FMOD for their engine, and for
	making it available to students like us.
	You can learn more about FMOD by going to there website here : http://www.fmod.org/
	or if the link is for some reason dead feel free to look them up
	using "The Great and Powerful God" Google.
*/
// </summary>
// ***********************************************************************
#include "AudioEngine.h"
#include "..\Components\AudioSource.h"

FMOD_VECTOR AudioEngine::glmToFMOD(glm::vec3 vector)
{
	FMOD_VECTOR Temp;

	Temp.x = vector.x;
	Temp.y = vector.y;
	Temp.z = vector.z;

	return Temp;
}

AudioEngine::AudioEngine() :
m_system(nullptr),
m_soundEffectChannels(nullptr),
m_streamEffectChannels(nullptr)
{
	// Create FMOD system object
	m_result = FMOD::System_Create(&m_system);
	FMODVerifyResult(m_result);

	init();

}

AudioEngine::~AudioEngine()
{
	dispose(*m_soundList, *m_streamList);
	if (m_soundList)
	{
		delete m_soundList;
	}
	if (m_streamList)
	{
		delete m_streamList;
	}
}

void AudioEngine::init()
{
	unsigned int version;
	int numDrivers;
	FMOD_SPEAKERMODE speakerMode;
	FMOD_CAPS caps;
	char name[256];

	// Get version of FMOD
	m_result = m_system->getVersion(&version);
	FMODVerifyResult(m_result);

	if (version < FMOD_VERSION)
	{
		std::cout << "You're using an old version of FMOD." << std::endl;
		return;
	}

	m_result = m_system->getNumDrivers(&numDrivers);
	FMODVerifyResult(m_result);

	if (numDrivers == 0)
	{
		m_result = m_system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
		FMODVerifyResult(m_result);
	}
	else
	{
		m_result = m_system->getDriverCaps(0, &caps, 0, &speakerMode);
		FMODVerifyResult(m_result);

		/*

		Set the user selected speaker mode

		*/
		m_result = m_system->setSpeakerMode(speakerMode);
		FMODVerifyResult(m_result);

		if (caps & FMOD_CAPS_HARDWARE_EMULATED)
		{
			/*

			The user has the 'Acceleration slider set to off!
			This is really bad for latency, warn the user about this.

			*/
			std::cout << "Acceleration is not activated, please activate accleration\nto reduce latency." << std::endl;

			m_result = m_system->setDSPBufferSize(1024, 10);
			FMODVerifyResult(m_result);
		}

		if (strstr(name, "SigmaTel"))
		{
			/*

			SigmaTel sound devices crackle for some reason if the format is PCM 16bit
			PCM floating point output seems to solve it

			*/
			m_result = m_system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0, 0, FMOD_DSP_RESAMPLER_LINEAR);
			FMODVerifyResult(m_result);
		}
	}

	m_result = m_system->init(NUM_SOUND_CHANNELS, FMOD_INIT_NORMAL, 0);

	if (m_result == FMOD_ERR_OUTPUT_CREATEBUFFER)
	{
		/*

		If the speaker mode selected isn't compatible with
		this sound card, switch the speaker mode to stereo instead

		*/

		m_result = m_system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
		FMODVerifyResult(m_result);

		m_result = m_system->init(NUM_SOUND_CHANNELS, FMOD_INIT_NORMAL, 0);
	}

	FMODVerifyResult(m_result);

	// Setup ChannelGroups
	FMODVerifyResult(m_system->createChannelGroup(NULL, &m_streamEffectChannels));
	FMODVerifyResult(m_system->createChannelGroup(NULL, &m_soundEffectChannels));

}

void AudioEngine::dispose(const std::vector<std::string> & soundList, const std::vector<std::string> & streamList)
{
	//Clean up the SoundEffects and Stream Effects
	if (!soundList.empty())
	{
		for (size_t i = 0; i < soundList.size(); i++)
		{
			m_soundEffects[i]->release();
		}
	}

	if (m_soundEffects != nullptr)
	{
		//delete [] m_soundEffects;
	}

	if (!streamList.empty())
	{
		for (size_t i = 0; i < streamList.size(); i++)
		{
			m_streams[i]->release();
		}
	}

	if (m_streams != nullptr)
	{
		//delete [] m_streams;
	}

	//Clean up the Channel Lists
	if (m_soundChannels != nullptr)
	{
		//delete [] m_soundChannels;
	}

	if (m_streamChannels != nullptr)
	{
		//delete [] m_streamChannels;
	}

	//Clean up the Channel Groups
	if (m_soundEffectChannels != nullptr)
	{
		m_soundEffectChannels->release();
	}

	if (m_streamEffectChannels != nullptr)
	{
		m_streamEffectChannels->release();
	}

	// Clean up the System Object
	if (m_system != nullptr)
	{
		m_system->release();
	}

}

/// <summary>
/// Sets the sound.
/// </summary>
/// <param name="index">The index.</param>
void AudioEngine::setSound(std::string filepath)
{
	// TODO: stream needs to work like below
	// make m_sounds a member variable	
	// fix load sounds and streams to work with this.

	m_soundEffects[m_soundMap[filepath].second]->release();
	m_system->createSound(filepath.c_str(), FMOD_3D | FMOD_DEFAULT, 0, &m_soundMap[filepath].first);
	m_system->playSound(FMOD_CHANNELINDEX(m_soundMap[filepath].second), m_soundMap[filepath].first, true, &m_soundChannels[m_soundMap[filepath].second]);
	m_soundChannels[m_soundMap[filepath].second]->setChannelGroup(m_soundEffectChannels);
}

void AudioEngine::setStream(std::string filepath)
{
	m_streams[m_streamMap[filepath].second]->release();
	m_system->createSound(filepath.c_str(), FMOD_3D | FMOD_DEFAULT, 0, &m_streamMap[filepath].first);
	m_system->playSound(FMOD_CHANNELINDEX(m_streamMap[filepath].second), m_streamMap[filepath].first, true, &m_streamChannels[m_streamMap[filepath].second]);
	m_streamChannels[m_streamMap[filepath].second]->setChannelGroup(m_streamEffectChannels);
}

void AudioEngine::playSound(std::string filepath)
{
	m_soundChannels[m_soundMap[filepath].second]->setPaused(false);
}

void AudioEngine::playStream(std::string filepath, bool looping)
{
	if (looping)
	{
		m_streamChannels[m_streamMap[filepath].second]->setMode(FMOD_LOOP_NORMAL);
		m_streamChannels[m_streamMap[filepath].second]->setLoopCount(-1);
	}
	m_streamChannels[m_streamMap[filepath].second]->setPaused(false);
}

void AudioEngine::pauseSound(bool pause, std::string filepath)
{
	m_soundChannels[m_soundMap[filepath].second]->setPaused(pause);
}

void AudioEngine::pauseStream(bool pause, std::string filepath)
{
	m_streamChannels[m_streamMap[filepath].second]->setPaused(pause);
}

void AudioEngine::stopAllSoundEffects()
{
	for (int i = 0; i < NUM_SOUND_CHANNELS; i++)
	{
		if (m_soundChannels[i] != NULL)
		{
			m_soundChannels[i]->stop();
		}
	}
}

void AudioEngine::stopAllStreams()
{
	for (int i = 0; i < NUM_STREAM_CHANNELS; i++)
	{
		if (m_streamChannels[i] != NULL)
		{
			m_streamChannels[i]->stop();
		}
	}
}

bool AudioEngine::isSoundPlaying(std::string filepath)
{
	bool result;

	m_soundChannels[m_soundMap[filepath].second]->isPlaying(&result);

	return result;
}

bool AudioEngine::isStreamPlaying(std::string filepath)
{
	bool result;

	m_streamChannels[m_streamMap[filepath].second]->isPlaying(&result);

	return result;
}

void AudioEngine::setSoundEffectVolume(float volumeLevel)
{
	m_soundEffectChannels->setVolume(volumeLevel);
}

void AudioEngine::setSoundEffectVolume(std::string filepath, float volumeLevel)
{
	m_soundChannels[m_soundMap[filepath].second]->setVolume(volumeLevel);
}

void AudioEngine::setStreamEffectVolume(std::string filepath, float volumeLevel)
{
	m_streamChannels[m_streamMap[filepath].second]->setVolume(volumeLevel);
}

void AudioEngine::setStreamEffectVolume(float volumeLevel)
{
	m_streamEffectChannels->setVolume(volumeLevel);
}

float & AudioEngine::getSoundVolume()
{
	m_soundEffectChannels->getVolume(&m_soundVolume);
	return m_soundVolume;
}

float & AudioEngine::getStreamVolume()
{
	m_streamEffectChannels->getVolume(&m_streamVolume);
	return m_streamVolume;
}

void AudioEngine::setListener(glm::vec3 pos, glm::vec3 vel, glm::vec3 forward, glm::vec3 up)
{
	m_system->set3DListenerAttributes(0, &glmToFMOD(pos), &glmToFMOD(vel), &glmToFMOD(forward), &glmToFMOD(up));
}

void AudioEngine::setSoundPosVel(std::string filepath, glm::vec3 pos, glm::vec3 vel)
{
	m_soundChannels[m_soundMap[filepath].second]->set3DAttributes(&glmToFMOD(pos), &glmToFMOD(vel));
}

void AudioEngine::setStreamPosVel(std::string filepath, glm::vec3 pos, glm::vec3 vel)
{
	m_streamChannels[m_streamMap[filepath].second]->set3DAttributes(&glmToFMOD(pos), &glmToFMOD(vel));
}

void AudioEngine::setSoundPan(std::string filepath, float pan)
{
	m_soundChannels[m_soundMap[filepath].second]->setPan(pan);
}

void AudioEngine::setStreamPan(std::string filepath, float pan)
{
	m_streamChannels[m_streamMap[filepath].second]->setPan(pan);
}

void AudioEngine::setSoundDopplerLevel(std::string filepath, float dopplerLevel)
{
	m_soundChannels[m_soundMap[filepath].second]->set3DDopplerLevel(dopplerLevel);
}

void AudioEngine::setStreamDopplerLevel(std::string filepath, float dopplerLevel)
{
	m_streamChannels[m_streamMap[filepath].second]->set3DDopplerLevel(dopplerLevel);
}

void AudioEngine::setSoundConeOrientation(std::string filepath, glm::vec3 orientation)
{
	m_soundChannels[m_soundMap[filepath].second]->set3DConeOrientation(&glmToFMOD(orientation));
}

void AudioEngine::setSoundConeSettings(std::string filepath, float insideConeAngle, float outsideConeAngle, float outsideVolume)
{
	m_soundChannels[m_soundMap[filepath].second]->set3DConeSettings(insideConeAngle, outsideConeAngle, outsideVolume);
}

void AudioEngine::setSoundDistanceFilter(std::string filepath, bool custom, bool customLevel, float centerFreq)
{
	m_soundChannels[m_soundMap[filepath].second]->set3DDistanceFilter(custom, customLevel, centerFreq);
}

void AudioEngine::setSound3DMinMaxDistance(std::string filepath, float min, float max)
{
	m_soundChannels[m_soundMap[filepath].second]->set3DMinMaxDistance(min, max);
}

void AudioEngine::setStream3DMinMaxDistance(std::string filepath, float min, float max)
{
	m_streamChannels[m_streamMap[filepath].second]->set3DMinMaxDistance(min, max);
}

void AudioEngine::setSoundOcclusion(std::string filepath, float attenuation, float reverberation)
{
	m_streamChannels[m_streamMap[filepath].second]->set3DOcclusion(attenuation, reverberation);
}

void AudioEngine::setStreamOcclusion(std::string filepath, float attenuation, float reverberation)
{
	m_streamEffectChannels[m_streamMap[filepath].second].set3DOcclusion(attenuation, reverberation);
}

bool AudioEngine::loadSounds(std::vector<std::string> soundList)
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

bool AudioEngine::loadStreams(std::vector<std::string> streamList)
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

void AudioEngine::update()
{
	m_system->update();
}