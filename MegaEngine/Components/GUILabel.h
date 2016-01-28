#pragma once
#include "GUIComponent.h"
#include <glm\glm.hpp>

class GUILabel : public GUIComponent
{
public:
	GUILabel(const std::string& text, const glm::vec4& destRectPerc, const glm::vec4& destRectPix) :
		GUIComponent(destRectPerc, destRectPix), m_text(text) { }
	~GUILabel() { }

	virtual void addToEngine(CoreEngine* engine) const
	{
		auto wi = createWidget(engine->getGUIEngine()->getSchemeStyle() + "/Label");
		wi->setText(m_text);
	}

protected:
	std::string m_text;
};