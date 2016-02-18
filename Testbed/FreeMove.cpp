#include "freeMove.h"
#include <Core\Utility.h>
void FreeMove::processInput(const InputManager& input, float delta)
{
	float movAmt = m_speed * delta;

	if (input.GetThumbLPosition().y > 0.1f)
		Move(Utility::getForward(*getTransform()->getRotation()), movAmt * glm::abs(input.GetThumbLPosition().y));
	else if (input.GetThumbLPosition().y < -0.1f)
		Move(Utility::getBack(*getTransform()->getRotation()), movAmt * glm::abs(input.GetThumbLPosition().y));
	if (input.GetThumbLPosition().x < -0.1f)
		Move(Utility::getLeft(*getTransform()->getRotation()), movAmt * glm::abs(input.GetThumbLPosition().x));
	else if (input.GetThumbLPosition().x > 0.1f)
		Move(Utility::getRight(*getTransform()->getRotation()), movAmt * glm::abs(input.GetThumbLPosition().x));

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
}

void FreeMove::Move(const glm::vec3& direction, float amt)
{
	glm::vec3 result = *getTransform()->getPosition() + (direction * amt);
	getTransform()->setPosition(*getTransform()->getPosition() + (direction * amt));
}