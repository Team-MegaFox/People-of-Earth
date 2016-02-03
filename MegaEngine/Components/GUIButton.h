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
	/// <param name="text">The text in the button.</param>
	/// <param name="destRectPerc">The size of the widget relative the parent widget.</param>
	/// <param name="destRectPix">The size of the widget in pixels.</param>
	/// <param name="pfcn">The function to call when the button is clicked.</param>
	GUIButton(const std::string& text, const glm::vec4& destRectPerc,
		const glm::vec4& destRectPix, std::function<bool(MegaEvents)> pfcn = nullptr) :
		GUILabel(text, destRectPerc, destRectPix), f_clicked(pfcn) { }
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
		auto wi = createWidget(engine->getGUIEngine()->getSchemeStyle() + "/Button");
		wi->setText(getText());
		wi->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIButton::pushButton, this));
	}
	
	/// <summary>
	/// Sets the on click function when the button is clicked.
	/// </summary>
	/// <param name="pfcn">The function to call when the button is clicked.</param>
	void setOnClick(std::function<bool(MegaEvents)> pfcn)
	{
		f_clicked = pfcn;
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
			return f_clicked(megaEvents);
		}
		return false;
	}

	/// <summary>
	/// The function to call when the button is clicked.
	/// </summary>
	std::function<bool(MegaEvents)> f_clicked;

	/// <summary>
	/// The mega events
	/// </summary>
	MegaEvents megaEvents;
};