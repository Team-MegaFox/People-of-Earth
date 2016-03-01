
#pragma once

#include <Components\GameComponents.h>
#include <Core\GameObject.h>

class SteeringBehaviour : public GameComponent {

public:

	SteeringBehaviour() : forwardDirection(glm::vec3(0)), direction(glm::vec3(0)), SPEED_REDUCTION(1.0f),
		targetObject(nullptr), targetPoint(glm::vec3(0))
	{}

	~SteeringBehaviour()
	{}

	//Initialize
	virtual void init() = 0;

	//Conversion of direction to quaternion
	glm::quat ConvertDirectionVectorToQuaternion(glm::vec3 vDirection)
	{
		//Quaternion variable for the rotation in the direction
		glm::quat quaternion = glm::quat();

		//Get the axis (normal) of the forward and direction
		glm::vec3 axis = glm::cross(forwardDirection, vDirection);

		//Angle between the 2 directions
		float angle = 0;

		//Special case statement when magnitude of the either direction is 0 so it does not give a null angle (divide by 0)
		if (forwardDirection.length() != 0 || vDirection.length() != 0)
		{
			//Get the angle value
			angle = glm::dot(forwardDirection, vDirection);
			angle = glm::acos(angle);
			angle /= (forwardDirection.length() * vDirection.length());
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
		glm::quat directionQuaternion = ConvertDirectionVectorToQuaternion(direction) * *getTransform()->getRotation();

		//Slerp the ship from current rotation to final rotation
		//this.transform.setRotation(this.transform.getRotation() + glm::slerp(transform.getRotation(), directionQuaternion, timestep));
		getTransform()->setRotation(*getTransform()->getRotation() +
			glm::slerp(*getTransform()->getRotation(), directionQuaternion, timestep));

	}

	//Seek to the point
	void SeekToPoint(glm::vec3 point, float timestep)
	{
		//Get the direction
		direction = glm::normalize(point - *getTransform()->getPosition());

		//Get the forward direction
		forwardDirection = Utility::getForward(*getTransform()->getRotation());

		//Rotate the ship towards the direction
		RotateShip(timestep);
	}

	//Seek to the current set target
	void SeekToTarget(float timestep)
	{
		//Get the direction from this ship to target
		direction = glm::normalize(*targetObject->getTransform()->getPosition() - *getTransform()->getPosition());

		//Get the forward direction
		forwardDirection = Utility::getForward(*getTransform()->getRotation());

		//Rotate the ship towards the direction
		RotateShip(timestep);
	}

	//Wander the ship
	void Wander(float timestep)
	{
		//Wandering using waypoint 

		//if the ship is close enough to the current waypoint then
		if ((targetPoint - *getTransform()->getPosition()).length() < 5.0f)
		{
			//Change the position of the waypoint (random number between -10 to 10
			targetPoint = *getTransform()->getPosition() + glm::vec3((rand() % -21) - 10, (rand() % -21) - 10, (rand() % -21) - 10);
		}

		//Seek to the waypoint
		SeekToPoint(targetPoint, timestep);
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

	//Any agent will inherit this function
	virtual void UpdateAI(float timestep) = 0;

	// Update is called once per frame
	void update(float timestep) override
	{
		//Get the forward direction
		forwardDirection = Utility::getForward(*getTransform()->getRotation());

		UpdateAI(timestep);

		//Get the forward direction
		forwardDirection = Utility::getForward(*getTransform()->getRotation());

		//Update the position
		getTransform()->setPosition(*getTransform()->getPosition() 
			+ glm::vec3(forwardDirection.x / SPEED_REDUCTION, 
						forwardDirection.y / SPEED_REDUCTION, 
						forwardDirection.z / SPEED_REDUCTION));

	}

protected:
	glm::vec3 forwardDirection;
	glm::vec3 direction;
	float SPEED_REDUCTION;
	GameObject* targetObject;
	glm::vec3 targetPoint;


};