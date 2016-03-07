// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Jesse Derochie
// Last Modified On : 03-01-2016
// ***********************************************************************
// <copyright file="GameComponents.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once
#include "GUILabel.h"
#include <iostream>
#include <functional>

/// <summary>
/// Some sort of event thing for the engine. Haven't decided what to do with it yet.
/// </summary>
struct MegaEvents
{

};

/// <summary>
/// The class GUIBUtton is the button widget for click events.
/// </summary>
/// <seealso cref="GUILabel" />
class GUIButton : public GUILabel
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="GUIButton"/> class.
	/// </summary>
	/// <param name="destRectPerc">The size of the widget relative the parent widget.</param>
	/// <param name="destRectPix">The size of the widget in pixels.</param>
	/// <param name="text">The text in the button.</param>
	/// <param name="pfcn">The function to call when the button is clicked.</param>
	GUIButton(const PxVec4& destRectPerc,
		const PxVec4& destRectPix, const std::string& text,
		std::function<bool(const GameObject&)> pfcn = nullptr, Uint8 size = 10) :
		GUILabel(destRectPerc, destRectPix, text, size), f_clicked(pfcn) { }
	/// <summary>
	/// Finalizes an instance of the <see cref="GUIButton"/> class.
	/// </summary>
	~GUIButton() { }

	/// <summary>
	/// Creates the widget, sets the text and subscribes the event to the button.
	/// </summary>
	/// <param name="engine">The engine.</param>
	virtual void addToEngine(CoreEngine* engine)
	{
		GUIComponent::addToEngine(engine);
		auto wi = createWidget(engine->getGUIEngine()->getSchemeStyle() + "/Button");
		wi->setText(getText());
		wi->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIButton::pushButton, this));
		engine->getGUIEngine()->addFont(engine->getGUIEngine()->getDefaultFontName(), getTextSize());
		wi->setFont(engine->getGUIEngine()->getDefaultFontName() + "-" + std::to_string(getTextSize()));
	}
	
	/// <summary>
	/// Sets the on click function when the button is clicked.
	/// </summary>
	/// <param name="pfcn">The function to call when the button is clicked.</param>
	void setOnClick(std::function<bool(const GameObject&)> pfcn)
	{
		f_clicked = pfcn;
	}

	void click()
	{
		CEGUI::EventArgs args;
		getWidget()->fireEvent(CEGUI::PushButton::EventClicked, args);
	}

private:
	/// <summary>
	/// The onClick function managed by CEGUI. It calls a function pointer so we can abstract CEGUI.
	/// </summary>
	/// <param name="e">The event handler by CEGUI.</param>
	/// <returns>Don't know. It's for CEGUI.</returns>
	bool pushButton(const CEGUI::EventArgs& e)
	{
		if (f_clicked != nullptr)
		{
			return f_clicked(*getParent());
		}
		return false;
	}

	/// <summary>
	/// The function to call when the button is clicked.
	/// </summary>
	std::function<bool(const GameObject&)> f_clicked;

	/// <summary>
	/// The mega events
	/// </summary>
	MegaEvents megaEvents;
};