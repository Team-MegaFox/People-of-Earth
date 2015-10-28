#pragma once
#include <iostream>
#include <FMOD\fmod.h>
#include <FMOD\fmod.hpp>
#include <FMOD\fmod_errors.h>

#include <GLM\glm.hpp>

#include <vector>
#include <string>

static const int NUM_SOUND_CHANNELS = 100;
static const int NUM_STREAM_CHANNELS = 50;

class AudioEngine
{
public:
	~AudioEngine();

	/*
	Used to set a sound to a channel initially, 
	also if a sound has been played once,
	it must be re-set to the channel it was last on using this method.
	*/
	void setSound(int index);

	/*
	Used to set a stream to a channel initially, 
	also if a stream has been played once, 
	it must be re-set to the channel it was last on using this method.
	*/
	void setStream(int index);

	/*
	Plays the sound in question
	*/
	void playSound(int index);

	/* 
	Plays the stream in question
	*/
	void playStream(int index, bool looping = false);

	/*
	Either pauses or unpauses the sound
	in question depending on how this method is called
	*/
	void pauseSound(bool pause, int index);

	/*
	Either pauses or unpauses the stream 
	in question depending on how this method is called
	*/
	void pauseStream(bool pause, int index);

	/*
	Stops all sounds whether they are playing or not
	*/
	void stopAllSoundEffects();

	/*
	Stops all streams whether they are playing or not
	*/
	void stopAllStreams();

	/*
	Returns true if the sound in question
	is currently playing
	*/
	bool isSoundPlaying(int index);

	/*
	Returns true if the stream in question
	is currently playing
	*/
	bool isStreamPlaying(int index);

	/*
	Sets the volume level of all sounds
	*/
	void setSoundEffectVolume(float volumeLevel);
	
	/*
	Affect an individual sound channels volume level
	*/
	void setSoundEffectVolume(int index, float volumeLevel);

	/*
	Affect an individual stream channels volume level
	*/
	void setStreamEffectVolume(int index, float volumeLevel);

	/*
	Sets the volume level of all streams
	*/
	void setStreamEffectVolume(float volumeLevel);
	
	/*
	Gets the current volume level of all
	sounds
	*/
	float & getSoundVolume();
	
	/*
	Gets the current volume level of all
	streams
	*/
	float & getStreamVolume();

	/*
	This method sets the position of the listener in the world
	This in most game would be the player character
	*/
	void setListener(glm::vec3 pos, glm::vec3 vel, glm::vec3 forward, glm::vec3 up);

	/*
	This method sets the position of the sound in the world
	if there is a velocity that the sound is travelling
	at then this is passed in as well.
	*/
	void setSoundPosVel(int index, glm::vec3 pos, glm::vec3 vel);

	/*
	This method sets the position of the stream in the world
	if there is a velocity that the stream is travelling
	at then this is passed in as well.
	*/
	void setStreamPosVel(int index, glm::vec3 pos, glm::vec3 vel);

	/*
	Panning is used to set a sound effect to be either to the
	left, center or right of the listener
	*/
	void setSoundPan(int index, float pan);

	/*
	Panning is used to set a stream effect to be either to the
	left, center or right of the listener
	*/
	void setStreamPan(int index, float pan);

	/*
	Doppler is the change in frequency of a sound as it moves relative to the position of
	the listener (the Doppler Effect). So if a sound is moving past a listener, or a listener
	is moving past a sound (or if they are both moving), the listener will perceive the pitch
	of the sound changing as the object moves.
	*/
	void setSoundDopplerLevel(int index, float dopplerLevel);

	/*
	Doppler is the change in frequency of a stream as it moves relative to the position of
	the listener (the Doppler Effect). So if a stream is moving past a listener, or a listener
	is moving past a stream (or if they are both moving), the listener will perceive the pitch
	of the stream changing as the object moves.
	*/
	void setStreamDopplerLevel(int index, float dopplerLevel);

	/*
	Sets the orientation of the sound projection cone.
	*/
	void setSoundConeOrientation(int index, glm::vec3 orientation);

	/*
	Sets the size and shape of the sound projection cone
	outsideVolume must be a value between 0.0 and 1.0
	the default is 1.0. This is the volume of the sound
	outside the cone angles and direction
	*/
	void setSoundConeSettings(int index, float insideConeAngle, float outsideConeAngle, float outsideVolume);

	/*
	Control the behaviour of a 3D distance filter, whether to enable or disable it, and frequency characteristics.
	@param custom - if true, disable FMOD distance rolloff
	@param customLevel - set attenuation factor here, 1.0 is no attenuation, 0.0 complete attenuation
	@param centreFreq - Specify a center frequency for the high-pass filter used to simulate distance attenuation.
	*/
	void setSoundDistanceFilter(int index, bool custom, bool customLevel, float centreFreq);

	/*
	3D Min distance refers to the minimum distance a sound travels before it starts to
	attenuate and 3D Max distance refers to the maximum distance a sound travels before it
	stops attenuating.
	*/
	void setSound3DMinMaxDistance(int index, float min, float max = NULL);

	/*
	3D Min distance refers to the minimum distance a stream travels before it starts to
	attenuate and 3D Max distance refers to the maximum distance a stream travels before it
	stops attenuating.
	*/
	void setStream3DMinMaxDistance(int index, float min, float max = NULL);

	/*
	This is used when there are obstacles in the way of a sound

	@param index -  the particular channel to affect
	@param attenuation - must be a value between 0.0 and 1.0
	at 0.0 there is no attenuation, at 1.0 there is complete attenuation
	@param reverberation - must be a value between 0.0 and 1.0
	at 0.0 there is no reverberation, at 1.0 there is complete reverberation
	*/
	void setSoundOcclusion(int index, float attenuation, float reverberation = 0.0f);

	/*
	This is used when there are obstacles in the way of a stream

	@param index -  the particular channel to affect
	@param attenuation - must be a value between 0.0 and 1.0
	at 0.0 there is no attenuation, at 1.0 there is complete attenuation
	@param reverberation - must be a value between 0.0 and 1.0
	at 0.0 there is no reverberation, at 1.0 there is complete reverberation
	*/
	void setStreamOcclusion(int index, float attenuation, float reverberation = 0.0f);

	/*
	Load all sounds the Engine will have to know about for
	your game.
	@param soundList - This must be a vector of filePaths in string form
	these filepaths will be used to store the sounds in channels
	where they will then be arranged into a channelgroup.
	*/
	bool loadSounds(std::vector<std::string> soundList);

	/*
	Load all streams the Engine will have to know about for
	your game.
	@param streamList - This must be a vector of filePaths in string form
	these filepaths will be used to store the streams in channels
	where they will then be arranged into a channelgroup.
	*/
	bool loadStreams(std::vector<std::string> streamList);

	/*
	deletes all pointers, 
	releases all resources 
	and the instance object when called
	*/
	void dispose(const std::vector<std::string> & soundList, const std::vector<std::string> & streamList);

	/*
	Updates the system object
	(should be called every frame)
	*/
	void update();

	/*
	Returns the singular instance of the AudioEngine
	*/
	static AudioEngine * getInstance()
	{
		if (!instance)
		{
			instance = new AudioEngine;
		}
		return instance;
	}

private:
	AudioEngine();
	
	/*
	Initializes FMOD
	called automatically when the
	AudioEngine instance is created.
	*/
	void init();

	/*
	Verifies that each step of the initialization 
	was properly initalized.
	*/
	void FMODVerifyResult(FMOD_RESULT result)
	{
		if (result != FMOD_OK)
		{
			std::cout << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
		}
	}

	/*
	Converts glm::vec3's to FMOD_VECTOR *'s
	for use in FMOD's positioning of the listener
	and sound/stream positioning
	*/
	FMOD_VECTOR glmToFMOD(glm::vec3 vector);

	static AudioEngine * instance;

	// Volume Controls
	float m_soundVolume;
	float m_streamVolume;

	// FMOD requirements
	FMOD::System * m_system;
	FMOD_RESULT m_result;

	// Sound Effects
	FMOD::Sound * m_soundEffects[NUM_SOUND_CHANNELS];
	FMOD::Channel * m_soundChannels[NUM_SOUND_CHANNELS];
	FMOD::ChannelGroup * m_soundEffectChannels;
	const std::vector<std::string> * m_soundList;

	// Stream Effects (Music)
	FMOD::Sound * m_streams[NUM_STREAM_CHANNELS];
	FMOD::Channel * m_streamChannels[NUM_STREAM_CHANNELS];
	FMOD::ChannelGroup * m_streamEffectChannels;
	const std::vector<std::string> * m_streamList;
};

