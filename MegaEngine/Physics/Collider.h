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

//Enum of what shape the collider is.
enum ShapeCollider{
	QUAD,
	SPHERE,
	CYLINDER,
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
		glm::vec3 position,
		glm::quat rotation,
		float scale,
		float mass,
		glm::vec3 velocity,
		glm::vec3 acceleration,
        int id = 0
    );

	/// <summary>
	/// Rotate the Collider.
	/// </summary>
	/// <param name="rotation">Quaternion value of how much to rotate the Collider.</param>
	virtual void applyRotation(glm::quat rotation);

	/// <summary>
	/// Update force value of the Collider.
	/// </summary>
	/// <param name="force">A Force value of how much force is being applied to the Collider.</param>
	virtual void applyForce(glm::vec3 force);

	/// <summary>
	/// Update acceleration value of the Collider.
	/// </summary>
	/// <param name="accel">An acceleation value of how much acceleration is being applied to the Collider.</param>
	virtual void applyAcceleration(glm::vec3 accel);

	/// <summary>
	/// Check the collision with this Collider with the vector of Colliders.
	/// </summary>
	/// <param name="collidableObjects">Vectors of Colliders this collider will be checking.</param>
	/// <returns>Vector of Collider this collider collided with.</returns>
	virtual std::vector<Collider*> checkCollision(std::vector<Collider*> collidableObjects) = 0;

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
	glm::vec3 getPosition()
	{
		return m_position;
	}

	/// <summary>
	/// Gets the rotation.
	/// </summary>
	/// <returns>The rotation quaternion.</returns>
	glm::quat getRotation()
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
	glm::vec3 getVelocity()
	{
		return m_velocity;
	}

	/// <summary>
	/// Gets the acceleration.
	/// </summary>
	/// <returns>The acceleration vector.</returns>
	glm::vec3 getAcceleration()
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
	/// Sets the identifier.
	/// </summary>
	/// <param name="id">The identifier.</param>
	void setID(int id)
	{
		m_id = id;
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
	glm::vec3 m_position;
	/// <summary>
	/// The rotation vector.
	/// </summary>
	glm::quat m_rotation;
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
	glm::vec3 m_velocity;
	/// <summary>
	/// The acceleration vector.
	/// </summary>
	glm::vec3 m_acceleration;
	/// <summary>
	/// if it has collided.
	/// </summary>
	bool m_collided;
};

