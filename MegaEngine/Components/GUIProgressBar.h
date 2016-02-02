#pragma once
#include "GUIComponent.h"

class GUIProgressBar : public GUIComponent
{
public:
	GUIProgressBar(const glm::vec4& destRectPerc, const glm::vec4& destRectPix, float startPerc = 1.0f, float stepPerc = 0.01f) :
	GUIComponent(destRectPerc, destRectPix), m_percent(startPerc) { }
	~GUIProgressBar() { }

	virtual void addToEngine(CoreEngine* engine)
	{
		m_progressBar = static_cast<CEGUI::ProgressBar*>(createWidget(engine->getGUIEngine()->getSchemeStyle() + "/ProgressBar"));
		m_progressBar->setProgress(m_percent);
		m_progressBar->setStepSize(m_stepPerc);
	}

	float getPercent() { return m_percent; }
	float getStepPercent() { return m_stepPerc; }

	void setPercent(float percent) { m_percent = percent; m_progressBar->setProgress(m_percent); }
	void setStepPercent(float stepPerc) { m_stepPerc = stepPerc; m_progressBar->setStepSize(stepPerc); }

private:
	CEGUI::ProgressBar* m_progressBar;

	float m_percent;

	float m_stepPerc;

};