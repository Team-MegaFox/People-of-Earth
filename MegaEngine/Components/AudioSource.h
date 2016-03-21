// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 03-21-2016
// ***********************************************************************
// <copyright file="AudioSource.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
/*	
	This AudioSource.h file was created to allow users to interface with
	the AudioEngine in MegaEngine, the methods available within this class
	make it so that anything we could foresee being useful was obtainable.
*/
// </summary>
// ***********************************************************************

#pragma once
#include "GameComponents.h"
#include <string>
#include "../Core/CoreEngine.h"
#include "../Core/GameObject.h"

#include "../Audio/Sound.h"
#include "../Audio/Stream.h"

enum AudioType
{
	STREAM,
	SOUND
};

class AudioSource : public GameComponent
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="AudioSource"/> class.
	/// </summary>
	AudioSource() {}
	/// <summary>
	/// Initializes a new instance of the <see cref="AudioSource"/> class.
	/// </summary>
	/// <param name="sound">The sound.</param>
	AudioSource(const std::string & fileName, AudioType type, bool TwoD = false, bool deleteOnEnd = false);
	/// <summary>
	/// Finalizes an instance of the <see cref="AudioSource"/> class.
	/// </summary>
	~AudioSource();

	virtual void onStart() override;

	virtual void update(float delta) override;

	/// <summary>
	/// Checks if the Audio Source is a stream sound.
	/// </summary>
	/// <returns>Weather the object is a stream.</returns>
	bool isStream();

	/// <summary>
	/// Plays the sound.
	/// </summary>
	void play(bool looping = false);
	/// <summary>
	/// Stops all sounds.
	/// </summary>
	void stop();
	/// <summary>
	/// Pauses the sound.
	/// </summary>
	/// <param name="paused">if set to <c>true</c> [paused].</param>
	void pause(bool paused);
	/// <summary>
	/// Determines whether [is sound playing].
	/// </summary>
	/// <returns></returns>
	bool isPlaying();

	/// <summary>
	/// Gets global sound volume.
	/// </summary>
	/// <returns></returns>
	float getVolume();

	/// <summary>
	/// Sets this sounds volume.
	/// </summary>
	/// <param name="volume">The volume level.</param>
	void setVolume(float volume);
	/// <summary>
	/// Sets the new volume.
	/// </summary>
	void updateVolume();

	/// <summary>
	/// Sets the sound position and vel.
	/// </summary>
	/// <param name="pos">The position of this sound.</param>
	void setPosition(PxVec3 pos);

	/// <summary>
	/// Sets the panning of this sound.
	/// </summary>
	/// <param name="pan">The pan.</param>
	void setPan(float pan);

	/// <summary>
	/// Sets this sounds doppler level.
	/// </summary>
	/// <param name="dop">The dop.</param>
	void setDoppler(float dop);

	/// <summary>
	/// Sets up the sound cone.
	/// </summary>
	/// <param name="orient">The orientation.</param>
	/// <param name="iCA">The inside Cone Angle.</param>
	/// <param name="oCA">The outside cone angle.</param>
	/// <param name="oVol">The outside volume (the level of volume outside the cone).</param>
	void setupCone(PxVec3 orient, float iCA, float oCA, float oVol);

	/// <summary>
	/// Sets the sound distance filter.
	/// </summary>
	/// <param name="custom">if set to <c>true</c> [custom].</param>
	/// <param name="customLevel">if set to <c>true</c> [custom level].</param>
	/// <param name="centreFreq">The centre freq.</param>
	void setDistanceFilter(bool custom, bool customLevel, float centerFreq);

	/// <summary>
	/// Sets the sound 3D minimum distance for attenuation.
	/// </summary>
	/// <param name="min">The minimum.</param>
	void set3DMinDist(float min, float max = NULL);

protected:
	 
	/// <summary>
	/// The sound source handle
	/// </summary>
	Sound * m_soundSource;

	/// <summary>
	/// The stream source handle
	/// </summary>
	Stream * m_streamSource;

	/// <summary>
	/// The volume ratio value
	/// </summary>
	float m_originalVolume = 1.0f;

	/// <summary>
	/// Weather to delete the Audio Source and attached GameObject when the audio is finished playing.
	/// </summary>
	bool m_deleteOnEnd;
};
