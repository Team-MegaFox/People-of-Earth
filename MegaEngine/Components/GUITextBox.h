// ***********************************************************************
// Author           : Pavan Jakhu
// Created          : 02-03-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 03-01-2016
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
	GUITextBox(physx::PxVec4& destRectPerc, const physx::PxVec4& destRectPix,
		const std::string& text = "", int maxLength = -1) : 
	GUIComponent(destRectPerc, destRectPix), m_text(text), m_maxLength(maxLength), m_textChanged(false) { }
	/// <summary>
	/// Finalizes an instance of the <see cref="GUITextBox"/> class.
	/// </summary>
	~GUITextBox() { }

	/// <summary>
	/// Virtual function for custom update functionality.
	/// </summary>
	/// <param name="delta">The frame time delta.</param>
	virtual void update(float delta) 
	{
		if (m_textChanged)
		{
			m_textChanged = false;
			/*m_timeToChangeText -= delta;
			if (m_timeToChangeText <= 0.0f)
			{
				
				m_timeToChangeText = 0.5f;
			}*/
		}
	}
	/// <summary>
	/// Adds to Core Engine.
	/// </summary>
	/// <param name="engine">The Core Engine.</param>
	virtual void addToEngine(CoreEngine* engine)
	{ 
		GUIComponent::addToEngine(engine);
		m_editbox = static_cast<CEGUI::Editbox*>(createWidget(engine->getGUIEngine()->getSchemeStyle() + "/Editbox"));
		m_editbox->setText(m_text);
		if (m_maxLength > 0)
		{
			m_editbox->setMaxTextLength(m_maxLength);
		}
		m_editbox->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&GUITextBox::onTextChanged, this));
	}

	/// <summary>
	/// Gets the text inputed in the text box.
	/// </summary>
	/// <returns>The text inputted.</returns>
	std::string getText() const { return std::string(m_editbox->getText().c_str()); }
	/// <summary>
	/// Gets the maximum text length for the text box.
	/// </summary>
	/// <returns>The maximum character length.</returns>
	int getMaxLength() const { return m_maxLength; }
	/// <summary>
	/// if the text in the text box has changed.
	/// </summary>
	/// <returns>Weather the text in the box has changed.</returns>
	bool textChanged() const { return m_textChanged; }

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
	bool onTextChanged(const CEGUI::EventArgs& e)
	{
		m_textChanged = true;
		return true;
	}

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

	/// <summary>
	/// If the text has changed.
	/// </summary>
	bool m_textChanged;

	float m_timeToChangeText = 0.5f;

};