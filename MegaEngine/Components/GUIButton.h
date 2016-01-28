#pragma once
#include "GUILabel.h"
#include <iostream>

struct MegaEvents
{

};

class GUIButton : public GUILabel
{
public:
	GUIButton(const std::string& text, const glm::vec4& destRectPerc, const glm::vec4& destRectPix, bool (*clickedButton)(MegaEvents)) :
		GUILabel(text, destRectPerc, destRectPix) 
	{
		m_clickedButton = clickedButton;
	}
	~GUIButton() { }

	virtual void addToEngine(CoreEngine* engine)
	{
		auto wi = createWidget(engine->getGUIEngine()->getSchemeStyle() + "/Button");
		wi->setText(m_text);
		wi->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIButton::pushButton, this));
	}

private:
	bool pushButton(const CEGUI::EventArgs& e)
	{
		return m_clickedButton(megaEvents);
	}

	bool (*m_clickedButton)(MegaEvents);
	MegaEvents megaEvents;
};