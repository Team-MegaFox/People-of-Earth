// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Jesse Derochie
// Last Modified On : 01-30-2016
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
#include "..\Audio\AudioEngine.h"
#include "../Core/Utility.h"

class AudioSource : public GameComponent
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="AudioSource"/> class.
	/// </summary>
	/// <param name="fileName">Name of the file.</param>
	AudioSource(const std::string& fileName) :
		m_parent(nullptr), 
		m_fileName(fileName) { }
	/// <summary>
	/// Finalizes an instance of the <see cref="AudioSource"/> class.
	/// </summary>
	~AudioSource() { }

	/// <summary>
	/// Sets the parent GameObject..
	/// </summary>
	/// <param name="parent">The GameObject to be attached to.</param>
	virtual void setParent(GameObject* parent) { m_parent = parent; }


	/// <summary>
	/// Plays the sound.
	/// </summary>
	void playSound() { a->playSound(m_filePath + m_fileName); }

	/// <summary>
	/// Plays the stream.
	/// </summary>
	void playStream() { a->playStream(m_filePath + m_fileName); }

	/// <summary>
	/// Stops all sounds.
	/// </summary>
	void stopAllSounds() { a->stopAllSoundEffects(); }

	/// <summary>
	/// Stops all streams.
	/// </summary>
	void stopAllStreams() { a->stopAllStreams(); }

	/// <summary>
	/// Pauses the sound.
	/// </summary>
	/// <param name="paused">if set to <c>true</c> [paused].</param>
	void pauseSound(bool paused) { a->pauseSound(paused, m_filePath + m_fileName); }

	/// <summary>
	/// Pauses the stream.
	/// </summary>
	/// <param name="paused">if set to <c>true</c> [paused].</param>
	void pauseStream(bool paused) { a->pauseStream(paused, m_filePath + m_fileName); }

	/// <summary>
	/// Determines whether [is sound playing].
	/// </summary>
	/// <returns></returns>
	bool isSoundPlaying()
	{
		if (a->isSoundPlaying(m_filePath + m_fileName))
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
		if (a->isStreamPlaying(m_filePath + m_fileName))
			return true;
		else
			return false;
	}

	/// <summary>
	/// Originally sets the sound later used to reset the sound.
	/// </summary>
	void setSound() { a->setSound(m_filePath + m_fileName); }

	/// <summary>
	/// Originally sets the stream later used to reset the stream.
	/// </summary>
	void setStream() { a->setStream(m_filePath + m_fileName); }

	/// <summary>
	/// Sets this as the listener in the scene.
	/// </summary>
	void setAsListener()
	{
		glm::vec3 forward = Utility::getForward(*m_parent->getTransform()->getRotation());
		glm::vec3 up = Utility::getUp(*m_parent->getTransform()->getRotation());

		a->setListener(
			*m_parent->getTransform()->getPosition(), 
			glm::vec3(0.0f), 
			forward, 
			up);
	}

	/// <summary>
	/// Gets global sound volume.
	/// </summary>
	/// <returns></returns>
	float getSoundVolume() { return a->getSoundVolume(); }

	/// <summary>
	/// Gets global stream volume.
	/// </summary>
	/// <returns></returns>
	float getStreamVolume() { return a->getStreamVolume(); }

	/// <summary>
	/// Sets the sound volume for all sounds.
	/// </summary>
	/// <param name="volume">The volume level.</param>
	void setSoundVolumeAll(float volume) { a->setSoundEffectVolume(volume); }

	/// <summary>
	/// Sets this sounds volume.
	/// </summary>
	/// <param name="volume">The volume level.</param>
	void setSoundVolume(float volume) { a->setSoundEffectVolume(m_filePath + m_fileName, volume); }

	/// <summary>
	/// Sets the stream volume for all streams.
	/// </summary>
	/// <param name="volume">The volume level.</param>
	void setStreamVolumeAll(float volume) { a->setStreamEffectVolume(volume); }

	/// <summary>
	/// Sets this streams volume.
	/// </summary>
	/// <param name="volume">The volume level.</param>
	void setStreamVolume(float volume) { a->setStreamEffectVolume(m_filePath + m_fileName, volume); }

	/// <summary>
	/// Sets the sound position and vel.
	/// </summary>
	/// <param name="pos">The position of this sound.</param>
	void setSoundPosition(glm::vec3 pos) { a->setSoundPosVel(m_filePath + m_fileName, pos); }

	/// <summary>
	/// Sets the stream position and vel.
	/// </summary>
	/// <param name="pos">The position of this stream.</param>
	void setStreamPosition(glm::vec3 pos) { a->setStreamPosVel(m_filePath + m_fileName, pos); }

	/// <summary>
	/// Sets the panning of this sound.
	/// </summary>
	/// <param name="pan">The pan.</param>
	void setSoundPan(float pan) { a->setSoundPan(m_filePath + m_fileName, pan); }

	/// <summary>
	/// Sets the panning of this stream.
	/// </summary>
	/// <param name="pan">The pan.</param>
	void setStreamPan(float pan) { a->setStreamPan(m_filePath + m_fileName, pan); }

	/// <summary>
	/// Sets this sounds doppler level.
	/// </summary>
	/// <param name="dop">The dop.</param>
	void setSoundDoppler(float dop) { a->setSoundDopplerLevel(m_filePath + m_fileName, dop); }

	/// <summary>
	/// Sets this streams doppler level.
	/// </summary>
	/// <param name="dop">The dop.</param>
	void setStreamDoppler(float dop) { a->setStreamDopplerLevel(m_filePath + m_fileName, dop); }

	/// <summary>
	/// Sets up the sound cone.
	/// </summary>
	/// <param name="orient">The orientation.</param>
	/// <param name="iCA">The inside Cone Angle.</param>
	/// <param name="oCA">The outside cone angle.</param>
	/// <param name="oVol">The outside volume (the level of volume outside the cone).</param>
	void setupSoundCone(glm::vec3 orient, float iCA, float oCA, float oVol)
	{
		a->setSoundConeSettings(m_filePath + m_fileName, iCA, oCA, oVol);
		a->setSoundConeOrientation(m_filePath + m_fileName, orient);
	}

	/// <summary>
	/// Sets the sound distance filter.
	/// </summary>
	/// <param name="custom">if set to <c>true</c> [custom].</param>
	/// <param name="customLevel">if set to <c>true</c> [custom level].</param>
	/// <param name="centreFreq">The centre freq.</param>
	void setSoundDistanceFilter(bool custom, bool customLevel, float centerFreq)
	{
		a->setSoundDistanceFilter(m_filePath + m_fileName, custom, customLevel, centerFreq);
	}

	/// <summary>
	/// Sets the sound 3D minimum distance for attenuation.
	/// </summary>
	/// <param name="min">The minimum.</param>
	void setSound3DMinDist(float min) { a->setSound3DMinMaxDistance(m_filePath + m_fileName, min); }

	/// <summary>
	/// Sets the stream 3D minimum distance for attenuation.
	/// </summary>
	/// <param name="min">The minimum.</param>
	void setStream3DMinDist(float min) { a->setStream3DMinMaxDistance(m_filePath + m_fileName, min); }

	/// <summary>
	/// Sets the occlusion (if something is in the way of the sound).
	/// </summary>
	/// <param name="attenuation">The attenuation.</param>
	void setSoundOcclusion(float attenuation) { a->setSoundOcclusion(m_filePath + m_fileName, attenuation); }

	/// <summary>
	/// Sets the occlusion (if something is in the way of the stream).
	/// </summary>
	/// <param name="attenuation">The attenuation.</param>
	void setStreamOcclusion(float attenuation) { a->setStreamOcclusion(m_filePath + m_fileName, attenuation); }

	/// <summary>
	/// Loads the sounds list.
	/// </summary>
	/// <param name="fileNames">The sounds' file names.</param>
	void loadSoundList(std::vector<std::string> fileNames) { a->loadSounds(fileNames); }

	/// <summary>
	/// Loads the streams list.
	/// </summary>
	/// <param name="fileNames">The streams' file names.</param>
	void loadStreamList(std::vector<std::string> fileNames) { a->loadStreams(fileNames); }

	/// <summary>
	/// Disposes the specified sounds and streams in the engine.
	/// </summary>
	/// <param name="soundFileNames">The sound file names.</param>
	/// <param name="streamFileNames">The stream file names.</param>
	void dispose(std::vector<std::string> soundFileNames, std::vector<std::string> streamFileNames)
	{
		a->dispose(soundFileNames, streamFileNames);
	}

	void setFilePath(std::string filePath)
	{
		m_filePath = filePath;
	}

protected:

	AudioEngine * a = m_parent->getCoreEngine()->getAudioEngine();
	/// <summary>
	/// Gets the core engine.
	/// </summary>
	/// <returns></returns>
	CoreEngine* getCoreEngine() { return m_parent->getCoreEngine(); }
	 

private:
	/// <summary>
	/// The file name of this audiosource file
	/// </summary>
	std::string m_fileName;

	/// <summary>
	/// The m_parent Game Object
	/// </summary>
	GameObject * m_parent;

	/// <summary>
	/// The file path of this audiosource file
	/// </summary>
	std::string m_filePath = "";

};
