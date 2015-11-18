/*
A basic physics world that updates all the Collider collision and physics.
It has a position and radius for culling out any collider to update by using distance check.

Author: Christopher Maeda
Last Edit: November 18 2015
*/


#pragma once

#include "MultiCollider.h"

class World
{
public:
	World();
	~World();
	
    /*
		Description: Initialize the member variable value of the World
		Parameter: 
		@param position - Position of the World
		@param radius - Radius of the World (Sphere World)
		Return: None
	*/
	void init(glm::vec3 position, float radius);

    /*
		Description: Update all the Colliders in the World
		Parameter: 
		@param timeStep - Time step from last time update to current update time (displacement of the time)
		Return: None
	*/
	void update(float timeStep);
	
    /*
        Description: Check to see if the Collider is inside the World space 
		Parameter: 
		@param collidableObject - Specific Collider to check if its inside the World
		Return: Boolean telling if the Specific Collider is inside the World
    */
	bool checkInsideWorld(Collider* collidableObject);

    /*
        Description: Add the specific collider to the World 
        Parameter: 
        @param collider - The collider that will be added to the World
        Return: None
    */
	void addCollidableObject(Collider* collidableObject);

    /*
        Description: Apply a rebound acceleration to the first Collider object from the 2 Colliders colliding
        Parameter: 
        @param obj1 - The first collider object of the 2 Colliders colliding
        @param obj2 - The second collider object of the 2 Colliders colliding
        @param timeStep - Time step from last time update to current update time (displacement of the time)
        Return: None
    */
	void calculateCollision(Collider* obj1, Collider* obj2, float timeStep);
	
    //Properties Getters

    glm::vec3 getPosition()
	{
		return m_position;
	}

	float getRadius()
	{
		return m_radius;
	}

	std::vector<Collider*> getColliders()
	{
		return colliders;
	}

    //Properties Setters

	void setPosition(glm::vec3& newPosition)
	{
		m_position = newPosition;
	}

	void setRadius(float newRadius)
	{
		m_radius = newRadius;
	}

private:
	std::vector<Collider*> colliders;

	glm::vec3 m_position;

	float m_radius;
};

