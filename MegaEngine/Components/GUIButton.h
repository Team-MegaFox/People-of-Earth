#pragma once
#include "GUILabel.h"

class GUIButton : public GUILabel
{
public:
	GUIButton(const std::string& text, const glm::vec4& destRectPerc, const glm::vec4& destRectPix) :
	GUILabel(text, destRectPerc, destRectPix) { }
	~GUIButton() { }

	virtual void addToEngine(CoreEngine* engine) const
	{
		auto wi = createWidget(engine->getGUIEngine()->getSchemeStyle() + "/Button");
		wi->setText(m_text);
	}

private:

};