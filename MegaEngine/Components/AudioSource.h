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
#include "GameComponents.h"
#include "..\Audio\Audio.h"
#include <iostream>

/// <summary>
/// Whether the type of audio is a sound or stream.
/// Can add to this later.
/// </summary>
enum class AudioType { SOUND, STREAM };

/// <summary>
/// The source of audio to play. It can be a sound or stream (long/big files).
/// </summary>
/// <seealso cref="GameComponent" />
class AudioSource : public GameComponent
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="AudioSource"/> class.
	/// </summary>
	/// <param name="fileName">Name of the file.</param>
	/// <param name="audioType">Type of the audio.</param>
	/// <param name="playOnStart">Whether the audio should play on start.</param>
	/// <param name="audioDim">The audio dimension  (2D or 3D).</param>
	AudioSource(const std::string& fileName, AudioType audioType, bool playOnStart = true, float volume = 1.0f, bool destroyAtEnd = false, bool looping = false, AudioDimension audioDim = AudioDimension::TWOD) :
		m_fileName(fileName), m_type(audioType), m_playOnStart(playOnStart), m_volume(volume), m_destroyAtEnd(destroyAtEnd), m_loopOnStart(looping), m_dim(audioDim), m_played(false) { }
	/// <summary>
	/// Finalizes an instance of the <see cref="AudioSource"/> class.
	/// </summary>
	~AudioSource() { delete m_audio; }

	// The reason for doing this onStart is because we do not have access to
	// the Audio Engine when contructing this object to load audio.
	/// <summary>
	/// An initialization method for game components that is called
	/// when game components are added to the scene.
	/// Creates the sound based on what type of audio is and plays it
	/// if play on start is enabled.
	/// </summary>
	virtual void onStart() override
	{
		if (m_type == AudioType::SOUND)
		{
			m_audio = new Sound(getCoreEngine()->getAudioEngine(), m_fileName, m_dim);
		}
		else if (m_type == AudioType::STREAM)
		{
			m_audio = new Stream(getCoreEngine()->getAudioEngine(), m_fileName, m_dim);
		}

		if (m_playOnStart)
		{
			m_audio->play();
		}
		else
		{
			setVolume(m_volume);
		}

		setLooping(m_loopOnStart, -1);
	}

	/// <summary>
	/// Virtual function for custom update functionality.
	/// Updates the position of the audio is the type is 3D.
	/// </summary>
	/// <param name="delta">The frame time delta.</param>
	virtual void update(float delta) override
	{
		if (m_dim == AudioDimension::THREED)
		{
			m_audio->setPosition(*getTransform()->getPosition(), PxVec3(0.0f));
		}

		if (m_destroyAtEnd && m_played && !isPlaying())
		{
			destroy(getParent());
		}
	}

	/// <summary>
	/// Plays the audio.
	/// </summary>
	void play() 
	{ 
		m_audio->play(); 
		setVolume(m_volume);
		m_played = true; 
	}
	/// <summary>
	/// Stops the audio.
	/// </summary>
	void stop() const { m_audio->stop(); }

	/// <summary>
	/// Sets the roll of distance from the listener.
	/// </summary>
	/// <param name="min">The minimum distance where how audible the music is one-to-one to the channel's volume.</param>
	/// <param name="max">The maximum distance where how audible the music is completely muted.</param>
	void set3DDistance(float min, float max) { m_audio->set3DDistance(min, max); }
	/// <summary>
	/// Sets whether the audio was playing when the scene was pushed onto the stack.
	/// </summary>
	/// <param name="paused">Whether the audio was playing.</param>
	void setWasPlaying(bool wasPlaying) { m_wasPlaying = wasPlaying; }
	/// <summary>
	/// Sets the audio to be paused.
	/// </summary>
	/// <param name="paused">Whether the audio is paused.</param>
	void setPaused(bool paused) { m_audio->setPaused(paused); }
	/// <summary>
	/// Sets the volume.
	/// </summary>
	/// <param name="volume">The volume.</param>
	void setVolume(float volume) { m_audio->setVolume(volume); }
	/// <summary>
	/// Sets if the audio is looping and how many times.
	/// </summary>
	/// <param name="looping">Whether the audio is looping.</param>
	/// <param name="amount">The amount of times to loop. 0 = oneshot, 1 = loop once then stop, -1 = loop forever and default = -1.</param>
	void setLooping(bool looping, int amount = 0) { m_audio->setLooping(looping, amount); }

	/// <summary>
	/// Gets the type of audio.
	/// </summary>
	/// <returns>The type of audio (sound or stream).</returns>
	AudioType getType() const { return m_type; }
	/// <summary>
	/// Gets the audio's dimension.
	/// </summary>
	/// <returns>The audio's demnsion (2D or 3D).</returns>
	AudioDimension getDimension() const { return m_dim; }
	/// <summary>
	/// Whether the audio was playing when a scene was pushed onto the stack.
	/// </summary>
	/// <returns>If the audio was playing.</returns>
	bool wasPlaying() const { return m_wasPlaying; }
	/// <summary>
	/// Determines whether this audio is paused.
	/// </summary>
	/// <returns>Whether the audio is paused.</returns>
	bool isPaused() const { return m_audio->isPaused(); }
	/// <summary>
	/// Determines whether this audio is playing.
	/// </summary>
	/// <returns>Whether the audio is playing.</returns>
	bool isPlaying() const { return m_audio->isPlaying(); }
	/// <summary>
	/// Gets the volume.
	/// </summary>
	/// <returns>The volume.</returns>
	float getVolume() const { return m_audio->getVolume(); }
	/// <summary>
	/// If the audio is looping.
	/// </summary>
	/// <returns>Whether the audio is looping.</returns>
	bool getLooping() const { return m_audio->getLooping(); }

private:
	/// <summary>
	/// The audio data.
	/// </summary>
	Audio* m_audio;

	/// <summary>
	/// The file name
	/// </summary>
	std::string m_fileName;

	/// <summary>
	/// The type of audio (sound or stream).
	/// </summary>
	AudioType m_type;

	/// <summary>
	/// The dimension (2D or 3D).
	/// </summary>
	AudioDimension m_dim;

	/// <summary>
	/// The starting volume of the audio.
	/// </summary>
	float m_volume;

	/// <summary>
	/// Whether the audio plays on start.
	/// </summary>
	bool m_playOnStart;

	/// <summary>
	/// Whether the audio loops on start.
	/// </summary>
	bool m_loopOnStart;

	/// <summary>
	/// Whether the audio was playing when a scene got pushed onto the stack.
	/// </summary>
	bool m_wasPlaying;

	/// <summary>
	/// Whether the audio should be destroyed once the audio has finished playing.
	/// </summary>
	bool m_destroyAtEnd;

	/// <summary>
	/// Whether the audio was played at least once.
	/// </summary>
	bool m_played;

};
