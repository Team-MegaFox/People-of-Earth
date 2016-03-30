#pragma once
#include <string>
#include <FMOD\fmod.hpp>
#include <PhysX\PxPhysicsAPI.h>
using namespace physx;

#include "AudioEngine.h"

enum class AudioDimension { TWOD, THREED };

class Audio
{
public:
	Audio(AudioEngine* audioEngine);
	~Audio();

	virtual void createAudio(const std::string& fileName, AudioDimension audioDim) = 0;

	virtual void play() = 0;
	void stop() const;

	void set3DDistance(float min, float max);
	void setPaused(bool paused);
	void setPosition(const PxVec3& pos, const PxVec3& vel);
	void setVolume(float volume);
	void setLooping(bool looping, int amount = 0);

	bool isPaused() const;
	bool isPlaying() const;
	float getVolume() const;
	bool getLooping() const;

protected:
	AudioEngine* m_audioEngine;

	FMOD::Sound* m_sound;

	FMOD::Channel* m_channel;

};

class Sound : public Audio
{
public:
	Sound(AudioEngine* audioEngine, const std::string& fileName, AudioDimension audioDim) : Audio(audioEngine) 
	{
		std::string filePath = "Assets/" + fileName;
		createAudio(filePath, audioDim);
	}
	~Sound() { }

	virtual void createAudio(const std::string& fileName, AudioDimension audioDim) override;

	virtual void play() override;
};

class Stream : public Audio
{
public:
	Stream(AudioEngine* audioEngine, const std::string& fileName, AudioDimension audioDim) : Audio(audioEngine) 
	{
		std::string filePath = "Assets/" + fileName;
		createAudio(filePath, audioDim);
	}
	~Stream() { }

	virtual void createAudio(const std::string& fileName, AudioDimension audioDim) override;

	virtual void play() override;

};
