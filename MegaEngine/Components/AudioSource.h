#pragma once
#include "GameComponents.h"
#include <string>
#include "..\Audio\AudioEngine.h"
#include "..\Core\CoreEngine.h"

class AudioSource : public GameComponent
{
public:
	AudioSource(const std::string& musicFile) : m_fileName(musicFile) { }
	~AudioSource() { }

	virtual void addToEngine(CoreEngine* engine) const
	{
		engine->getAudioEngine()->addAudioSource(*this);
	}

	void play()
	{
		
	}

private:
	std::string m_fileName;

};
