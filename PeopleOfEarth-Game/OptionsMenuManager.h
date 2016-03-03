#pragma once
#include <MegaEngine.h>
#include "TextLerpAlpha.h"

class OptionsMenuManager : public GameComponent
{
public:
	OptionsMenuManager(GameObject* effectsSlider = nullptr, GameObject* effectsBox = nullptr, 
		GameObject* bgmSlider = nullptr, GameObject* bgmBox = nullptr, GameObject* backButton = nullptr, GameObject* controlsButton = nullptr)
	{
		m_effectsSlider = effectsSlider->getGUIComponent<GUISlider>();
		m_effectsBox = effectsBox->getGUIComponent<GUILabel>();
		m_bgmSlider = bgmSlider->getGUIComponent<GUISlider>();
		m_bgmBox = bgmBox->getGUIComponent<GUILabel>();

		m_buttons.push_back(backButton->getGUIComponent<GUIButton>());
		m_buttons.push_back(controlsButton->getGUIComponent<GUIButton>());
		m_focusButton = 0;
		if (!m_usingMouse)
		{
			m_buttons[m_focusButton]->getParent()->addGameComponent(new TextLerpAlpha, true);
		}
	}
	~OptionsMenuManager() { }

	virtual void onStart() override
	{
		m_effectsSlider->setThumbPosition(getCoreEngine()->getAudioEngine()->getSoundVolume());
		m_effectsBox->setText(std::to_string((int)(m_effectsSlider->getThumbPosition() * 100.0f)));
		m_bgmSlider->setThumbPosition(getCoreEngine()->getAudioEngine()->getStreamVolume());
		m_bgmBox->setText(std::to_string((int)(m_bgmSlider->getThumbPosition() * 100.0f)));
	}

	/// <summary>
	/// Virtual function for custom input processing.
	/// </summary>
	/// <param name="input">The input manager.</param>
	/// <param name="delta">The frame time delta.</param>
	virtual void processInput(const InputManager& input, float delta) override
	{
		if (input.PadButtonPress(SDL_CONTROLLER_BUTTON_B))
		{
			getCoreEngine()->getSceneManager()->pop();
		}

		if (!m_usingMouse && input.MouseButtonPress(SDL_BUTTON_LEFT))
		{
			m_usingMouse = true;
			m_buttons[m_focusButton]->getParent()->removeGameComponent(m_buttons[m_focusButton]->getParent()->getGameComponent<TextLerpAlpha>());
		}
		else if (m_usingMouse && (input.KeyPress(SDLK_a) || input.KeyPress(SDLK_d) || input.PadButtonPress(SDL_CONTROLLER_BUTTON_A) || input.PadButtonPress(SDL_CONTROLLER_BUTTON_DPAD_LEFT) || input.PadButtonPress(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) || input.GetThumbLPosition().x < -0.1f || input.GetThumbLPosition().x > 0.1f))
		{
			m_usingMouse = false;
			m_buttons[m_focusButton]->getParent()->addGameComponent(new TextLerpAlpha, true);
		}

		if (input.KeyPress(SDLK_a) || input.GetThumbLPosition().x < -0.1f || input.PadButtonPress(SDL_CONTROLLER_BUTTON_DPAD_LEFT))
		{
			m_buttons[m_focusButton]->getParent()->removeGameComponent(m_buttons[m_focusButton]->getParent()->getGameComponent<TextLerpAlpha>());

			if (m_focusButton > 0) m_focusButton--;
			else m_focusButton = 0;

			m_buttons[m_focusButton]->getParent()->addGameComponent(new TextLerpAlpha, true);
		}

		if (input.KeyPress(SDLK_d) || input.GetThumbLPosition().x > 0.1f || input.PadButtonPress(SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
		{
			m_buttons[m_focusButton]->getParent()->removeGameComponent(m_buttons[m_focusButton]->getParent()->getGameComponent<TextLerpAlpha>());

			if (m_focusButton < m_buttons.size() - 1) m_focusButton++;
			else m_focusButton = m_buttons.size() - 1;

			m_buttons[m_focusButton]->getParent()->addGameComponent(new TextLerpAlpha, true);
		}

		if (input.KeyPress(SDLK_RETURN) || input.PadButtonPress(SDL_CONTROLLER_BUTTON_A))
		{
			m_buttons[m_focusButton]->click();
		}
	}

	virtual void update(float delta) override
	{
		float bob = m_effectsSlider->getThumbPosition();
		printf("bob = %f\n", bob);

		if (m_effectsSlider->valueChanged())
		{
			getCoreEngine()->getAudioEngine()->setSoundVolume(m_effectsSlider->getThumbPosition());
			m_effectsBox->setText(std::to_string((int)(m_effectsSlider->getThumbPosition() * 100.0f)));
		}

		if (m_bgmSlider->valueChanged())
		{
			getCoreEngine()->getAudioEngine()->setStreamVolume(m_bgmSlider->getThumbPosition());
			m_bgmBox->setText(std::to_string((int)(m_bgmSlider->getThumbPosition() * 100.0f)));
		}
	}

private:
	GUISlider* m_effectsSlider;
	GUILabel* m_effectsBox;
	GUISlider* m_bgmSlider;
	GUILabel* m_bgmBox;

	bool m_usingMouse = false;
	std::vector<GUIButton*> m_buttons;
	size_t m_focusButton;

};
