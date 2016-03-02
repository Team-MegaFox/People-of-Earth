// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 02-01-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 03-01-2016
// ***********************************************************************
// <copyright file="StreamSource.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
// </summary>
// ***********************************************************************

#pragma once
#include "..\Audio\AudioEngine.h"
#include <cstdint>

class Stream
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="StreamSource"/> class.
	/// </summary>
	Stream() {}
	/// <summary>
	/// Initializes a new instance of the <see cref="StreamSource"/> class.
	/// </summary>
	/// <param name="fileName">Name of the file.</param>
	/// <param name="TwoD">if true this sound is 2D (default is false)</param>
	Stream(const std::string& fileName, bool TwoD = false);
	/// <summary>
	/// Finalizes an instance of the <see cref="StreamSource"/> class.
	/// </summary>
	~Stream() { }

	/// <summary>
	/// Sets the stream.
	/// </summary>
	void setStream();

	/// <summary>
	/// Plays the stream.
	/// </summary>
	/// <param name="looping">if set to <c>true</c> [looping].</param>
	void playStream(bool looping);

	/// <summary>
	/// Pauses the stream.
	/// </summary>
	/// <param name="pause">if set to <c>true</c> [pause].</param>
	void pauseStream(bool pause);

	/// <summary>
	/// Stops all streams.
	/// </summary>
	void stop();

	/// <summary>
	/// Determines whether this stream is playing.
	/// </summary>
	/// <returns></returns>
	bool isStreamPlaying();

	/// <summary>
	/// Sets the stream effect volume.
	/// </summary>
	/// <param name="volumeLevel">The volume level.</param>
	void setStreamEffectVolume(float volumeLevel);

	/// <summary>
	/// Gets the stream volume.
	/// </summary>
	/// <returns></returns>
	float & getStreamVolume();

	/// <summary>
	/// Sets the stream position vel.
	/// </summary>
	/// <param name="pos">The position.</param>
	/// <param name="vel">The vel.</param>
	void setStreamPosVel(PxVec3 pos, PxVec3 vel = PxVec3(0.0f, 0.0f, 0.0f));

	/// <summary>
	/// Pan level, from -1.0 (left) to 1.0 (right), default = 0 (center).
	/// </summary>
	/// <param name="pan">The pan.</param>
	void setStreamPan(float pan);

	/// <summary>
	/// Sets the stream doppler level.
	/// Use with (but before) setStreamDistanceFilter for proper effect
	/// </summary>
	/// <param name="dopplerLevel">The doppler level.</param>
	void setStreamDopplerLevel(float dopplerLevel);

	/// <summary>
	/// Sets the sound distance filter.
	/// use with (but after) setStreamDopplerLevel for proper effect
	/// </summary>
	/// <param name="custom">if set to <c>true</c> [custom].</param>
	/// <param name="customLevel">if set to <c>true</c> [custom level].</param>
	/// <param name="centerFreq">The center freq.</param>
	void setStreamDistanceFilter(bool custom, bool customLevel, float centerFreq);

	/// <summary>
	/// In summary, increase the mindistance of a stream to make it 'louder' in a 3D world, 
	/// and decrease it to make it 'quieter' in a 3D world.
	/// Maxdistance is effectively obsolete unless you need the stream to stop fading out at 
	/// a certain point.Do not adjust this from the default if you dont need to.
	///	Some people have the confusion that maxdistance is the point the stream will fade out to, 
	/// this is not the case.
	/// </summary>
	/// <param name="min">The minimum.</param>
	/// <param name="max">The maximum.</param>
	void setStream3DMinMaxDistance(float min, float max = NULL);

private:

	/// <summary>
	/// The file name of this audiosource file
	/// </summary>
	std::string m_fileName;

	/// <summary>
	/// The stream's volume.
	/// </summary>
	float m_streamVolume;

	/// <summary>
	/// The stream pair
	/// Pair is made up of the FMOD:Sound * and the FMOD::Channel* that stream needs to be playable
	/// </summary>
	std::pair<FMOD::Sound*, FMOD::Channel*> m_streamPair;

	/// <summary>
	/// This boolean determines whether or not to use 3D streaming
	/// </summary>
	bool m_twoDimensionalSound;
	/// <summary>
	/// For making this sound a 2D stream
	/// </summary>
	uint16_t m_twoDimensional	= FMOD_2D | FMOD_DEFAULT;
	/// <summary>
	/// For making this sound a 3D stream
	/// </summary>
	uint16_t m_threeDimensional = FMOD_3D | FMOD_DEFAULT;
};
