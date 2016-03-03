// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 02-01-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 03-01-2016
// ***********************************************************************
// <copyright file="Audio.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************

#pragma once
#include "GameComponents.h"
#include "AudioSource.h"

enum AudioType
{
	STREAM,
	SOUND
};

class Audio : public GameComponent
{
public:

	/// <summary>
	/// Initializes a new instance of the <see cref="Audio"/> class.
	/// </summary>
	/// <param name="fileName">The name of the music file including the extension, put music into Assets/Music directly</param>
	/// <param name="type">The type of audio component either Stream or Sound</param>
	/// <param name="TwoD">If set to true, this sound uses 2D sound (default = false).</param>
	Audio(const std::string & fileName, AudioType type, bool TwoD = false) :
		m_type(type)
	{
		if (m_type == STREAM)
		{
			m_source = new AudioSource(new Stream(fileName, TwoD));
		}
		else if (m_type == SOUND)
		{
			m_source = new AudioSource(new Sound(fileName, TwoD));
		}

	}

	/// <summary>
	/// Finalizes an instance of the <see cref="Audio"/> class.
	/// </summary>
	~Audio()
	{
		//getCoreEngine()->getAudioEngine()->removeAudioComp(this);
		delete m_source;
	}

	/// <summary>
	/// An initialization method for game components that is called
	/// when game components are added to the scene
	/// </summary>
	virtual void onStart() override
	{
		if (m_type == STREAM)
		{
			setVolume(getCoreEngine()->getAudioEngine()->getStreamVolume());
		}
		else if (m_type == SOUND)
		{
			setVolume(getCoreEngine()->getAudioEngine()->getSoundVolume());
		}
		getCoreEngine()->getAudioEngine()->addAudioComp(this);
	}

	/// <summary>
	/// Plays the specified looping.
	/// </summary>
	/// <param name="looping">if set to <c>true</c> [looping]. defaulted to false</param>
	void play(bool looping = false)
	{
		if (m_type == STREAM)
		{
			m_source->playStream(looping);
		}
		else if (m_type == SOUND)
		{
			m_source->playSound();
		}
	}

	/// <summary>
	/// Pauses the specified pause.
	/// </summary>
	/// <param name="pause">if set to <c>true</c> [pause].</param>
	void pause(bool pause = true)
	{
		if (m_type == STREAM)
		{
			m_source->pauseStream(pause);
		}
		else if (m_type == SOUND)
		{
			m_source->pauseSound(pause);
		}
	}

	/// <summary>
	/// Stops all sound channels or stream channels from playing.
	/// </summary>
	void stop()
	{
		if (m_type == STREAM)
		{
			m_source->stopStream();
		}
		else if (m_type == SOUND)
		{
			m_source->stopSound();
		}
	}

	/// <summary>
	/// Determines whether this instance is playing.
	/// </summary>
	/// <returns> returnValue returns [true] if this is playing</returns>
	bool isPlaying()
	{
		bool returnValue;
		if (m_type == STREAM)
		{
			returnValue = m_source->isStreamPlaying();
		}
		else if (m_type == SOUND)
		{
			returnValue = m_source->isSoundPlaying();
		}
		return returnValue;
	}

	/// <summary>
	/// Sets the volume.
	/// </summary>
	/// <param name="value">The volume level for this audio source.</param>
	void setVolume(float value)
	{
		m_volumeRatioValue = value;
		if (m_type == STREAM)
		{
			m_source->setStreamVolume(
				m_volumeRatioValue * getCoreEngine()->getAudioEngine()->getStreamVolume());
		}
		else if (m_type == SOUND)
		{
			m_source->setSoundVolume(
				m_volumeRatioValue * getCoreEngine()->getAudioEngine()->getSoundVolume());
		}
	}

	/// <summary>
	/// Sets the new volume.
	/// </summary>
	void setNewVolume()
	{
		if (m_type == STREAM)
		{
			m_source->setStreamVolume(
				m_volumeRatioValue * getCoreEngine()->getAudioEngine()->getStreamVolume());
		}
		else if (m_type == SOUND)
		{
			m_source->setSoundVolume(
				m_volumeRatioValue * getCoreEngine()->getAudioEngine()->getSoundVolume());
		}
	}

	/// <summary>
	/// Sets the position.
	/// </summary>
	/// <param name="position">The position of this audio source.</param>
	void setPosition(PxVec3 position)
	{
		if (m_type == STREAM)
		{
			m_source->setStreamPosition(position);
		}
		else if (m_type == SOUND)
		{
			m_source->setSoundPosition(position);
		}
	}

	/// <summary>
	/// Pan level, from -1.0 (left) to 1.0 (right), default = 0 (center).
	/// </summary>
	/// <param name="value">The pan value to use for this audio source.</param>
	void setPan(float value)
	{
		if (m_type == STREAM)
		{
			m_source->setStreamPan(value);
		}
		else if (m_type == SOUND)
		{
			m_source->setSoundPan(value);
		}
	}

	/// <summary>
	/// Sets the doppler.
	/// Use with (but before) setDistanceFilter for proper effect
	/// </summary>
	/// <param name="value">The doppler value to use for this audio source.</param>
	void setDoppler(float value)
	{
		if (m_type == STREAM)
		{
			m_source->setStreamDoppler(value);
		}
		else if (m_type == SOUND)
		{
			m_source->setSoundDoppler(value);
		}
	}

	/// <summary>
	/// Sets the sound cone orientation.
	/// </summary>
	/// <param name="orientation">The orientation of the cone.</param>
	/// <param name="insideConeAngle">The inside cone angle.</param>
	/// <param name="outsideConeAngle">The outside cone angle.</param>
	/// <param name="outsideVolume">The outside volume level.</param>
	void setSoundConeOrientation(
		PxVec3 orientation,
		float insideConeAngle, 
		float outsideConeAngle, 
		float outsideVolume)
	{
		m_source->setupSoundCone(orientation, insideConeAngle, outsideConeAngle, outsideVolume);
	}

	/// <summary>
	/// Sets the distance filter.
	/// Use with (but after) setDoppler for proper effect
	/// </summary>
	/// <param name="custom">if set to <c>true</c> [custom].</param>
	/// <param name="customLevel">if set to <c>true</c> [custom level].</param>
	/// <param name="centerFreq">The center freq.</param>
	void setDistanceFilter(bool custom, bool customLevel, float centerFreq)
	{
		if (m_type == STREAM)
		{
			m_source->setStreamDistanceFilter(custom, customLevel, centerFreq);
		}
		else if (m_type == SOUND)
		{
			m_source->setSoundDistanceFilter(custom, customLevel, centerFreq);
		}

	}

	/// <summary>
	/// In summary, increase the mindistance of a sound to make it 'louder' in a 3D world, 
	/// and decrease it to make it 'quieter' in a 3D world.
	/// Maxdistance is effectively obsolete unless you need the sound to stop fading out at 
	/// a certain point.Do not adjust this from the default if you dont need to.
	///	Some people have the confusion that maxdistance is the point the sound will fade out to, 
	/// this is not the case.
	/// </summary>
	/// <param name="min">The minimum.</param>
	/// <param name="max">The maximum defaulted to NULL.</param>
	void set3DMinMaxDistance(float min, float max = NULL)
	{
		if (m_type == STREAM)
		{
			m_source->setStream3DMinDist(min, max);
		}
		else if (m_type == SOUND)
		{
			m_source->setSound3DMinDist(min, max);
		}
	}

	/// <summary>
	/// Gets the type.
	/// </summary>
	AudioType getType() { return m_type; }


private:
	/// <summary>
	/// The  audio source
	/// </summary>
	AudioSource * m_source;
	/// <summary>
	/// The audio type
	/// </summary>
	AudioType m_type;
	/// <summary>
	/// The volume ratio value
	/// </summary>
	float m_volumeRatioValue;
};