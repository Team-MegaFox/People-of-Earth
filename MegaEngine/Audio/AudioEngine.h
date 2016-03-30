#pragma once
#include <unordered_map>
#include <string>
#include <FMOD\fmod.hpp>

void ERRCHECK_fn(FMOD_RESULT result, const char *file, int line);
#define ERRCHECK(_result) ERRCHECK_fn(_result, __FILE__, __LINE__)

class AudioEngine
{
public:
	AudioEngine();
	~AudioEngine();

	void update();

	float getSoundVolume() const;
	float getStreamVolume() const;
	FMOD::ChannelGroup* getSoundGroup() const { return m_sounds; }
	FMOD::ChannelGroup* getStreamGroup() const { return m_streams; }
	FMOD::System* getSystem() const { return m_system; }

	void setSoundVolume(float volume);
	void setStreamVolume(float volume);

private:
	FMOD::System* m_system;

	FMOD::ChannelGroup* m_sounds;

	FMOD::ChannelGroup* m_streams;

	FMOD::ChannelGroup* m_masterGroup;

};

