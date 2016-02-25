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
		m_focusButton->getParent()->addGameComponent(new TextLerpAlpha, true);
	}

	/// <summary>
	/// Virtual function for custom input processing.
	/// </summary>
	/// <param name="input">The input manager.</param>
	/// <param name="delta">The frame time delta.</param>
	virtual void processInput(const InputManager& input, float delta) override
	{
		if (input.PadButtonPress(SDL_CONTROLLER_BUTTON_START) && m_showSplash)
		{
			m_showSplash = false;
			m_splashScreen->setEnabled(false);
			m_mainMenuScreen->setEnabled(true);
		}

		if (!m_showSplash)
		{
			if (input.PadButtonPress(SDL_CONTROLLER_BUTTON_A))
			{
				m_focusButton->click();
			}

			if (input.PadButtonPress(SDL_CONTROLLER_BUTTON_B))
			{
				m_showSplash = true;
				m_splashScreen->setEnabled(true);
				m_mainMenuScreen->setEnabled(false);
			}

			if (m_focusButton == m_playButton && (input.GetThumbLPosition().y < -0.1f || input.PadButtonPress(SDL_CONTROLLER_BUTTON_DPAD_DOWN)))
			{
				m_focusButton->getParent()->removeGameComponent(m_focusButton->getParent()->getGameComponent<TextLerpAlpha>());

				m_focusButton = m_exitButton;

				m_focusButton->getParent()->addGameComponent(new TextLerpAlpha, true);
			}
			else if (m_focusButton == m_exitButton && (input.GetThumbLPosition().y > 0.1f || input.PadButtonPress(SDL_CONTROLLER_BUTTON_DPAD_UP)))
			{
				m_focusButton->getParent()->removeGameComponent(m_focusButton->getParent()->getGameComponent<TextLerpAlpha>());

				m_focusButton = m_playButton;

				m_focusButton->getParent()->addGameComponent(new TextLerpAlpha, true);
			}
		}
	}

private:
	bool m_showSplash = true;

	GameObject* m_splashScreen;

	GameObject* m_mainMenuScreen;

	GUIButton* m_playButton;

	GUIButton* m_exitButton;

	GUIButton* m_focusButton;

};
