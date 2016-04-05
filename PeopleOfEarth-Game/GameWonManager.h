#pragma once
#include <MegaEngine.h>
#include <iostream>
#include "TextLerpAlpha.h"

class GameWonManager : public GameComponent
{
public:
	GameWonManager() { }
	~GameWonManager() { }

	virtual void onStart() override
	{
		m_buttons.push_back(getGameObjectByName("Exit Button")->getGUIComponent<GUIButton>());
		m_focusButton = 0;
		if (!m_usingMouse)
		{
			m_buttons[m_focusButton]->getParent()->addGameComponent(new TextLerpAlpha, true);
		}
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
		else if (m_usingMouse && (input.KeyPress(SDLK_w) || input.KeyPress(SDLK_s) || input.PadButtonPress(SDL_CONTROLLER_BUTTON_A) || input.ThumbLMoved()))
		{
			m_usingMouse = false;
			m_buttons[m_focusButton]->getParent()->addGameComponent(new TextLerpAlpha, true);
		}

		//Check if the player is using a controller
		if (!m_usingController && (input.PadButtonPress(SDL_CONTROLLER_BUTTON_A) || input.PadButtonPress(SDL_CONTROLLER_BUTTON_DPAD_UP) || input.PadButtonPress(SDL_CONTROLLER_BUTTON_DPAD_DOWN) || input.PadButtonPress(SDL_CONTROLLER_BUTTON_START) || input.ThumbLMoved()))
		{
			m_usingController = true;
		}
		else if (m_usingController && (input.KeyPress(SDLK_w) || input.KeyPress(SDLK_a) || input.KeyPress(SDLK_s) || input.KeyPress(SDLK_d) || input.KeyPress(SDLK_SPACE) || input.KeyPress(SDLK_RETURN)))
		{
			m_usingController = false;
		}
		//Dectecting if the player put the controller to rest
		if (m_usingController && input.PadButtonUp(SDL_CONTROLLER_BUTTON_DPAD_DOWN) && input.PadButtonUp(SDL_CONTROLLER_BUTTON_DPAD_UP) &&
			input.GetThumbLPosition().x < 0.1f && input.GetThumbLPosition().x > -0.1f && input.GetThumbLPosition().y < 0.1f && input.GetThumbLPosition().y > -0.1f)
		{
			m_ableToPlayMoveSound = true;
		}

		if (input.KeyPress(SDLK_w) || (input.GetThumbLPosition().y > 0.2f && m_ableToPlayMoveSound) || input.PadButtonPress(SDL_CONTROLLER_BUTTON_DPAD_UP))
		{
			if (m_focusButton > 0)
			{
				m_buttons[m_focusButton]->getParent()->removeGameComponent(m_buttons[m_focusButton]->getParent()->getGameComponent<TextLerpAlpha>());

				m_focusButton--;

				m_buttons[m_focusButton]->getParent()->addGameComponent(new TextLerpAlpha, true);
			}
			else m_focusButton = 0;

			m_ableToPlayMoveSound = false;
		}

		if (input.KeyPress(SDLK_s) || input.GetThumbLPosition().y < -0.1f || input.PadButtonPress(SDL_CONTROLLER_BUTTON_DPAD_DOWN))
		{
			if (m_focusButton < m_buttons.size() - 1)
			{
				m_buttons[m_focusButton]->getParent()->removeGameComponent(m_buttons[m_focusButton]->getParent()->getGameComponent<TextLerpAlpha>());

				m_focusButton++;

				m_buttons[m_focusButton]->getParent()->addGameComponent(new TextLerpAlpha, true);
			}
			else m_focusButton = m_buttons.size() - 1;

			m_ableToPlayMoveSound = false;
		}

		if (input.KeyPress(SDLK_RETURN) || input.PadButtonPress(SDL_CONTROLLER_BUTTON_A))
		{
			m_buttons[m_focusButton]->click();
		}
	}

private:
	bool m_ableToPlayMoveSound = true;

	bool m_usingController = false;

	bool m_usingMouse = false;

	std::vector<GUIButton*> m_buttons;

	size_t m_focusButton;

};