// ***********************************************************************
// Author           : Christopher Maeda
// Created          : 09-15-2015
//
// Last Modified By : Jesse Derochie
// Last Modified On : 03-01-2016
// ***********************************************************************
// <copyright file="SphereCollider.cpp" company="">
//     Copyright (c) . All rights reserved.
// </copyright>
// <summary>7
// A derived class of Collider.
// This class will handle sphere to sphere collision only.
// </summary>
// ***********************************************************************
#include "SphereCollider.h"
#include "MultiCollider.h"
#include <iostream>

SphereCollider::SphereCollider()
{
}

SphereCollider::SphereCollider(SphereCollider& collider)
{
	m_shapeCollider = collider.m_shapeCollider;
	m_position = collider.m_position;
	m_rotation = collider.m_rotation; 
	m_scale = collider.m_scale;
	m_mass = collider.m_mass;
	m_velocity = collider.m_velocity;
	m_acceleration = collider.m_acceleration;
    m_radiusSphere = collider.m_radiusSphere; 
	m_id = collider.m_id;
}

SphereCollider::~SphereCollider()
{
}

void SphereCollider::init(
		physx::PxVec3 position,
		physx::PxQuat rotation,
		float scale,
		float mass,
		physx::PxVec3 velocity,
		physx::PxVec3 acceleration,
		float radiusSphere,
		int id)
{
	Collider::init(position, rotation, scale, mass, velocity, acceleration, id);
	m_shapeCollider = ShapeCollider::SPHERE;
	m_radiusSphere = radiusSphere; 
}

std::vector<Collider*> SphereCollider::checkCollision(std::vector<Collider*> collidableObjects)
{
	//Create a vector of collided object it collided with
	std::vector<Collider*> collidedObject;
	//Loop through all the collidable objects
	for (size_t i = 0; i < collidableObjects.size(); i++)
	{
		//Checking to see if the collidable object is not checking itself
        if (m_id != collidableObjects[i]->getID())
		{
			//Distance collision check theory
			
			//Get the distance from this position to the other position
            //glm::vec3 distanceVec = collidableObjects[i]->getPosition() - m_position;
			//float distance = glm::length(distanceVec);
            float distance = (collidableObjects[i]->getPosition() - m_position).magnitude();
			//Check to see if the 2 radius is lower than distance magnitude
            if (m_radiusSphere + collidableObjects[i]->getRadiusSphere() >= distance)
			{
                //if the collider is a multi-collider then
                if (collidableObjects[i]->getShapeCollider() == OTHER)
                {
                    //Check collision with this Collider with the Multi Colliders colliders
                    if (checkCollision(dynamic_cast<MultiCollider*>(collidableObjects[i])->getMultiCollider()).size() > 0) 
                    {
                        //Push back the collided object to the return collided object
                        collidedObject.push_back(collidableObjects[i]);
                        //std::cout << "Multi Collided\n";
                    }
                }
                //Collider is a sphere or polygon
                else
                {
                    //Push back the collided object to the return collided object
				    collidedObject.push_back(collidableObjects[i]);
                    //std::cout << "Sphere Collided\n";
                }	
			}
		}
	}

    //If the return collided object is more than 0 then 
	if (collidedObject.size() > 0)
	{
		//std::cout << "Collisions\n";
		m_collided = true;
	}
    //No return collided objects meaning no collision
	else
	{
		//std::cout << "No Collisions\n";
		m_collided = false;
	}

	//Return the collided objects
	return collidedObject;
}

bool SphereCollider::checkCollision(Collider* collidableObject)
{
	//Checking to see if the collidable object is not checking itself
	if (m_id != collidableObject->getID())
	{
		//Distance collision check theory

		//Get the distance from this position to the other position
		float distance = (collidableObject->getPosition() - m_position).magnitude();
		//Check to see if the 2 radius is lower than distance magnitude
		if (m_radiusSphere + collidableObject->getRadiusSphere() >= distance)
		{
			//if the collider is a multi-collider then
			if (collidableObject->getShapeCollider() == OTHER)
			{
				//Check collision with this Collider with the Multi Colliders colliders
				if (checkCollision(dynamic_cast<MultiCollider*>(collidableObject)->getMultiCollider()).size() > 0)
				{
					//Push back the collided object to the return collided object
					return true;
				}
			}
			//Collider is a sphere or polygon
			else
			{
				//Push back the collided object to the return collided object
				return true;
			}
		}
	}
	//No collision
	return false;
}

bool SphereCollider::checkCollision(physx::PxVec3 rayPosition, physx::PxVec3 rayDirection, float &timeOfCollision)
{
	//Tutorial from http://www.miguelcasillas.com/?p=74

	//Create a vector from the sphere to the ray's start point
	physx::PxVec3 spherePosToRayPos = rayPosition - m_position;

	//Get the dot product of this vector with the ray's direction
	float projection = spherePosToRayPos.dot(rayDirection);

	//Get the square distance from the start of the ray to the sphere's surface
	float squaredDistance = spherePosToRayPos.dot(spherePosToRayPos) - (m_radiusSphere * m_radiusSphere);

	//If the ray starts outside the sphere and points away from it, we return false
	if (squaredDistance > 0.0f && projection > 0.0f)
	{
		return false;
	}
	
	//Get the discriminant for our equation
	float discriminant = projection * projection - squaredDistance;

	//If this is less than zero, we return false (No intersection)
	if (discriminant < 0.0f)
	{
		return false;
	}

	//We solve our equation and get the time of collision
	//We use -sqrt(fDisc) to get the smallest root, ie. the first point in which the ray touches the sphere
	timeOfCollision = -projection - physx::PxSqrt(discriminant);

	//If the time is less than zero, it means the ray started inside the sphere (Already Collision)
	if (timeOfCollision < 0.0f)
	{
		timeOfCollision = 0.0f;
	}

	//Our collision point is going to be:
	physx::PxVec3 collisionPoint = rayPosition + rayDirection * timeOfCollision;

	//Collided
	return true;

}