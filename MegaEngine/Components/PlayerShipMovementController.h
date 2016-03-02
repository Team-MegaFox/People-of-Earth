// ***********************************************************************
// Author           : Pavan Jakhu, Jesse Derochie and Christopher Maeda
// Created          : 09-17-2015
//
// Last Modified By : Jesse Derochie
// Last Modified On : 03-01-2016
// ***********************************************************************
// <copyright file="PlayerShipMovementController.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
//		This PlayerShipMovementController class is customized for 
//		use with ships that fly either in the air or in space.
//</summary>
// ***********************************************************************

#pragma once
#include "../MegaEngine.h"
#include <PhysX/PxPhysicsAPI.h>

class PlayerShipMovementController : public GameComponent
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="PlayerMovementController"/> class.
	/// </summary>
	/// <param name="nameOfCameraInstance">The name of camera instance.</param>
	/// <param name="velocityValue">The velocity value.</param>
	/// <param name="accelerationValue">The acceleration value.</param>
	PlayerShipMovementController(const std::string & nameOfCameraInstance, float velocityValue = 30.0f, float accelerationValue = 500.0f);
	/// <summary>
	/// Finalizes an instance of the <see cref="PlayerMovementController"/> class.
	/// </summary>
	~PlayerShipMovementController();

	/// <summary>
	/// Ons the start.
	/// </summary>
	virtual void onStart() override;

	/// <summary>
	/// Processes the input.
	/// </summary>
	/// <param name="input">The input.</param>
	/// <param name="delta">The delta.</param>
	virtual void processInput(const InputManager& input, float delta) override;

	/// <summary>
	/// Looks the around.
	/// </summary>
	/// <param name="input">The input.</param>
	void lookAround(const InputManager& input);

	/// <summary>
	/// Movements the specified input.
	/// </summary>
	/// <param name="input">The input.</param>
	/// <param name="delta">The delta.</param>
	void movement(const InputManager& input, float delta);

	/// <summary>
	/// Returns to actual rotation.
	/// </summary>
	void returnToActualRotation();

	/// <summary>
	/// Shows the visual ship rotation.
	/// </summary>
	void showVisualShipRotation();

	/// <summary>
	/// Checks the lerp.
	/// </summary>
	/// <param name="input">The input.</param>
	void checkLerp(const InputManager& input);

	/// <summary>
	/// Lerps this instance.
	/// </summary>
	void lerp();

private:
	/// <summary>
	/// The rigid body of the player
	/// </summary>
	RigidBody* m_rigidBody;
	/// <summary>
	/// The camera instance name
	/// </summary>
	std::string m_cameraInstanceName;
	/// <summary>
	/// A reference to the camera in the scene (Camera must be created)
	/// </summary>
	CameraComponent* m_camera;
	/// <summary>
	/// The acceleration value of the player
	/// </summary>
	float m_accelerationValue;
	/// <summary>
	/// The distance
	/// </summary>
	float m_distance;
	/// <summary>
	/// The velocity value of the player
	/// </summary>
	float m_velocityValue;
	/// <summary>
	/// The player ships visual rotation
	/// </summary>
	physx::PxVec3 m_shipsVisualRotation = physx::PxVec3(0.0f, 0.0f, 0.0f);
	/// <summary>
	/// The x axis lerp  of the ship
	/// </summary>
	bool m_lerp_X_Axis_Ship;
	/// <summary>
	/// The y axis lerp  of the ship
	/// </summary>
	bool m_lerp_Y_Axis_Ship;
	/// <summary>
	/// The forward direction
	/// </summary>
	physx::PxVec3 m_forwardDirection = physx::PxVec3(0.0f, 0.0f, 0.0f);
	/// <summary>
	/// The up direction
	/// </summary>
	physx::PxVec3 m_upDirection = physx::PxVec3(0.0f, 0.0f, 0.0f);



};

