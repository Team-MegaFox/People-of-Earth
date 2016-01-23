/*
Base abstract class that has all the functionality to handle collision.
This class will know what type of collider it is.
It will have basic physics representation in the world such as position.
It has it's own ID number to know if it is not check itself for collision or part of another collider
It also has a bool flag to know if this class collided or not

Author: Christopher Maeda
Last Edit: November 18 2015
*/

#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>

//Enum of what kind of Collider the collider is
enum ShapeCollider{
	QUAD,
	SPHERE,
	CYLINDER,
	OTHER
};	

class Collider
{
public:
    Collider();
	Collider(Collider& collider);
    ~Collider();

	/*
		Description: Initialize the member variable value of the Collider
		Parameter: 
		@param position - Position of the Collider
		@param rotation - Rotation of the Collider 
		@param scale - Scale of the Collider
		@param mass - Mass of the Collider
		@param velocity - Starting Velocity of the Collider
		@param acceleration - Starting Acceleration of the Collider
		@param id - id of the Collider
		Return: None
	*/
	void init(
		glm::vec3 position,
		glm::quat rotation,
		float scale,
		float mass,
		glm::vec3 velocity,
		glm::vec3 acceleration,
        int id = 0
    );

	/*
		Description: Rotate the Collider
		Parameter: 
		@param rotation - Quaternion value of how much to rotate the Collider
		Return: None
	*/
    virtual void applyRotation(glm::quat rotation);

	/*
		Description: Update force value of the Collider
		Parameter: 
		@param force - A Force value of how much force is being applied to the Collider
		Return: None
	*/
    virtual void applyForce(glm::vec3 force);

	/*
		Description: Update acceleration value of the Collider
		Parameter:
		@param acceleration - A Acceleation value of how much acceleration is being applied to the Collider
		Return: None
	*/
	virtual void applyAcceleration(glm::vec3 accel);

	/*
		Description: Check the collision with this Collider with the vector of Colliders
		Parameter: 
		@param collidableObjects - Vectors of Colliders this collider will be checking
		Return: Vector of Collider this collider collided with
	*/
	virtual std::vector<Collider*> checkCollision( std::vector<Collider*> collidableObjects ) = 0;

	/*
		Description: Create an ID value for this collider
		Parameter: None
		Return: None
	*/
	void createUniqueID();

	/*
		Description: Update the values of the Collider
		Parameter: 
		@param timeStep - Time step from last time update to current update time (displacement of the time)
		Return: None
	*/
	virtual void update(float timeStep);

    //Properties Getters

    ShapeCollider getShapeCollider()
	{
		return m_shapeCollider;
	}

	float getRadiusSphere()
	{
		return m_radiusSphere;
	}

	glm::vec3 getPosition()
	{
		return m_position;
	}

	glm::quat getRotation()
	{
		return m_rotation;
	}

	float getScale()
	{
		return m_scale;
	}

	float getMass()
	{
		return m_mass;
	}

	int getID()
	{
		return m_id;
	}

	glm::vec3 getVelocity()
	{
		return m_velocity;
	}

	glm::vec3 getAcceleration()
	{
		return m_acceleration;
	}

	bool getCollided()
	{
		return m_collided;
	}

    //Properties Setters

    void setID(int id)
	{
		m_id = id;
	}

protected:
    ShapeCollider m_shapeCollider;
	float m_radiusSphere; 
	glm::vec3 m_position;
	glm::quat m_rotation; 
	float m_scale;
	float m_mass;
    int m_id;
    glm::vec3 m_velocity;
	glm::vec3 m_acceleration;
	bool m_collided;
};

