// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 02-01-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 02-04-2016
// ***********************************************************************
// <copyright file="Sound.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
// </summary>
// ***********************************************************************

#pragma once
#include "..\Audio\AudioEngine.h"

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
	Sound(const std::string& fileName)
	{ 
		m_fileName = "Assets/Music/" + fileName;
		setSound();
	}
	/// <summary>
	/// Finalizes an instance of the <see cref="SoundSource"/> class.
	/// </summary>
	~Sound() {	}

	/// <summary>
	/// Disposes this instance.
	/// </summary>
	void dispose()
	{
		//Clean up the Channel Groups
		if (AudioEngine::getSoundChannelGroup() != nullptr)
		{
			AudioEngine::getSoundChannelGroup()->release();
		}
	}

	/// <summary>
	/// Sets the sound.
	/// </summary>
	void setSound()
	{
		if (m_soundPair.first) m_soundPair.first->release();
		AudioEngine::FMODVerifyResult(AudioEngine::getSystem()->createSound(m_fileName.c_str(), FMOD_3D | FMOD_DEFAULT, 0, &m_soundPair.first));
		AudioEngine::FMODVerifyResult(AudioEngine::getSystem()->playSound(FMOD_CHANNELINDEX(m_soundPair.second), m_soundPair.first, true, &AudioEngine::getSoundChannels()[m_soundPair.second]));
		AudioEngine::FMODVerifyResult(AudioEngine::getSoundChannels()[m_soundPair.second]->setChannelGroup(AudioEngine::getSoundChannelGroup()));
	}

	/// <summary>
	/// Plays the sound.
	/// </summary>
	void playSound()
	{
		setSound();
		AudioEngine::getSoundChannels()[m_soundPair.second]->setPaused(false);
	}

	/// <summary>
	/// Pauses the sound.
	/// </summary>
	/// <param name="pause">if set to <c>true</c> [pause].</param>
	void pauseSound(bool pause)
	{
		AudioEngine::getSoundChannels()[m_soundPair.second]->setPaused(pause);
	}

	/// <summary>
	/// Stops all sound effects.
	/// </summary>
	void stopAllSoundEffects()
	{
		for (int i = 0; i < NUM_SOUND_CHANNELS; i++)
		{
			if (AudioEngine::getSoundChannels()[i] != NULL)
			{
				AudioEngine::getSoundChannels()[i]->stop();
			}
		}
	}

	/// <summary>
	/// Determines whether [is sound playing].
	/// </summary>
	/// <returns></returns>
	bool isSoundPlaying()
	{
		bool result;

		AudioEngine::getSoundChannels()[m_soundPair.second]->isPlaying(&result);

		return result;
	}

	/// <summary>
	/// Sets the sound effect volume.
	/// </summary>
	/// <param name="volumeLevel">The volume level.</param>
	void setSoundEffectVolume(float volumeLevel)
	{
		AudioEngine::getSoundChannelGroup()->setVolume(volumeLevel);
	}

	/// <summary>
	/// Sets the sound effect volume all.
	/// </summary>
	/// <param name="volumeLevel">The volume level.</param>
	void setSoundEffectVolumeAll(float volumeLevel)
	{
		AudioEngine::getSoundChannels()[m_soundPair.second]->setVolume(volumeLevel);
	}

	/// <summary>
	/// Gets the sound volume.
	/// </summary>
	/// <returns></returns>
	float & getSoundVolume()
	{
		AudioEngine::getSoundChannelGroup()->getVolume(&m_soundVolume);
		return m_soundVolume;
	}

	/// <summary>
	/// Sets the sound position vel.
	/// </summary>
	/// <param name="pos">The position.</param>
	/// <param name="vel">The vel.</param>
	void setSoundPosVel(glm::vec3 pos, glm::vec3 vel = glm::vec3(0.0f))
	{
		AudioEngine::getSoundChannels()[m_soundPair.second]->set3DAttributes(&glmToFMOD(pos), &glmToFMOD(vel));
	}

	/// <summary>
	/// Pan level, from -1.0 (left) to 1.0 (right), default = 0 (center).
	/// </summary>
	/// <param name="pan">The pan.</param>
	void setSoundPan(float pan)
	{
		AudioEngine::getSoundChannels()[m_soundPair.second]->setPan(pan);
	}

	/// <summary>
	/// Sets the sound doppler level.
	/// Use with (but before) setSoundDistanceFilter for proper effect
	/// </summary>
	/// <param name="dopplerLevel">The doppler level.</param>
	void setSoundDopplerLevel(float dopplerLevel)
	{
		AudioEngine::getSoundChannels()[m_soundPair.second]->set3DDopplerLevel(dopplerLevel);
	}

	/// <summary>
	/// Sets the sound cone orientation.
	/// </summary>
	/// <param name="orientation">The orientation.</param>
	void setSoundConeOrientation(glm::vec3 orientation)
	{
		AudioEngine::getSoundChannels()[m_soundPair.second]->set3DConeOrientation(&glmToFMOD(orientation));
	}

	/// <summary>
	/// Sets the sound cone settings.
	/// </summary>
	/// <param name="insideConeAngle">The inside cone angle.</param>
	/// <param name="outsideConeAngle">The outside cone angle.</param>
	/// <param name="outsideVolume">The outside volume.</param>
	void setSoundConeSettings(float insideConeAngle, float outsideConeAngle, float outsideVolume)
	{
		AudioEngine::getSoundChannels()[m_soundPair.second]->set3DConeSettings(insideConeAngle, outsideConeAngle, outsideVolume);
	}

	/// <summary>
	/// Sets the sound distance filter.
	/// Use with but after setSoundDopplerLevel
	/// </summary>
	/// <param name="custom">if set to <c>true</c> [custom].</param>
	/// <param name="customLevel">if set to <c>true</c> [custom level].</param>
	/// <param name="centerFreq">The center freq.</param>
	void setSoundDistanceFilter(bool custom, bool customLevel, float centerFreq)
	{
		AudioEngine::getSoundChannels()[m_soundPair.second]->set3DDistanceFilter(custom, customLevel, centerFreq);
	}

	/// <summary>
	/// In summary, increase the mindistance of a sound to make it 'louder' in a 3D world, 
	/// and decrease it to make it 'quieter' in a 3D world.
	/// Maxdistance is effectively obsolete unless you need the sound to stop fading out at 
	/// a certain point.Do not adjust this from the default if you dont need to.
	///	Some people have the confusion that maxdistance is the point the sound will fade out to, 
	/// this is not the case.
	/// </summary>
	/// <param name="min">The minimum.</param>
	/// <param name="max">The maximum.</param>
	void setSound3DMinMaxDistance(float min, float max = NULL)
	{
		AudioEngine::getSoundChannels()[m_soundPair.second]->set3DMinMaxDistance(min, max);
	}

	/// <summary>
	/// Sets the sound occlusion.
	/// </summary>
	/// <param name="attenuation">The attenuation.</param>
	/// <param name="reverberation">The reverberation.</param>
	void setSoundOcclusion(float attenuation, float reverberation = NULL)
	{
		AudioEngine::getSoundChannels()[m_soundPair.second]->set3DOcclusion(attenuation, reverberation);
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
	/// The sound's volume.
	/// </summary>
	float m_soundVolume;

	/// <summary>
	/// The m_sound pair
	/// Pair is made up of the FMOD:Sound and the index of that sound in the channel group
	/// </summary>
	std::pair<FMOD::Sound*, int> m_soundPair;
	
};

