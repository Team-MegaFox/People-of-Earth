// ***********************************************************************
// Author           : Pavan Jakhu
// Created          : 02-02-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 03-01-2016
// ***********************************************************************
// <copyright file="GUIProgressBar.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once
#include "GUIComponent.h"

/// <summary>
/// TThe GUIProgressBar class displays a progress bar on the screen.
/// </summary>
/// <seealso cref="GUIComponent" />
class GUIProgressBar : public GUIComponent
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="GUIProgressBar"/> class.
	/// </summary>
	/// <param name="destRectPerc">The size of the widget relative the parent widget.</param>
	/// <param name="destRectPix">The size of the widget in pixels.</param>
	/// <param name="startPerc">The start percentage. Defaults to 1.0f (100%).</param>
	/// <param name="stepPerc">The step percentage. Defaults to 0.1f (1%).(</param>
	GUIProgressBar(const physx::PxVec4& destRectPerc, const physx::PxVec4& destRectPix, float startPerc = 1.0f, float stepPerc = 0.01f) :
	GUIComponent(destRectPerc, destRectPix), m_percent(startPerc) { }
	/// <summary>
	/// Finalizes an instance of the <see cref="GUIProgressBar"/> class.
	/// </summary>
	~GUIProgressBar() { }

	/// <summary>
	/// Adds to the Core Engine.
	/// </summary>
	/// <param name="engine">A pointer to the Core Engine.</param>
	virtual void addToEngine(CoreEngine* engine)
	{
		GUIComponent::addToEngine(engine);
		m_progressBar = static_cast<CEGUI::ProgressBar*>(createWidget(engine->getGUIEngine()->getSchemeStyle() + "/ProgressBar"));
		m_progressBar->setProgress(m_percent);
		m_progressBar->setStepSize(m_stepPerc);
	}
	
	/// <summary>
	/// Steps the progress bar by the step amount set.
	/// Default is 0.01f (1%).
	/// </summary>
	void step() const { m_progressBar->step(); }

	/// <summary>
	/// Gets the current percentage of the bar.
	/// </summary>
	/// <returns>The percentage of the bar according to the step value.</returns>
	float getPercent() const { return m_percent; }
	/// <summary>
	/// Gets the step percentage.
	/// </summary>
	/// <returns>The step value.</returns>
	float getStepPercent() const { return m_stepPerc; }

	/// <summary>
	/// Sets the current percentage of the bar.
	/// </summary>
	/// <param name="percent">The percentage of the bar right now.</param>
	void setPercent(float percent) { m_percent = percent; m_progressBar->setProgress(m_percent); }
	/// <summary>
	/// Sets the step percentage of the bar.
	/// </summary>
	/// <param name="stepPerc">The step percentage of the bar.</param>
	void setStepPercent(float stepPerc) { m_stepPerc = stepPerc; m_progressBar->setStepSize(stepPerc); }

private:
	/// <summary>
	/// The progress bar widget.
	/// </summary>
	CEGUI::ProgressBar* m_progressBar;

	/// <summary>
	/// The percentage of the bar
	/// </summary>
	float m_percent;

	/// <summary>
	/// The amount to step the progress bar.
	/// </summary>
	float m_stepPerc;

};