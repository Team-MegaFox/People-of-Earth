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
#include <unordered_map>
#include <string>
#include <FMOD\fmod.hpp>

void ERRCHECK_ok(FMOD_RESULT result, const char *file, int line);
void ERRCHECK_invalid(FMOD_RESULT result, const char *file, int line);
#define ERRCHECK_OK(_result) ERRCHECK_ok(_result, __FILE__, __LINE__)
#define ERRCHECK_INVALID(_result) ERRCHECK_invalid(_result, __FILE__, __LINE__)

/// <summary>
/// The Audio Engine that holds audio settings such as the sound and stream
/// volume and the FMOD system.
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
	/// Updates the FMOD system. This is used for updating the 3D portions.
	/// </summary>
	void update();

	/// <summary>
	/// Gets the sound volume.
	/// </summary>
	/// <returns>The sound group volume.</returns>
	float getSoundVolume() const;
	/// <summary>
	/// Gets the stream volume.
	/// </summary>
	/// <returns>The sound group volume.</returns>
	float getStreamVolume() const;
	/// <summary>
	/// Gets the sound group.
	/// </summary>
	/// <returns>The sound group.</returns>
	FMOD::ChannelGroup* getSoundGroup() const { return m_sounds; }
	/// <summary>
	/// Gets the stream group.
	/// </summary>
	/// <returns>The stream group.</returns>
	FMOD::ChannelGroup* getStreamGroup() const { return m_streams; }
	/// <summary>
	/// Gets the FMOD system.
	/// </summary>
	/// <returns>The FMOD system</returns>
	FMOD::System* getSystem() const { return m_system; }

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

private:
	/// <summary>
	/// The FMOD system.
	/// </summary>
	FMOD::System* m_system;

	/// <summary>
	/// The sound channel group.
	/// </summary>
	FMOD::ChannelGroup* m_sounds;

	/// <summary>
	/// The stream channel group.
	/// </summary>
	FMOD::ChannelGroup* m_streams;

	/// <summary>
	/// The master channel group. Has all the other channels and sounds.
	/// </summary>
	FMOD::ChannelGroup* m_masterGroup;

};

