// ***********************************************************************
// Author           : Pavan Jakhu
// Created          : 02-03-2016
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 02-03-2016
// ***********************************************************************
// <copyright file="GUITextBox.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once
#include "GUIComponent.h"
#include <iostream>

/// <summary>
/// THe class GUITextBox is a text box on the screen that you can input text into and text from.
/// </summary>
/// <seealso cref="GUIComponent" />
class GUITextBox : public GUIComponent
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="GUITextBox"/> class.
	/// </summary>
	/// <param name="destRectPerc">The size of the widget relative the parent widget.</param>
	/// <param name="destRectPix">The size of the widget in pixels.</param>
	/// <param name="text">The text at the start of the text box.</param>
	/// <param name="maxLength">The maximum text length can input in the text box.</param>
	GUITextBox(glm::vec4& destRectPerc, const glm::vec4& destRectPix,
		const std::string& text = "", int maxLength = -1) : 
	GUIComponent(destRectPerc, destRectPix), m_text(text), m_maxLength(maxLength) { }
	/// <summary>
	/// Finalizes an instance of the <see cref="GUITextBox"/> class.
	/// </summary>
	~GUITextBox() { }


	/// <summary>
	/// Adds to Core Engine.
	/// </summary>
	/// <param name="engine">The Core Engine.</param>
	virtual void addToEngine(CoreEngine* engine)
	{ 
		m_editbox = static_cast<CEGUI::Editbox*>(createWidget(engine->getGUIEngine()->getSchemeStyle() + "/Editbox"));
		m_editbox->setText(m_text);
		if (m_maxLength > 0)
		{
			m_editbox->setMaxTextLength(m_maxLength);
		}
	}

	/// <summary>
	/// Gets the text inputed in the text box.
	/// </summary>
	/// <returns>The text inputted.</returns>
	std::string getText()
	{
		return std::string(m_editbox->getText().c_str());
	}
	/// <summary>
	/// Gets the maximum text length for the text box.
	/// </summary>
	/// <returns>The maximum character length.</returns>
	int getMaxLength()
	{
		return m_maxLength;
	}

	/// <summary>
	/// Sets the text in the text box.
	/// </summary>
	/// <param name="text">The text in the text box.</param>
	void setText(const std::string& text)
	{
		m_editbox->setText(text);
	}
	/// <summary>
	/// Sets the maximum character length of the text box.
	/// </summary>
	/// <param name="maxLength">The maximum character length.</param>
	void setMaxLength(int maxLength)
	{
		m_maxLength = maxLength;
		m_editbox->setMaxTextLength(m_maxLength);
	}

private:
	/// <summary>
	/// The CEGUI edit box widget.
	/// </summary>
	CEGUI::Editbox* m_editbox;

	/// <summary>
	/// The text box's text.
	/// </summary>
	std::string m_text;

	/// <summary>
	/// The text box's maximum character length.
	/// </summary>
	int m_maxLength;

};