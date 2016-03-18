// ***********************************************************************
// Author           : Christopher Maeda
// Created          : 02-23-2016
//
// Last Modified By : Christopher Maeda
// Last Modified On : 03-11-2016
// ***********************************************************************
// <copyright file="SteeringBehaviour.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
//</summary>
// ***********************************************************************

#pragma once
#include <PhysX/PxPhysicsAPI.h>
#include <MegaEngine.h>
using namespace physx;

class SteeringBehaviour : public GameComponent {

public:

	SteeringBehaviour() : m_forwardDirection(PxVec3(0.0f, 0.0f, 0.0f)), m_direction(PxVec3(0.0f, 0.0f, 0.0f)),
		m_targetObject(nullptr), m_targetPoint(PxVec3(0.0f, 0.0f, 0.0f))
	{}

	~SteeringBehaviour()
	{}

	virtual void onStart()
	{
		init();

		m_rigidBody = getParent()->getGameComponent<RigidBody>();
		m_rigidBody->setPosition(*getTransform()->getPosition());
		m_rigidBody->setRotation(*getTransform()->getRotation());
	}

	//Initialize
	virtual void init() = 0;

	//Conversion of direction to quaternion
	PxQuat ConvertDirectionVectorToQuaternion(PxVec3 vDirection)
	{
		//Quaternion variable for the rotation in the direction
		PxQuat quaternion = PxQuat(PxIdentity);

		//Get the axis (normal) of the forward and direction
		PxVec3 axis = m_forwardDirection.cross(vDirection);

		//Angle between the 2 directions
		float angle = 0;

		//Special case statement when magnitude of the either direction is 0 so it does not give a null angle (divide by 0)
		if (m_forwardDirection.magnitude() != 0 || vDirection.magnitude() != 0)
		{
			//Get the angle value
			angle = PxAcos(m_forwardDirection.dot(vDirection) / (m_forwardDirection.magnitude() * vDirection.magnitude()));
		}

		//Set the value from the axis and angle to the quaternion
		quaternion.w = PxCos(angle / 2.0f);
		quaternion.x = axis.x * PxSin(angle / 2.0f);
		quaternion.y = axis.y * PxSin(angle / 2.0f);
		quaternion.z = axis.z * PxSin(angle / 2.0f);

		//Return the result
		return quaternion;
	}

	//Rotating the ship from current transfrom to final transform
	void RotateShip(float timestep)
	{
		//Tutorial from how I got it to rotate properly
		//http://www.ogre3d.org/tikiwiki/Quaternion+and+Rotation+Primer

		//Get the transform of the ship pointing towards the direction
		PxQuat directionQuaternion = ConvertDirectionVectorToQuaternion(m_direction) * *getTransform()->getRotation();

		//Slerp the ship from current rotation to final rotation
		//this.transform.setRotation(this.transform.getRotation() + glm::slerp(transform.getRotation(), directionQuaternion, timestep));
		
		//getTransform()->setRotation(//*getTransform()->getRotation() *
		//	glm::slerp(*getTransform()->getRotation(), directionQuaternion, timestep));

		m_rigidBody->setRotation(Utility::slerp(*getTransform()->getRotation(), directionQuaternion, timestep));

	}

	//Seek to the point
	void SeekToPoint(PxVec3 point, float timestep)
	{
		if (point != *getTransform()->getPosition())
		{
			//Get the direction
			m_direction = (point - *getTransform()->getPosition()).getNormalized();
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
		m_direction = (*m_targetObject->getTransform()->getPosition() - *getTransform()->getPosition()).getNormalized();

		//Get the forward direction
		m_forwardDirection = Utility::getForward(*getTransform()->getRotation());

		//Rotate the ship towards the direction
		RotateShip(timestep);
	}

	//Check if anything is in front of the ship
	void CheckPath(float timestep)
	{
		/*
		TODO : Optimize CheckPath()
		When there is an obstacle in the way, this method lags the prgram really hard.
		If there is a way to optimize this method we will work on it after the presentation.
		for now we turned it off because of the lag, and because checking for
		objects in our path was less important right now, than having asteroids in the scene.

		*/

		if (m_delayCheckInFront < 0.0f)
		{
			std::vector<GameObject*> collidableGameObjects;
			collidableGameObjects = getAllEnemyObject();
			float m_collisionTime;
			for (size_t i = 0; i < collidableGameObjects.size(); i++)
			{
				if (collidableGameObjects[i]->getGameComponent<RigidBody>()->getCollider()->checkCollision(
					*getTransform()->getPosition(), (m_rigidBody->getVelocity()).getNormalized(),
					m_collisionTime)
					)
				{
					m_collisionTime /= 60.0f;
					//Within the 10 sec
					if (m_collisionTime < 10.0f)
					{
						if (collidableGameObjects[i]->getGameComponent<RigidBody>()->getVelocity() != PxVec3(0.0f))
						{
							m_wayPoints.push_back(collidableGameObjects[i]->getGameComponent<RigidBody>()->getPosition() + 
								(collidableGameObjects[i]->getGameComponent<RigidBody>()->getVelocity()).getNormalized() * -5.0f /*multiply by scale*/);
							m_delayCheckInFront = 1.0f;
							break;
						}
						else
						{
							m_wayPoints.push_back(collidableGameObjects[i]->getGameComponent<RigidBody>()->getPosition() +
								PxVec3(Utility::getRandomNumber(timestep, 100, -100), Utility::getRandomNumber(100, -100), 0.0f) /*multiply by scale*/);
							m_delayCheckInFront = 1.0f;
							break;
						}
					}
				}
			}
		}
		else
		{
			m_delayCheckInFront -= timestep;
		}
	}

	virtual std::vector<GameObject*> getAllEnemyObject() = 0;

	//Wander the ship
	void Wander(float timestep)
	{
		//Wandering using waypoint 

		//if the ship is close enough to the current waypoint then
		
		if (Utility::getDistance(m_targetPoint, *getTransform()->getPosition()) < 75.0f)
		{
			//Change the position of the waypoint (random number between -100 to 100)
			m_targetPoint = *getTransform()->getPosition() + PxVec3(
				Utility::getRandomNumber(timestep, -100, 100),
				Utility::getRandomNumber(timestep, -100, 100),
				Utility::getRandomNumber(timestep, -100, 100));
		}

		//Seek to the waypoint
		SeekToPoint(m_targetPoint, timestep);
	}

	//Pursue the target
	void Pursue(GameObject& pursueObject, float timestep)
	{
		//Get the next future position of the evaded object
		PxVec3 futurePoint = *pursueObject.getTransform()->getPosition() +
			Utility::getForward(*pursueObject.getTransform()->getRotation());
			//pursueObject.forwardDirection;

		//Seek towards the future position
		SeekToPoint(futurePoint, timestep);
	}

	//Evade the target 
	void Evade(GameObject& evadeObject, float timestep)
	{
		//Get the next future position of the evaded object
		PxVec3 futurePoint = *evadeObject.getTransform()->getPosition() +
			Utility::getForward(*evadeObject.getTransform()->getRotation());
			//evadeObject.forwardDirection;
		
		//Get the direction from future point to your position
		PxVec3 futureDirection = *getTransform()->getPosition() - futurePoint;
		
		//Seek towards your current position added with the direction
		SeekToPoint(*getTransform()->getPosition() + futureDirection, timestep);
	}

	//Waypoint
	void WayPoint(float timestep)
	{
		CheckPath(timestep);
		if (m_wayPoints.size() > 0)
		{
			if (Utility::getDistance(m_wayPoints[m_wayPoints.size() - 1], *getTransform()->getPosition()) < m_distanceToChangeWayPoint)
			{
				m_wayPoints.pop_back();
			}
			else
			{
				//Get the direction
				m_direction = ((m_wayPoints[m_wayPoints.size() - 1] - *getTransform()->getPosition())).getNormalized();

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

		m_rigidBody->updateVelocity(m_forwardDirection * m_velocityValue);

		//Update the position
		/*getTransform()->setPosition(*getTransform()->getPosition() 
			+ glm::vec3(forwardDirection.x / SPEED_REDUCTION, 
						forwardDirection.y / SPEED_REDUCTION, 
						forwardDirection.z / SPEED_REDUCTION));*/

	}

protected:
	//Directions
	PxVec3 m_forwardDirection;
	PxVec3 m_direction;

	//Seek targets
	GameObject* m_targetObject;
	PxVec3 m_targetPoint;
	
	//Waypoints
	/*All the waypoint must be that the 0 index being the last waypoint to the first waypoint*/
	std::vector<PxVec3> m_wayPoints;
	float m_delayCheckInFront;
	float m_distanceToChangeWayPoint;

	//Physics
	RigidBody* m_rigidBody;
	float m_velocityValue;
};