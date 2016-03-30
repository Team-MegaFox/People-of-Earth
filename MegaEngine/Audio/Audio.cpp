#include "Audio.h"


Audio::Audio(AudioEngine* audioEngine) :
m_audioEngine(audioEngine)
{
}

Audio::~Audio()
{
	ERRCHECK(m_sound->release());
}

void Audio::stop() const
{
	ERRCHECK(m_channel->stop());
}

void Audio::set3DDistance(float min, float max)
{
	ERRCHECK(m_sound->set3DMinMaxDistance(min, max));
}

void Audio::setPaused(bool paused)
{
	ERRCHECK(m_channel->setPaused(paused));
}

void Audio::setPosition(const PxVec3& pos, const PxVec3& vel)
{
	FMOD_VECTOR posF = { pos.x, pos.y, pos.z };
	FMOD_VECTOR velF = { vel.x, vel.y, vel.z };

	ERRCHECK(m_channel->set3DAttributes(&posF, &velF));
}

void Audio::setVolume(float volume)
{
	ERRCHECK(m_channel->setVolume(volume));
}

void Audio::setLooping(bool looping, int amount)
{
	if (looping)
	{
		ERRCHECK(m_channel->setMode(FMOD_LOOP_NORMAL));
		ERRCHECK(m_channel->setLoopCount(amount));
	}
	else
	{
		ERRCHECK(m_channel->setMode(FMOD_LOOP_OFF));
	}
}

bool Audio::isPaused() const
{
	bool paused;
	ERRCHECK(m_channel->getPaused(&paused));
	return paused;
}

bool Audio::isPlaying() const
{
	bool playing;
	ERRCHECK(m_channel->isPlaying(&playing));
	return playing;
}

float Audio::getVolume() const
{
	float volume;
	ERRCHECK(m_channel->getVolume(&volume));
	return volume;
}

bool Audio::getLooping() const
{
	bool result = false;
	FMOD_MODE mode;
	ERRCHECK(m_channel->getMode(&mode));
	if (mode & FMOD_LOOP_NORMAL)
	{
		result = true;
	}
	return result;
}

void Sound::createAudio(const std::string& fileName, AudioDimension audioDim)
{
	FMOD_MODE mode = FMOD_LOOP_OFF | FMOD_3D_WORLDRELATIVE | FMOD_3D_INVERSEROLLOFF;
	if (audioDim == AudioDimension::TWOD)
	{
		mode |= FMOD_2D;
	}
	else if (audioDim == AudioDimension::THREED)
	{
		mode |= FMOD_3D;
	}
	ERRCHECK(m_audioEngine->getSystem()->createSound(fileName.c_str(), mode, nullptr, &m_sound));

	//ERRCHECK(m_audioEngine->getSystem()->playSound(m_sound, m_audioEngine->getSoundGroup(), true, &m_channel));
}

void Sound::play()
{
	ERRCHECK(m_audioEngine->getSystem()->playSound(m_sound, m_audioEngine->getSoundGroup(), false, &m_channel));
}

void Stream::createAudio(const std::string& fileName, AudioDimension audioDim)
{
	FMOD_MODE mode = FMOD_LOOP_OFF | FMOD_3D_WORLDRELATIVE | FMOD_3D_INVERSEROLLOFF;
	if (audioDim == AudioDimension::TWOD)
	{
		mode |= FMOD_2D;
	}
	else if (audioDim == AudioDimension::THREED)
	{
		mode |= FMOD_3D;
	}
	ERRCHECK(m_audioEngine->getSystem()->createStream(fileName.c_str(), mode, nullptr, &m_sound));

	//ERRCHECK(m_audioEngine->getSystem()->playSound(m_sound, m_audioEngine->getStreamGroup(), false, &m_channel));
}

void Stream::play()
{
	ERRCHECK(m_audioEngine->getSystem()->playSound(m_sound, m_audioEngine->getStreamGroup(), false, &m_channel));
}
