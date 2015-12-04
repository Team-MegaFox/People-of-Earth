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
		/*
		
		We're rotating about the origin of the world. That's why everything is all fucked up and we have weird flickering.
		
		*/

		glm::vec2 deltaPos = input.GetMousePosition() - m_windowCenter;

		bool rotY = deltaPos.x != 0;
		bool rotX = deltaPos.y != 0;

		Transform* trans = getTransform();
		glm::vec3 upVec = getUp(*trans->getRotation());
		glm::vec3 rightVec = getRight(*trans->getRotation());
		glm::quat bobby = glm::quat((deltaPos.y * m_sensitivity) * (3.1415926536f / 180.0f), glm::normalize(rightVec));
		glm::quat annie = glm::quat((deltaPos.x * m_sensitivity) * (3.1415926536f / 180.0f), glm::normalize(upVec));

		if (rotY)
		{
			getTransform()->rotate(annie);// glm::normalize(glm::vec3(0, 1, 0)), ToRadians(deltaPos.x * m_sensitivity));
			printf("deltaX = %f\n", deltaPos.x);
		}
		//if (rotX)
		//{
		//	getTransform()->rotate(bobby);// rightVec, ToRadians(deltaPos.y * m_sensitivity));
		//	printf("deltaY = %f\n", deltaPos.y);
		//}

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
