// ***********************************************************************
// Author           : Christopher Maeda
// Created          : 09-15-2015
//
// Last Modified By : Jesse Derochie
// Last Modified On : 03-01-2016
// ***********************************************************************
// <copyright file="Collider.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
// Base abstract class that has all the functionality to handle collision.
// This class will know what type of collider it is.
// It will have basic physics representation in the world such as position.
// It has it's own ID number to know if it is not check itself for collision or part of another collider
// It also has a bool flag to know if this class collided or not
// </summary>
// ***********************************************************************
#pragma once

#include <string>
#include <vector>

#include <PhysX/PxPhysicsAPI.h>

//Enum of what shape the collider is.
enum ShapeCollider{
	QUAD,
	SPHERE,
	OTHER
};	

/// <summary>
/// Base abstract class that has all the functionality to handle collision.
/// This class will know what type of collider it is.
/// It will have basic physics representation in the world such as position.
/// It has it's own ID number to know if it is not check itself for collision or part of another collider
/// It also has a bool flag to know if this class collided or not
/// </summary>
class Collider
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Collider"/> class.
	/// </summary>
	Collider();
	/// <summary>
	/// Initializes a new instance of the <see cref="Collider"/> class.
	/// </summary>
	/// <param name="collider">The collider.</param>
	Collider(Collider& collider);
	/// <summary>
	/// Finalizes an instance of the <see cref="Collider"/> class.
	/// </summary>
	~Collider();

	/// <summary>
	/// Initialize the member variable value of the Collider.
	/// </summary>
	/// <param name="position">Position of the Collider.</param>
	/// <param name="rotation">Rotation of the Collider .</param>
	/// <param name="scale">Scale of the Collider.</param>
	/// <param name="mass">Mass of the Collider.</param>
	/// <param name="velocity">Starting Velocity of the Collider.</param>
	/// <param name="acceleration">Starting Acceleration of the Collider.</param>
	/// <param name="id">The identifier of the Collider.</param>
	void init(
		physx::PxVec3 position,
		physx::PxQuat rotation,
		float scale,
		float mass,
		physx::PxVec3 velocity,
		physx::PxVec3 acceleration,
        int id = 0
    );

	/// <summary>
	/// Rotate the Collider.
	/// </summary>
	/// <param name="rotation">Quaternion value of how much to rotate the Collider.</param>
	virtual void applyRotation(physx::PxQuat rotation);

	/// <summary>
	/// Update force value of the Collider.
	/// </summary>
	/// <param name="force">A Force value of how much force is being applied to the Collider.</param>
	virtual void applyForce(physx::PxVec3 force);

	/// <summary>
	/// Update acceleration value of the Collider.
	/// </summary>
	/// <param name="accel">An acceleation value of how much acceleration is being applied to the Collider.</param>
	virtual void applyAcceleration(physx::PxVec3 accel);

	/// <summary>
	/// Check the collision with this Collider with the vector of Colliders.
	/// </summary>
	/// <param name="collidableObjects">Vectors of Colliders this collider will be checking.</param>
	/// <returns>Vector of Collider this collider collided with.</returns>
	virtual std::vector<Collider*> checkCollision(std::vector<Collider*> collidableObjects) = 0;

	virtual bool checkCollision(Collider* collidableObject) = 0;

	virtual bool checkCollision(physx::PxVec3 rayPosition, physx::PxVec3 rayDirection, float &timeOfCollision) { return false; }

	/// <summary>
	/// Create an ID value for this collider.
	/// </summary>
	void createUniqueID();

	/// <summary>
	/// Update the values of the Collider.
	/// </summary>
	/// <param name="timeStep">Time step from last time update to current update time (displacement of the time).</param>
	virtual void update(float timeStep);

    //Properties Getters
	/// <summary>
	/// Gets the shape collider.
	/// </summary>
	/// <returns>The shape collider.</returns>
	ShapeCollider getShapeCollider()
	{
		return m_shapeCollider;
	}

	/// <summary>
	/// Gets the radius of the sphere.
	/// </summary>
	/// <returns>The radius of the sphere..</returns>
	float getRadiusSphere()
	{
		return m_radiusSphere;
	}

	/// <summary>
	/// Gets the position.
	/// </summary>
	/// <returns>The position vector.</returns>
	physx::PxVec3 getPosition()
	{
		return m_position;
	}

	/// <summary>
	/// Gets the rotation.
	/// </summary>
	/// <returns>The rotation quaternion.</returns>
	physx::PxQuat getRotation()
	{
		return m_rotation;
	}

	/// <summary>
	/// Gets the scale.
	/// </summary>
	/// <returns>The scale.</returns>
	float getScale()
	{
		return m_scale;
	}

	/// <summary>
	/// Gets the mass.
	/// </summary>
	/// <returns>The mass.</returns>
	float getMass()
	{
		return m_mass;
	}

	/// <summary>
	/// Gets the identifier.
	/// </summary>
	/// <returns>The identifier.</returns>
	int getID()
	{
		return m_id;
	}

	/// <summary>
	/// Gets the velocity.
	/// </summary>
	/// <returns>The velocity vector.</returns>
	physx::PxVec3 getVelocity()
	{
		return m_velocity;
	}

	/// <summary>
	/// Gets the acceleration.
	/// </summary>
	/// <returns>The acceleration vector.</returns>
	physx::PxVec3 getAcceleration()
	{
		return m_acceleration;
	}

	/// <summary>
	/// Gets the collided.
	/// </summary>
	/// <returns>If it collided.</returns>
	bool getCollided()
	{
		return m_collided;
	}

    //Properties Setters
	/// <summary>
	/// Sets the radius of the sphere.
	/// </summary>
	/// <param name="id">The radius sphere.</param>
	void setRadiusSphere(float radiusSphere)
	{
		m_radiusSphere = radiusSphere;
	}

	/// <summary>
	/// Sets the position.
	/// </summary>
	/// <param name="id">The position.</param>
	void setPosition(physx::PxVec3 position)
	{
		m_position = position;
	}

	/// <summary>
	/// Sets the rotation.
	/// </summary>
	/// <param name="id">The rotation.</param>
	void setRotation(physx::PxQuat rotation)
	{
		m_rotation = rotation;
	}

	/// <summary>
	/// Sets the scale.
	/// </summary>
	/// <param name="id">The scale.</param>
	void setScale(float scale)
	{
		m_scale = scale;
	}

	/// <summary>
	/// Sets the mass.
	/// </summary>
	/// <param name="id">The mass.</param>
	void setMass(float mass)
	{
		m_mass = mass;
	}

	/// <summary>
	/// Sets the identifier.
	/// </summary>
	/// <param name="id">The identifier.</param>
	void setID(int id)
	{
		m_id = id;
	}

	/// <summary>
	/// Sets the velocity.
	/// </summary>
	/// <param name="id">The velocity.</param>
	void setVelocity(physx::PxVec3 velocity)
	{
		m_velocity = velocity;
	}

	/// <summary>
	/// Sets the acceleration.
	/// </summary>
	/// <param name="id">The acceleration.</param>
	void setAcceleration(physx::PxVec3 acceleration)
	{
		m_acceleration = acceleration;
	}

protected:
	/// <summary>
	/// The shape collider.
	/// </summary>
	ShapeCollider m_shapeCollider;
	/// <summary>
	/// The radius sphere.
	/// </summary>
	float m_radiusSphere;
	/// <summary>
	/// The position vector.
	/// </summary>
	physx::PxVec3 m_position;
	/// <summary>
	/// The rotation vector.
	/// </summary>
	physx::PxQuat m_rotation;
	/// <summary>
	/// The scale.
	/// </summary>
	float m_scale;
	/// <summary>
	/// The mass.
	/// </summary>
	float m_mass;
	/// <summary>
	/// The identifier.
	/// </summary>
	int m_id;
	/// <summary>
	/// The velocity vector.
	/// </summary>
	physx::PxVec3 m_velocity;
	/// <summary>
	/// The acceleration vector.
	/// </summary>
	physx::PxVec3 m_acceleration;
	/// <summary>
	/// if it has collided.
	/// </summary>
	bool m_collided;
};

