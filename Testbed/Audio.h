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
	}

	/*
	
	Set defaults and give access to/for all methods in stream and sound
	once done AudioEngine is completed!

	*/

	~Audio() 
	{
		delete m_source;
	}

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

private:
	AudioSource * m_source;
	AudioType m_type;
};