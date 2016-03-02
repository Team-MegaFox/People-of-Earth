// ***********************************************************************
// Author           : Pavan Jakhu, Jesse Derochie and Christopher Maeda
// Created          : 09-17-2015
//
// Last Modified By : Jesse Derochie
// Last Modified On : 03-01-2016
// ***********************************************************************
// <copyright file="PlayerShipMovementController.cpp" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
//		This PlayerShipMovementController class is customized for 
//		use with ships that fly either in the air or in space.
//</summary>
// ***********************************************************************

#include "PlayerShipMovementController.h"

/*
	Player Ship Movement Controller Macros
*/
#define COS_ANGLE(x) physx::PxCos(0.5f * x)
#define SIN_ANGLE(x) physx::PxSin(0.5f * x)
#define ROTATE_X_AXIS(x) physx::PxQuat(0, SIN_ANGLE(x), 0, COS_ANGLE(x))
#define ROTATE_Y_AXIS(x) physx::PxQuat(SIN_ANGLE(x), 0, 0, COS_ANGLE(x))
#define ROTATE_Z_AXIS(x) physx::PxQuat(0, 0, SIN_ANGLE(x), COS_ANGLE(x))
#define SHIP_ROTATION(x, y)	physx::PxQuat(						\
		physx::PxSin(0.5f * x),									\
		physx::PxSin(0.5f * y), 0,								\
		physx::PxCos(0.5f * (x + y))							\
)		

PlayerShipMovementController::PlayerShipMovementController(
	const std::string & nameOfCameraInstance, float velocityValue, float accelerationValue)
{
	m_velocityValue = velocityValue;
	m_accelerationValue = accelerationValue;
	m_cameraInstanceName = nameOfCameraInstance;
}

PlayerShipMovementController::~PlayerShipMovementController()
{
}

void PlayerShipMovementController::onStart()
{
	m_rigidBody = getParent()->getGameComponent<RigidBody>();
	m_camera = getGameObjectByName(m_cameraInstanceName)->getGameComponent<CameraComponent>();
	m_distance = (m_rigidBody->getPosition() - *m_camera->getTransform()->getPosition()).magnitude();
	m_forwardDirection = Utility::getForward(m_rigidBody->getRotation());
	m_upDirection = Utility::getUp(m_rigidBody->getRotation());
}

void PlayerShipMovementController::processInput(const InputManager& input, float delta)
{
	lookAround(input);

	movement(input, delta);
	
	checkLerp(input);
	
	if (m_lerp_X_Axis_Ship || m_lerp_Y_Axis_Ship)
	{
		lerp();
	}

	//Updates the camera position from the rigidbody
	m_camera->getTransform()->setPosition(m_rigidBody->getPosition() - (m_distance * m_forwardDirection) + (m_upDirection * 10.0f));

}

void PlayerShipMovementController::lookAround(const InputManager& input)
{
	if (input.GetThumbRPosition().x > 0.3f)
	{
		returnToActualRotation();

		m_rigidBody->updateRotation(ROTATE_X_AXIS(-1.0f));

		m_forwardDirection = Utility::getForward(m_rigidBody->getRotation());

		m_upDirection = Utility::getUp(m_rigidBody->getRotation());

		//Rotates the camera view
		m_camera->getTransform()->setRotation(*m_camera->getTransform()->getRotation() * ROTATE_X_AXIS(-1.0f));

		if (m_shipsVisualRotation.y > -15.0f)
		{
			m_shipsVisualRotation.y--;
		}

		showVisualShipRotation();

		m_lerp_Y_Axis_Ship = false;
	}

	if (input.GetThumbRPosition().x < -0.3f)
	{
		returnToActualRotation();
		m_rigidBody->updateRotation(ROTATE_X_AXIS(1.0f));

		m_forwardDirection = Utility::getForward(m_rigidBody->getRotation());

		m_upDirection = Utility::getUp(m_rigidBody->getRotation());

		//Rotates the camera view
		m_camera->getTransform()->setRotation(*m_camera->getTransform()->getRotation() * ROTATE_X_AXIS(1.0f));
		
		if (m_shipsVisualRotation.y < 15.0f)
		{
			m_shipsVisualRotation.y++;
		}
		showVisualShipRotation();
		m_lerp_Y_Axis_Ship = false;
	}

	if (input.GetThumbRPosition().y > 0.3f)
	{
		returnToActualRotation();

		m_rigidBody->updateRotation(ROTATE_Y_AXIS(1.0f));

		m_forwardDirection = Utility::getForward(m_rigidBody->getRotation());

		m_upDirection = Utility::getUp(m_rigidBody->getRotation());

		//Rotates the camera view
		m_camera->getTransform()->setRotation(*m_camera->getTransform()->getRotation() * ROTATE_Y_AXIS(1.0f));
		
		if (m_shipsVisualRotation.x < 15.0f)
		{
			m_shipsVisualRotation.x++;
		}
		showVisualShipRotation();
		m_lerp_X_Axis_Ship = false;
	}

	if (input.GetThumbRPosition().y < -0.3f)
	{
		returnToActualRotation();

		m_rigidBody->updateRotation(ROTATE_Y_AXIS(-1.0f));

		m_forwardDirection = Utility::getForward(m_rigidBody->getRotation());

		m_upDirection = Utility::getUp(m_rigidBody->getRotation());

		//Rotates the camera view
		m_camera->getTransform()->setRotation(*m_camera->getTransform()->getRotation() * ROTATE_Y_AXIS(-1.0f));

		if (m_shipsVisualRotation.x > -15.0f)
		{
			m_shipsVisualRotation.x--;
		}

		showVisualShipRotation();
		m_lerp_X_Axis_Ship = false;
	}
}

void PlayerShipMovementController::movement(const InputManager& input, float delta)
{
	m_rigidBody->updateVelocity(physx::PxVec3(0.0f, 0.0f, 0.0f));

	//Controller inputs
	if (input.GetThumbLPosition().y > 0.3f)
	{
		m_rigidBody->updateVelocity(m_forwardDirection * m_velocityValue);
	}
	if (input.GetThumbLPosition().y < -0.3f)
	{
		m_rigidBody->updateVelocity(-m_forwardDirection * m_velocityValue);
	}
	if (input.PadButtonDown(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER))
	{
		returnToActualRotation();
		m_rigidBody->updateRotation(ROTATE_Z_AXIS(-1.0f));
		m_forwardDirection = Utility::getForward(m_rigidBody->getRotation());
		m_upDirection = Utility::getUp(m_rigidBody->getRotation());
		//Rotates the camera view
		m_camera->getTransform()->setRotation(*m_camera->getTransform()->getRotation() * ROTATE_Z_AXIS(-1.0f));
		showVisualShipRotation();
	}
	if (input.PadButtonDown(SDL_CONTROLLER_BUTTON_LEFTSHOULDER))
	{
		returnToActualRotation();
		m_rigidBody->updateRotation(ROTATE_Z_AXIS(1.0f));
		m_forwardDirection = Utility::getForward(m_rigidBody->getRotation());
		m_upDirection = Utility::getUp(m_rigidBody->getRotation());
		//Rotates the camera view
		m_camera->getTransform()->setRotation(*m_camera->getTransform()->getRotation() * ROTATE_Z_AXIS(1.0f));
		showVisualShipRotation();
	}
}

void PlayerShipMovementController::returnToActualRotation()
{
	if (glm::abs(m_shipsVisualRotation.x) != 0 || glm::abs(m_shipsVisualRotation.y) != 0)
	{
		m_rigidBody->updateRotation(ROTATE_Y_AXIS(-m_shipsVisualRotation.x));
		m_rigidBody->updateRotation(ROTATE_X_AXIS(-m_shipsVisualRotation.y));
	}
}

void PlayerShipMovementController::showVisualShipRotation()
{
	m_rigidBody->updateRotation(ROTATE_X_AXIS(m_shipsVisualRotation.y));
	m_rigidBody->updateRotation(ROTATE_Y_AXIS(m_shipsVisualRotation.x));
}

void PlayerShipMovementController::checkLerp(const InputManager& input)
{
	if ((input.GetThumbRPosition().y > 0.3f) || (input.GetThumbRPosition().y < -0.3f))
	{
		m_lerp_X_Axis_Ship = false;
	}
	else
	{
		m_lerp_X_Axis_Ship = true;
	}

	if ((input.GetThumbRPosition().x > 0.3f) || (input.GetThumbRPosition().x < -0.3f))
	{
		m_lerp_Y_Axis_Ship = false;
	}
	else
	{
		m_lerp_Y_Axis_Ship = true;
	}
}

void PlayerShipMovementController::lerp()
{
	returnToActualRotation();
	if (m_lerp_X_Axis_Ship)
	{
		if (m_shipsVisualRotation.x > 0)
		{
			m_shipsVisualRotation.x--;
		}
		else if (m_shipsVisualRotation.x < 0)
		{
			m_shipsVisualRotation.x++;
		}
	}
	if (m_lerp_Y_Axis_Ship)
	{
		if (m_shipsVisualRotation.y > 0)
		{
			m_shipsVisualRotation.y--;
		}
		else if (m_shipsVisualRotation.y < 0)
		{
			m_shipsVisualRotation.y++;
		}
	}
	showVisualShipRotation();

}