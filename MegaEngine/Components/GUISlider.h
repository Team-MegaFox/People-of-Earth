// ***********************************************************************
// Author           : Pavan Jakhu
// Created          : 02-03-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 03-01-2016
// ***********************************************************************
// <copyright file="GUISlider.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once
#include "GUIComponent.h"

/// <summary>
/// The GUISlider class is a slider on the GUI that has a max value from 0 that the user can slide between.
/// </summary>
/// <seealso cref="GUIComponent" />
class GUISlider : public GUIComponent
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="GUISlider"/> class.
	/// </summary>
	/// <param name="destRectPerc">The size of the widget relative the parent widget.</param>
	/// <param name="destRectPix">The size of the widget in pixels.</param>
	/// <param name="position">The slider's thumb position.</param>
	/// <param name="maxValue">The maximum value of the slider.</param>
	/// <param name="stepAmt">The step amount of the slider.</param>
	GUISlider(const PxVec4& destRectPerc, const PxVec4& destRectPix,
		float position = 0.0f, float maxValue = 1.0f, float stepAmt = 0.01f) :
	GUIComponent(destRectPerc, destRectPix), m_position(position), m_maxValue(maxValue), m_stepAmt(stepAmt) { }
	/// <summary>
	/// Finalizes an instance of the <see cref="GUISlider"/> class.
	/// </summary>
	~GUISlider() { }

	/// <summary>
	/// Adds to Core Engine.
	/// </summary>
	/// <param name="engine">The Core Engine.</param>
	virtual void addToEngine(CoreEngine* engine)
	{
		GUIComponent::addToEngine(engine);
		m_slider = static_cast<CEGUI::Slider*>(createWidget(engine->getGUIEngine()->getSchemeStyle() + "/Slider"));
		m_slider->setCurrentValue(m_position);
		m_slider->setMaxValue(m_maxValue);
		m_slider->setClickStep(m_stepAmt);
		m_slider->subscribeEvent(CEGUI::Slider::EventValueChanged, CEGUI::Event::Subscriber(&GUISlider::onThumbChange, this));
		m_slider->subscribeEvent(CEGUI::Slider::EventInputCaptureLost, CEGUI::Event::Subscriber(&GUISlider::onFocusLost, this));
	}

	/// <summary>
	/// Gets the thumb posiiton.
	/// </summary>
	/// <returns>The slider's thumb position right now.</returns>
	float getThumbPosiiton() const { return m_slider->getCurrentValue(); }
	/// <summary>
	/// Gets the maximum value of the slider.
	/// </summary>
	/// <returns>The maximum value of the sider.</returns>
	float getMaxValue() const { return m_maxValue; }
	/// <summary>
	/// Gets the step amount of the slider.
	/// </summary>
	/// <returns>The step amount of the slider.</returns>
	float getStepAmount() const { return m_stepAmt; }
	/// <summary>
	/// If the value of the thumb changed.
	/// </summary>
	/// <returns>Wheather the thumb value changed.</returns>
	float valueChanged() const { return m_valueChanged; }

	/// <summary>
	/// Sets the slider's thumb position.
	/// </summary>
	/// <param name="position">The slider's thumb position.</param>
	void setThumbPosition(float position)
	{
		m_position = position;
		m_slider->setCurrentValue(m_position);
	}
	/// <summary>
	/// Sets the maximum value of the slider.
	/// </summary>
	/// <param name="maxValue">The maximum value.</param>
	void setMaxValue(float maxValue)
	{
		m_maxValue = maxValue;
		m_slider->setMaxValue(m_maxValue);
	}
	/// <summary>
	/// Sets the step amount.
	/// </summary>
	/// <param name="stepAmt">The step amount.</param>
	void setStepAmount(float stepAmt)
	{
		m_stepAmt = stepAmt;
		m_slider->setClickStep(m_stepAmt);
	}

private:
	bool onThumbChange(const CEGUI::EventArgs& e)
	{
		m_valueChanged = true;
		return true;
	}

	bool onFocusLost(const CEGUI::EventArgs& e)
	{
		m_valueChanged = false;
		return true;
	}

	/// <summary>
	/// The slider widget.
	/// </summary>
	CEGUI::Slider* m_slider;

	/// <summary>
	/// The slider's thumb position.
	/// </summary>
	float m_position;

	/// <summary>
	/// The maximum value the slider can reach.
	/// </summary>
	float m_maxValue;

	/// <summary>
	/// The amount to step by.
	/// </summary>
	float m_stepAmt;

	/// <summary>
	/// If slider value changed.
	/// </summary>
	bool m_valueChanged;

};