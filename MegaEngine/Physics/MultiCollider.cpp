// ***********************************************************************
// Author           : Christopher Maeda
// Created          : 09-15-2015
//
// Last Modified By : Christopher Maeda
// Last Modified On : 04-04-2016
// ***********************************************************************
// <copyright file="MultiCollider.cpp" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
// A derived class of PolygonCollider.
// This class will handle sphere to sphere collision as a whole collider object from all the collider it holds
// then handles all the collider in the Mulit Collider Object with its own collision check.
// </summary>
// ***********************************************************************
#include "MultiCollider.h"
#include <iostream>

MultiCollider::MultiCollider()
{
}

MultiCollider::MultiCollider(MultiCollider& collider)
{
    m_position = collider.m_position;
	m_rotation = collider.m_rotation;
	m_scale = collider.m_scale;
	m_mass = collider.m_mass;
	m_velocity = collider.m_velocity;
	m_acceleration = collider.m_acceleration;
    m_multipleCollider = collider.m_multipleCollider;
	m_id = collider.m_id;
}

MultiCollider::~MultiCollider()
{
}

void MultiCollider::init(
		PxVec3 position,
		PxQuat rotation,
		float scale,
		float mass,
		PxVec3 velocity,
		PxVec3 acceleration,
        int id)
{
	Collider::init(position, rotation, scale, mass, velocity, acceleration, id);
    m_radiusSphere = 0.0f;
    m_shapeCollider = ShapeCollider::OTHER;
}

void MultiCollider::addColliderToObject(Collider* collider)
{
	/*
    //Set the collider id so it is part of the Multi Collider 
    collider->setID(m_id);
    m_multipleCollider.push_back(collider);
	m_distanceColliderFromCenterOfGravity.push_back(PxVec3(0.0f, 0.0f, 0.0f));

	//Set the Center of the gravity
	m_position = PxVec3(0.0f, 0.0f, 0.0f);
	for (size_t i = 0; i < m_multipleCollider.size(); i++)
	{
		m_position += m_multipleCollider[i]->getPosition();
	}
	m_position /= (PxReal)m_multipleCollider.size();

    //Calculate the highest radius of the multiple collider object
    m_radiusSphere = 0.0f;
    for (size_t i = 0; i < m_multipleCollider.size(); i++)
    {
        //if the current radius sphere is smaller then the specific collider disance from Multi Collider position and specific collider radius then
        if (m_radiusSphere < (m_multipleCollider[i]->getPosition() - m_position).magnitude() + m_multipleCollider[i]->getRadiusSphere())
        {
            //Update the value of the radius
            m_radiusSphere = (m_multipleCollider[i]->getPosition() - m_position).magnitude() + m_multipleCollider[i]->getRadiusSphere();
        }
    }

	//Set the distance for each collider from the center of gravity of the colliders
	for (size_t i = 0; i < m_multipleCollider.size(); i++)
	{
		m_distanceColliderFromCenterOfGravity[i] = m_multipleCollider[i]->getPosition() - m_position;
	}
    */

	//Set the collider id so it is part of the Multi Collider 
	collider->setID(m_id);
	m_multipleCollider.push_back(collider);
	m_distanceColliderFromCenterOfGravity.push_back(collider->getPosition() - m_position);
	m_offsetRotationFromMultiCollider.push_back(collider->getRotation() * m_rotation.getConjugate());

	//Calculate the highest radius of the multiple collider object
	m_radiusSphere = 0.0f;
	float distance = 0.0f;
	for (size_t i = 0; i < m_multipleCollider.size(); i++)
	{
		distance = (m_multipleCollider[i]->getPosition() - m_position).magnitude() + m_multipleCollider[i]->getRadiusSphere();
		//if the current radius sphere is smaller then the specific collider distance from Multi Collider position and specific collider radius then
		if (m_radiusSphere < distance)
		{
			//Update the value of the radius
			m_radiusSphere = distance;
		}
	}
}

std::vector<Collider*> MultiCollider::checkCollision( std::vector<Collider*> collidableObjects ) 
{
    //Create a vector of collided object it collided with
	std::vector<Collider*> collidedObject;
    std::vector<Collider*> collidedPartObject;
    std::vector<Collider*> trueCollidedObject;

    //Call base class collision check to take out any unnecessary collision check 
    collidedObject = SphereCollider::checkCollision(collidableObjects);

    //If there were any collision then
    if (collidedObject.size() > 0)
    {
        //Loop through all the parts in the multi-collider and check collision with the ones that passed the collision
        for (size_t i = 0; i < m_multipleCollider.size(); i++)
        {
            //Get the collision of this specific collider
            collidedPartObject = m_multipleCollider[i]->checkCollision(collidedObject);
            //Loop through all the collided objects of this specific collider
            for (size_t j = 0; j < collidedPartObject.size(); j++)
            {
                //If type of collider is another multi then
                if (collidedPartObject[j]->getShapeCollider() == ShapeCollider::OTHER)
                {
                    //Check collision with this Collider with the Multi Colliders colliders
                    if (!multiMultiCollisionCheck(m_multipleCollider[i], dynamic_cast<MultiCollider*>(collidedPartObject[j])))
                    {
                        //Remove the multi collider from the colllided part objects
                        collidedPartObject.erase(collidedPartObject.begin() + j);
                        j--;
                    }
                }
            }
            //If there were any collision then
            if (collidedPartObject.size() > 0)
            {
                //std::cout << "Multi Collided" << std::endl;
                //Push back all the collided object
                for (size_t i = 0; i < collidedPartObject.size(); i++)
                {
                    //Add all the collider that collided with the specific multi collider to the return collided object 
                    trueCollidedObject.push_back(collidedPartObject[i]);
                }
            }
        }
    }
    
    //If the return collided object is more than 0 then 
	if (trueCollidedObject.size() > 0)
	{
		m_collided = true;
	}
    //No return collided objects meaning no collision
	else
	{
		m_collided = false;
	}

    //Return the collided objects
	return trueCollidedObject;
}

bool MultiCollider::checkCollision(Collider* collidableObject)
{
	//If there were any collision then
	if (SphereCollider::checkCollision(collidableObject))
	{
		//Loop through all the parts in the multi-collider and check collision with the ones that passed the collision
		for (size_t i = 0; i < m_multipleCollider.size(); i++)
		{
			//Get the collision of this specific collider
			if (m_multipleCollider[i]->checkCollision(collidableObject))
			{
				if (collidableObject->getShapeCollider() == ShapeCollider::OTHER)
				{
					if (dynamic_cast<MultiCollider*>(collidableObject)->checkCollision(m_multipleCollider[i]))
					{
						return true;
					}
				}
				else
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool MultiCollider::checkCollision(PxVec3 rayPosition, PxVec3 rayDirection, float &timeOfCollision)
{
	float shortestTimeOfCollision = 9999999.0f;
	bool collided = false;

	//Check collision with the total radius collider
	if (SphereCollider::checkCollision(rayPosition, rayDirection, timeOfCollision))
	{
		//Loop through all the colliders
		for (size_t i = 0; i < m_multipleCollider.size(); i++)
		{
			//Check the collision with specific collider
			if (m_multipleCollider[i]->checkCollision(rayPosition, rayDirection, timeOfCollision))
			{
				//Collision is true
				collided = true;
				//Check to see if this is the shortest distance
				if (shortestTimeOfCollision > timeOfCollision)
				{
					shortestTimeOfCollision = timeOfCollision;
				}
			}
		}
	}
	//Set the collision time (shortest distance of time)
	timeOfCollision = shortestTimeOfCollision;
	//Return the collision flag
	return collided;
}

bool MultiCollider::multiMultiCollisionCheck(Collider* mulitSpecficCollider, MultiCollider* multiCollider)
{
    //Create a vector of collided object it collided with
    std::vector<Collider*> collidedObjects;
    //Check collision with this Collider with the Multi Colliders colliders
    collidedObjects = mulitSpecficCollider->checkCollision(multiCollider->getMultiCollider());
    //if there are any collider in the vector then collision was true
    if (collidedObjects.size() > 0)
    {
        return true;
    }
    //No collision then return false
    return false;
}

void MultiCollider::applyRotation(PxQuat rotation)
{
    //Apply the rotation on all the collider in the multi collider
    for (size_t i = 0; i < m_multipleCollider.size(); i++)
    {
        m_multipleCollider[i]->applyRotation(rotation);
    }
    //Apply rotation on the multi collider
    Collider::applyRotation(m_rotation);
}

void MultiCollider::applyForce(PxVec3 force)
{
    //Apply the force on all the collider in the multi collider
    for (size_t i = 0; i < m_multipleCollider.size(); i++)
    {
        m_multipleCollider[i]->applyForce(force);
    }
    //Apply force on the multi collider
    Collider::applyForce(force);
}

void MultiCollider::applyAcceleration(PxVec3 accel)
{
    //Apply the acceleration on all the collider in the multi collider
    for (size_t i = 0; i < m_multipleCollider.size(); i++)
    {
        m_multipleCollider[i]->applyAcceleration(accel);
    }
    //Apply acceleration on the multi collider
    Collider::applyAcceleration(accel);
}

void MultiCollider::update(float timeStep)
{
    //Update all the collider in the multi collider
	for (size_t i = 0; i < m_multipleCollider.size(); i++)
    {
        m_multipleCollider[i]->update(timeStep);
    }
    //Update the multi collider
    Collider::update(timeStep);
}
