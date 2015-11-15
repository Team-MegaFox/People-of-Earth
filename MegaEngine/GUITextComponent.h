#pragma once
#include "GUIComponent.h"

class GUITextComponent
	: public GUIComponent
{
public:
	GUITextComponent(
		const std::string & type, 
		const std::string & name, 
		const std::string & labelText, 
		const glm::vec4 & destRectPerc, 
		const glm::vec4 & destRectPix);

	std::string & getText() { return m_text; }
	void setText(std::string & text) { m_text = text; }

private:
	std::string m_text;
};

