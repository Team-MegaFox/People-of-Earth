#include "PlayerMovementController.h"


PlayerMovementController::PlayerMovementController(int forwardKey, int backKey, int leftKey, int rightKey, int upKey, int downKey)
{
	m_forwardKey = forwardKey;
	m_backKey = backKey;
	m_leftKey = leftKey;
	m_rightKey = rightKey;
	m_upKey = upKey;
	m_downKey = downKey;
}

PlayerMovementController::~PlayerMovementController()
{
}

void PlayerMovementController::onStart()
{
	m_rigidBody = getParent()->getGameComponent<RigidBody>();
}

void PlayerMovementController::processInput(const InputManager& input, float delta)
{
	if (input.KeyDown(m_forwardKey))
	{
		//m_polyCollider->applyRotation(glm::quat(glm::angleAxis(glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f))));
		m_rigidBody->updateAcceleration(Utility::getForward(*getTransform()->getRotation()) * 10000.0f);
	}
	if (input.KeyDown(m_backKey))
	{
		m_rigidBody->updateAcceleration(Utility::getBack(*getTransform()->getRotation()) * 10000.0f);
	}
	if (input.KeyDown(m_leftKey))
	{
		m_rigidBody->updateAcceleration(Utility::getLeft(*getTransform()->getRotation()) * 10000.0f);
	}
	if (input.KeyDown(m_rightKey))
	{
		m_rigidBody->updateAcceleration(Utility::getRight(*getTransform()->getRotation()) * 10000.0f);
	}
	if (input.KeyDown(m_upKey))
	{
		m_rigidBody->updateAcceleration(Utility::getUp(*getTransform()->getRotation()) * 10000.0f);
	}
	if (input.KeyDown(m_downKey))
	{
		m_rigidBody->updateAcceleration(Utility::getDown(*getTransform()->getRotation()) * delta * 1000.0f);
	}
	
}
