// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Jesse Derochie
// Last Modified On : 01-28-2016
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
	GUILabel(const glm::vec4& destRectPerc, const glm::vec4& destRectPix, const std::string& text) :
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
		GUIComponent::addToEngine(engine);
		auto wi = createWidget(engine->getGUIEngine()->getSchemeStyle() + "/Label");
		wi->setText(m_text);
	}
	
	/// <summary>
	/// Gets the widget's text.
	/// </summary>
	/// <returns>The text string of the widget.</returns>
	std::string getText() const { return m_text; }
	
	/// <summary>
	/// Sets the widget's text.
	/// </summary>
	/// <param name="text">The text string of the widget.</param>
	void setText(const std::string& text)
	{
		m_text = text;
		getWidget()->setText(m_text);
	}

private:
	/// <summary>
	/// The widget's text.
	/// </summary>
	std::string m_text;
};