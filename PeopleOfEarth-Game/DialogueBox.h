// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 03-28-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 03-29-2016
// ***********************************************************************
// <copyright file="DialogueBox.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>Controls message flow to the dialogue box in the mission.</summary>
// ***********************************************************************
#pragma once
#include "MegaEngine.h"
/// <summary>
/// The importance of a message determines whether or not this message
/// will be displayed. If this message is critically important to the 
/// player, it will be displayed instead of something less critical
/// ie. "Health is dangerously low!! Return to passenger ship for repairs!"
/// is more important than, "Ship is undergoing repairs..."
/// </summary>
enum Importance
{
	DEFAULT,
	LOW,
	MEDIUM,
	HIGH,
	CRITICAL
};

class DialogueBox : public GameComponent
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="DialogueBox"/> class.
	/// </summary>
	DialogueBox() : m_counter(1200) {}
	/// <summary>
	/// Finalizes an instance of the <see cref="DialogueBox"/> class.
	/// </summary>
	~DialogueBox() {}

	/// <summary>
	/// Sets variables 
	/// </summary>
	void onStart()
	{
		m_guiLabel = getParent()->getGUIComponent<GUILabel>();
		sendMessage(m_message + "!");
	}

	/// <summary>
	/// Sets the Message to display.
	/// </summary>
	/// <param name="newText">The new message.</param>
	void sendMessage(const std::string& newMessage, Importance importanceOfMessage = Importance::DEFAULT)
	{
		if (m_message != newMessage)
		{
			if (m_importanceLevel <= importanceOfMessage)
			{
				m_messageReceived = true;
				m_message = newMessage;

				if (m_message.length() > 25)
				{
					multiLineTool(25, m_message);
				}
				m_importanceLevel = importanceOfMessage;
			}
		}
	}

	/// <summary>
	/// Sets the text settings.
	/// <code> [font='DejaVuSans-12'][padding='l:5 t:0 r:5 b:0'][colour='FFFF0000'] </code>
	/// </summary>
	/// <param name="newSettings">The new settings.</param>
	void setTextSettings(const std::string& newSettings) { m_textSettings = newSettings; }

	/// <summary>
	/// Updates the GUI label text
	/// </summary>
	/// <param name="deltaTime">delta time.</param>
	virtual void update(float deltaTime) override
	{
		m_guiLabel->setText(m_textSettings + m_message);
		if (m_messageReceived)
		{
			if (m_counter > 0)
			{
				m_counter--;
			}
			else if (m_counter <= 600)
			{
				m_importanceLevel = Importance::DEFAULT;
			}
			else if (m_counter == 0)
			{
				sendMessage(m_defaultMessage);
				m_messageReceived = false;
				m_counter = 1200;
			}

		}
	}

	/// <summary>
	/// Recursive method that breaks the message 
	/// into lines no longer than 25 characters
	/// </summary>
	/// <param name="index">The index.</param>
	/// <param name="text">the message</param>
	/// <returns></returns>
	std::string multiLineTool(unsigned int index, std::string& message)
	{
		// start at this index
		// move backward until you find a space
		// make that space a newline
		size_t i;
		size_t count = 0;
		for (i = index; i < message.length(); i++)
		{
			count++;
			if (message[i] == ' ')
			{
				message[i] = '\n';
				break;
			}
			else if (count >= 24)
			{
				message[index] = '\n';
				break;
			}
		}
		count = 0;
		// if the index in the string
		// subtracted from the string length 
		// is still greater than 25
		// call this method again
		// passing the index of 25 + the curent position in the string;
		if (message.length() - i > 25)
		{
			multiLineTool(i + 25, message);
		}
		return message;
	}

private:

	/// <summary>
	/// The text settings for the message to display
	/// <code> [font='DejaVuSans-12'][padding='l:5 t:0 r:5 b:0'] </code>
	/// </summary>
	std::string m_textSettings = "[font='DejaVuSans-12'][padding='l:5 t:0 r:5 b:0']";
	/// <summary>
	/// The message to display
	/// </summary>
	std::string m_message = "Hello! Welcome to The People of Earth Demo! We hope you enjoy your time with us. Feel free to ask us any questions you have.";
	std::string m_defaultMessage = "Hello! Welcome to The People of Earth Demo! We hope you enjoy your time with us. Feel free to ask us any questions you have.";
	/// <summary>
	/// The gui label
	/// </summary>
	GUILabel * m_guiLabel;
	int m_counter;
	bool m_messageReceived = false;
	Importance m_importanceLevel = Importance::DEFAULT;

};

