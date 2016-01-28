#pragma once
#include "GameComponents.h"
#include <string>
#include "../Core/CoreEngine.h"
#include "../Core/GameObject.h"
#include "..\Audio\AudioEngine.h"
#include "../Core/Utility.h"

class AudioSource : public GameComponent
{
public:
	AudioSource(const std::string& fileName) : 
		m_parent(nullptr), 
		m_fileName(fileName) { }
	~AudioSource() { }

	/// <summary>
	/// Sets the parent GameObject..
	/// </summary>
	/// <param name="parent">The GameObject to be attached to.</param>
	virtual void setParent(GameObject* parent) { m_parent = parent; }

	void playSound() 
	{
		a->playSound(m_fileName);
	}

	void playStream()
	{
		a->playStream(m_fileName);
	}

	void stopAllSounds()
	{
		a->stopAllSoundEffects();
	}

	void stopAllStreams()
	{
		a->stopAllStreams();
	}

	void pauseSound(bool paused)
	{
		a->pauseSound(paused, m_fileName);
	}

	void pauseStream(bool paused)
	{
		a->pauseStream(paused, m_fileName);
	}

	bool isSoundPlaying()
	{
		if (a->isSoundPlaying(m_fileName))
			return true;
		else
			return false;
	}

	bool isStreamPlaying()
	{
		if (a->isStreamPlaying(m_fileName))
			return true;
		else
			return false;
	}

	void resetSound()
	{
		a->setSound(m_fileName);
	}

	void resetStream()
	{
		a->setStream(m_fileName);
	}

	void setAsListener()
	{
		glm::vec3 forward = Utility::getForward(*m_parent->getTransform()->getRotation());
		glm::vec3 up = Utility::getUp(*m_parent->getTransform()->getRotation());

		a->setListener(
			*m_parent->getTransform()->getPosition(), 
			glm::vec3(0.0f), 
			forward, 
			up);
	}


protected:

	AudioEngine * a = m_parent->getCoreEngine()->getAudioEngine();
	CoreEngine* getCoreEngine() { return m_parent->getCoreEngine(); }
	 

private:
	std::string m_fileName;
	GameObject * m_parent;

};
