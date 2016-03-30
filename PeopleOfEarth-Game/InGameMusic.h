// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 03-28-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 03-30-2016
// ***********************************************************************
// <copyright file="InGameMusic.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>Controls music flow for the game.</summary>
// ***********************************************************************
#pragma once
#include <MegaEngine.h>
#include "ShipStats.h"
#include "DialogueBox.h"

class InGameMusic : public GameComponent
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="InGameMusic"/> class.
	/// </summary>
	InGameMusic() { }
	/// <summary>
	/// Finalizes an instance of the <see cref="InGameMusic"/> class.
	/// </summary>
	~InGameMusic() { }

	/// <summary>
	/// Ons the start. <- no really thats what it does I swear.
	/// </summary>
	virtual void onStart() override
	{
		// required handles
		// Needed simply to be able to check if they are currently playing
		m_Intro = new AudioSource("In Game Music Intro.wav", AudioType::STREAM, true);
		m_Transition = new AudioSource("In Game Music Transition 1.wav", AudioType::STREAM, true);
		m_Music1 = new AudioSource("In Game Music 1.wav", AudioType::STREAM, true);
		m_Music2 = new AudioSource("In Game Music 2.wav", AudioType::STREAM, true);
		m_Danger1 = new AudioSource("In Game Music Danger.wav", AudioType::STREAM, true);
		m_Danger2 = new AudioSource("In Game Music Danger 2.wav", AudioType::STREAM, true);


		// Nothing has played yet
		m_introPlayed = false;
		m_music1Played = false;
		m_music2Played = false;
		m_transitionPlayed = false;
		m_danger1Played = false;
		m_danger2Played = false;

		m_playerStats = getGameObjectByName("player")->getGameComponent<ShipStats>();

		// Nothing should play yet
		m_Intro->stop();
		m_Music1->stop();
		m_Music2->stop();
		m_Danger1->stop();
		m_Danger2->stop();
		m_Transition->stop();
	}

	/// <summary>
	/// Processes input.
	/// </summary>
	/// <param name="input">The input.</param>
	/// <param name="delta">The delta.</param>
	virtual void processInput(const InputManager& input, float delta) override
	{
		if ((m_playerStats->getHealth() <= 0.6f) || (m_playerStats->getEnergy() <= 0.6f) || (m_playerStats->getFuel() <= 0.6f))
		{
			m_inDanger = true;
		}
		else
		{
			m_inDanger = false;
		}

		checkMusic();
	}

	/// <summary>
	/// Decides what music to play based on the 
	/// recent history of what has been played
	/// and whether the player is in any danger
	/// denoted by (health, energy or fuel below 60%)
	/// </summary>
	void checkMusic()
	{
		if (m_firstTimeOnly)
		{
			m_Intro = new AudioSource("In Game Music Intro.wav", AudioType::STREAM, true);
			instantiate((new GameObject("m_Intro"))
				->addGameComponent(m_Intro));
			m_Intro->pause(false);
			m_introPlayed = true;
			m_firstTimeOnly = false;
		}

		// If there is no music playing right now
		if (!m_Intro->isPlaying() 
			&& !m_Music1->isPlaying()
			&& !m_Music2->isPlaying()
			&& !m_Danger1->isPlaying()
			&& !m_Danger2->isPlaying()
			&& !m_Transition->isPlaying())
		{
			// if either music1 was played or music2 was played 
			// or the player is in danger and
			// either danger1 was played or danger2 was played
			// but the transition music hasn't been played
			// play the transition music
			if (((m_introPlayed && !m_transitionPlayed)
				|| (m_music1Played && !m_transitionPlayed)
				|| (m_music2Played && !m_transitionPlayed)
				|| (m_danger1Played && !m_transitionPlayed)
				|| (m_danger2Played && !m_transitionPlayed)))
			{
				m_Transition = new AudioSource("In Game Music Transition 1.wav", AudioType::STREAM, true);
				instantiate((new GameObject("m_Transition"))
					->addGameComponent(m_Transition));
				m_Transition->pause(false);
				// reset booleans
				m_transitionPlayed = true;
			}

			if (!m_inDanger)
			{
				// if the last thing to play was the intro 
				// or we transitioned here from music2
				if (((m_introPlayed && m_transitionPlayed) || (m_music2Played && m_transitionPlayed))
					&& ((!m_Transition->isPlaying()) && (!m_Music2->isPlaying()) && (!m_Intro->isPlaying())))
				{
					m_Music1 = new AudioSource("In Game Music 1.wav", AudioType::STREAM, true);
					instantiate((new GameObject("m_Music1"))
						->addGameComponent(m_Music1));
					m_Music1->pause(false);
					// reset booleans
					m_music1Played = true;
					m_transitionPlayed = false;
					if (m_music2Played)
					{
						m_music2Played = false;
					}
					if (m_introPlayed)
					{
						m_introPlayed = false;
					}
				}
				// if we transitioned here from music 1
				if ((m_music1Played && m_transitionPlayed)
					&& ((!m_Music1->isPlaying()) && (!m_Transition->isPlaying())))
				{
					m_Music2 = new AudioSource("In Game Music 2.wav", AudioType::STREAM, true);
					instantiate((new GameObject("m_Music2"))
						->addGameComponent(m_Music2));
					m_Music2->pause(false);
					// reset booleans
					m_music2Played = true;
					m_music1Played = false;
					m_transitionPlayed = false;
				}
				// if we transitioned here from either of the danger musics
				if (((m_danger1Played && m_transitionPlayed) || (m_danger2Played && m_transitionPlayed))
					&&((!m_Danger1->isPlaying()) && (!m_Transition->isPlaying()) && (!m_Danger2->isPlaying())))
				{
					m_Music1 = new AudioSource("In Game Music 1.wav", AudioType::STREAM, true);
					instantiate((new GameObject("m_Music1"))
						->addGameComponent(m_Music1));
					m_Music1->pause(false);
					// reset booleans
					m_music1Played = true;
					m_transitionPlayed = false;
					if (m_danger1Played)
					{
						m_danger1Played = false;
					}
					if (m_danger2Played)
					{
						m_danger2Played = false;
					}
				}
			}
			else
			{
				// if the player is now in danger, or remains in danger and we
				// have transitioned here from danger2 music
				// or we transitioned here from either music1 or music2
				// because we are in a danger state
				if (((m_introPlayed && m_transitionPlayed)
					||(m_music1Played && m_transitionPlayed)
					|| (m_music2Played && m_transitionPlayed)
					|| (m_danger2Played && m_transitionPlayed))
					&& ((!m_Intro->isPlaying()) 
					&& (!m_Music1->isPlaying()) 
					&& (!m_Music2->isPlaying()) 
					&& (!m_Transition->isPlaying())))
				{
					m_Danger1 = new AudioSource("In Game Music Danger.wav", AudioType::STREAM, true);
					instantiate((new GameObject("m_Danger1"))
						->addGameComponent(m_Danger1));
					m_Danger1->pause(false);
					// reset booleans
					m_danger1Played = true;
					m_transitionPlayed = false;
					if (m_danger2Played)
					{
						m_danger2Played = false;
					}
					if (m_music1Played)
					{
						m_music1Played = false;
					}
					if (m_music2Played)
					{
						m_music2Played = false;
					}
					if (m_introPlayed)
					{
						m_introPlayed = false;
					}
				}
				// if we transitioned here from the danger1 music
				if ((m_danger1Played && m_transitionPlayed)
					&& ((!m_Danger1->isPlaying()) && (!m_Transition->isPlaying())))
				{
					m_Danger2 = new AudioSource("In Game Music Danger 2.wav", AudioType::STREAM, true);
					instantiate((new GameObject("m_Danger2"))
						->addGameComponent(m_Danger2)); 
					m_Danger2->pause(false);
					m_danger2Played = true;
					m_transitionPlayed = false;
					m_danger1Played = false;
				}
			}
			
		}
	}

private:
	/// <summary>
	/// The intro music
	/// </summary>
	AudioSource * m_Intro;
	/// <summary>
	/// The music1 music
	/// </summary>
	AudioSource * m_Music1;
	/// <summary>
	/// The music2 music
	/// </summary>
	AudioSource * m_Music2;
	/// <summary>
	/// The danger1 music
	/// </summary>
	AudioSource * m_Danger1;
	/// <summary>
	/// The danger2 music
	/// </summary>
	AudioSource * m_Danger2;
	/// <summary>
	/// The transition music
	/// </summary>
	AudioSource * m_Transition;

	/// <summary>
	/// The m_intro music played
	/// </summary>
	bool m_introPlayed;
	/// <summary>
	/// The m_music1 music played
	/// </summary>
	bool m_music1Played;
	/// <summary>
	/// The m_music2 music played
	/// </summary>
	bool m_music2Played;
	/// <summary>
	/// The m_transition music played
	/// </summary>
	bool m_transitionPlayed;
	/// <summary>
	/// The m_danger1 music played
	/// </summary>
	bool m_danger1Played;
	/// <summary>
	/// The m_danger2 music played
	/// </summary>
	bool m_danger2Played;
	/// <summary>
	/// The player ship stats
	/// </summary>
	ShipStats * m_playerStats;
	/// <summary>
	/// The in danger boolean
	/// </summary>
	bool m_inDanger;
	/// <summary>
	/// The first time run only boolean
	/// </summary>
	bool m_firstTimeOnly = true;
};
