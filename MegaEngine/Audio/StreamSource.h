// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 02-01-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 02-01-2016
// ***********************************************************************
// <copyright file="StreamSource.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
// </summary>
// ***********************************************************************

#pragma once
#include "..\Audio\AudioEngine.h"

class StreamSource
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="StreamSource"/> class.
	/// </summary>
	StreamSource() {}
	/// <summary>
	/// Initializes a new instance of the <see cref="StreamSource"/> class.
	/// </summary>
	/// <param name="fileName">Name of the file.</param>
	StreamSource(const std::string& fileName) :
		m_parent(nullptr),
		m_fileName(fileName) { }
	/// <summary>
	/// Finalizes an instance of the <see cref="StreamSource"/> class.
	/// </summary>
	~StreamSource() {}

	/// <summary>
	/// Used to set a stream to a channel initially, 
	/// also if a stream has been played once,
	/// it must be re - set to the channel it was last on using this method.
	/// </summary>
	/// <param name="index">The index.</param>
	void setStream(std::string filepath)
	{
		m_audioEngine->setStream(m_filePath + m_fileName);
	}

	/// <summary>
	/// Plays the stream.
	/// </summary>
	void playStream() { m_audioEngine->playStream(m_filePath + m_fileName); }

	/// <summary>
	/// Stops all streams.
	/// </summary>
	void stopAllStreams() { m_audioEngine->stopAllStreams(); }

	/// <summary>
	/// Pauses the stream.
	/// </summary>
	/// <param name="paused">if set to <c>true</c> [paused].</param>
	void pauseStream(bool paused) { m_audioEngine->pauseStream(paused, m_filePath + m_fileName); }

	/// <summary>
	/// Determines whether [is stream playing].
	/// </summary>
	/// <returns></returns>
	bool isStreamPlaying()
	{
		if (m_audioEngine->isStreamPlaying(m_filePath + m_fileName))
			return true;
		else
			return false;
	}

	/// <summary>
	/// Originally sets the stream later used to reset the stream.
	/// </summary>
	void setStream() { m_audioEngine->setStream(m_filePath + m_fileName); }

	/// <summary>
	/// Gets global stream volume.
	/// </summary>
	/// <returns></returns>
	float getStreamVolume() { return m_audioEngine->getStreamVolume(); }

	/// <summary>
	/// Sets the stream volume for all streams.
	/// </summary>
	/// <param name="volume">The volume level.</param>
	void setStreamVolumeAll(float volume) { m_audioEngine->setStreamEffectVolume(volume); }

	/// <summary>
	/// Sets this streams volume.
	/// </summary>
	/// <param name="volume">The volume level.</param>
	void setStreamVolume(float volume) { m_audioEngine->setStreamEffectVolume(m_filePath + m_fileName, volume); }

	/// <summary>
	/// Sets the stream position and vel.
	/// </summary>
	/// <param name="pos">The position of this stream.</param>
	void setStreamPosition(glm::vec3 pos) { m_audioEngine->setStreamPosVel(m_filePath + m_fileName, pos); }

	/// <summary>
	/// Sets the panning of this stream.
	/// </summary>
	/// <param name="pan">The pan.</param>
	void setStreamPan(float pan) { m_audioEngine->setStreamPan(m_filePath + m_fileName, pan); }

	/// <summary>
	/// Sets this streams doppler level.
	/// </summary>
	/// <param name="dop">The dop.</param>
	void setStreamDoppler(float dop) { m_audioEngine->setStreamDopplerLevel(m_filePath + m_fileName, dop); }

	/// <summary>
	/// Sets the stream 3D minimum distance for attenuation.
	/// </summary>
	/// <param name="min">The minimum.</param>
	void setStream3DMinDist(float min) { m_audioEngine->setStream3DMinMaxDistance(m_filePath + m_fileName, min); }

	/// <summary>
	/// Sets the occlusion (if something is in the way of the stream).
	/// </summary>
	/// <param name="attenuation">The attenuation.</param>
	void setStreamOcclusion(float attenuation) { m_audioEngine->setStreamOcclusion(m_filePath + m_fileName, attenuation); }

	/// <summary>
	/// Loads the streams list.
	/// </summary>
	/// <param name="fileNames">The streams' file names.</param>
	void loadStreamList(std::vector<std::string> fileNames) { m_audioEngine->loadStreams(fileNames); }

	/// <summary>
	/// Sets the file path.
	/// </summary>
	/// <param name="filePath">The file path.</param>
	void setFilePath(std::string filePath)
	{
		m_filePath = filePath;
	}

protected:
	/// <summary>
	/// The audio engine handle
	/// </summary>
	AudioEngine * m_audioEngine = m_parent->getCoreEngine()->getAudioEngine();

private:

	/// <summary>
	/// The file name of this audiosource file
	/// </summary>
	std::string m_fileName;

	/// <summary>
	/// The parent Game Object
	/// </summary>
	GameObject * m_parent;

	/// <summary>
	/// The file path of this StreamSource file
	/// </summary>
	std::string m_filePath = "";
};

