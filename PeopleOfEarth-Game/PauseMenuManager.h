#pragma once
#include <MegaEngine.h>
#include <iostream>
#include "TextLerpAlpha.h"

class PauseMenuManager : public GameComponent
{
public:
	PauseMenuManager() { }
	~PauseMenuManager() { }

	virtual void onStart() override
	{
		m_buttons.push_back(getGameObjectByName("Resume Button")->getGUIComponent<GUIButton>());
		m_buttons.push_back(getGameObjectByName("Options Button")->getGUIComponent<GUIButton>());
		m_buttons.push_back(getGameObjectByName("Mission Select Button")->getGUIComponent<GUIButton>());
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

private:
	bool m_usingMouse = false;

	std::vector<GUIButton*> m_buttons;

	size_t m_focusButton;

};
