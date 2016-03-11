#pragma once
#include <MegaEngine.h>
#include <iostream>
#include "TextLerpAlpha.h"
#include "PauseScene.h"

class MainMenuManager : public GameComponent
{
public:
	MainMenuManager() { }
	~MainMenuManager() { }

	virtual void onStart() override
	{
		m_splashScreen = getGameObjectByName("Splash");
		m_mainMenuScreen = getGameObjectByName("Main Menu");
		m_mainMenuScreen->setEnabled(false);

		m_buttons.push_back(getGameObjectByName("Play Button")->getGUIComponent<GUIButton>());
		m_buttons.push_back(getGameObjectByName("Options Button")->getGUIComponent<GUIButton>());
		m_buttons.push_back(getGameObjectByName("Exit Button")->getGUIComponent<GUIButton>());
		m_focusButton = 0;
		if (!m_usingMouse)
		{
			m_buttons[m_focusButton]->getParent()->addGameComponent(new TextLerpAlpha, true);
		}

		m_testbar = getGameObjectByName("test bar")->getGUIComponent<GUIImage>();
		m_barOGSize = m_testbar->getPercentSize();
	}

	/// <summary>
	/// Virtual function for custom input processing.
	/// </summary>
	/// <param name="input">The input manager.</param>
	/// <param name="delta">The frame time delta.</param>
	virtual void processInput(const InputManager& input, float delta) override
	{
		if (!m_usingMouse && input.MouseButtonPress(SDL_BUTTON_LEFT))
		{
			m_usingMouse = true;
			m_buttons[m_focusButton]->getParent()->removeGameComponent(m_buttons[m_focusButton]->getParent()->getGameComponent<TextLerpAlpha>());
		}
		else if (m_usingMouse && (input.KeyPress(SDLK_w) || input.KeyPress(SDLK_s) || input.PadButtonPress(SDL_CONTROLLER_BUTTON_A) || input.ThumbLMoved()))
		{
			m_usingMouse = false;
			m_buttons[m_focusButton]->getParent()->addGameComponent(new TextLerpAlpha, true);
		}

		if (m_showSplash)
		{
			if (input.KeyPress(SDLK_SPACE) || input.PadButtonPress(SDL_CONTROLLER_BUTTON_START) || input.MouseButtonPress(SDL_BUTTON_LEFT))
			{
				m_splashScreen->setEnabled(false);
				m_mainMenuScreen->setEnabled(true);
				m_showSplash = false;
			}
		}
		else
		{
			if (input.KeyPress(SDLK_w) || input.GetThumbLPosition().y > 0.1f || input.PadButtonPress(SDL_CONTROLLER_BUTTON_DPAD_UP))
			{
				m_buttons[m_focusButton]->getParent()->removeGameComponent(m_buttons[m_focusButton]->getParent()->getGameComponent<TextLerpAlpha>());

				if (m_focusButton > 0) m_focusButton--;
				else m_focusButton = 0;

				m_buttons[m_focusButton]->getParent()->addGameComponent(new TextLerpAlpha, true);
			}

			if (input.KeyPress(SDLK_s) || input.GetThumbLPosition().y < -0.1f || input.PadButtonPress(SDL_CONTROLLER_BUTTON_DPAD_DOWN))
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
	}

	/// <summary>
	/// Virtual function for custom update functionality.
	/// </summary>
	/// <param name="delta">The frame time delta.</param>
	virtual void update(float delta) 
	{
		if (m_barPercent > 0.0f)
		{
			m_barPercent -= 15.0f * delta;
			if (m_barPercent <= 0.0f) m_barPercent = 0.0001f;
			m_testbar->setPercentSize(PxVec2((m_barPercent / 100.0f) * m_barOGSize.x, m_barOGSize.y));
			m_testbar->setAspectRatio(((m_barPercent / 100.0f) * m_barOGSize.x) / m_barOGSize.y);
		}
	}

private:
	bool m_showSplash = true;

	bool m_usingMouse = false;

	GameObject* m_splashScreen;

	GameObject* m_mainMenuScreen;

	std::vector<GUIButton*> m_buttons;

	size_t m_focusButton;

	GUIImage* m_testbar;

	PxVec2 m_barOGSize;

	float m_barPercent = 100.0f;

};
