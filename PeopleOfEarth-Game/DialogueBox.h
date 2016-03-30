// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 03-28-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 03-30-2016
// ***********************************************************************
// <copyright file="DialogueBox.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>Controls message flow to the dialogue box in the mission.</summary>
// ***********************************************************************
#pragma once
#include <MegaEngine.h>
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
	DialogueBox() : m_timeMessageWasSent(Time::getTime()), m_lineLength(28) {}
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
		sendMessage(m_message + " ", Importance::CRITICAL, false);
	}

	/// <summary>
	/// Sets the Message to display.
	/// </summary>
	/// <param name="newText">The new message.</param>
	void sendMessage(const std::string& newMessage, Importance importanceOfMessage = Importance::DEFAULT, bool useMultiLineTool = true)
	{
		// if a new message was received
		if (m_message != newMessage)
		{
			// if the importance level of that message is greater than
			// the current importance level of the current message
			if (m_importanceLevel <= importanceOfMessage)
			{
				// if the importance of the incoming message is 
				// greater than any current lasting message, the lasting 
				// message may be removed
				m_lastingMessage = false;
				m_messageReceived = true;
				m_message = newMessage;

				// if the message needs to be formatted using the multiLinetool
				if ((m_message.length() > m_lineLength) && useMultiLineTool)
				{
					multiLineTool(m_lineLength, m_message);
				}
				// set the new importance level and set the timeMessagewasReceived variable to the current time
				m_importanceLevel = importanceOfMessage;
				m_timeMessageWasSent = Time::getTime();
			}
		}
	}

	/// <summary>
	/// Sets the Message to display.
	/// </summary>
	/// <param name="newText">The new message.</param>
	void sendLastingMessage(const std::string& newMessage, Importance importanceOfMessage = Importance::DEFAULT, bool useMultiLineTool = true)
	{
		// if a new message was received
		if (m_message != newMessage)
		{
			// if the importance level of that message is greater than
			// the current importance level of the current message
			if (m_importanceLevel <= importanceOfMessage)
			{
				m_messageReceived = true;
				m_message = newMessage;

				// if the message needs to be formatted using the multiLinetool
				if ((m_message.length() > m_lineLength) && useMultiLineTool)
				{
					multiLineTool(m_lineLength, m_message);
				}
				// set the new importance level and set the timeMessagewasReceived variable to the current time
				m_importanceLevel = importanceOfMessage;
				m_lastingMessage = true;
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
	/// Restores the text settings.
	/// </summary>
	void restoreTextSettings() { m_textSettings = m_originalSettings; }

	/// <summary>
	/// Updates the GUI label text
	/// </summary>
	/// <param name="deltaTime">delta time.</param>
	virtual void update(float deltaTime) override
	{
		// set the message text
		m_guiLabel->setText(m_textSettings + m_message);

		// if a new message was received and it isn't 
		// a message that should stay up for a while
		if (m_messageReceived && !m_lastingMessage)
		{
			double currentTime = Time::getTime();
			// if it has been 5 seconds, reduce the importance level of the message
			if ((currentTime - m_timeMessageWasSent) >= 5.0)
			{
				m_importanceLevel = Importance::DEFAULT;
			}
			// if it has been 10 seconds restore the default message text
			if ((currentTime - m_timeMessageWasSent) >= 10.0)
			{
				sendMessage(m_defaultMessage);
				m_messageReceived = false;
				m_timeMessageWasSent = 0.0;
				if (m_textSettings != m_originalSettings)
				{
					restoreTextSettings();
				}
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
			else if (count >= m_lineLength - 1)
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
		if (message.length() - i > m_lineLength)
		{
			multiLineTool(i + m_lineLength, message);
		}
		return message;
	}

private:

	/// <summary>
	/// The current text settings
	/// </summary>
	std::string m_textSettings = "[font='DejaVuSans-12'][padding='l:5 t:0 r:5 b:0'][colour='FFFFFFFF']";
	/// <summary>
	/// The original text settings
	/// <code> [font='DejaVuSans-12'][padding='l:5 t:0 r:5 b:0'] </code>
	/// </summary>
	std::string m_originalSettings = "[font='DejaVuSans-12'][padding='l:5 t:0 r:5 b:0'][colour='FFFFFFFF']";
	/// <summary>
	/// The message to display
	/// </summary>
	std::string m_message = " ";
	/// <summary>
	/// The default message for the dialogue box
	/// </summary>
	std::string m_defaultMessage = " ";
	/// <summary>
	/// The gui label
	/// </summary>
	GUILabel * m_guiLabel;
	/// <summary>
	/// Counter that is used to determine when to erase the last message.
	/// </summary>
	double m_timeMessageWasSent;
	/// <summary>
	/// The amount of time to keep a message alive before restoring the default message
	/// </summary>
	double m_eraseTime = 10.0;
	/// <summary>
	/// The length the line is allowed to be before a newline is inserted
	/// </summary>
	int m_lineLength;
	/// <summary>
	/// The received message
	/// </summary>
	bool m_messageReceived = false;
	/// <summary>
	/// The importance level of the current message
	/// </summary>
	Importance m_importanceLevel = Importance::DEFAULT;
	bool m_lastingMessage = false;

};

