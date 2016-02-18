// ***********************************************************************
// Author           : Christopher Maeda
// Created          : 09-15-2015
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 01-24-2016
// ***********************************************************************
// <copyright file="SphereCollider.h" company="">
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
		glm::vec3 position,
		glm::quat rotation,
		float scale,
		float mass,
		glm::vec3 velocity,
		glm::vec3 acceleration,
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
            float distance = glm::length(collidableObjects[i]->getPosition() - m_position);
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
		std::cout << "Collisions\n";
		m_collided = true;
	}
    //No return collided objects meaning no collision
	else
	{
		std::cout << "No Collisions\n";
		m_collided = false;
	}

	//Return the collided objects
	return collidedObject;
}