#pragma once
#include <MegaEngine.h>

class OptionsMenuManager : public GameComponent
{
public:
	OptionsMenuManager(GameObject* effectsSlider = nullptr, GameObject* effectsBox = nullptr, 
		GameObject* bgmSlider = nullptr, GameObject* bgmBox = nullptr) 
	{
		m_effectsSlider = effectsSlider->getGUIComponent<GUISlider>();
		m_effectsBox = effectsBox->getGUIComponent<GUILabel>();
		m_bgmSlider = bgmSlider->getGUIComponent<GUISlider>();
		m_bgmBox = bgmBox->getGUIComponent<GUILabel>();
	}
	~OptionsMenuManager() { }

	virtual void onStart() override
	{
		m_effectsSlider->setThumbPosition(getCoreEngine()->getAudioEngine()->getSoundVolume());
		m_effectsBox->setText(std::to_string((int)(m_effectsSlider->getThumbPosiiton() * 100.0f)));
		m_bgmSlider->setThumbPosition(getCoreEngine()->getAudioEngine()->getStreamVolume());
		m_bgmBox->setText(std::to_string((int)(m_bgmSlider->getThumbPosiiton() * 100.0f)));
	}

	virtual void update(float delta) override
	{
		if (m_effectsSlider->valueChanged())
		{
			getCoreEngine()->getAudioEngine()->setSoundVolume(m_effectsSlider->getThumbPosiiton());
			m_effectsBox->setText(std::to_string((int)(m_effectsSlider->getThumbPosiiton() * 100.0f)));
		}

		if (m_bgmSlider->valueChanged())
		{
			getCoreEngine()->getAudioEngine()->setStreamVolume(m_bgmSlider->getThumbPosiiton());
			m_bgmBox->setText(std::to_string((int)(m_bgmSlider->getThumbPosiiton() * 100.0f)));
		}
	}

private:
	GUISlider* m_effectsSlider;
	GUILabel* m_effectsBox;
	GUISlider* m_bgmSlider;
	GUILabel* m_bgmBox;

};
