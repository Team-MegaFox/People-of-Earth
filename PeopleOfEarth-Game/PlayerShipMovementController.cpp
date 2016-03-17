// ***********************************************************************
// Author           : Pavan Jakhu, Jesse Derochie and Christopher Maeda
// Created          : 09-17-2015
//
// Last Modified By : Christopher Maeda
// Last Modified On : 03-11-2016
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
#include "pauseScene.h"
#include "ShipStats.h"

/*
	Player Ship Movement Controller Macros
*/
#define COS_ANGLE(x) PxCos(0.5f * x)
#define SIN_ANGLE(x) PxSin(0.5f * x)
#define ROTATE_X_AXIS(x) PxQuat(0, SIN_ANGLE(x), 0, COS_ANGLE(x))  //ToRadians(COS_ANGLE(x)), PxVec3(0, SIN_ANGLE(x), 0))
#define ROTATE_Y_AXIS(x) PxQuat(SIN_ANGLE(x), 0, 0, COS_ANGLE(x)) //ToRadians(COS_ANGLE(x)), PxVec3(SIN_ANGLE(x), 0, 0))
#define ROTATE_Z_AXIS(x) PxQuat(0, 0, SIN_ANGLE(x), COS_ANGLE(x)) //ToRadians(COS_ANGLE(x)), PxVec3(0, 0, SIN_ANGLE(x)))
#define SHIP_ROTATION(x, y)	PxQuat(						\
		ToRadians(PxCos(0.5f * (x + y))),				\
		PxVec3(PxSin(0.5f * x),							\
		PxSin(0.5f * y), 0)								\
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
	m_distance = Utility::getDistance(m_rigidBody->getPosition(), *m_camera->getTransform()->getPosition());
	m_forwardDirection = Utility::getForward(m_rigidBody->getRotation());
	m_upDirection = Utility::getUp(m_rigidBody->getRotation());
}

void PlayerShipMovementController::processInput(const InputManager& input, float delta)
{
	if (input.KeyPress(SDLK_ESCAPE) || input.PadButtonPress(SDL_CONTROLLER_BUTTON_START))
	{
		getCoreEngine()->getSceneManager()->push(new PauseScene, Modality::Popup);
	}

	lookAround(input);

	movement(input, delta);
	
	checkLerp(input);
	
	if (m_lerp_X_Axis_Ship || m_lerp_Y_Axis_Ship)
	{
		lerp();
	}

	//Updates the camera position from the rigidbody
	m_camera->getTransform()->setPosition(m_rigidBody->getPosition() - (m_distance * m_forwardDirection) + (m_upDirection * 10.0f));

	//If any collision occured then
	if (m_rigidBody->getCollided())
	{
		std::vector<GameObject*> collidedObjects = m_rigidBody->checkCollision(getGameObjectsByName("enemyFighter"));
		if (collidedObjects.size() > 0)
		{
			getParent()->getGameComponent<ShipStats>()->setHealth(0.0f);
		}
		//collidedObjects = m_rigidBody->checkCollision(getGameObjectsByName("passengerShip"));
		//if (collidedObjects.size() > 0)
		//{
		//	getParent()->getGameComponent<ShipStats>()->setHealth(0.0f);
		//}
	}
}

void PlayerShipMovementController::lookAround(const InputManager& input)
{
	if (input.GetThumbRPosition().x > 0.3f)
	{
		returnToActualRotation();

		m_rigidBody->updateRotation(ROTATE_X_AXIS(0.025f));

		m_forwardDirection = Utility::getForward(m_rigidBody->getRotation());

		m_upDirection = Utility::getUp(m_rigidBody->getRotation());

		//Rotates the camera view
		m_camera->getTransform()->setRotation(*m_camera->getTransform()->getRotation() * ROTATE_X_AXIS(0.025f));

		if (m_shipsVisualRotation.y < 50.0f)
		{
			m_shipsVisualRotation.y++;
		}

		showVisualShipRotation();

		m_lerp_Y_Axis_Ship = false;
	}

	if (input.GetThumbRPosition().x < -0.3f)
	{
		returnToActualRotation();
		m_rigidBody->updateRotation(ROTATE_X_AXIS(-0.025f));

		m_forwardDirection = Utility::getForward(m_rigidBody->getRotation());

		m_upDirection = Utility::getUp(m_rigidBody->getRotation());

		//Rotates the camera view
		m_camera->getTransform()->setRotation(*m_camera->getTransform()->getRotation() * ROTATE_X_AXIS(-0.025f));
		
		if (m_shipsVisualRotation.y > -50.0f)
		{
			m_shipsVisualRotation.y--;
		}
		showVisualShipRotation();
		m_lerp_Y_Axis_Ship = false;
	}

	if (input.GetThumbRPosition().y > 0.3f)
	{
		returnToActualRotation();

		m_rigidBody->updateRotation(ROTATE_Y_AXIS(-0.025f));

		m_forwardDirection = Utility::getForward(m_rigidBody->getRotation());

		m_upDirection = Utility::getUp(m_rigidBody->getRotation());

		//Rotates the camera view
		m_camera->getTransform()->setRotation(*m_camera->getTransform()->getRotation() * ROTATE_Y_AXIS(-0.025f));
		
		if (m_shipsVisualRotation.x > -50.0f)
		{
			m_shipsVisualRotation.x--;
		}
		showVisualShipRotation();
		m_lerp_X_Axis_Ship = false;
	}

	if (input.GetThumbRPosition().y < -0.3f)
	{
		returnToActualRotation();

		m_rigidBody->updateRotation(ROTATE_Y_AXIS(0.025f));

		m_forwardDirection = Utility::getForward(m_rigidBody->getRotation());

		m_upDirection = Utility::getUp(m_rigidBody->getRotation());

		//Rotates the camera view
		m_camera->getTransform()->setRotation(*m_camera->getTransform()->getRotation() * ROTATE_Y_AXIS(0.025f));

		if (m_shipsVisualRotation.x < 50.0f)
		{
			m_shipsVisualRotation.x++;
		}

		showVisualShipRotation();
		m_lerp_X_Axis_Ship = false;
	}
}

void PlayerShipMovementController::movement(const InputManager& input, float delta)
{
	m_rigidBody->updateVelocity(PxVec3(0.0f, 0.0f, 0.0f));

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
		m_rigidBody->updateRotation(ROTATE_Z_AXIS(-0.025f));
		m_forwardDirection = Utility::getForward(m_rigidBody->getRotation());
		m_upDirection = Utility::getUp(m_rigidBody->getRotation());
		//Rotates the camera view
		m_camera->getTransform()->setRotation(*m_camera->getTransform()->getRotation() * ROTATE_Z_AXIS(-0.025f));
		showVisualShipRotation();
	}
	if (input.PadButtonDown(SDL_CONTROLLER_BUTTON_LEFTSHOULDER))
	{
		returnToActualRotation();
		m_rigidBody->updateRotation(ROTATE_Z_AXIS(0.025f));
		m_forwardDirection = Utility::getForward(m_rigidBody->getRotation());
		m_upDirection = Utility::getUp(m_rigidBody->getRotation());
		//Rotates the camera view
		m_camera->getTransform()->setRotation(*m_camera->getTransform()->getRotation() * ROTATE_Z_AXIS(0.025f));
		showVisualShipRotation();
	}
	if (input.PadButtonDown(SDL_CONTROLLER_BUTTON_A))
	{
		m_velocityValue = 130.0f;
	}
	else if (input.PadButtonUp(SDL_CONTROLLER_BUTTON_A))
	{
		m_velocityValue = 30.0f;
	}
}

void PlayerShipMovementController::returnToActualRotation()
{
	if (PxAbs(m_shipsVisualRotation.x) != 0 || PxAbs(m_shipsVisualRotation.y) != 0)
	{
		m_rigidBody->updateRotation(ROTATE_Y_AXIS(-m_shipsVisualRotation.x / 100.0f));
		m_rigidBody->updateRotation(ROTATE_X_AXIS(-m_shipsVisualRotation.y / 100.0f));
	}
}

void PlayerShipMovementController::showVisualShipRotation()
{
	m_rigidBody->updateRotation(ROTATE_X_AXIS(m_shipsVisualRotation.y / 100.0f));
	m_rigidBody->updateRotation(ROTATE_Y_AXIS(m_shipsVisualRotation.x / 100.0f));
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