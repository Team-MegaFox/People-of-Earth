#include "freeLook.h"
#include <Core\Utility.h>
#include <Core\SceneManager.h>
#include "PopupMenuScene.h"

void FreeLook::processInput(const InputManager& input, float delta)
{
	if (input.KeyPress(SDLK_q))
	{
		input.SetCursor(true);
		m_mouseLocked = false;
		getCoreEngine()->getSceneManager()->push(new PopupMenuScene, Modality::Popup);
	}

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
			getTransform()->rotate(glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(deltaPos.x * m_sensitivity));
		}
		if (rotX)
		{
			getTransform()->rotate(Utility::getRight(*getTransform()->getRotation()), glm::radians(deltaPos.y * m_sensitivity));
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
