// ***********************************************************************
// Author           : Pavan Jakhu, Jesse Derochie and Christopher Maeda
// Created          : 09-17-2015
//
// Last Modified By : Christopher Maeda
// Last Modified On : 04-03-2016
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
	m_shipStats = getGameObjectByName("player")->getGameComponent<ShipStats>();
	m_welcomeLabel = getGameObjectByName("WelcomeLabel")->getGameComponent<DialogueBox>();
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
	if (!m_invertXAxis)
	{
		if (input.GetThumbLPosition().x > 0.3f)
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

		if (input.GetThumbLPosition().x < -0.3f)
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
	}
	else if (m_invertXAxis)
	{
		if (input.GetThumbLPosition().x < -0.3f)
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

		if (input.GetThumbLPosition().x > 0.3f)
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
	}

	if (!m_invertYAxis)
	{
		if (input.GetThumbLPosition().y > 0.3f)
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

		if (input.GetThumbLPosition().y < -0.3f)
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
	else if (m_invertYAxis)
	{
		if (input.GetThumbLPosition().y < -0.3f)
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

		if (input.GetThumbLPosition().y > 0.3f)
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

	/*GameObject* passengerShip = getGameObjectByName("passengerShip");
	RigidBody* psRigidBody = passengerShip->getGameComponent<RigidBody>();
	psRigidBody->setDebugDraw(true);
	m_rigidBody->setDebugDraw(true);
	if (psRigidBody->getCollider()->checkCollision(m_rigidBody->getCollider()))
	{
		printf("Collision\n");
	}
	else
	{
		printf("No Collision\n");
	}*/


	/*if (m_rigidBody->getCollided())
	{
		printf("Collided\n");
	}
	else
	{
		printf("No Collision\n");
	}*/

	////Ray collision check code
	//if (input.PadButtonDown(SDL_CONTROLLER_BUTTON_Y))
	//{
	//	GameObject* passengerShip = getGameObjectByName("passengerShip");
	//	RigidBody* psRigidBody = passengerShip->getGameComponent<RigidBody>();
	//	//psRigidBody->setDebugDraw(true);
	//	float timeOfCollision = 0.0f;
	//	if (psRigidBody->getCollider()->checkCollision(
	//		m_rigidBody->getPosition(),
	//		Utility::getForward(m_rigidBody->getRotation()),
	//		timeOfCollision))
	//	{
	//		printf("Collision \t%f\n", timeOfCollision);
	//	}
	//	else
	//	{
	//		printf("No Collision\n");
	//	}
	//}
}

void PlayerShipMovementController::movement(const InputManager& input, float delta)
{
	m_rigidBody->updateVelocity(PxVec3(0.0f, 0.0f, 0.0f));

	if (m_canMoveForward)
	{
		m_rigidBody->updateVelocity(m_forwardDirection * m_velocityValue);
	}
	if (input.PadButtonDown(SDL_CONTROLLER_BUTTON_X) && !m_canMoveForward)
	{
		m_canMoveForward = true;
		m_welcomeLabel->sendLastingMessage("[colour='FFFFFFFF'][font='SaucerBB-16'][padding='l:5 t:0 r:5 b:0']Press Start for Options Menu", Importance::HIGH, false);
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
		m_shipStats->updateFuel(-0.0075f / 60.0f);
	}
	else if (input.PadButtonUp(SDL_CONTROLLER_BUTTON_A))
	{
		m_velocityValue = 30.0f;
		m_shipStats->updateFuel(-0.001f / 60.0f);
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
	if ((input.GetThumbLPosition().y > 0.3f) || (input.GetThumbLPosition().y < -0.3f))
	{
		m_lerp_X_Axis_Ship = false;
	}
	else
	{
		m_lerp_X_Axis_Ship = true;
	}

	if ((input.GetThumbLPosition().x > 0.3f) || (input.GetThumbLPosition().x < -0.3f))
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