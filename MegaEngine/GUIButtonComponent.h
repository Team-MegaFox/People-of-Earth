#pragma once
#include "GUIComponent.h"

class GUIButtonComponent 
	:	public GUIComponent
{
public:
	GUIButtonComponent(
		const std::string & type, 
		const std::string & name, 
		const std::string & buttonText, 
		const glm::vec4 & destRectPerc, 
		const glm::vec4 & destRectPix);

	std::string & getText() { return m_buttonText; }
	bool isHovering();
	bool isPushed();

	void setText(const std::string & text) { m_buttonText = text; }
	void setOnClick(Event::Subscriber subscribe);

private:
	std::string m_buttonText;
};

