#pragma once
#include "GameComponents.h"
#include "..\Audio\Audio.h"

enum class AudioType { SOUND, STREAM };

class AudioSource : public GameComponent
{
public:
	AudioSource(const std::string& fileName, AudioType audioType, bool playOnStart = true, AudioDimension audioDim = AudioDimension::TWOD) :
		m_fileName(fileName), m_type(audioType), m_playOnStart(playOnStart), m_dim(audioDim) { }
	~AudioSource() { delete m_audio; }

	virtual void onStart() override
	{
		if (m_type == AudioType::SOUND)
		{
			m_audio = new Sound(getCoreEngine()->getAudioEngine(), m_fileName, m_dim);
		}
		else if (m_type == AudioType::STREAM)
		{
			m_audio = new Stream(getCoreEngine()->getAudioEngine(), m_fileName, m_dim);
		}

		if (m_playOnStart)
		{
			m_audio->play();
		}
	}

	virtual void update(float delta) override
	{
		if (m_dim == AudioDimension::THREED)
		{
			m_audio->setPosition(*getTransform()->getPosition(), PxVec3(0.0f));
		}
	}

	void play() const { m_audio->play(); }
	void stop() const { m_audio->stop(); }

	void set3DDistance(float min, float max) { m_audio->set3DDistance(min, max); }
	void setPaused(bool paused) { m_audio->setPaused(paused); }
	//void setPosition(const PxVec3& pos, const PxVec3& vel) { m_audio->setPosition(pos, vel); }
	void setVolume(float volume) { m_audio->setVolume(volume); }
	void setLooping(bool looping, int amount = 0) { m_audio->setLooping(looping, amount); }

	AudioType getType() const { return m_type; }
	AudioDimension getDimension() const { return m_dim; }
	bool isPaused() const { return m_audio->isPaused(); }
	bool isPlaying() const { return m_audio->isPlaying(); }
	float getVolume() const { return m_audio->getVolume(); }
	bool getLooping() const { return m_audio->getLooping(); }

private:
	Audio* m_audio;

	std::string m_fileName;

	AudioType m_type;

	AudioDimension m_dim;

	bool m_playOnStart;

};
