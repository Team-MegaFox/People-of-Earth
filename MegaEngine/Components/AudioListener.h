#pragma once
#include "GameComponents.h"
#include "..\Audio\AudioEngine.h"

class AudioListener : public GameComponent
{
public:
	AudioListener() { }
	~AudioListener() { }

	virtual void onStart() override
	{
		m_audioEngine = getCoreEngine()->getAudioEngine();
	}

	virtual void update(float delta) override
	{
		m_audioEngine->setListenerPosition(
			getTransform()->getTransformedPos(), 
			Utility::getForward(getTransform()->getTransformedRot()), 
			Utility::getUp(getTransform()->getTransformedRot()));
	}

private:
	AudioEngine* m_audioEngine;

};
