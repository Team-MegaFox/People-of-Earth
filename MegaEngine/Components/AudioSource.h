// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Jesse Derochie
// Last Modified On : 02-01-2016
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
#include "../Audio/AudioListener.h"

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
	AudioSource(const Sound & sound) :
		m_soundSource(sound)
	{}
	/// <summary>
	/// Initializes a new instance of the <see cref="AudioSource"/> class.
	/// </summary>
	/// <param name="stream">The stream.</param>
	AudioSource(const Stream & stream) :
		m_streamSource(stream)
	{}
	/// <summary>
	/// Initializes a new instance of the <see cref="AudioSource"/> class.
	/// </summary>
	/// <param name="listener">The listener.</param>
	AudioSource(const AudioListener & listener) :
		m_audioListener(listener) 
	{}
	/// <summary>
	/// Initializes a new instance of the <see cref="AudioSource"/> class.
	/// </summary>
	/// <param name="fileName">Name of the file.</param>
	AudioSource(const std::string& fileName) { }
	/// <summary>
	/// Finalizes an instance of the <see cref="AudioSource"/> class.
	/// </summary>
	~AudioSource() { }

	/// <summary>
	/// Sets the parent.
	/// </summary>
	/// <param name="parent">The parent.</param>
	virtual void setParent(GameObject * parent) { m_parent = parent; }

	/// <summary>
	/// Plays the sound.
	/// </summary>
	void playSound() { m_soundSource.playSound(); }

	/// <summary>
	/// Plays the stream.
	/// </summary>
	void playStream(bool looping) { m_streamSource.playStream(looping); }

	/// <summary>
	/// Stops all sounds.
	/// </summary>
	void stopAllSounds() { m_soundSource.stopAllSoundEffects(); }

	/// <summary>
	/// Stops all streams.
	/// </summary>
	void stopAllStreams() { m_streamSource.stopAllStreams(); }

	/// <summary>
	/// Pauses the sound.
	/// </summary>
	/// <param name="paused">if set to <c>true</c> [paused].</param>
	void pauseSound(bool paused) { m_soundSource.pauseSound(paused); }

	/// <summary>
	/// Pauses the stream.
	/// </summary>
	/// <param name="paused">if set to <c>true</c> [paused].</param>
	void pauseStream(bool paused) { m_streamSource.pauseStream(paused); }

	/// <summary>
	/// Determines whether [is sound playing].
	/// </summary>
	/// <returns></returns>
	bool isSoundPlaying()
	{
		if (m_soundSource.isSoundPlaying())
			return true;
		else
			return false;
	}

	/// <summary>
	/// Determines whether [is stream playing].
	/// </summary>
	/// <returns></returns>
	bool isStreamPlaying()
	{
		if (m_streamSource.isStreamPlaying())
			return true;
		else
			return false;
	}

	/// <summary>
	/// Originally sets the sound later used to reset the sound.
	/// </summary>
	void setSound(std::string filename) { m_soundSource.setSound(filename); }

	/// <summary>
	/// Originally sets the stream later used to reset the stream.
	/// </summary>
	void setStream(std::string filename) { m_streamSource.setStream(filename); }

	/// <summary>
	/// Gets global sound volume.
	/// </summary>
	/// <returns></returns>
	float getSoundVolume() { return m_soundSource.getSoundVolume(); }

	/// <summary>
	/// Gets global stream volume.
	/// </summary>
	/// <returns></returns>
	float getStreamVolume() { return m_streamSource.getStreamVolume(); }

	/// <summary>
	/// Sets the sound volume for all sounds.
	/// </summary>
	/// <param name="volume">The volume level.</param>
	void setSoundVolumeAll(float volume) { m_soundSource.setSoundEffectVolumeAll(volume); }

	/// <summary>
	/// Sets this sounds volume.
	/// </summary>
	/// <param name="volume">The volume level.</param>
	void setSoundVolume(float volume) { m_soundSource.setSoundEffectVolume(volume); }

	/// <summary>
	/// Sets the stream volume for all streams.
	/// </summary>
	/// <param name="volume">The volume level.</param>
	void setStreamVolumeAll(float volume) { m_streamSource.setStreamEffectVolumeAll(volume); }

	/// <summary>
	/// Sets this streams volume.
	/// </summary>
	/// <param name="volume">The volume level.</param>
	void setStreamVolume(float volume) { m_streamSource.setStreamEffectVolume(volume); }

	/// <summary>
	/// Sets the sound position and vel.
	/// </summary>
	/// <param name="pos">The position of this sound.</param>
	void setSoundPosition(glm::vec3 pos) { m_soundSource.setSoundPosVel(pos); }

	/// <summary>
	/// Sets the stream position and vel.
	/// </summary>
	/// <param name="pos">The position of this stream.</param>
	void setStreamPosition(glm::vec3 pos) { m_streamSource.setStreamPosVel(pos); }

	/// <summary>
	/// Sets the panning of this sound.
	/// </summary>
	/// <param name="pan">The pan.</param>
	void setSoundPan(float pan) { m_soundSource.setSoundPan(pan); }

	/// <summary>
	/// Sets the panning of this stream.
	/// </summary>
	/// <param name="pan">The pan.</param>
	void setStreamPan(float pan) { m_streamSource.setStreamPan(pan); }

	/// <summary>
	/// Sets this sounds doppler level.
	/// </summary>
	/// <param name="dop">The dop.</param>
	void setSoundDoppler(float dop) { m_soundSource.setSoundDopplerLevel(dop); }

	/// <summary>
	/// Sets this streams doppler level.
	/// </summary>
	/// <param name="dop">The dop.</param>
	void setStreamDoppler(float dop) { m_streamSource.setStreamDopplerLevel(dop); }

	/// <summary>
	/// Sets up the sound cone.
	/// </summary>
	/// <param name="orient">The orientation.</param>
	/// <param name="iCA">The inside Cone Angle.</param>
	/// <param name="oCA">The outside cone angle.</param>
	/// <param name="oVol">The outside volume (the level of volume outside the cone).</param>
	void setupSoundCone(glm::vec3 orient, float iCA, float oCA, float oVol)
	{
		m_soundSource.setSoundConeOrientation(orient);
		m_soundSource.setSoundConeSettings(iCA, oCA, oVol);
	}

	/// <summary>
	/// Sets the sound distance filter.
	/// </summary>
	/// <param name="custom">if set to <c>true</c> [custom].</param>
	/// <param name="customLevel">if set to <c>true</c> [custom level].</param>
	/// <param name="centreFreq">The centre freq.</param>
	void setSoundDistanceFilter(bool custom, bool customLevel, float centerFreq
	{
		m_soundSource.setSoundDistanceFilter(custom, customLevel, centerFreq);
	}

	/// <summary>
	/// Sets the sound 3D minimum distance for attenuation.
	/// </summary>
	/// <param name="min">The minimum.</param>
	void setSound3DMinDist(float min, float max = NULL) { m_soundSource.setSound3DMinMaxDistance(min, max); }

	/// <summary>
	/// Sets the stream 3D minimum distance for attenuation.
	/// </summary>
	/// <param name="min">The minimum.</param>
	void setStream3DMinDist(float min, float max = NULL) { m_streamSource.setStream3DMinMaxDistance(min, max); }

	/// <summary>
	/// Sets the occlusion (if something is in the way of the sound).
	/// </summary>
	/// <param name="attenuation">The attenuation.</param>
	void setSoundOcclusion(float attenuation, float reverberation = NULL) { m_soundSource.setSoundOcclusion(attenuation); }

	/// <summary>
	/// Sets the occlusion (if something is in the way of the stream).
	/// </summary>
	/// <param name="attenuation">The attenuation.</param>
	void setStreamOcclusion(float attenuation, float reverberation = NULL) { m_streamSource.setStreamOcclusion(attenuation); }

	/// <summary>
	/// Loads the sounds list.
	/// </summary>
	/// <param name="fileNames">The sounds' file names.</param>
	void loadSoundList(std::vector<std::string> fileNames) { m_soundSource.loadSounds(fileNames); }

	/// <summary>
	/// Loads the streams list.
	/// </summary>
	/// <param name="fileNames">The streams' file names.</param>
	void loadStreamList(std::vector<std::string> fileNames) { m_streamSource.loadStreams(fileNames); }

	/// <summary>
	/// Sets as listener.
	/// </summary>
	void setAsListener()
	{
		m_audioListener.setAsListener(m_parent);
	}

protected:
	 
	/// <summary>
	/// The sound source handle
	/// </summary>
	Sound m_soundSource;
	/// <summary>
	/// The stream source handle
	/// </summary>
	Stream m_streamSource;

	/// <summary>
	/// The audio listener handle
	/// </summary>
	AudioListener m_audioListener;

private:
	/// <summary>
	/// The parent Game Object
	/// </summary>
	GameObject * m_parent;

};
