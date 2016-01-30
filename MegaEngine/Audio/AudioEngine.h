// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Jesse Derochie
// Last Modified On : 01-30-2016
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

class AudioSource;

static const int NUM_SOUND_CHANNELS = 45;
static const int NUM_STREAM_CHANNELS = 15;

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
	~AudioEngine();

	/// <summary>
	/// Sets the file path.
	/// </summary>
	/// <param name="filepath">The filepath.</param>
	void setFilePath(std::string filepath);

	/// <summary>
	/// Used to set a sound to a channel initially, 
	/// also if a sound has been played once,
	/// it must be re - set to the channel it was last on using this method.
	/// </summary>
	/// <param name="index">The index.</param>
	void setSound(std::string filepath);

	/// <summary>
	/// Used to set a stream to a channel initially, 
	/// also if a stream has been played once,
	/// it must be re - set to the channel it was last on using this method.
	/// </summary>
	/// <param name="index">The index.</param>
	void setStream(std::string filepath);

	/// <summary>
	/// Plays the sound in question.
	/// </summary>
	/// <param name="index">The index.</param>
	void playSound(std::string filepath);

	/// <summary>
	/// Plays the stream in question.
	/// </summary>
	/// <param name="index">The index.</param>
	/// <param name="looping">If it is looping.</param>
	void playStream(std::string filepath, bool looping = false);

	/// <summary>
	/// Either pauses or unpauses the sound
	/// in question depending on how this method is called.
	/// </summary>
	/// <param name="pause">If it is paused.</param>
	/// <param name="index">The index.</param>
	void pauseSound(bool pause, std::string filepath);

	/// <summary>
	/// Either pauses or unpauses the stream 
	/// in question depending on how this method is called.
	/// </summary>
	/// <param name="pause">The pause.</param>
	/// <param name="index">The index.</param>
	void pauseStream(bool pause, std::string filepath);

	/// <summary>
	/// Stops all sounds whether they are playing or not.
	/// </summary>
	void stopAllSoundEffects();

	/// <summary>
	/// Stops all streams whether they are playing or not.
	/// </summary>
	void stopAllStreams();

	/// <summary>
	/// Returns true if the sound in question
	/// is currently playing
	/// </summary>
	/// <param name="index">The index.</param>
	/// <returns>If the sound is playing.</returns>
	bool isSoundPlaying(std::string filepath);

	/// <summary>
	/// Returns true if the stream in question
	/// is currently playing
	/// </summary>
	/// <param name="index">The index.</param>
	/// <returns>If the stream is playing.</returns>
	bool isStreamPlaying(std::string filepath);

	/// <summary>
	/// Sets the volume level of all sounds
	/// </summary>
	/// <param name="volumeLevel">The volume level.</param>
	void setSoundEffectVolume(float volumeLevel);
	
	/// <summary>
	/// Affect an individual sound channels volume level
	/// </summary>
	/// <param name="index">The index.</param>
	/// <param name="volumeLevel">The volume level.</param>
	void setSoundEffectVolume(std::string filepath, float volumeLevel);

	/// <summary>
	/// Affect an individual stream channels volume level.
	/// </summary>
	/// <param name="index">The index.</param>
	/// <param name="volumeLevel">The volume level.</param>
	void setStreamEffectVolume(std::string filepath, float volumeLevel);

	/// <summary>
	/// Sets the volume level of all streams
	/// </summary>
	/// <param name="volumeLevel">The volume level.</param>
	void setStreamEffectVolume(float volumeLevel);
	
	/// <summary>
	/// Gets the current volume level of all
	/// sounds
	/// </summary>
	/// <returns>The sound's volume level.</returns>
	float & getSoundVolume();
	
	/// <summary>
	/// Gets the current volume level of all
	/// streams
	/// </summary>
	/// <returns>The stream's volume level.</returns>
	float & getStreamVolume();
	
	/// <summary>
	/// Adds an audio source.
	/// </summary>
	/// <param name="source">The audio source.</param>
	void addAudioSource(AudioSource* source);

	/// <summary>
	/// This method sets the position of the listener in the world
	/// This in most game would be the player character
	/// </summary>
	/// <param name="pos">The position.</param>
	/// <param name="vel">The velocity.</param>
	/// <param name="forward">The forward vector.</param>
	/// <param name="up">The upward vector.</param>
	void setListener(glm::vec3 pos, glm::vec3 vel, glm::vec3 forward, glm::vec3 up);

	/// <summary>
	/// This method sets the position of the sound in the world
	/// if there is a velocity that the sound is traveling
	/// at then this is passed in as well.
	/// </summary>
	/// <param name="index">The index.</param>
	/// <param name="pos">The position.</param>
	/// <param name="vel">The velocity.</param>
	void setSoundPosVel(std::string filepath, glm::vec3 pos, glm::vec3 vel = glm::vec3(0.0f));

	/// <summary>
	/// This method sets the position of the stream in the world
	/// if there is a velocity that the stream is traveling
	/// at then this is passed in as well.
	/// </summary>
	/// <param name="index">The index.</param>
	/// <param name="pos">The position.</param>
	/// <param name="vel">The velocity.</param>
	void setStreamPosVel(std::string filepath, glm::vec3 pos, glm::vec3 vel = glm::vec3(0.0f));

	/// <summary>
	/// Panning is used to set a sound effect to be either to the
	/// left, center or right of the listener.
	/// </summary>
	/// <param name="index">The index.</param>
	/// <param name="pan">The pan.</param>
	void setSoundPan(std::string filepath, float pan);

	/// <summary>
	/// Panning is used to set a stream effect to be either to the
	/// left, center or right of the listener
	/// </summary>
	/// <param name="index">The index.</param>
	/// <param name="pan">The pan.</param>
	void setStreamPan(std::string filepath, float pan);

	/// <summary>
	/// Doppler is the change in frequency of a sound as it moves relative to the position of
	/// the listener(the Doppler Effect).So if a sound is moving past a listener, or a listener
	/// is moving past a sound(or if they are both moving), the listener will perceive the pitch
	/// of the sound changing as the object moves.
	/// </summary>
	/// <param name="index">The index.</param>
	/// <param name="dopplerLevel">The doppler level.</param>
	void setSoundDopplerLevel(std::string filepath, float dopplerLevel);

	/// <summary>
	/// Doppler is the change in frequency of a stream as it moves relative to the position of
	/// the listener(the Doppler Effect).So if a stream is moving past a listener, or a listener
	/// is moving past a stream(or if they are both moving), the listener will perceive the pitch
	/// of the stream changing as the object moves.
	/// </summary>
	/// <param name="index">The index.</param>
	/// <param name="dopplerLevel">The doppler level.</param>
	void setStreamDopplerLevel(std::string filepath, float dopplerLevel);

	/// <summary>
	/// Sets the orientation of the sound projection cone.
	/// </summary>
	/// <param name="index">The index.</param>
	/// <param name="orientation">The orientation of the cone.</param>
	void setSoundConeOrientation(std::string filepath, glm::vec3 orientation);

	/// <summary>
	/// Sets the size and shape of the sound projection cone
	/// outsideVolume must be a value between 0.0 and 1.0
	/// the default is 1.0.This is the volume of the sound
	/// outside the cone angles and direction
	/// </summary>
	/// <param name="index">The index.</param>
	/// <param name="insideConeAngle">The inside cone angle.</param>
	/// <param name="outsideConeAngle">The outside cone angle.</param>
	/// <param name="outsideVolume">The outside volume.</param>
	void setSoundConeSettings(std::string filepath, float insideConeAngle, float outsideConeAngle, float outsideVolume);

	/// <summary>
	/// Control the behaviour of a 3D distance filter, whether to enable or disable it, and frequency characteristics.
	/// </summary>
	/// <param name="index">The index.</param>
	/// <param name="custom">If true, disable FMOD distance rolloff.</param>
	/// <param name="customLevel">Set attenuation factor here, 1.0 is no attenuation, 0.0 complete attenuation.</param>
	/// <param name="centreFreq">Specify a center frequency for the high-pass filter used to simulate distance attenuation.</param>
	void setSoundDistanceFilter(std::string filepath, bool custom, bool customLevel, float centerFreq);

	/// <summary>
	/// 3D Min distance refers to the minimum distance a sound travels before it starts to
	/// attenuate and 3D Max distance refers to the maximum distance a sound travels before it
	/// stops attenuating.
	/// </summary>
	/// <param name="index">The index.</param>
	/// <param name="min">The minimum.</param>
	/// <param name="max">The maximum.</param>
	void setSound3DMinMaxDistance(std::string filepath, float min, float max = NULL);

	/// <summary>
	/// 3D Min distance refers to the minimum distance a stream travels before it starts to
	/// attenuate and 3D Max distance refers to the maximum distance a stream travels before it
	/// stops attenuating.
	/// </summary>
	/// <param name="index">The index.</param>
	/// <param name="min">The minimum.</param>
	/// <param name="max">The maximum.</param>
	void setStream3DMinMaxDistance(std::string filepath, float min, float max = NULL);

	/// <summary>
	/// This is used when there are obstacles in the way of a sound
	/// </summary>
	/// <param name="index">The index.</param>
	/// <param name="attenuation">Must be a value between 0.0 and 1.0
	/// at 0.0 there is no attenuation, at 1.0 there is complete attenuation</param>
	/// <param name="reverberation">must be a value between 0.0 and 1.0
	/// at 0.0 there is no reverberation, at 1.0 there is complete reverberation.</param>
	void setSoundOcclusion(std::string filepath, float attenuation, float reverberation = 0.0f);

	/// <summary>
	/// This is used when there are obstacles in the way of a stream
	/// </summary>
	/// <param name="index">The particular channel to affect</param>
	/// <param name="attenuation">must be a value between 0.0 and 1.0
	/// at 0.0 there is no attenuation, at 1.0 there is complete attenuation</param>
	/// <param name="reverberation">must be a value between 0.0 and 1.0
	/// at 0.0 there is no reverberation, at 1.0 there is complete reverberation</param>
	void setStreamOcclusion(std::string filepath, float attenuation, float reverberation = 0.0f);

	/// <summary>
	/// Load all sounds the Engine will have to know about for
	/// your game.
	/// </summary>
	/// <param name="soundList">This must be a vector of filePaths in string form
	/// these filepaths will be used to store the sounds in channels
	/// where they will then be arranged into a channelgroup.</param>
	/// <returns>If the sound was loaded.</returns>
	bool loadSounds(std::vector<std::string> soundList);

	/// <summary>
	/// Load all streams the Engine will have to know about for
	/// your game.
	/// </summary>
	/// <param name="streamList">This must be a vector of filePaths in string form
	/// these filepaths will be used to store the streams in channels
	/// where they will then be arranged into a channelgroup.< / param>
	/// <returns>If the stream was loaded.</returns>
	bool loadStreams(std::vector<std::string> streamList);

	/// <summary>
	/// Disposes the specified sound list.
	/// </summary>
	/// <param name="soundList">The sound list.</param>
	/// <param name="streamList">The stream list.</param>
	void dispose(const std::vector<std::string> & soundList, const std::vector<std::string> & streamList);

	/// <summary>
	/// Updates the system object
	/// (should be called every frame)
	/// </summary>
	void update();

private:
	
	/// <summary>
	/// Initializes FMOD
	/// called automatically when the
	/// AudioEngine instance is created.
	/// </summary>
	void init();

	/// <summary>
	/// Verifies that each step of the initialization 
	/// was properly initalized.
	/// </summary>
	/// <param name="result">The result.</param>
	void FMODVerifyResult(FMOD_RESULT result)
	{
		if (result != FMOD_OK)
		{
			std::cout << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
		}
	}

	/// <summary>
	/// Converts glm::vec3's to FMOD_VECTOR *'s
	/// for use in FMOD's positioning of the listener
	/// and sound / stream positioning
	/// </summary>
	/// <param name="vector">The glm vector to convert.</param>
	/// <returns>The resulting FMOD vector conversion.</returns>
	FMOD_VECTOR glmToFMOD(glm::vec3 vector);

	// Volume Controls
	/// <summary>
	/// The sound's volume.
	/// </summary>
	float m_soundVolume;
	/// <summary>
	/// The stream's volume.
	/// </summary>
	float m_streamVolume;

	// FMOD requirements
	/// <summary>
	/// The FMOD system.
	/// </summary>
	FMOD::System * m_system;
	/// <summary>
	/// The FMOD result.
	/// </summary>
	FMOD_RESULT m_result;

	// Sound Effects
	/// <summary>
	/// The sound effects list.
	/// </summary>
	FMOD::Sound * m_soundEffects[NUM_SOUND_CHANNELS];
	/// <summary>
	/// The sound channels.
	/// </summary>
	FMOD::Channel * m_soundChannels[NUM_SOUND_CHANNELS];
	/// <summary>
	/// The sound effect channels.
	/// </summary>
	FMOD::ChannelGroup * m_soundEffectChannels;
	/// <summary>
	/// The sound list.
	/// </summary>
	const std::vector<std::string> * m_soundList = new std::vector<std::string>();

	// Stream Effects (Music)
	/// <summary>
	/// The streams.
	/// </summary>
	FMOD::Sound * m_streams[NUM_STREAM_CHANNELS];
	/// <summary>
	/// The stream channels.
	/// </summary>
	FMOD::Channel * m_streamChannels[NUM_STREAM_CHANNELS];
	/// <summary>
	/// The stream effect channels.
	/// </summary>
	FMOD::ChannelGroup * m_streamEffectChannels;
	/// <summary>
	/// The stream list.
	/// </summary>
	const std::vector<std::string> * m_streamList = new std::vector<std::string>();
	
	/// <summary>
	/// The audio sources.
	/// </summary>
	std::vector<AudioSource*> m_audioSources; //<-- Do we really need this, I can't see why

	/// <summary>
	/// The m_sound map
	/// </summary>
	std::unordered_map<std::string, std::pair<FMOD::Sound*, int>> m_soundMap;

	/// <summary>
	/// The m_stream map
	/// </summary>
	std::unordered_map<std::string, std::pair<FMOD::Sound*, int>> m_streamMap;
};

