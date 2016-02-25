#pragma once
#include <MegaEngine.h>
#include <iostream>
#include "TextLerpAlpha.h"

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

		m_playButton = getGameObjectByName("Play Button")->getGUIComponent<GUIButton>();
		m_exitButton = getGameObjectByName("Exit Button")->getGUIComponent<GUIButton>();
		m_focusButton = m_playButton;
		if (!m_usingMouse)
		{
			m_focusButton->getParent()->addGameComponent(new TextLerpAlpha, true);
		}
	}

	/// <summary>
	/// Virtual function for custom input processing.
	/// </summary>
	/// <param name="input">The input manager.</param>
	/// <param name="delta">The frame time delta.</param>
	virtual void processInput(const InputManager& input, float delta) override
	{
		if (m_showSplash && (input.PadButtonPress(SDL_CONTROLLER_BUTTON_START) || input.KeyPress(SDLK_SPACE) || input.MouseButtonPress(SDL_BUTTON_LEFT)))
		{
			m_showSplash = false;
			m_splashScreen->setEnabled(false);
			m_mainMenuScreen->setEnabled(true);

			if (input.MouseButtonPress(SDL_BUTTON_LEFT) || input.KeyPress(SDLK_SPACE))
			{
				m_usingMouse = true;
			}
			else if (input.PadButtonPress(SDL_CONTROLLER_BUTTON_START))
			{
				m_usingMouse = false;
			}
		}

		if (!m_showSplash)
		{
			if (input.PadButtonPress(SDL_CONTROLLER_BUTTON_A) || input.KeyPress(SDLK_RETURN))
			{
				m_focusButton->click();
			}

			if (input.PadButtonPress(SDL_CONTROLLER_BUTTON_B) || input.KeyPress(SDLK_BACKSPACE))
			{
				m_showSplash = true;
				m_splashScreen->setEnabled(true);
				m_mainMenuScreen->setEnabled(false);

				if (input.KeyPress(SDLK_BACKSPACE))
				{
					m_usingMouse = true;
				}
				else if (input.PadButtonPress(SDL_CONTROLLER_BUTTON_B))
				{
					m_usingMouse = false;
				}
			}

			if (m_focusButton == m_playButton && 
				(input.GetThumbLPosition().y < -0.1f || input.PadButtonPress(SDL_CONTROLLER_BUTTON_DPAD_DOWN) || input.KeyPress(SDLK_s)))
			{
				if (input.KeyPress(SDLK_s))
				{
					m_usingMouse = true;
					m_focusButton->getParent()->removeGameComponent(m_focusButton->getParent()->getGameComponent<TextLerpAlpha>());
				}
				else if (input.GetThumbLPosition().y < -0.1f || input.PadButtonPress(SDL_CONTROLLER_BUTTON_DPAD_DOWN))
				{
					m_usingMouse = false;
				}

				if (!m_usingMouse)
				{
					m_focusButton->getParent()->removeGameComponent(m_focusButton->getParent()->getGameComponent<TextLerpAlpha>());
				}

				m_focusButton = m_exitButton;

				if (!m_usingMouse)
				{
					m_focusButton->getParent()->addGameComponent(new TextLerpAlpha, true);
				}
			}
			else if (m_focusButton == m_exitButton && 
				(input.GetThumbLPosition().y > 0.1f || input.PadButtonPress(SDL_CONTROLLER_BUTTON_DPAD_UP) || input.KeyPress(SDLK_w)))
			{
				if (input.KeyPress(SDLK_w))
				{
					m_usingMouse = true;
				}
				else if (input.GetThumbLPosition().y > 0.1f || input.PadButtonPress(SDL_CONTROLLER_BUTTON_DPAD_UP))
				{
					m_usingMouse = false;
				}

				if (!m_usingMouse)
				{
					m_focusButton->getParent()->removeGameComponent(m_focusButton->getParent()->getGameComponent<TextLerpAlpha>());
				}

				m_focusButton = m_playButton;

				if (!m_usingMouse)
				{
					m_focusButton->getParent()->addGameComponent(new TextLerpAlpha, true);
				}
			}
		}
	}

private:
	bool m_showSplash = true;

	bool m_usingMouse = false;

	GameObject* m_splashScreen;

	GameObject* m_mainMenuScreen;

	GUIButton* m_playButton;

	GUIButton* m_exitButton;

	GUIButton* m_focusButton;

};
