#include "freeMove.h"
#include <Core\Utility.h>
void FreeMove::processInput(const InputManager& input, float delta)
{
	float movAmt = m_speed * delta;

	if (input.KeyDown(m_forwardKey))
		Move(Utility::getForward(*getTransform()->getRotation()), movAmt);
	if (input.KeyDown(m_backKey))
		Move(Utility::getBack(*getTransform()->getRotation()), movAmt);
	if (input.KeyDown(m_leftKey))
		Move(Utility::getLeft(*getTransform()->getRotation()), movAmt);
	if (input.KeyDown(m_rightKey))
		Move(Utility::getRight(*getTransform()->getRotation()), movAmt);
	if (input.KeyDown(SDLK_r))
	{
		Move(Utility::getUp(*getTransform()->getRotation()), movAmt);
	}
	if (input.KeyDown(SDLK_f))
	{
		Move(Utility::getDown(*getTransform()->getRotation()), movAmt);
	}
	if (input.KeyDown(SDLK_1))
	{
		getTransform()->setPosition(glm::vec3(0.0f, -5.0f, -55000.0f));
	}
}

void FreeMove::Move(const glm::vec3& direction, float amt)
{
	getTransform()->setPosition(*getTransform()->getPosition() + (direction * amt));
}