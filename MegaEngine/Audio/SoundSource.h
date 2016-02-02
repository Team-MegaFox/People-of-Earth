// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 02-01-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 02-01-2016
// ***********************************************************************
// <copyright file="SoundSource.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
// </summary>
// ***********************************************************************

#pragma once
#include "..\Audio\AudioEngine.h"

class SoundSource
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="SoundSource"/> class.
	/// </summary>
	SoundSource() {}
	/// <summary>
	/// Initializes a new instance of the <see cref="SoundSource"/> class.
	/// </summary>
	/// <param name="fileName">Name of the file.</param>
	SoundSource(const std::string& fileName) :
		m_parent(nullptr),
		m_fileName(fileName) { }
	/// <summary>
	/// Finalizes an instance of the <see cref="SoundSource"/> class.
	/// </summary>
	~SoundSource() {}

	/// <summary>
	/// Used to set a sound to a channel initially, 
	/// also if a sound has been played once,
	/// it must be re - set to the channel it was last on using this method.
	/// </summary>
	/// <param name="index">The index.</param>
	void setSound(std::string filepath)
	{
		m_audioEngine->setSound(m_filePath + m_fileName);
	}

	/// <summary>
	/// Plays the sound.
	/// </summary>
	void playSound() { m_audioEngine->playSound(m_filePath + m_fileName); }

	/// <summary>
	/// Stops all sounds.
	/// </summary>
	void stopAllSounds() { m_audioEngine->stopAllSoundEffects(); }

	/// <summary>
	/// Pauses the sound.
	/// </summary>
	/// <param name="paused">if set to <c>true</c> [paused].</param>
	void pauseSound(bool paused) { m_audioEngine->pauseSound(paused, m_filePath + m_fileName); }

	/// <summary>
	/// Determines whether [is sound playing].
	/// </summary>
	/// <returns></returns>
	bool isSoundPlaying()
	{
		if (m_audioEngine->isSoundPlaying(m_filePath + m_fileName))
			return true;
		else
			return false;
	}

	/// <summary>
	/// Originally sets the sound later used to reset the sound.
	/// </summary>
	void setSound() { m_audioEngine->setSound(m_filePath + m_fileName); }

	/// <summary>
	/// Gets global sound volume.
	/// </summary>
	/// <returns></returns>
	float getSoundVolume() { return m_audioEngine->getSoundVolume(); }

	/// <summary>
	/// Sets the sound volume for all sounds.
	/// </summary>
	/// <param name="volume">The volume level.</param>
	void setSoundVolumeAll(float volume) { m_audioEngine->setSoundEffectVolume(volume); }

	/// <summary>
	/// Sets this sounds volume.
	/// </summary>
	/// <param name="volume">The volume level.</param>
	void setSoundVolume(float volume) { m_audioEngine->setSoundEffectVolume(m_filePath + m_fileName, volume); }

	/// <summary>
	/// Sets the sound position and vel.
	/// </summary>
	/// <param name="pos">The position of this sound.</param>
	void setSoundPosition(glm::vec3 pos) { m_audioEngine->setSoundPosVel(m_filePath + m_fileName, pos); }

	/// <summary>
	/// Sets the panning of this sound.
	/// </summary>
	/// <param name="pan">The pan.</param>
	void setSoundPan(float pan) { m_audioEngine->setSoundPan(m_filePath + m_fileName, pan); }

	/// <summary>
	/// Sets this sounds doppler level.
	/// </summary>
	/// <param name="dop">The dop.</param>
	void setSoundDoppler(float dop) { m_audioEngine->setSoundDopplerLevel(m_filePath + m_fileName, dop); }

	/// <summary>
	/// Sets up the sound cone.
	/// </summary>
	/// <param name="orient">The orientation.</param>
	/// <param name="iCA">The inside Cone Angle.</param>
	/// <param name="oCA">The outside cone angle.</param>
	/// <param name="oVol">The outside volume (the level of volume outside the cone).</param>
	void setupSoundCone(glm::vec3 orient, float iCA, float oCA, float oVol)
	{
		m_audioEngine->setSoundConeSettings(m_filePath + m_fileName, iCA, oCA, oVol);
		m_audioEngine->setSoundConeOrientation(m_filePath + m_fileName, orient);
	}

	/// <summary>
	/// Sets the sound distance filter.
	/// </summary>
	/// <param name="custom">if set to <c>true</c> [custom].</param>
	/// <param name="customLevel">if set to <c>true</c> [custom level].</param>
	/// <param name="centreFreq">The centre freq.</param>
	void setSoundDistanceFilter(bool custom, bool customLevel, float centerFreq)
	{
		m_audioEngine->setSoundDistanceFilter(m_filePath + m_fileName, custom, customLevel, centerFreq);
	}

	/// <summary>
	/// Sets the sound 3D minimum distance for attenuation.
	/// </summary>
	/// <param name="min">The minimum.</param>
	void setSound3DMinDist(float min) { m_audioEngine->setSound3DMinMaxDistance(m_filePath + m_fileName, min); }

	/// <summary>
	/// Sets the occlusion (if something is in the way of the sound).
	/// </summary>
	/// <param name="attenuation">The attenuation.</param>
	void setSoundOcclusion(float attenuation) { m_audioEngine->setSoundOcclusion(m_filePath + m_fileName, attenuation); }

	/// <summary>
	/// Loads the sounds list.
	/// </summary>
	/// <param name="fileNames">The sounds' file names.</param>
	void loadSoundList(std::vector<std::string> fileNames) { m_audioEngine->loadSounds(fileNames); }

	/// <summary>
	/// Sets the file path.
	/// </summary>
	/// <param name="filePath">The file path.</param>
	void setFilePath(std::string filePath)
	{
		m_filePath = filePath;
	}

protected:
	/// <summary>
	/// The audio engine handle
	/// </summary>
	AudioEngine * m_audioEngine = m_parent->getCoreEngine()->getAudioEngine();

private:

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
};

