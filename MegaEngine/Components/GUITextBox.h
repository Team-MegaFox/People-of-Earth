#pragma once
#include "GUIComponent.h"
#include <iostream>

class GUITextBox : public GUIComponent
{
public:
	GUITextBox(glm::vec4& destRectPerc, const glm::vec4& destRectPix,
		const std::string& text, int maxLength) : 
	GUIComponent(destRectPerc, destRectPix), m_text(text), m_maxLength(maxLength) { }
	~GUITextBox() { }

	/// <summary>
	/// Adds to Core Engine.
	/// </summary>
	/// <param name="engine">The Core Engine.</param>
	virtual void addToEngine(CoreEngine* engine) 
	{ 
		m_editbox = static_cast<CEGUI::Editbox*>(createWidget(engine->getGUIEngine()->getSchemeStyle() + "/Editbox"));
		m_editbox->setText(m_text);
		if (m_maxLength > 0)
		{
			m_editbox->setMaxTextLength(m_maxLength);
		}
	}

	std::string getText()
	{
		return std::string(m_editbox->getText().c_str());
	}

private:
	CEGUI::Editbox* m_editbox;

	std::string m_text;

	int m_maxLength;

};