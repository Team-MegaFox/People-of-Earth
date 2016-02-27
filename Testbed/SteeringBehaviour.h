// ***********************************************************************
// Author           : Christopher Maeda
// Created          : 02-23-2016
//
// Last Modified By : Christopher Maeda
// Last Modified On : 02-25-2016
// ***********************************************************************
// <copyright file="SteeringBehaviour.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
//</summary>
// ***********************************************************************

#pragma once
#include <Components\GameComponents.h>
#include <Core\GameObject.h>

class SteeringBehaviour : public GameComponent {

public:

	SteeringBehaviour() : m_forwardDirection(glm::vec3(0)), m_direction(glm::vec3(0)),
		m_targetObject(nullptr), m_targetPoint(glm::vec3(0))
	{}

	~SteeringBehaviour()
	{}

	virtual void onStart()
	{
		init();

		m_rigidBody = getParent()->getGameComponent<RigidBody>();
		m_rigidBody->setPosition(*getTransform()->getPosition());
		m_rigidBody->setRotation(*getTransform()->getRotation());
		m_rigidBody->setDebugDraw(true);
	}

	//Initialize
	virtual void init() = 0;

	//Conversion of direction to quaternion
	glm::quat ConvertDirectionVectorToQuaternion(glm::vec3 vDirection)
	{
		//Quaternion variable for the rotation in the direction
		glm::quat quaternion = glm::quat();

		//Get the axis (normal) of the forward and direction
		glm::vec3 axis = glm::cross(m_forwardDirection, vDirection);

		//Angle between the 2 directions
		float angle = 0;

		//Special case statement when magnitude of the either direction is 0 so it does not give a null angle (divide by 0)
		if (m_forwardDirection.length() != 0 || vDirection.length() != 0)
		{
			//Get the angle value
			angle = glm::acos(glm::dot(m_forwardDirection, vDirection) / (m_forwardDirection.length() * vDirection.length()));
		}

		//Set the value from the axis and angle to the quaternion
		quaternion.w = glm::cos(angle / 2.0f);
		quaternion.x = axis.x * glm::sin(angle / 2.0f);
		quaternion.y = axis.y * glm::sin(angle / 2.0f);
		quaternion.z = axis.z * glm::sin(angle / 2.0f);

		//Return the result
		return quaternion;
	}

	//Rotating the ship from current transfrom to final transform
	void RotateShip(float timestep)
	{
		//Tutorial from how I got it to rotate properly
		//http://www.ogre3d.org/tikiwiki/Quaternion+and+Rotation+Primer

		//Get the transform of the ship pointing towards the direction
		glm::quat directionQuaternion = ConvertDirectionVectorToQuaternion(m_direction) * *getTransform()->getRotation();

		//Slerp the ship from current rotation to final rotation
		//this.transform.setRotation(this.transform.getRotation() + glm::slerp(transform.getRotation(), directionQuaternion, timestep));
		
		//getTransform()->setRotation(//*getTransform()->getRotation() *
		//	glm::slerp(*getTransform()->getRotation(), directionQuaternion, timestep));

		m_rigidBody->setRotation(glm::slerp(*getTransform()->getRotation(), directionQuaternion, timestep));

	}

	//Seek to the point
	void SeekToPoint(glm::vec3 point, float timestep)
	{
		if (point != *getTransform()->getPosition())
		{
			//Get the direction
			m_direction = glm::normalize(point - *getTransform()->getPosition());
		}
		else
		{
			m_direction = m_forwardDirection = Utility::getForward(*getTransform()->getRotation());
		}

		//Get the forward direction
		m_forwardDirection = Utility::getForward(*getTransform()->getRotation());

		//Rotate the ship towards the direction
		RotateShip(timestep);
	}

	//Seek to the current set target
	void SeekToTarget(float timestep)
	{
		//Get the direction from this ship to target
		m_direction = glm::normalize(*m_targetObject->getTransform()->getPosition() - *getTransform()->getPosition());

		//Get the forward direction
		m_forwardDirection = Utility::getForward(*getTransform()->getRotation());

		//Rotate the ship towards the direction
		RotateShip(timestep);
	}

	int RandomNumber(int max, int min)
	{
		int randnum = (rand() % (glm::abs(max) + glm::abs(min))) - ((glm::abs(max) + glm::abs(min)) / 2);
		return randnum;
	}

	//Check if anything is in front of the ship
	void CheckPath(float timestep)
	{
		//Forward direction is the ray
		//Direction of the object

	}

	//Wander the ship
	void Wander(float timestep)
	{
		//Wandering using waypoint 

		//if the ship is close enough to the current waypoint then
		if (glm::distance(m_targetPoint, *getTransform()->getPosition()) < 75.0f)
		{
			//Change the position of the waypoint (random number between -100 to 100)
			m_targetPoint = *getTransform()->getPosition() + glm::vec3(RandomNumber(100, -100),
																	   RandomNumber(100, -100), 
																	   RandomNumber(100, -100));
		}

		//Seek to the waypoint
		SeekToPoint(m_targetPoint, timestep);
	}

	//Pursue the target
	void Pursue(GameObject pursueObject, float timestep)
	{
		//Get the next future position of the evaded object
		glm::vec3 futurePoint = *pursueObject.getTransform()->getPosition() +
			Utility::getForward(*pursueObject.getTransform()->getRotation());
			//pursueObject.forwardDirection;

		//Seek towards the future position
		SeekToPoint(futurePoint, timestep);
	}

	//Evade the target 
	void Evade(GameObject evadeObject, float timestep)
	{
		//Get the next future position of the evaded object
		glm::vec3 futurePoint = *evadeObject.getTransform()->getPosition() +
			Utility::getForward(*evadeObject.getTransform()->getRotation());
			//evadeObject.forwardDirection;
		
		//Get the direction from future point to your position
		glm::vec3 futureDirection = *getTransform()->getPosition() - futurePoint;
		
		//Seek towards your current position added with the direction
		SeekToPoint(*getTransform()->getPosition() + futureDirection, timestep);
	}

	//Waypoint
	void WayPoint(float timestep)
	{
		CheckPath(timestep);
		if (m_wayPoints.size() > 0)
		{
			if (glm::distance(m_wayPoints[m_wayPoints.size() - 1], *getTransform()->getPosition()) < m_distanceToChangeWayPoint)
			{
				m_wayPoints.pop_back();
			}
			else
			{
				//Get the direction
				m_direction = glm::normalize((m_wayPoints[m_wayPoints.size() - 1] - *getTransform()->getPosition()));

				RotateShip(timestep);
			}
		}
	}

	//Any agent will inherit this function
	virtual void UpdateAI(float timestep) = 0;

	// Update is called once per frame
	void update(float timestep) override
	{
		//Get the forward direction
		m_forwardDirection = Utility::getForward(*getTransform()->getRotation());

		UpdateAI(timestep);

		//Get the forward direction
		m_forwardDirection = Utility::getForward(*getTransform()->getRotation());

		//m_rigidBody->updateVelocity(m_forwardDirection * m_velocityValue);

		//Update the position
		/*getTransform()->setPosition(*getTransform()->getPosition() 
			+ glm::vec3(forwardDirection.x / SPEED_REDUCTION, 
						forwardDirection.y / SPEED_REDUCTION, 
						forwardDirection.z / SPEED_REDUCTION));*/

	}

protected:
	//Directions
	glm::vec3 m_forwardDirection;
	glm::vec3 m_direction;

	//Seek targets
	GameObject* m_targetObject;
	glm::vec3 m_targetPoint;
	
	//Waypoints
	/*All the waypoint must be that the 0 index being the last waypoint to the first waypoint*/
	std::vector<glm::vec3> m_wayPoints;
	float m_delayCheckInFront;
	float m_distanceToChangeWayPoint;

	//Physics
	RigidBody* m_rigidBody;
	float m_velocityValue;
};