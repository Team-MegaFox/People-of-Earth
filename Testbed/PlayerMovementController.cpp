#include "PlayerMovementController.h"


PlayerMovementController::PlayerMovementController(float accelerationValue, int forwardKey, int backKey, int leftKey, int rightKey, int upKey, int downKey)
{
	m_accelerationValue = accelerationValue;
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
	m_camera = getGameObjectByName("camera")->getGameComponent<CameraComponent>();
	m_accelerationValue = 500.0f;
}

void PlayerMovementController::processInput(const InputManager& input, float delta)
{
	//if (input.GetThumbLPosition().x < -0.3f)
	//	m_rigidBody->updateAcceleration(Utility::getLeft(*getTransform()->getRotation()) * delta * m_accelerationValue);// * glm::abs(input.GetThumbLPosition().x));
	//if (input.GetThumbLPosition().x > 0.3f)
	//	m_rigidBody->updateAcceleration(Utility::getRight(*getTransform()->getRotation()) * delta * m_accelerationValue);// * glm::abs(input.GetThumbLPosition().x));

	if (input.GetThumbRPosition().x > 0.3f)
	{
		m_rigidBody->setRotation(m_rigidBody->getRotation() *
			glm::quat(glm::cos(0.5f * -1.0f * 3.14159625f / 180.0f),
			0, glm::sin(0.5f * -1.0f * 3.14159265f / 180.0f), 0));

		m_camera->getTransform()->setPosition(m_rigidBody->getPosition() - (20.0f * Utility::getForward(*getTransform()->getRotation())));// - new Vector3(0.0f, -0.5f, 0.0f);
		
		//Rotates the camera view
		//m_camera->getTransform()->setRotation(*m_camera->getTransform()->getRotation() *
		//	glm::quat(glm::cos(0.5f * -1.0f * 3.14159625f / 180.0f),
		//	0, glm::sin(0.5f * -1.0f * 3.14159265f / 180.0f), 0));	
	}

	if (input.GetThumbLPosition().y > 0.3f)
	{
		m_rigidBody->updateAcceleration(Utility::getForward(m_rigidBody->getRotation()) * delta * m_accelerationValue);// *glm::abs(input.GetThumbLPosition().y));
	}
	if (input.GetThumbLPosition().y < -0.3f)
	{
		m_rigidBody->updateAcceleration(Utility::getBack(m_rigidBody->getRotation()) * delta * m_accelerationValue);// * glm::abs(input.GetThumbLPosition().y));
	}

	if (input.KeyDown(m_forwardKey))
	{
		m_rigidBody->updateAcceleration(Utility::getForward(m_rigidBody->getRotation()) * delta * m_accelerationValue);
	}
	if (input.KeyDown(m_backKey))
	{
		m_rigidBody->updateAcceleration(Utility::getBack(m_rigidBody->getRotation()) * delta * m_accelerationValue);
	}
	if (input.KeyDown(m_leftKey))
	{
		m_rigidBody->updateAcceleration(Utility::getLeft(m_rigidBody->getRotation()) * delta * m_accelerationValue);
	}
	if (input.KeyDown(m_rightKey))
	{
		m_rigidBody->updateAcceleration(Utility::getRight(m_rigidBody->getRotation()) * delta * m_accelerationValue);
	}
	if (input.KeyDown(m_upKey))
	{
		m_rigidBody->updateAcceleration(Utility::getUp(m_rigidBody->getRotation()) * delta * m_accelerationValue);
	}
	if (input.KeyDown(m_downKey))
	{
		m_rigidBody->updateAcceleration(Utility::getDown(m_rigidBody->getRotation()) * delta * m_accelerationValue);
	}
	
}


