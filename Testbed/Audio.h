#pragma once
#include <Components/GameComponents.h>
#include <Components/AudioSource.h>

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
	/// <param name="fileName">Name of the file to play.</param>
	/// <param name="type">The audio type.</param>
	Audio(const std::string & fileName, AudioType type) :
		m_type(type)
	{
		if (m_type == STREAM)
		{
			m_source = new AudioSource(Stream(fileName));
		}
		else if (m_type == SOUND)
		{
			m_source = new AudioSource(Sound(fileName));
		}

		set3DMinMaxDistance(0.1f);
		setDoppler(0.5f);
		setVolume(100.0f);
		
	}

	/// <summary>
	/// Finalizes an instance of the <see cref="Audio"/> class.
	/// </summary>
	~Audio()
	{
		delete m_source;
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
		if (m_type == STREAM)
		{
			m_source->setStreamVolume(value);
		}
		else if (m_type == SOUND)
		{
			m_source->setSoundVolume(value);
		}
	}

	/// <summary>
	/// Sets the position.
	/// </summary>
	/// <param name="position">The position of this audio source.</param>
	void setPosition(glm::vec3 position)
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
		glm::vec3 orientation, 
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
	/// Sets the occlusion.
	/// </summary>
	/// <param name="attenuation">The attenuation.</param>
	/// <param name="reverberation">The reverberation. defaulted to NULL</param>
	void setOcclusion(float attenuation, float reverberation = NULL)
	{
		if (m_type == STREAM)
		{
			m_source->setStreamOcclusion(attenuation, reverberation);
		}
		else if (m_type == SOUND)
		{
			m_source->setSoundOcclusion(attenuation, reverberation);
		}
	}

private:
	/// <summary>
	/// The  audio source
	/// </summary>
	AudioSource * m_source;
	/// <summary>
	/// The audio type
	/// </summary>
	AudioType m_type;
};