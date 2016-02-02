#pragma once
#include "GUIComponent.h"
#include <glm\glm.hpp>

class GUILabel : public GUIComponent
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="GUILabel"/> class.
	/// </summary>
	/// <param name="text">The text.</param>
	/// <param name="destRectPerc">The dest rect perc.</param>
	/// <param name="destRectPix">The dest rect pix.</param>
	GUILabel(const std::string& text, const glm::vec4& destRectPerc, const glm::vec4& destRectPix) :
		GUIComponent(destRectPerc, destRectPix), m_text(text) { }

	/// <summary>
	/// Finalizes an instance of the <see cref="GUILabel"/> class.
	/// </summary>
	~GUILabel() { }

	/// <summary>
	/// Adds to engine.
	/// </summary>
	/// <param name="engine">The engine.</param>
	virtual void addToEngine(CoreEngine* engine)
	{
		auto wi = createWidget(engine->getGUIEngine()->getSchemeStyle() + "/Label");
		wi->setText(m_text);
	}

	void setText(const std::string& text)
	{
		m_text = text;
		getWidget()->setText(m_text);
	}

protected:
	std::string getText() { return m_text; }

private:
	/// <summary>
	/// The m_text
	/// </summary>
	std::string m_text;
};