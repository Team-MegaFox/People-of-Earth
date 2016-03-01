// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Jesse Derochie
// Last Modified On : 02-24-2016
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
	AudioSource(const Sound & sound);
	/// <summary>
	/// Initializes a new instance of the <see cref="AudioSource"/> class.
	/// </summary>
	/// <param name="stream">The stream.</param>
	AudioSource(const Stream & stream);
	/// <summary>
	/// Finalizes an instance of the <see cref="AudioSource"/> class.
	/// </summary>
	~AudioSource() { }

	/// <summary>
	/// Plays the sound.
	/// </summary>
	void playSound();
	/// <summary>
	/// Plays the stream.
	/// </summary>
	void playStream(bool looping);
	/// <summary>
	/// Stops all sounds.
	/// </summary>
	void stopSound();
	/// <summary>
	/// Stops all streams.
	/// </summary>
	void stopStream();
	/// <summary>
	/// Pauses the sound.
	/// </summary>
	/// <param name="paused">if set to <c>true</c> [paused].</param>
	void pauseSound(bool paused);
	/// <summary>
	/// Pauses the stream.
	/// </summary>
	/// <param name="paused">if set to <c>true</c> [paused].</param>
	void pauseStream(bool paused);
	/// <summary>
	/// Determines whether [is sound playing].
	/// </summary>
	/// <returns></returns>
	bool isSoundPlaying();

	/// <summary>
	/// Determines whether [is stream playing].
	/// </summary>
	/// <returns></returns>
	bool isStreamPlaying();

	/// <summary>
	/// Gets global sound volume.
	/// </summary>
	/// <returns></returns>
	float getSoundVolume();

	/// <summary>
	/// Gets global stream volume.
	/// </summary>
	/// <returns></returns>
	float getStreamVolume();

	/// <summary>
	/// Sets this sounds volume.
	/// </summary>
	/// <param name="volume">The volume level.</param>
	void setSoundVolume(float volume);

	/// <summary>
	/// Sets this streams volume.
	/// </summary>
	/// <param name="volume">The volume level.</param>
	void setStreamVolume(float volume);

	/// <summary>
	/// Sets the sound position and vel.
	/// </summary>
	/// <param name="pos">The position of this sound.</param>
	void setSoundPosition(glm::vec3 pos);

	/// <summary>
	/// Sets the stream position and vel.
	/// </summary>
	/// <param name="pos">The position of this stream.</param>
	void setStreamPosition(glm::vec3 pos);

	/// <summary>
	/// Sets the panning of this sound.
	/// </summary>
	/// <param name="pan">The pan.</param>
	void setSoundPan(float pan);

	/// <summary>
	/// Sets the panning of this stream.
	/// </summary>
	/// <param name="pan">The pan.</param>
	void setStreamPan(float pan);

	/// <summary>
	/// Sets this sounds doppler level.
	/// </summary>
	/// <param name="dop">The dop.</param>
	void setSoundDoppler(float dop);

	/// <summary>
	/// Sets this streams doppler level.
	/// </summary>
	/// <param name="dop">The dop.</param>
	void setStreamDoppler(float dop);

	/// <summary>
	/// Sets up the sound cone.
	/// </summary>
	/// <param name="orient">The orientation.</param>
	/// <param name="iCA">The inside Cone Angle.</param>
	/// <param name="oCA">The outside cone angle.</param>
	/// <param name="oVol">The outside volume (the level of volume outside the cone).</param>
	void setupSoundCone(glm::vec3 orient, float iCA, float oCA, float oVol);

	/// <summary>
	/// Sets the sound distance filter.
	/// </summary>
	/// <param name="custom">if set to <c>true</c> [custom].</param>
	/// <param name="customLevel">if set to <c>true</c> [custom level].</param>
	/// <param name="centreFreq">The centre freq.</param>
	void setSoundDistanceFilter(bool custom, bool customLevel, float centerFreq);

	/// <summary>
	/// Sets the stream distance filter.
	/// </summary>
	/// <param name="custom">if set to <c>true</c> [custom].</param>
	/// <param name="customLevel">if set to <c>true</c> [custom level].</param>
	/// <param name="centreFreq">The centre freq.</param>
	void setStreamDistanceFilter(bool custom, bool customLevel, float centerFreq);

	/// <summary>
	/// Sets the sound 3D minimum distance for attenuation.
	/// </summary>
	/// <param name="min">The minimum.</param>
	void setSound3DMinDist(float min, float max = NULL);

	/// <summary>
	/// Sets the stream 3D minimum distance for attenuation.
	/// </summary>
	/// <param name="min">The minimum.</param>
	void setStream3DMinDist(float min, float max = NULL);

protected:
	 
	/// <summary>
	/// The sound source handle
	/// </summary>
	Sound m_soundSource;

	/// <summary>
	/// The stream source handle
	/// </summary>
	Stream m_streamSource;
};
