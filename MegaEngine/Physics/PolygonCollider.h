/*
A derived class of SphereCollider.
This class will handle sphere to sphere collision from base class then handle
Separating Axis Theorm collision check.

Author: Christopher Maeda
Last Edit: November 18 2015
*/

#pragma once

#include "SphereCollider.h"

class PolygonCollider : public SphereCollider
{
public:
	PolygonCollider();
    PolygonCollider(PolygonCollider& collider);
	~PolygonCollider();
	
	/*
		Description: Initialize the member variable value of the Polygon Collider
		Parameter: 
		@param position - Position of the Polygon Collider
		@param rotation - Rotation of the Polygon Collider 
		@param scale - Scale of the Polygon Collider
		@param mass - Mass of the Polygon Collider
		@param velocity - Starting Velocity of the Polygon Collider
		@param acceleration - Starting Acceleration of the Polygon Collider
		@param halfWidth - Half width of the Polygon Collider
		@param halfHeight - Half height of the Polygon Collider
		@param halfDepth - Half depth of the Polygon Collider
		@param id - id of the Polygon Collider
		Return: None
	*/
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

	/*
		Description: Check the collision with this Polygon Collider with the vector of Colliders
		Parameter: 
		@param collidableObjects - Vectors of Colliders this Polygon Collider will be checking
		Return: Vector of Collider this Polygon Collider collided with
	*/
    virtual std::vector<Collider*> checkCollision( std::vector<Collider*> collidableObjects ) override; 

	/*
		Description: Check the collision with this Polygon Collider with the other Polygon Collider using Separating Axis Theorm
		Parameter: 
		@param collidableObjects - Collider this collider will be checking
		Return: Boolean telling if this collider collided with the other collider
	*/
	bool checkSATCollision( PolygonCollider* collidableObject);

	/*
		Description: Check the collision with the specific axis and the Polygon Collider
		Parameter:
		@param tPosition - Vector from this Collider Position to the other Collider Position
		@param axis - Specific axis to check
		@param rightDirection1 - Right direction of this Polygon Collider 
		@param upDirection1 - Up direction of this Polygon Collider
		@param forwardDirection1 - Forward direction of this Polygon Collider
		@param rightDirection2 - Right Direction of the other Polygon Collider
		@param upDirection2 - Up Direction of the other Polygon Collider
		@param forwardDirection2 - Forward Direction of the other Polygon Collider
		@param collidableObject - Other Polygon Collider (Collider to check with)
        Return: Boolean telling if this axis collided with the other collider
	*/
	bool checkAxisCollision(glm::vec3 tPosition, glm::vec3 axis, glm::vec3 rightDirection1, glm::vec3 upDirection1, glm::vec3 forwardDirection1, 
		glm::vec3 rightDirection2, glm::vec3 upDirection2, glm::vec3 forwardDirection2, PolygonCollider* collidableObject);

    /*
        Description: Convert the quaternion to a vector format in the x axis rotation 
        Parameter: 
        @param quat - Quaternion value to convert to vectors
        Return: Vector of the x axis rotation
    */
    glm::vec3 GetRightVector(glm::quat quat) 
    {
        return glm::vec3( 1 - 2 * (quat.y * quat.y - quat.z * quat.z),
                        2 * (quat.x * quat.y - quat.w * quat.z),
                        2 * (quat.x * quat.z + quat.w * quat.y));
    }

    /*
        Description: Convert the quaternion to a vector format in the y axis rotation 
        Parameter: 
        @param quat - Quaternion value to convert to vectors
        Return: Vector of the y axis rotation
    */
    glm::vec3 GetUpVector(glm::quat quat) 
    {
	    return glm::vec3( 2 * (quat.x * quat.y + quat.w * quat.z), 
                        1 - 2 * (quat.x * quat.x + quat.z * quat.z),
                        2 * (quat.y * quat.z - quat.w * quat.x));
    }

    /*
        Description: Convert the quaternion to a vector format in the z axis rotation 
        Parameter: 
        @param quat - Quaternion value to convert to vectors
        Return: Vector of the z axis rotation
    */
    glm::vec3 GetForwardVector(glm::quat quat) 
    {
	    return glm::vec3( 2 * (quat.x * quat.z - quat.w * quat.y), 
                        2 * (quat.y * quat.z + quat.w * quat.x),
                        1 - 2 * (quat.x * quat.x + quat.y * quat.y));
    }
 

	//Properties Getters

    float getHalfWidth()
	{
		return m_halfWidth;
	}

	float getHalfHeight()
	{
		return m_halfHeight;
	}

	float getHalfDepth()
	{
		return m_halfDepth;
	}

protected:
	float m_halfWidth, m_halfHeight, m_halfDepth;

};

