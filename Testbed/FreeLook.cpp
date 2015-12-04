#include "freeLook.h"
#include <Viewport.h>
#include <Utility.h>

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
			//getTransform()->rotate(glm::normalize(glm::vec3(0, 1, 0)), ToRadians(deltaPos.x * m_sensitivity));
			getTransform()->rotate(glm::quat(cos(ToRadians(0.5f * deltaPos.x / 2.0f)), 0.0f, sin(ToRadians(0.5f * deltaPos.x / 2.0f)), 0.0f));
		}
		if (rotX)
		{
			//Transform* trans = getTransform();
			//glm::vec3 rightVec = getRight(*trans->getRotation());
			//getTransform()->rotate(rightVec, ToRadians(deltaPos.y * m_sensitivity));
			getTransform()->rotate(glm::quat(cos(ToRadians(0.5f * deltaPos.y / 2.0f)), sin(ToRadians(0.5f * deltaPos.y / 2.0f)), 0.0f, 0.0f));
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
