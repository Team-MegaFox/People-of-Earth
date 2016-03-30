// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 03-30-2016
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 03-30-2016
// ***********************************************************************
// <copyright file="MegaEngine.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once
#include <string>
#include <FMOD\fmod.hpp>
#include <PhysX\PxPhysicsAPI.h>
using namespace physx;

#include "AudioEngine.h"

/// <summary>
/// Wheather the audio is 2D or 3D.
/// </summary>
enum class AudioDimension { TWOD, THREED };

/// <summary>
/// The audio class that holds the data for the audio such as the sound data itself
/// and the channel it is playing in. It has a virtual function that is dependent on what
/// kind of audio it creates, i.e. sound or stream.
/// </summary>
class Audio
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Audio"/> class.
	/// </summary>
	/// <param name="audioEngine">The audio engine.</param>
	Audio(AudioEngine* audioEngine);
	/// <summary>
	/// Finalizes an instance of the <see cref="Audio"/> class.
	/// </summary>
	~Audio();

	/// <summary>
	/// A pure virtual function that creates the audio data based on the file path.
	/// </summary>
	/// <param name="fileName">Name of the file.</param>
	/// <param name="audioDim">The audio dimension (2D or 3D).</param>
	virtual void createAudio(const std::string& fileName, AudioDimension audioDim) = 0;

	/// <summary>
	/// A virtual function that plays the audio based on what type of audio it is.
	/// </summary>
	virtual void play() = 0;
	/// <summary>
	/// Stops playing the audio. It goes back to the beginning of the audio stored.
	/// </summary>
	void stop() const;

	/// <summary>
	/// Sets the roll of distance from the listener.
	/// </summary>
	/// <param name="min">The minimum distance where how audible the music is one-to-one to the channel's volume.</param>
	/// <param name="max">The maximum distance where how audible the music is completely muted.</param>
	void set3DDistance(float min, float max);
	/// <summary>
	/// Sets the audio to be paused.
	/// </summary>
	/// <param name="paused">Whether the audio is paused.</param>
	void setPaused(bool paused);
	/// <summary>
	/// Sets the position of the audio if the audio is 3D.
	/// </summary>
	/// <param name="pos">The position of the audio.</param>
	/// <param name="vel">The velocity of the audio.</param>
	void setPosition(const PxVec3& pos, const PxVec3& vel);
	/// <summary>
	/// Sets the volume.
	/// </summary>
	/// <param name="volume">The volume.</param>
	void setVolume(float volume);
	/// <summary>
	/// Sets if the audio is looping and how many times.
	/// </summary>
	/// <param name="looping">Whether the audio is looping.</param>
	/// <param name="amount">The amount of times to loop. 0 = oneshot, 1 = loop once then stop, -1 = loop forever and default = -1.</param>
	void setLooping(bool looping, int amount = 0);

	/// <summary>
	/// Determines whether this audio is paused.
	/// </summary>
	/// <returns>Whether the audio is paused.</returns>
	bool isPaused() const;
	/// <summary>
	/// Determines whether this audio is playing.
	/// </summary>
	/// <returns>Whether the audio is playing.</returns>
	bool isPlaying() const;
	/// <summary>
	/// Gets the volume.
	/// </summary>
	/// <returns>The volume.</returns>
	float getVolume() const;
	/// <summary>
	/// If the audio is looping.
	/// </summary>
	/// <returns>Whether the audio is looping.</returns>
	bool getLooping() const;

protected:
	/// <summary>
	/// The Audio Engine.
	/// </summary>
	AudioEngine* m_audioEngine;

	/// <summary>
	/// The sound data structure. This is where the audio data is stored.
	/// </summary>
	FMOD::Sound* m_sound;

	/// <summary>
	/// The channel the audio is playing in. Only filled if it is currently playing.
	/// </summary>
	FMOD::Channel* m_channel;

};

/// <summary>
/// Creates data used for sound. It loads the entire sound file into memory.
/// Do not use this for long and big sound files.
/// </summary>
/// <seealso cref="Audio" />
class Sound : public Audio
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Sound"/> class.
	/// </summary>
	/// <param name="audioEngine">The audio engine.</param>
	/// <param name="fileName">Name of the file.</param>
	/// <param name="audioDim">The audio dimemsion (2D or 3D).</param>
	Sound(AudioEngine* audioEngine, const std::string& fileName, AudioDimension audioDim) : Audio(audioEngine)
	{
		std::string filePath = "Assets/" + fileName;
		createAudio(filePath, audioDim);
	}
	/// <summary>
	/// Finalizes an instance of the <see cref="Sound"/> class.
	/// </summary>
	~Sound() { }

	/// <summary>
	/// Creates the audio based on sound.
	/// </summary>
	/// <param name="fileName">Name of the file.</param>
	/// <param name="audioDim">The audio dimension (2D or 3D).</param>
	virtual void createAudio(const std::string& fileName, AudioDimension audioDim) override;

	/// <summary>
	/// Plays the sound and stores it into the Audio Engine's sound group.
	/// </summary>
	virtual void play() override;
};

/// <summary>
/// Creates data based on streams. It loads some of the audio data into memory
/// and streams the rest of the data while it is playing. This is used for large
/// audio files.
/// </summary>
/// <seealso cref="Audio" />
class Stream : public Audio
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Stream"/> class.
	/// </summary>
	/// <param name="audioEngine">The audio engine.</param>
	/// <param name="fileName">Name of the file.</param>
	/// <param name="audioDim">The audio dimension (2D or 3D).</param>
	Stream(AudioEngine* audioEngine, const std::string& fileName, AudioDimension audioDim) : Audio(audioEngine)
	{
		std::string filePath = "Assets/" + fileName;
		createAudio(filePath, audioDim);
	}
	/// <summary>
	/// Finalizes an instance of the <see cref="Stream"/> class.
	/// </summary>
	~Stream() { }

	/// <summary>
	/// Creates the based on streams.
	/// </summary>
	/// <param name="fileName">Name of the file.</param>
	/// <param name="audioDim">The audio dimension (2D or 3D).</param>
	virtual void createAudio(const std::string& fileName, AudioDimension audioDim) override;

	/// <summary>
	/// Plays the stream and stores the stream in Audio Engine's stream group.
	/// </summary>
	virtual void play() override;

};
