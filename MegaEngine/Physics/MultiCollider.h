// ***********************************************************************
// Author           : Christopher Maeda
// Created          : 09-15-2015
//
// Last Modified By : Jesse Derochie
// Last Modified On : 03-01-2016
// ***********************************************************************
// <copyright file="MultiCollider.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
// A derived class of PolygonCollider.
// This class will handle sphere to sphere collision as a whole collider object from all the collider it holds
// then handles all the collider in the Mulit Collider Object with its own collision check.
// </summary>
// ***********************************************************************
#pragma once

#include "PolygonCollider.h"

/// <summary>
/// A derived class of PolygonCollider.
/// This class will handle sphere to sphere collision as a whole collider object from all the collider it holds
/// then handles all the collider in the Mulit Collider Object with its own collision check.
/// </summary>
/// <seealso cref="PolygonCollider" />
class MultiCollider : public PolygonCollider
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="MultiCollider"/> class.
	/// </summary>
	MultiCollider();
	/// <summary>
	/// Initializes a new instance of the <see cref="MultiCollider"/> class.
	/// </summary>
	/// <param name="collider">The collider.</param>
	MultiCollider(MultiCollider& collider);
	/// <summary>
	/// Finalizes an instance of the <see cref="MultiCollider"/> class.
	/// </summary>
	~MultiCollider();
    
	/// <summary>
	/// Initialize the member variable value of the Multi Collider.
	/// </summary>
	/// <param name="position">Position of the Multi Collider.</param>
	/// <param name="rotation">Rotation of the Multi Collider.</param>
	/// <param name="scale">Scale of the Multi Collider.</param>
	/// <param name="mass">Mass of the Multi Collider.</param>
	/// <param name="velocity">Starting Velocity of the Multi Collider.</param>
	/// <param name="acceleration">Starting Acceleration of the Multi Collider.</param>
	/// <param name="id">The identifier of the Multi Collider.</param>
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
	/// Add the specific collider to the Multi Collider.
	/// </summary>
	/// <param name="collider">The collider that will be added to the Multi Collider.</param>
	void addColliderToObject(Collider* collider);

	/// <summary>
	/// Check the collision with this Multi Collider with the vector of Colliders.
	/// </summary>
	/// <param name="collidableObjects">Vectors of Colliders this Multi Collider will be checking.</param>
	/// <returns>Vector of Collider this Multi Collider collided with.</returns>
	virtual std::vector<Collider*> checkCollision(std::vector<Collider*> collidableObjects) override;

	/// <summary>
	/// Check the collision with this Multi Collider with the Collider
	/// </summary>
	/// <param name="collidableObjects">Collider this Multi Collider will be checking.</param>
	/// <returns>Return bool flag to determine this Multi Collider collided with the Collider</returns>
	virtual bool checkCollision(Collider* collidableObject) override;

	/// <summary>
	/// Check the collision with the specific Collider in the Multi Collider with the other Multi Collider Object (Different Multi Collider objects).
	/// </summary>
	/// <param name="mulitSpecficCollider">Specific Collider in the Multi Collider.</param>
	/// <param name="multiCollider">Other Multi Collider this Collider is checking.</param>
	/// <returns>Boolean telling if the specific collider in the Multi Collider collided with the other Multi Collider.</returns>
	bool multiMultiCollisionCheck(Collider* mulitSpecficCollider, MultiCollider* multiCollider);

	/// <summary>
	/// Rotate the Multi Collider and the collider in the Multi Collider.
	/// </summary>
	/// <param name="rotation">Quaternion value of how much to rotate the Colliders.</param>
	virtual void applyRotation(physx::PxQuat rotation) override;

	/// <summary>
	/// Update force value of the Multi Collider and the collider in the Multi Collider.
	/// </summary>
	/// <param name="force">A Force value of how much force is being applied to the Colliders.</param>
	virtual void applyForce(physx::PxVec3 force) override;

	/// <summary>
	/// Update acceleration value of the Multi Collider and the collider in the Multi Collider.
	/// </summary>
	/// <param name="accel">A Acceleation value of how much acceleration is being applied to the Colliders.</param>
	virtual void applyAcceleration(physx::PxVec3 accel) override;

	/// <summary>
	/// Update the values of the Multi Collider and the collider in the Multi Collider.
	/// </summary>
	/// <param name="timeStep">Time step from last time update to current update time (displacement of the time).</param>
	virtual void update(float timeStep) override;

    //Properties Getters
	/// <summary>
	/// Gets the multi collider.
	/// </summary>
	/// <returns>The vector colliders.</returns>
	std::vector<Collider*> getMultiCollider()
    {
        return m_multipleCollider;
    }

private:
	/// <summary>
	/// The multiple collider.
	/// </summary>
	std::vector<Collider*> m_multipleCollider;
	/// <summary>
	/// The distance this collider is from the center of gravity
	/// </summary>
	std::vector<physx::PxVec3> m_distanceColliderFromCenterOfGravity;
};

