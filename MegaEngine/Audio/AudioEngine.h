// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Jesse Derochie
// Last Modified On : 02-03-2016
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
#include <string>
#include <unordered_map>

static const int NUM_STREAM_CHANNELS = 100;
static const int NUM_SOUND_CHANNELS = 100;

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
	/// Gets the sound channel group.
	/// </summary>
	/// <returns></returns>
	static FMOD::ChannelGroup * getSoundChannelGroup() { return m_soundEffectChannels; }

	/// <summary>
	/// Gets the stream channel group.
	/// </summary>
	/// <returns></returns>
	static FMOD::ChannelGroup * getStreamChannelGroup() { return m_streamEffectChannels; }

	/// <summary>
	/// Gets the streams.
	/// </summary>
	/// <returns></returns>
	static FMOD::Sound ** getStreams() { return m_streams; }

	/// <summary>
	/// Gets the stream channels.
	/// </summary>
	/// <returns></returns>
	static FMOD::Channel ** getStreamChannels() { return m_streamChannels; }


	static FMOD::Sound ** getSounds() { return m_sounds; }


	static FMOD::Channel ** getSoundChannels() { return m_soundChannels; }

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
	static void FMODVerifyResult(FMOD_RESULT result)
	{
		if (result != FMOD_OK)
		{
			std::cout << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
		}
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
	/// The stream effect channels.
	/// </summary>
	static FMOD::ChannelGroup * m_streamEffectChannels;

	/// <summary>
	/// The sound effect channels.
	/// </summary>
	static FMOD::ChannelGroup * m_soundEffectChannels;

		/// <summary>
	/// The streams.
	/// </summary>
	static FMOD::Sound * m_streams[NUM_STREAM_CHANNELS];
	/// <summary>
	/// The stream channels.
	/// </summary>
	static FMOD::Channel * m_streamChannels[NUM_STREAM_CHANNELS];

	/// <summary>
	/// The sound effects list.
	/// </summary>
	static FMOD::Sound * m_sounds[NUM_SOUND_CHANNELS];
	/// <summary>
	/// The sound channels.
	/// </summary>
	static FMOD::Channel * m_soundChannels[NUM_SOUND_CHANNELS];

	/// <summary>
	/// The FMOD result.
	/// </summary>
	FMOD_RESULT m_result;

};

