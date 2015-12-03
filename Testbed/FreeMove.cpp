#include "freeMove.h"
#include <Utility.h>
void FreeMove::processInput(const InputManager& input, float delta)
{
	float movAmt = m_speed * delta;

	if (input.KeyDown(m_forwardKey))
		Move(getForward(*getTransform()->getRotation()), movAmt);
	if (input.KeyDown(m_backKey))
		Move(getBack(*getTransform()->getRotation()), movAmt);
	if (input.KeyDown(m_leftKey))
		Move(getLeft(*getTransform()->getRotation()), movAmt);
	if (input.KeyDown(m_rightKey))
		Move(getRight(*getTransform()->getRotation()), movAmt);
}

void FreeMove::Move(const glm::vec3& direction, float amt)
{
	getTransform()->setPosition(*getTransform()->getPosition() + (direction * amt));
}