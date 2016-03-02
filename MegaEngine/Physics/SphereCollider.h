// ***********************************************************************
// Author           : Christopher Maeda
// Created          : 09-15-2015
//
// Last Modified By : Christopher Maeda
// Last Modified On : 02-27-2016
// ***********************************************************************
// <copyright file="SphereCollider.h" company="">
//     Copyright (c) . All rights reserved.
// </copyright>
// <summary>7
// A derived class of Collider.
// This class will handle sphere to sphere collision only.
// </summary>
// ***********************************************************************
#pragma once

#include "Collider.h"

/// <summary>
/// A derived class of Collider.
/// This class will handle sphere to sphere collision only.
/// </summary>
/// <seealso cref="Collider" />
class SphereCollider : public Collider
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="SphereCollider"/> class.
	/// </summary>
	SphereCollider();
	/// <summary>
	/// Initializes a new instance of the <see cref="SphereCollider"/> class.
	/// </summary>
	/// <param name="collider">The collider.</param>
	SphereCollider(SphereCollider& collider);
	/// <summary>
	/// Finalizes an instance of the <see cref="SphereCollider"/> class.
	/// </summary>
	~SphereCollider();

	/// <summary>
	/// Initialize the member variable value of the Sphere Collider.
	/// </summary>
	/// <param name="position">Position of the Sphere Collider.</param>
	/// <param name="rotation">Rotation of the Sphere Collider .</param>
	/// <param name="scale">Scale of the Sphere Collider.</param>
	/// <param name="mass">Mass of the Sphere Collider.</param>
	/// <param name="velocity">Starting Velocity of the Sphere Collider.</param>
	/// <param name="acceleration">Starting Acceleration of the Sphere Collider.</param>
	/// <param name="radiusSphere">Radius of the Sphere Collider.</param>
	/// <param name="id">The identifier of the Sphere Collider.</param>
	void init(
		glm::vec3 position,
		glm::quat rotation,
		float scale,
		float mass,
		glm::vec3 velocity,
		glm::vec3 acceleration,
		float radiusSphere,
		int id = 0
		);  

	/// <summary>
	/// Check the collision with this Sphere Collider with the vector of Colliders.
	/// </summary>
	/// <param name="collidableObjects">Vectors of Colliders this Sphere Collider will be checking.</param>
	/// <returns>Vector of Collider this Sphere Collider collided with.</returns>
	virtual std::vector<Collider*> checkCollision(std::vector<Collider*> collidableObjects);

	/// <summary>
	/// Check the collision with this Sphere Collider with the Collider
	/// </summary>
	/// <param name="collidableObjects">Collider this Sphere Collider will be checking.</param>
	/// <returns>Return bool flag to determine this Sphere Collider collided with the Collider</returns>
	virtual bool checkCollision(Collider* collidableObject) override;

	/// <summary>
	/// Check the collision with this Sphere Collider with the ray
	/// </summary>
	/// <param name="rayPosition">Ray Position.</param>
	/// <param name = "rayDirection">Ray Direction.</param>
	/// <returns>Return bool flag to determine this Sphere Collider collided with the ray</returns>
	virtual bool checkCollision(glm::vec3 rayPosition, glm::vec3 rayDirection, float &timeOfCollision) override;

};

