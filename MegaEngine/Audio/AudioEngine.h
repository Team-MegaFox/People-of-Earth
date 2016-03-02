// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Jesse Derochie
// Last Modified On : 02-24-2016
// ***********************************************************************
// <copyright file="AudioEngine.h" company="Team MegaFox">
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
#pragma once
#include <iostream>
#include <FMOD\fmod.h>
#include <FMOD\fmod.hpp>
#include <FMOD\fmod_errors.h>

#include <GLM\glm.hpp>
#include <vector>
#include <algorithm>


#include <string>

const int MAX_NUM_CHANNELS = 100;

class Audio;

/// <summary>
/// Class AudioEngine.
/// </summary>
class AudioEngine
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="AudioEngine"/> class.
	/// </summary>
	AudioEngine();
	/// <summary>
	/// Finalizes an instance of the <see cref="AudioEngine"/> class.
	/// </summary>
	~AudioEngine() {}
	/// <summary>
	/// Initializes a new instance of the <see cref="AudioEngine"/> class.
	/// Nullify the copy constructor
	/// </summary>
	/// <param name="">The .</param>
	AudioEngine(const AudioEngine&) = delete;

	/// <summary>
	/// Disposes the specified sound list.
	/// </summary>
	void dispose();

	/// <summary>
	/// Gets the system.
	/// </summary>
	/// <returns></returns>
	static FMOD::System * getSystem() { return m_system; }

	/// <summary>
	/// Updates the system object
	/// (should be called every frame)
	/// </summary>
	void update();

	/// <summary>
	/// Verifies that each step of the initialization 
	/// was properly initalized.
	/// </summary>
	/// <param name="result">The result.</param>
	static void FMODVerifyResult(FMOD_RESULT result);

	/// <summary>
	/// Converts glm::vec3's to FMOD_VECTOR *'s
	/// for use in FMOD's positioning of the listener
	/// and sound / stream positioning
	/// </summary>
	/// <param name="vector">The glm vector to convert.</param>
	/// <returns>The resulting FMOD vector conversion.</returns>
	static FMOD_VECTOR glmToFMOD(glm::vec3 vector);

	/// <summary>
	/// Gets the sound volume.
	/// </summary>
	/// <returns></returns>
	inline float getSoundVolume() const { return m_soundVolume; }
	/// <summary>
	/// Gets the stream volume.
	/// </summary>
	/// <returns></returns>
	inline float getStreamVolume() const { return m_streamVolume; }

	/// <summary>
	/// Sets the sound volume.
	/// </summary>
	/// <param name="volume">The volume.</param>
	void setSoundVolume(float volume);
	/// <summary>
	/// Sets the stream volume.
	/// </summary>
	/// <param name="volume">The volume.</param>
	void setStreamVolume(float volume);

	/// <summary>
	/// Adds the audio comp.
	/// </summary>
	/// <param name="audio">The audio.</param>
	void addAudioComp(Audio * audio) { m_audioComp.push_back(audio); }
	/// <summary>
	/// Removes the audio comp.
	/// </summary>
	/// <param name="audio">The audio.</param>
	void removeAudioComp(Audio * audio) { 
		m_audioComp.erase(std::find(m_audioComp.begin(), m_audioComp.end(), audio));
	}

private:
	
	/// <summary>
	/// Initializes FMOD
	/// called automatically when the
	/// AudioEngine instance is created.
	/// </summary>
	void init();

	// FMOD requirements
	/// <summary>
	/// The FMOD system.
	/// </summary>
	static FMOD::System * m_system;

	/// <summary>
	/// The FMOD result.
	/// </summary>
	FMOD_RESULT m_result;

	/// <summary>
	/// The stream volume
	/// </summary>
	float m_streamVolume = 1.0f;
	/// <summary>
	/// The sound volume
	/// </summary>
	float m_soundVolume = 1.0f;

	/// <summary>
	/// The audio components vector
	/// </summary>
	std::vector<Audio *> m_audioComp;
};

