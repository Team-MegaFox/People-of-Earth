/*
A derived class of Collider.
This class will handle sphere to sphere collision only.

Author: Christopher Maeda
Last Edit: November 18 2015
*/


#pragma once

#include "Collider.h"

class SphereCollider : public Collider
{
public:
	SphereCollider();
	SphereCollider(SphereCollider& collider);
	~SphereCollider();

	/*
		Description: Initialize the member variable value of the Sphere Collider
		Parameter: 
		@param position - Position of the Sphere Collider
		@param rotation - Rotation of the Sphere Collider 
		@param scale - Scale of the Sphere Collider
		@param mass - Mass of the Sphere Collider
		@param velocity - Starting Velocity of the Sphere Collider
		@param acceleration - Starting Acceleration of the Sphere Collider
		@param radiusSphere - Radius of the Sphere Collider
		@param id - id of the Sphere Collider
		Return: None
	*/
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

	/*
		Description: Check the collision with this Sphere Collider with the vector of Colliders
		Parameter: 
		@param collidableObjects - Vectors of Colliders this Sphere Collider will be checking
		Return: Vector of Collider this Sphere Collider collided with
	*/
    virtual std::vector<Collider*> checkCollision( std::vector<Collider*> collidableObjects );

};

