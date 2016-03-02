// ***********************************************************************
// Author           : Christopher Maeda
// Created          : 09-15-2015
//
// Last Modified By : Christopher Maeda
// Last Modified On : 02-25-2016
// ***********************************************************************
// <copyright file="PolygonCollider.h" company="">
//     Copyright (c) . All rights reserved.
// </copyright>
// <summary>
// A derived class of SphereCollider.
// This class will handle sphere to sphere collision from base class then handle
// Separating Axis Theorm collision check.
// </summary>
// ***********************************************************************
#pragma once

#include "SphereCollider.h"

/// <summary>
/// A derived class of SphereCollider.
/// This class will handle sphere to sphere collision from base class then handle
/// Separating Axis Theorm collision check.
/// </summary>
/// <seealso cref="SphereCollider" />
class PolygonCollider : public SphereCollider
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="PolygonCollider"/> class.
	/// </summary>
	PolygonCollider();
	/// <summary>
	/// Initializes a new instance of the <see cref="PolygonCollider"/> class.
	/// </summary>
	/// <param name="collider">The collider.</param>
	PolygonCollider(PolygonCollider& collider);
	/// <summary>
	/// Finalizes an instance of the <see cref="PolygonCollider"/> class.
	/// </summary>
	~PolygonCollider();
	
	/// <summary>
	/// Initialize the member variable value of the Polygon Collider.
	/// </summary>
	/// <param name="position">Position of the Polygon Collider.</param>
	/// <param name="rotation">Rotation of the Polygon Collider.</param>
	/// <param name="scale">Scale of the Polygon Collider.</param>
	/// <param name="mass">Mass of the Polygon Collider.</param>
	/// <param name="velocity">Starting Velocity of the Polygon Collider.</param>
	/// <param name="acceleration">Starting Acceleration of the Polygon Collider.</param>
	/// <param name="halfWidth">Half width of the Polygon Collider.</param>
	/// <param name="halfHeight">Half height of the Polygon Collider.</param>
	/// <param name="halfDepth">Half depth of the Polygon Collider.</param>
	/// <param name="id">The identifier of the Polygon Collider.</param>
	void init(
		glm::vec3 position,
		glm::quat rotation,
		float scale,
		float mass,
		glm::vec3 velocity,
		glm::vec3 acceleration,
		float halfWidth,
        float halfHeight,
        float halfDepth,
		int id = 0
		);

	/// <summary>
	/// Check the collision with this Polygon Collider with the vector of Colliders
	/// </summary>
	/// <param name="collidableObjects">Vectors of Colliders this Polygon Collider will be checking.</param>
	/// <returns>Vector of Collider this Polygon Collider collided with.</returns>
	virtual std::vector<Collider*> checkCollision(std::vector<Collider*> collidableObjects) override;

	/// <summary>
	/// Check the collision with this Polygon Collider with the Collider
	/// </summary>
	/// <param name="collidableObjects">Collider this Polygon Collider will be checking.</param>
	/// <returns>Return bool flag to determine this Polygon Collider collided with the Collider</returns>
	virtual bool checkCollision(Collider* collidableObject) override;

	/// <summary>
	/// Check the collision with this Polygon Collider with the other Polygon Collider using Separating Axis Theorm.
	/// </summary>
	/// <param name="collidableObject">Collider this collider will be checking.</param>
	/// <returns>Boolean telling if this collider collided with the other collider.</returns>
	bool checkSATCollision(PolygonCollider* collidableObject);

	/// <summary>
	/// Check the collision with the specific axis and the Polygon Collider.
	/// </summary>
	/// <param name="tPosition">Vector from this Collider Position to the other Collider Position.</param>
	/// <param name="axis">Specific axis to check.</param>
	/// <param name="rightDirection1">Right direction of this Polygon Collider.</param>
	/// <param name="upDirection1">Up direction of this Polygon Collider.</param>
	/// <param name="forwardDirection1">Forward direction of this Polygon Collider.</param>
	/// <param name="rightDirection2">Right Direction of the other Polygon Collider.</param>
	/// <param name="upDirection2">Up Direction of the other Polygon Collider.</param>
	/// <param name="forwardDirection2">Forward Direction of the other Polygon Collider.</param>
	/// <param name="collidableObject">Other Polygon Collider (Collider to check with).</param>
	/// <returns>Boolean telling if this axis collided with the other collider.</returns>
	bool checkAxisCollision(glm::vec3 tPosition, glm::vec3 axis, glm::vec3 rightDirection1, glm::vec3 upDirection1, glm::vec3 forwardDirection1,
		glm::vec3 rightDirection2, glm::vec3 upDirection2, glm::vec3 forwardDirection2, PolygonCollider* collidableObject);

	/// <summary>
	/// Convert the quaternion to a vector format in the x axis rotation.
	/// </summary>
	/// <param name="quat">Quaternion value to convert to vectors.</param>
	/// <returns>Vector of the x axis rotation.</returns>
	glm::vec3 GetRightVector(glm::quat quat)
    {
        return glm::vec3( 1 - 2 * (quat.y * quat.y - quat.z * quat.z),
                        2 * (quat.x * quat.y - quat.w * quat.z),
                        2 * (quat.x * quat.z + quat.w * quat.y));
    }

	/// <summary>
	/// Convert the quaternion to a vector format in the y axis rotation.
	/// </summary>
	/// <param name="quat">Quaternion value to convert to vectors.</param>
	/// <returns>Vector of the y axis rotation.</returns>
	glm::vec3 GetUpVector(glm::quat quat)
    {
	    return glm::vec3( 2 * (quat.x * quat.y + quat.w * quat.z), 
                        1 - 2 * (quat.x * quat.x + quat.z * quat.z),
                        2 * (quat.y * quat.z - quat.w * quat.x));
    }

	/// <summary>
	/// Convert the quaternion to a vector format in the z axis rotation.
	/// </summary>
	/// <param name="quat">Quaternion value to convert to vectors.</param>
	/// <returns>Vector of the z axis rotation.</returns>
	glm::vec3 GetForwardVector(glm::quat quat)
    {
	    return glm::vec3( 2 * (quat.x * quat.z - quat.w * quat.y), 
                        2 * (quat.y * quat.z + quat.w * quat.x),
                        1 - 2 * (quat.x * quat.x + quat.y * quat.y));
    }
 

	//Properties Getters
	/// <summary>
	/// Gets half of the width.
	/// </summary>
	/// <returns>Half of the width.</returns>
	float getHalfWidth()
	{
		return m_halfWidth;
	}

	/// <summary>
	/// Gets half of the height.
	/// </summary>
	/// <returns>Half of the height.</returns>
	float getHalfHeight()
	{
		return m_halfHeight;
	}

	/// <summary>
	/// Gets half the depth.
	/// </summary>
	/// <returns>Half the depth.</returns>
	float getHalfDepth()
	{
		return m_halfDepth;
	}

protected:
	/// <summary>
	/// Half of the width.
	/// </summary>
	float m_halfWidth;
	/// <summary>
	/// Half of the height.
	/// </summary>
	float m_halfHeight;
	/// <summary>
	/// Half of the depth.
	/// </summary>
	float m_halfDepth;

};

