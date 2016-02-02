// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 02-01-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 02-01-2016
// ***********************************************************************
// <copyright file="AudioListener.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
// </summary>
// ***********************************************************************

#pragma once
#include "..\Audio\AudioEngine.h"
#include "..\Core\Utility.h"

class AudioListener
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="AudioListener"/> class.
	/// </summary>
	AudioListener() : m_parent(nullptr) {}
	/// <summary>
	/// Finalizes an instance of the <see cref="AudioListener"/> class.
	/// </summary>
	~AudioListener() {}

	/// <summary>
	/// Sets this as the listener in the scene.
	/// </summary>
	void setAsListener()
	{
		glm::vec3 forward = Utility::getForward(*m_parent->getTransform()->getRotation());
		glm::vec3 up = Utility::getUp(*m_parent->getTransform()->getRotation());

		m_audioEngine->setListener(
			*m_parent->getTransform()->getPosition(),
			glm::vec3(0.0f),
			forward,
			up);
	}

protected:
	/// <summary>
	/// The audio engine handle
	/// </summary>
	AudioEngine * m_audioEngine = m_parent->getCoreEngine()->getAudioEngine();

private:

	/// <summary>
	/// The parent Game Object
	/// </summary>
	GameObject * m_parent;
};

