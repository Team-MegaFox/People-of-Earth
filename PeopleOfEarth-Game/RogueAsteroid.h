// ***********************************************************************
// Author           : Christopher Maeda
// Created          : 03-17-2016
//
// Last Modified By : Christopher Maeda
// Last Modified On : 03-18-2016
// ***********************************************************************
// <copyright file="RogueAsteroid.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
//</summary>
// ***********************************************************************

#pragma once
#include <MegaEngine.h>

class RogueAsteroid : public GameComponent
{

public:
	RogueAsteroid(float velocityValue = 10.0f, float rotationSpeed = 0.005f) :
		m_velocityValue(velocityValue), m_rotationSpeed(rotationSpeed)
	{}

	~RogueAsteroid()
	{}

	virtual void onStart() override
	{
		m_rigidBody = getParent()->getGameComponent<RigidBody>();
		//Create 2 points for the asteroid (start and end point)
		createNewPath();
		m_rigidBody->setPosition(PxVec3(0.0f, 0.0f, 100.0f));
	}

	// Update is called once per frame
	void update(float timestep) override
	{
		//Update the rotation of the asteroid
		m_rigidBody->updateRotation(PxQuat(
			m_axisOfRotation.x * PxSin(0.5f * m_rotationSpeed),
			m_axisOfRotation.y * PxSin(0.5f * m_rotationSpeed),
			m_axisOfRotation.z * PxSin(0.5f * m_rotationSpeed),
			PxCos(0.5f * m_rotationSpeed)));

		if (Utility::getDistance(m_rigidBody->getPosition(), m_endPoint) < 100.0f)
		{
			//Create 2 new points for the asteroid (start and end point)
			createNewPath();
		}
	}

	void createNewPath()
	{
		//Set the start point for the asteroid
		m_rigidBody->setPosition(pickPoint());
		//Set the end point the asteroid is headed
		m_endPoint = pickPoint();
		//Velocity of the asteroid going from start to end direction
		m_rigidBody->updateVelocity(
			(m_endPoint - m_rigidBody->getPosition()).getNormalized()
			* m_velocityValue);
		//Pick a random axis to rotate
		m_axisOfRotation = PxVec3(Utility::getRandomNumber(0, -1, 1), Utility::getRandomNumber(0, -1, 1), Utility::getRandomNumber(0, -1, 1));
	}

	PxVec3 pickPoint()
	{
		PxVec3 point;
		bool isLooping;
		//Loop until find a point that is not within -0.25 and 0.25 in all axis
		do
		{
			isLooping = false;
			//Get a random point
			point = PxVec3(Utility::getRandomNumber(0, -1, 1), Utility::getRandomNumber(0, -1, 1), Utility::getRandomNumber(0, -1, 1));
			//Check to see if the point is within the -0.25 and 0.25 in each axis
			if (PxAbs(point.x) < 0.25)
			{
				isLooping = true;
			}
			else if (PxAbs(point.y) < 0.25)
			{
				isLooping = true;
			}
			else if (PxAbs(point.z) < 0.25)
			{
				isLooping = true;
			}
		} while (isLooping);
		//Return the random point with the scale to the physics world (edges of the world)
		return point * PhysicsEngine::getPhysicsWorld()->getRadius();
	}

private:
	RigidBody* m_rigidBody;
	PxVec3 m_endPoint;
	float m_velocityValue = 0.0f;
	PxVec3 m_axisOfRotation;
	float m_rotationSpeed;
};