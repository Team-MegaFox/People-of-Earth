#include "freeLook.h"
#include <Viewport.h>
#include <Utility.h>
#include <iostream>

void FreeLook::processInput(const InputManager& input, float delta)
{

	if (input.KeyDown(m_unlockMouseKey))
	{
		input.SetCursor(true);
		m_mouseLocked = false;
	}

	if (m_mouseLocked)
	{
		glm::vec2 deltaPos = input.GetMousePosition() - m_windowCenter;

		bool rotY = deltaPos.x != 0;
		bool rotX = deltaPos.y != 0;

		if (rotY)
		{
			getTransform()->rotate(getUp(getTransform()->getRotation()), ToDegree(deltaPos.x * m_sensitivity));
		}
		if (rotX)
		{
			getTransform()->rotate(getRight(getTransform()->getRotation()), ToDegree(deltaPos.y * m_sensitivity));
		}

		if (rotY || rotX)
		{
			input.SetMousePosition(m_windowCenter);
		}
	}

	if (input.MouseButtonDown(SDL_BUTTON_LEFT))
	{
		input.SetCursor(false);
		input.SetMousePosition(m_windowCenter);
		m_mouseLocked = true;
	}
}
