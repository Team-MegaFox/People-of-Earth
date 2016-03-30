#pragma once
#include <MegaEngine.h>
#include <iostream>
#include "TextLerpAlpha.h"
#include "PauseScene.h"

class MainMenuManager : public GameComponent
{
public:
	MainMenuManager(Uint8 numMissions) : m_numMissions(numMissions) { }
	~MainMenuManager() { }

	virtual void onStart() override
	{
		//Main menu
		m_logo = getGameObjectByName("Logo");
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

		//Mission Select
		m_missionSelectScreen = getGameObjectByName("Mission Select Menu");
		m_missionSelectScreen->setEnabled(false);
		for (size_t i = 1; i <= m_numMissions; i++)
		{
			m_missionWidgets.push_back(getGameObjectByName("Mission " + std::to_string(i))->getGUIComponent<GUIContainer>());
		}
		m_focusMission = m_missionWidgets[m_focusMissionIndex];
		m_backButton = getGameObjectByName("Back Button")->getGUIComponent<GUIButton>();

		m_moveSound = getGameObjectByName("Moved button sound")->getGameComponent<AudioSource>();
		m_selectedSound = getGameObjectByName("Selected button sound")->getGameComponent<AudioSource>();
	}

	virtual void processInput(const InputManager& input, float delta) override
	{
		//If the player uses the mouse turn off the alpha lerping for text.
		if (!m_usingMouse && input.MouseButtonPress(SDL_BUTTON_LEFT))
		{
			m_usingMouse = true;
			m_buttons[m_focusButton]->getParent()->removeGameComponent(m_buttons[m_focusButton]->getParent()->getGameComponent<TextLerpAlpha>());
			m_focusMission->getParent()->getAllChildren()[0]->removeGameComponent(m_focusMission->getParent()->getAllChildren()[0]->getGameComponent<TextLerpAlpha>());
		}
		//Put the text lerping back if uses key or anything
		else if (m_usingMouse && (input.KeyPress(SDLK_w) || input.KeyPress(SDLK_a) || input.KeyPress(SDLK_s) || input.KeyPress(SDLK_d) || input.PadButtonPress(SDL_CONTROLLER_BUTTON_A) || input.ThumbLMoved()))
		{
			m_usingMouse = false;
			m_buttons[m_focusButton]->getParent()->addGameComponent(new TextLerpAlpha, true);
			m_focusMission->getParent()->getAllChildren()[0]->addGameComponent(new TextLerpAlpha, true);
		}

		//If the main menu is showing
		if (m_showMainMenu)
		{
			//If the splash is showing
			if (m_showSplash)
			{
				if (input.KeyPress(SDLK_SPACE) || input.PadButtonPress(SDL_CONTROLLER_BUTTON_START) || input.MouseButtonPress(SDL_BUTTON_LEFT))
				{
					m_splashScreen->setEnabled(false);
					m_mainMenuScreen->setEnabled(true);
					m_showSplash = false;
				}
			}
			//If the main menu is showing
			else
			{
				//Go UP, take out text alpha lerp from focused button, decrement focus button, add text alpha lerp to new focus button and play audio.
				if (input.KeyPress(SDLK_w) || input.GetThumbLPosition().y > 0.1f || input.PadButtonPress(SDL_CONTROLLER_BUTTON_DPAD_UP))
				{
					m_buttons[m_focusButton]->getParent()->removeGameComponent(m_buttons[m_focusButton]->getParent()->getGameComponent<TextLerpAlpha>());

					if (m_focusButton > 0) m_focusButton--;
					else m_focusButton = 0;

					m_buttons[m_focusButton]->getParent()->addGameComponent(new TextLerpAlpha, true);

					m_moveSound->play();
				}

				//Go DOWN, take out text alpha lerp from focused button, decrement focus button, add text alpha lerp to new focus button and play audio.
				if (input.KeyPress(SDLK_s) || input.GetThumbLPosition().y < -0.1f || input.PadButtonPress(SDL_CONTROLLER_BUTTON_DPAD_DOWN))
				{
					m_buttons[m_focusButton]->getParent()->removeGameComponent(m_buttons[m_focusButton]->getParent()->getGameComponent<TextLerpAlpha>());

					if (m_focusButton < m_buttons.size() - 1) m_focusButton++;
					else m_focusButton = m_buttons.size() - 1;

					m_buttons[m_focusButton]->getParent()->addGameComponent(new TextLerpAlpha, true);

					m_moveSound->play();
				}

				//If the focus button is selected, show mission select menu if it is the play button, click the button and play audio.
				if (input.KeyPress(SDLK_RETURN) || input.PadButtonPress(SDL_CONTROLLER_BUTTON_A))
				{
					if (m_focusButton == 0)
					{
						m_showMainMenu = false;

						m_focusMission->getParent()->getAllChildren()[0]->addGameComponent(new TextLerpAlpha, true);
					}
					m_buttons[m_focusButton]->click();

					m_selectedSound->play();
				}
			}
		}
		//If the mission select menu is showing.
		else
		{
			//If the B button is pressed then press back button, show main menu and play audio.
			if (input.PadButtonPress(SDL_CONTROLLER_BUTTON_B))
			{
				m_backButton->click();
				m_showMainMenu = true;

				m_selectedSound->play();
			}

			//Go UP, select focused mission screen, remove text alpha lerp from back button.
			if (input.KeyPress(SDLK_w) || input.GetThumbLPosition().y > 0.1f || input.PadButtonPress(SDL_CONTROLLER_BUTTON_DPAD_UP))
			{
				m_onBackButton = false;
				m_backButton->getParent()->removeGameComponent(m_backButton->getParent()->getGameComponent<TextLerpAlpha>());

				m_focusMission->getParent()->getAllChildren()[0]->addGameComponent(new TextLerpAlpha, true);
			}
			//Go DOWN, select back button, remove text alpha lerp from focus mission.
			else if (input.KeyPress(SDLK_s) || input.GetThumbLPosition().y < -0.1f || input.PadButtonPress(SDL_CONTROLLER_BUTTON_DPAD_DOWN))
			{
				m_onBackButton = true;
				m_focusMission->getParent()->getAllChildren()[0]->removeGameComponent(m_focusMission->getParent()->getAllChildren()[0]->getGameComponent<TextLerpAlpha>());

				m_backButton->getParent()->addGameComponent(new TextLerpAlpha, true);
			}

			//If the mission menus aren't moving.
			if (!m_move)
			{
				//Go RIGHT, remove text alpha lerp from focus mission, if the focus mission isn't the last then incrase focus mission otherwise keep selecting back mission, add text alpha lerp and play sound.
				if (input.KeyPress(SDLK_d) || input.GetThumbLPosition().x > 0.2f || input.PadButtonPress(SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
				{
					m_focusMission->getParent()->getAllChildren()[0]->removeGameComponent(m_focusMission->getParent()->getAllChildren()[0]->getGameComponent<TextLerpAlpha>());

					if (m_focusMission != m_missionWidgets.back())
					{
						m_focusMissionIndex++;
						m_focusMission = m_missionWidgets[m_focusMissionIndex];

						m_move = true;
						m_moveLeft = false;
					}
					else
					{
						m_focusMission = m_missionWidgets.back();
					}

					m_focusMission->getParent()->getAllChildren()[0]->addGameComponent(new TextLerpAlpha, true);

					m_moveSound->play();
				}
				//Go LEFT, remove text alpha lerp from focus mission, if the focus mission isn't the first then incrase focus mission otherwise keep selecting back mission, add text alpha lerp and play sound.
				else if (input.KeyPress(SDLK_a) || input.GetThumbLPosition().x < -0.2f || input.PadButtonPress(SDL_CONTROLLER_BUTTON_DPAD_LEFT))
				{
					m_focusMission->getParent()->getAllChildren()[0]->removeGameComponent(m_focusMission->getParent()->getAllChildren()[0]->getGameComponent<TextLerpAlpha>());

					if (m_focusMission != m_missionWidgets.front())
					{
						m_focusMissionIndex--;
						m_focusMission = m_missionWidgets[m_focusMissionIndex];

						m_move = true;
						m_moveLeft = true;
					}
					else
					{
						m_focusMission = m_missionWidgets.front();
					}

					m_focusMission->getParent()->getAllChildren()[0]->addGameComponent(new TextLerpAlpha, true);

					m_moveSound->play();
				}

				//If enter is pressed, if the focus is on back button, then click and show main menu otherwise click the focus mission and play sound.
				if (input.KeyPress(SDLK_RETURN) || input.PadButtonPress(SDL_CONTROLLER_BUTTON_A))
				{
					if (m_onBackButton)
					{
						m_backButton->click();
						m_showMainMenu = true;
					}
					else
					{
						m_missionWidgets[m_focusMissionIndex]->getParent()->getAllChildren()[0]->getGUIComponent<GUIButton>()->click();
					}

					m_selectedSound->play();
				}
			}
		}
	}

	/// <summary>
	/// Virtual function for custom update functionality.
	/// Moves the focus mission when the player goes left or right between the menus.
	/// </summary>
	/// <param name="delta">The frame time delta.</param>
	virtual void update(float delta)
	{
		if (m_move)
		{
			m_movePosition += m_moveSpeed * delta;
			if (m_moveLeft)
			{
				for (size_t i = 0; i < m_missionWidgets.size(); i++)
				{
					m_missionWidgets[i]->setPercentPosition(m_missionWidgets[i]->getPercentPosition() + PxVec2(m_moveSpeed * delta, 0.0f));
				}
			}
			else
			{
				for (size_t i = 0; i < m_missionWidgets.size(); i++)
				{
					m_missionWidgets[i]->setPercentPosition(m_missionWidgets[i]->getPercentPosition() - PxVec2(m_moveSpeed * delta, 0.0f));
				}
			}

			if (m_movePosition >= 1.0f)
			{
				m_move = false;
				m_movePosition = 0.0f;
			}
		}
	}

private:
	//Main menu
	bool m_showMainMenu = true;

	bool m_showSplash = true;

	bool m_usingMouse = false;

	GameObject* m_logo;

	GameObject* m_splashScreen;

	GameObject* m_mainMenuScreen;

	std::vector<GUIButton*> m_buttons;

	size_t m_focusButton;

	//Mission Select
	GameObject* m_missionSelectScreen;

	std::vector<GUIContainer*> m_missionWidgets;

	GUIContainer* m_focusMission;

	GUIButton* m_backButton;

	Uint8 m_focusMissionIndex = 0;

	Uint8 m_numMissions = 0;

	bool m_onBackButton = false;

	bool m_moveLeft = false, m_move = false;

	float m_movePosition = 0.0f;

	float m_moveSpeed = 2.0f;

	//Sounds
	AudioSource* m_moveSound;

	AudioSource* m_selectedSound;

};
