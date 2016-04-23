#include "FreeMove.h"
#include <Core\Utility.h>

void FreeMove::processInput(const InputManager& input, float delta)
{
	float movAmt = m_speed * delta;

	if (input.GetThumbLPosition().y > 0.1f)
		Move(Utility::getForward(*getTransform()->getRotation()), movAmt * PxAbs(input.GetThumbLPosition().y));
	else if (input.GetThumbLPosition().y < -0.1f)
		Move(Utility::getBack(*getTransform()->getRotation()), movAmt * PxAbs(input.GetThumbLPosition().y));
	if (input.GetThumbLPosition().x < -0.1f)
		Move(Utility::getLeft(*getTransform()->getRotation()), movAmt * PxAbs(input.GetThumbLPosition().x));
	else if (input.GetThumbLPosition().x > 0.1f)
		Move(Utility::getRight(*getTransform()->getRotation()), movAmt * PxAbs(input.GetThumbLPosition().x));

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

void FreeMove::Move(const PxVec3& direction, float amt)
{
	PxVec3 result = *getTransform()->getPosition() + (direction * amt);
	getTransform()->setPosition(*getTransform()->getPosition() + (direction * amt));
	
	//Need to find a way to get another game component (specifically rigidbody) in a game component
	//Plan is Have the game component know the gameobject they are connected
	//Get the game object it is connected to and call the getGameComponent function to get the rigid body
	//Finally set the velocity and acceleration value properly



}