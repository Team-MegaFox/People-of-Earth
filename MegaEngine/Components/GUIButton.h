#pragma once
#include "GUILabel.h"
#include <iostream>

struct MegaEvents
{

};

typedef bool(*clickedButtonFcn)(MegaEvents);

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
	GUIButton(const std::string& text, const glm::vec4& destRectPerc, 
		const glm::vec4& destRectPix, clickedButtonFcn pfcn) :
		GUILabel(text, destRectPerc, destRectPix) 
	{
		f_clicked = pfcn;
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
		return this->f_clicked(megaEvents);
	}

	/// <summary>
	/// M_clickeds the button.
	/// </summary>
	/// <param name="">The .</param>
	/// <returns></returns>
	clickedButtonFcn f_clicked;

	/// <summary>
	/// The mega events
	/// </summary>
	MegaEvents megaEvents;
};