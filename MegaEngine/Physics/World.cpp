// ***********************************************************************
// Author           : Christopher Maeda
// Created          : 09-15-2015
//
// Last Modified By : Pavan
// Last Modified On : 01-24-2016
// ***********************************************************************
// <copyright file="World.h" company="">
//     Copyright (c) . All rights reserved.
// </copyright>
// <summary>
// A basic physics world that updates all the Collider collision and physics.
// It has a position and radius for culling out any collider to update by using distance check.
// </summary>
// ***********************************************************************
#include "World.h"

World::World()
{
	m_position = glm::vec3(0);
	m_radius = 0;
}

World::~World()
{
}

void World::init(glm::vec3 position, float radius)
{
	m_position = position;
	m_radius = radius;
}

void World::update(float timeStep)
{
	//Update all the collision
	for (size_t i = 0; i < colliders.size(); i++)
	{
		//Check if the object is inside the world
		if (checkInsideWorld(colliders[i]))
		{
			//Get the vector of collided objects
			std::vector<Collider*> collidedObjects = colliders[i]->checkCollision(colliders);
			//Loop to calculate all the forces needed to be added with the current collider with the collided objects
			for (size_t j = 0; j < collidedObjects.size(); j++)
			{
				calculateCollision(colliders[i], collidedObjects[j], timeStep);
			}
		}
	}
	//Update all the physics
	for (size_t i = 0; i < colliders.size(); i++)
	{
		//Check if the object is inside the world
		if (checkInsideWorld(colliders[i]))
		{
			colliders[i]->update(timeStep);
		}
	}
}
	
bool World::checkInsideWorld(Collider* collidableObject)
{
	//Get the distance from this position to the other position
	float distance = glm::length(collidableObject->getPosition() - m_position);
	//Check to see if the 2 radius is lower than distance magnitude
	if (m_radius + collidableObject->getRadiusSphere() > distance)
	{
		return true;
	}
	return false;
}

void World::addCollidableObject(Collider* collidableObject)
{
	colliders.push_back(collidableObject);
}

void World::calculateCollision(Collider* obj1, Collider* obj2, float timeStep)
{
	//Get the final velcoity of the first object from the idea of elastic collision formula
	glm::vec3 finalVelcoty = ((obj1->getMass() - obj2->getMass()) / (obj1->getMass() + obj2->getMass())) * obj1->getVelocity() + 
		((2 * obj2->getMass()) / (obj1->getMass() + obj2->getMass())) * obj2->getVelocity();
	//Push in the acceleration to first object using the formula:
	//Final vel = initial vel + acceleration * time
	obj1->applyAcceleration( ((finalVelcoty - obj1->getVelocity()) / timeStep) * 1.0f );
}