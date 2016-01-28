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


	/// <summary>
	/// Plays the sound.
	/// </summary>
	void playSound()
	{
		a->playSound(m_fileName);
	}

	/// <summary>
	/// Plays the stream.
	/// </summary>
	void playStream()
	{
		a->playStream(m_fileName);
	}

	/// <summary>
	/// Stops all sounds.
	/// </summary>
	void stopAllSounds()
	{
		a->stopAllSoundEffects();
	}

	/// <summary>
	/// Stops all streams.
	/// </summary>
	void stopAllStreams()
	{
		a->stopAllStreams();
	}

	/// <summary>
	/// Pauses the sound.
	/// </summary>
	/// <param name="paused">if set to <c>true</c> [paused].</param>
	void pauseSound(bool paused)
	{
		a->pauseSound(paused, m_fileName);
	}

	/// <summary>
	/// Pauses the stream.
	/// </summary>
	/// <param name="paused">if set to <c>true</c> [paused].</param>
	void pauseStream(bool paused)
	{
		a->pauseStream(paused, m_fileName);
	}

	/// <summary>
	/// Determines whether [is sound playing].
	/// </summary>
	/// <returns></returns>
	bool isSoundPlaying()
	{
		if (a->isSoundPlaying(m_fileName))
			return true;
		else
			return false;
	}

	/// <summary>
	/// Determines whether [is stream playing].
	/// </summary>
	/// <returns></returns>
	bool isStreamPlaying()
	{
		if (a->isStreamPlaying(m_fileName))
			return true;
		else
			return false;
	}

	/// <summary>
	/// Resets the sound.
	/// </summary>
	void resetSound()
	{
		a->setSound(m_fileName);
	}

	/// <summary>
	/// Resets the stream.
	/// </summary>
	void resetStream()
	{
		a->setStream(m_fileName);
	}

	/// <summary>
	/// Sets as listener.
	/// </summary>
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
	/// <summary>
	/// Gets the core engine.
	/// </summary>
	/// <returns></returns>
	CoreEngine* getCoreEngine() { return m_parent->getCoreEngine(); }
	 

private:
	/// <summary>
	/// The m_file name of this audiosource file
	/// </summary>
	std::string m_fileName;

	/// <summary>
	/// The m_parent Game Object
	/// </summary>
	GameObject * m_parent;

};
