#pragma once
#include <MegaEngine.h>
#include <iostream>

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
	}

	/// <summary>
	/// Virtual function for custom input processing.
	/// </summary>
	/// <param name="input">The input manager.</param>
	/// <param name="delta">The frame time delta.</param>
	virtual void processInput(const InputManager& input, float delta) override
	{
		if (input.KeyPress(SDLK_m))
		{
			m_showSplash = !m_showSplash;
			if (m_showSplash)
			{
				m_splashScreen->setEnabled(true);
				m_mainMenuScreen->setEnabled(false);
			}
			else
			{
				m_splashScreen->setEnabled(false);
				m_mainMenuScreen->setEnabled(true);
			}
		}
	}

private:
	bool m_showSplash = true;

	GameObject* m_splashScreen;

	GameObject* m_mainMenuScreen;

};
