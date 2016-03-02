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
#include "GUIComponent.h"
#include <glm\glm.hpp>

class GUILabel : public GUIComponent
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="GUILabel"/> class.
	/// </summary>
	/// <param name="destRectPerc">The dest rect perc.</param>
	/// <param name="destRectPix">The dest rect pix.</param>
	/// <param name="text">The text.</param>
	GUILabel(const PxVec4& destRectPerc, const PxVec4& destRectPix, const std::string& text, Uint8 size = 10) :
		GUIComponent(destRectPerc, destRectPix), m_text(text), m_textSize(size) { }

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
		GUIComponent::addToEngine(engine);
		auto wi = createWidget(engine->getGUIEngine()->getSchemeStyle() + "/Label");
		wi->setText(m_text);
		engine->getGUIEngine()->addFont(engine->getGUIEngine()->getDefaultFontName(), m_textSize);
		wi->setFont(engine->getGUIEngine()->getDefaultFontName() + "-" + std::to_string(m_textSize));
	}
	
	/// <summary>
	/// Gets the widget's text.
	/// </summary>
	/// <returns>The text string of the widget.</returns>
	std::string getText() const { return m_text; }

	/// <summary>
	/// Gets the widget's text size.
	/// </summary>
	/// <returns>The size of the text string in the widget.</returns>
	Uint8 getTextSize() const { return m_textSize; }

	/// <summary>
	/// Gets the widget's alpha value.
	/// </summary>
	/// <returns>The transperncy value of the text string of the widget.</returns>
	float getAlpha() const { return getWidget()->getAlpha(); }
	
	/// <summary>
	/// Sets the widget's text.
	/// </summary>
	/// <param name="text">The text string of the widget.</param>
	void setText(const std::string& text)
	{
		m_text = text;
		getWidget()->setText(m_text);
	}

	/// <summary>
	/// Sets the widget's text alpha.
	/// </summary>
	/// <param name="text">The alpha value of the text string.</param>
	void setAlpha(const float alpha) { getWidget()->setAlpha(alpha); }

private:
	/// <summary>
	/// The widget's text.
	/// </summary>
	std::string m_text;

	/// <summary>
	/// The widget's text size.
	/// </summary>
	Uint8 m_textSize;
};