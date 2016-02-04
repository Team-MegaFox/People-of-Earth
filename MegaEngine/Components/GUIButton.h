// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Jesse Derochie
// Last Modified On : 01-28-2016
// ***********************************************************************
// <copyright file="GameComponents.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************

#pragma once
#include "GUILabel.h"
#include <iostream>

struct MegaEvents
{

};

class GUIButton : public GUILabel
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="GUIButton"/> class.
	/// </summary>
	/// <param name="text">The text.</param>
	/// <param name="destRectPerc">The dest rect perc.</param>
	/// <param name="destRectPix">The dest rect pix.</param>
	/// <param name="clickedButton">The clicked button.</param>
	GUIButton(const std::string& text, const glm::vec4& destRectPerc, const glm::vec4& destRectPix, bool(*clickedButton)(MegaEvents)) :
		GUILabel(text, destRectPerc, destRectPix) 
	{
		m_clickedButton = clickedButton;
	}
	/// <summary>
	/// Finalizes an instance of the <see cref="GUIButton"/> class.
	/// </summary>
	~GUIButton() { }

	/// <summary>
	/// Adds to engine.
	/// </summary>
	/// <param name="engine">The engine.</param>
	virtual void addToEngine(CoreEngine* engine)
	{
		auto wi = createWidget(engine->getGUIEngine()->getSchemeStyle() + "/Button");
		wi->setText(m_text);
		wi->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIButton::pushButton, this));
	}

private:
	/// <summary>
	/// Pushes the button.
	/// </summary>
	/// <param name="e">The e.</param>
	/// <returns></returns>
	bool pushButton(const CEGUI::EventArgs& e)
	{
		return m_clickedButton(megaEvents);
	}

	/// <summary>
	/// M_clickeds the button.
	/// </summary>
	/// <param name="">The .</param>
	/// <returns></returns>
	bool(*m_clickedButton)(MegaEvents);
	/// <summary>
	/// The mega events
	/// </summary>
	MegaEvents megaEvents;
};