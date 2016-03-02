// ***********************************************************************
// Author           : Christopher Maeda
// Created          : 09-15-2015
//
// Last Modified By : Jesse Derochie
// Last Modified On : 03-01-2016
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
	m_position = PxVec3(0.0f, 0.0f, 0.0f);
	m_radius = 0;
}

World::~World()
{
}

void World::init(PxVec3 position, float radius)
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
				//printf("Collision occured\n");
				//calculateCollision(colliders[i], collidedObjects[j], timeStep);
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
	float distance = (collidableObject->getPosition() - m_position).magnitude();
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

void World::removeCollidableObject(Collider* collidableObject)
{
	for (size_t i = 0; i < colliders.size(); i++)
	{
		if (collidableObject == colliders[i])
		{
			auto it = colliders.begin() + i;
			colliders.erase(it);
		}
	}
}

void World::calculateCollision(Collider* obj1, Collider* obj2, float timeStep)
{
	//Get the final velcoity of the first object from the idea of elastic collision formula
	PxVec3 finalVelcoty = 
		(((obj1->getMass() - obj2->getMass()) / (obj1->getMass() + obj2->getMass())) * obj1->getVelocity())
		+ (((2 * obj2->getMass()) / (obj1->getMass() + obj2->getMass())) * obj2->getVelocity());
	//Push in the acceleration to first object using the formula:
	//Final vel = initial vel + acceleration * time
	obj1->applyAcceleration( ((finalVelcoty - obj1->getVelocity()) / timeStep) * 1.0f );
}