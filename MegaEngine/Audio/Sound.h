// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 02-01-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 02-25-2016
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
	Sound(const std::string& fileName);
	/// <summary>
	/// Finalizes an instance of the <see cref="SoundSource"/> class.
	/// </summary>
	~Sound() {	}

	/// <summary>
	/// Sets the sound.
	/// </summary>
	void setSound();

	/// <summary>
	/// Plays the sound.
	/// </summary>
	void playSound();

	/// <summary>
	/// Pauses the sound.
	/// </summary>
	/// <param name="pause">if set to <c>true</c> [pause].</param>
	void pauseSound(bool pause);

	/// <summary>
	/// Stops all sound effects.
	/// </summary>
	void stop();

	/// <summary>
	/// Determines whether this sound is playing.
	/// </summary>
	/// <returns></returns>
	bool isSoundPlaying();

	/// <summary>
	/// Sets the sound effect volume.
	/// </summary>
	/// <param name="volumeLevel">The volume level.</param>
	void setSoundEffectVolume(float volumeLevel);

	/// <summary>
	/// Gets the sound volume.
	/// </summary>
	/// <returns></returns>
	float & getSoundVolume();

	/// <summary>
	/// Sets the sound position vel.
	/// </summary>
	/// <param name="pos">The position.</param>
	/// <param name="vel">The vel.</param>
	void setSoundPosVel(glm::vec3 pos, glm::vec3 vel = glm::vec3(0.0f));

	/// <summary>
	/// Pan level, from -1.0 (left) to 1.0 (right), default = 0 (center).
	/// </summary>
	/// <param name="pan">The pan.</param>
	void setSoundPan(float pan);

	/// <summary>
	/// Sets the sound doppler level.
	/// Use with (but before) setSoundDistanceFilter for proper effect
	/// </summary>
	/// <param name="dopplerLevel">The doppler level.</param>
	void setSoundDopplerLevel(float dopplerLevel);

	/// <summary>
	/// Sets the sound cone orientation.
	/// </summary>
	/// <param name="orientation">The orientation.</param>
	void setSoundConeOrientation(glm::vec3 orientation);

	/// <summary>
	/// Sets the sound cone settings.
	/// </summary>
	/// <param name="insideConeAngle">The inside cone angle.</param>
	/// <param name="outsideConeAngle">The outside cone angle.</param>
	/// <param name="outsideVolume">The outside volume.</param>
	void setSoundConeSettings(float insideConeAngle, float outsideConeAngle, float outsideVolume);

	/// <summary>
	/// Sets the sound distance filter.
	/// Use with but after setSoundDopplerLevel
	/// </summary>
	/// <param name="custom">if set to <c>true</c> [custom].</param>
	/// <param name="customLevel">if set to <c>true</c> [custom level].</param>
	/// <param name="centerFreq">The center freq.</param>
	void setSoundDistanceFilter(bool custom, bool customLevel, float centerFreq);

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
	void setSound3DMinMaxDistance(float min, float max = NULL);

private:

	/// <summary>
	/// The file name of this audiosource file
	/// </summary>
	std::string m_fileName;

	/// <summary>
	/// The sound's volume.
	/// </summary>
	float m_soundVolume;

	/// <summary>
	/// The sound pair
	/// Pair is made up of the FMOD:Sound * and the FMOD::Channel* that sound needs to be playable
	/// </summary>
	std::pair<FMOD::Sound*, FMOD::Channel*> m_soundPair;

};

