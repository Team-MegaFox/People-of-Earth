#pragma once
#include <MegaEngine.h>

class OptionsMenuManager : public GameComponent
{
public:
	OptionsMenuManager(GameObject* effectsSlider = nullptr, GameObject* effectsBox = nullptr, 
		GameObject* bgmSlider = nullptr, GameObject* bgmBox = nullptr) 
	{
		m_effectsSlider = effectsSlider->getGUIComponent<GUISlider>();
		m_effectsBox = effectsBox->getGUIComponent<GUITextBox>();
		m_bgmSlider = bgmSlider->getGUIComponent<GUISlider>();
		m_bgmBox = bgmBox->getGUIComponent<GUITextBox>();
	}
	~OptionsMenuManager() { }

	virtual void onStart() override
	{
		m_effectsBox->setText(std::to_string((int)(m_effectsSlider->getThumbPosiiton() * 100.0f)));
		m_bgmBox->setText(std::to_string((int)(m_bgmSlider->getThumbPosiiton() * 100.0f)));
	}

	virtual void update(float delta) override
	{
		//std::cout << m_effectsSlider->valueChanged() << std::endl;
		if (m_effectsSlider->valueChanged())
		{
			m_effectsBox->setText(std::to_string((int)(m_effectsSlider->getThumbPosiiton() * 100.0f)));
		}
		if (m_bgmSlider->valueChanged())
		{
			m_bgmBox->setText(std::to_string((int)(m_bgmSlider->getThumbPosiiton() * 100.0f)));
		}

		std::cout << m_effectsBox->textChanged() << std::endl;
		if (m_effectsBox->textChanged() && m_effectsBox->getText() != "")
		{
			m_effectsSlider->setThumbPosition(std::stof(m_effectsBox->getText()) / 100.0f);
		}
		if (m_bgmBox->textChanged() && m_bgmBox->getText() != "")
		{
			m_bgmSlider->setThumbPosition(std::stof(m_bgmBox->getText()) / 100.0f);
		}
		
	}

private:
	GUISlider* m_effectsSlider;
	GUITextBox* m_effectsBox;
	GUISlider* m_bgmSlider;
	GUITextBox* m_bgmBox;

};
