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
#pragma once

#include "MultiCollider.h"

/// <summary>
/// A basic physics world that updates all the Collider collision and physics.
/// It has a position and radius for culling out any collider to update by using distance check.
/// </summary>
class World
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="World"/> class.
	/// </summary>
	World();
	/// <summary>
	/// Finalizes an instance of the <see cref="World"/> class.
	/// </summary>
	~World();

	/// <summary>
	/// Initialize the member variable value of the World.
	/// </summary>
	/// <param name="position">Position of the World.</param>
	/// <param name="radius">Radius of the World (Sphere World).</param>
	void init(PxVec3 position, float radius);

	/// <summary>
	/// Update all the Colliders in the World.
	/// </summary>
	/// <param name="timeStep">Time step from last time update to current update time (displacement of the time).</param>
	void update(float timeStep);
	
	/// <summary>
	/// Check to see if the Collider is inside the World space.
	/// </summary>
	/// <param name="collidableObject">Specific Collider to check if its inside the World.</param>
	/// <returns>Boolean telling if the Specific Collider is inside the World.</returns>
	bool checkInsideWorld(Collider* collidableObject);

	/// <summary>
	/// Add the specific collider to the World.
	/// </summary>
	/// <param name="collidableObject">The collider that will be added to the World.</param>
	void addCollidableObject(Collider* collidableObject);

	/// <summary>
	/// Remove the specific collider to the World.
	/// </summary>
	/// <param name="collidableObject">The collider that will be added to the World.</param>
	void removeCollidableObject(Collider* collidableObject);

	/// <summary>
	/// Apply a rebound acceleration to the first Collider object from the 2 Colliders colliding.
	/// </summary>
	/// <param name="obj1">The first collider object of the 2 Colliders colliding.</param>
	/// <param name="obj2">The second collider object of the 2 Colliders colliding.</param>
	/// <param name="timeStep">Time step from last time update to current update time (displacement of the time).</param>
	void calculateCollision(Collider* obj1, Collider* obj2, float timeStep);
	
    //Properties Getters
	/// <summary>
	/// Gets the position vector.
	/// </summary>
	/// <returns>The position vector.</returns>
	PxVec3 getPosition()
	{
		return m_position;
	}

	/// <summary>
	/// Gets the radius.
	/// </summary>
	/// <returns>The radius.</returns>
	float getRadius()
	{
		return m_radius;
	}

	/// <summary>
	/// Gets the colliders.
	/// </summary>
	/// <returns>The colliders.</returns>
	std::vector<Collider*> getColliders()
	{
		return colliders;
	}

    //Properties Setters

	/// <summary>
	/// Sets the position vector.
	/// </summary>
	/// <param name="newPosition">The new position.</param>
	void setPosition(const PxVec3& newPosition)
	{
		m_position = newPosition;
	}

	/// <summary>
	/// Sets the radius.
	/// </summary>
	/// <param name="newRadius">The new radius.</param>
	void setRadius(float newRadius)
	{
		m_radius = newRadius;
	}

private:
	/// <summary>
	/// The vector of colliders.
	/// </summary>
	std::vector<Collider*> colliders;

	/// <summary>
	/// The position vector.
	/// </summary>
	PxVec3 m_position;

	/// <summary>
	/// The radius.
	/// </summary>
	float m_radius;
};

