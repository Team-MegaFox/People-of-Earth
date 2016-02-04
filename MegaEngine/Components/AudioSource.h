#pragma once
#include "GameComponents.h"
#include <string>
#include "..\Core\CoreEngine.h"
#include "..\Audio\AudioEngine.h"

class AudioSource : public GameComponent
{
public:
	AudioSource(const std::string& musicFile) : m_fileName(musicFile) 
	{ 
		getCoreEngine()->getAudioEngine()->addAudioSource(this);
	}
	~AudioSource() { }
	void play()
	{
		
	}
private:
	/// <summary>
	/// The m_file name of this audiosource file
	/// </summary>
	std::string m_fileName;

};
