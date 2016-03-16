// ***********************************************************************
// Author           : Christopher Maeda and Jesse Derochie
// Created          : 02-04-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 03-01-2016
// ***********************************************************************
// <copyright file="RigidBody.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
/*
This RigidBody.h header was created to allow for the use of colliders in 
MegaEngine.
*/
// </summary>
// ***********************************************************************
#pragma once
#include "GameComponents.h"
#include "..\Physics\MultiCollider.h"
#include "..\Physics\PhysicsEngine.h"

#include <glew/glew.h>
#include <math.h>

class RigidBody : public GameComponent
{
public:

	/// <summary>
	/// Initializes a new instance of the <see cref="RigidBody"/> class
	/// This instance specialized for Sphere Colliders
	/// </summary>
	/// <param name="mass">The mass.</param>
	/// <param name="radius">The radius.</param>
	/// <param name="id">The identifier.</param>
	RigidBody(
		PxVec3 position, 
		PxQuat rotation,
		float mass, 
		float radius, 
		PxVec3 velocity = PxVec3(0.0f, 0.0f, 0.0f), 
		PxVec3 acceleration = PxVec3(0.0f, 0.0f, 0.0f),
		int id = 0)
	{
		m_sphereCollider = new SphereCollider();

		m_sphereCollider->init(
			position,
			rotation,
			0.0f,// *getTransform()->getScale(),		// TODO: This needs to be a vec3 in the sphere collider class
			mass,
			velocity,						
			acceleration,					
			radius,
			id);

		PhysicsEngine::getPhysicsWorld()->addCollidableObject(m_sphereCollider);
	}

	/// <summary>
	/// Initializes a new instance of the <see cref="RigidBody"/> class.
	/// This instance specialized for Polygonal Collider
	/// </summary>
	/// <param name="halfWidth">Width of the half.</param>
	/// <param name="halfHeight">Height of the half.</param>
	/// <param name="halfDepth">The half depth.</param>
	/// <param name="id">The identifier.</param>
	RigidBody(
		PxVec3 position, 
		PxQuat rotation,
		float mass, 
		float halfWidth, 
		float halfHeight, 
		float halfDepth, 
		PxVec3 velocity = PxVec3(0),
		PxVec3 acceleration = PxVec3(0),
		int id = 0)
	{
		m_polyCollider = new PolygonCollider();

		m_polyCollider->init(
			position,
			rotation,
			0,// *getTransform()->getScale(),		// TODO: This needs to be a vec3 in the polygon collider class
			mass,
			velocity,						
			acceleration,			
			halfWidth,
			halfHeight,
			halfDepth,
			id);

		PhysicsEngine::getPhysicsWorld()->addCollidableObject(m_polyCollider);
		//m_checkInput = false;
	}

	/// <summary>
	/// Initializes a new instance of the <see cref="RigidBody"/> class.
	/// This instance specialized for Multi Colliders
	/// </summary>
	/// <param name="mass">The mass.</param>
	/// <param name="id">The identifier.</param>
	RigidBody(
		PxVec3 position,
		PxQuat rotation,
		float mass, 
		PxVec3 velocity = PxVec3(0),
		PxVec3 acceleration = PxVec3(0),
		int id = 0)
	{
		m_multiCollider = new MultiCollider();

		m_multiCollider->init(
			position,
			rotation,
			0,// *getTransform()->getScale(),		// TODO: This needs to be a vec3 in the multi Collider class
			mass,
			velocity,						
			acceleration,						
			id);

		PhysicsEngine::getPhysicsWorld()->addCollidableObject(m_multiCollider);
		//m_checkInput = false;
	}

	/// <summary>
	/// Finalizes an instance of the <see cref="RigidBody"/> class.
	/// </summary>
	~RigidBody()
	{
		if (m_sphereCollider != nullptr)
		{
			PhysicsEngine::getPhysicsWorld()->removeCollidableObject(m_sphereCollider);
			delete m_sphereCollider;
		}
		else if (m_polyCollider != nullptr)
		{
			PhysicsEngine::getPhysicsWorld()->removeCollidableObject(m_polyCollider);
			delete m_polyCollider;
		}
		else if (m_multiCollider != nullptr)
		{
			PhysicsEngine::getPhysicsWorld()->removeCollidableObject(m_multiCollider);
			delete m_multiCollider;
		}
	}

	/// <summary>
	/// Initializes the rigidbody <see cref="RigidBody"/> class
	/// </summary>
	/// <param name="mass">The position.</param>
	/// <param name="radius">The rotation.</param>
	/// <param name="id">The velocity.</param>
	/// <param name="id">The acceleration.</param>
	void init(
		PxVec3 position, 
		PxQuat rotation, 
		PxVec3 velocity, 
		PxVec3 acceleration)
	{
		if (m_sphereCollider != nullptr)
		{
			m_sphereCollider->setPosition(position);
			m_sphereCollider->setRotation(rotation);
			m_sphereCollider->setVelocity(velocity);
			m_sphereCollider->setAcceleration(acceleration);
		}
		else if (m_polyCollider != nullptr)
		{
			m_polyCollider->setPosition(position);
			m_polyCollider->setRotation(rotation);
			m_polyCollider->setVelocity(velocity);
			m_polyCollider->setAcceleration(acceleration);
		}
		else if (m_multiCollider != nullptr)
		{
			m_multiCollider->setPosition(position);
			m_multiCollider->setRotation(rotation);
			m_multiCollider->setVelocity(velocity);
			m_multiCollider->setAcceleration(acceleration);
		}
	}

	/// <summary>
	/// Updates the collider every frame
	/// - updates the position and the rotation of the collider every frame
	/// </summary>
	/// <param name="deltaTime">The delta time.</param>
	virtual void update(float deltaTime) override
	{
		if (m_sphereCollider != nullptr)
		{
			getTransform()->setPosition(m_sphereCollider->getPosition());
			getTransform()->setRotation(m_sphereCollider->getRotation());
		}
		else if (m_polyCollider != nullptr)
		{
			PxVec3 pos = m_polyCollider->getPosition();
			getTransform()->setPosition(m_polyCollider->getPosition());
			getTransform()->setRotation(m_polyCollider->getRotation());
		}
		else if (m_multiCollider != nullptr)
		{
			getTransform()->setPosition(m_multiCollider->getPosition());
			getTransform()->setRotation(m_multiCollider->getRotation());
		}

	}

	/// <summary>
	/// Updates the velocity of the collider.
	/// </summary>
	/// <param name="velocity">The velocity.</param>
	void updateVelocity(PxVec3 velocity)
	{
		if (m_sphereCollider != nullptr)
		{
			m_sphereCollider->setVelocity(velocity);
		}
		else if (m_polyCollider != nullptr)
		{
			m_polyCollider->setVelocity(velocity);
		}
		else if (m_multiCollider != nullptr)
		{
			m_multiCollider->setVelocity(velocity);
		}
	}

	/// <summary>
	/// Updates the acceleration of the collider.
	/// </summary>
	/// <param name="acceleration">The acceleration.</param>
	void updateAcceleration(PxVec3 acceleration)
	{
		if (m_sphereCollider != nullptr)
		{
			m_sphereCollider->applyAcceleration(acceleration);
		}
		else if (m_polyCollider != nullptr)
		{
			m_polyCollider->applyAcceleration(acceleration);
		}
		else if (m_multiCollider != nullptr)
		{
			m_multiCollider->applyAcceleration(acceleration);
		}
	}

	/// <summary>
	/// Updates the rotation of the collider.
	/// </summary>
	/// <param name="rotation">The rotation.</param>
	void updateRotation(PxQuat rotation)
	{
		if (m_sphereCollider != nullptr)
		{
			m_sphereCollider->applyRotation(rotation);
		}
		else if (m_polyCollider != nullptr)
		{
			m_polyCollider->applyRotation(rotation);
		}
		else if (m_multiCollider != nullptr)
		{
			m_multiCollider->applyRotation(rotation);
		}
	}

	/// <summary>
	/// Adds a collider to the multicollider.
	/// </summary>
	/// <param name="collider">The collider.</param>
	/// <returns></returns>
	bool addCollider(Collider& collider)
	{
		if (m_sphereCollider != nullptr)
		{
			return false;
		}
		else if (m_polyCollider != nullptr)
		{
			return false;
		}
		else if (m_multiCollider != nullptr)
		{
			m_multiCollider->addColliderToObject(&collider);
			return true;
		}
	}

	/// <summary>
	/// Renders the specified shader using debug draw mode.
	/// </summary>
	/// <param name="shader">The shader.</param>
	/// <param name="renderingEngine">The rendering engine.</param>
	/// <param name="camera">The camera.</param>
	virtual void render(const Shader& shader, const RenderingEngine& renderingEngine, const Camera3D & camera) const
	{
		if (m_debugDraw)
		{

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glBegin(GL_LINES);

			if (m_sphereCollider != nullptr)
			{
				//Draw the sphere collider
				for (float height = 0.0f; height < 180.0f; height += 1.0f)
				{
					for (float theta = 0.0f; theta < 180.0f; theta += 1.0f)
					{
						glPushMatrix();
						glVertex3f(
							m_sphereCollider->getRadiusSphere() * cosf(height) * cosf(theta * 2 * 3.14159625f / 180.0f),
							m_sphereCollider->getRadiusSphere() * sinf(height),
							m_sphereCollider->getRadiusSphere()  * cosf(height) * sinf(theta * 2 * 3.14159625f / 180.0f));
						glPopMatrix();
					}
				}
			}
			else if (m_polyCollider != nullptr)
			{
				//Draw the polygon collider
				glPushMatrix();
				glVertex3f(m_polyCollider->getHalfWidth(), m_polyCollider->getHalfHeight(), m_polyCollider->getHalfDepth());
				glVertex3f(m_polyCollider->getHalfWidth(), -m_polyCollider->getHalfHeight(), m_polyCollider->getHalfDepth());

				glVertex3f(-m_polyCollider->getHalfWidth(), m_polyCollider->getHalfHeight(), m_polyCollider->getHalfDepth());
				glVertex3f(-m_polyCollider->getHalfWidth(), -m_polyCollider->getHalfHeight(), m_polyCollider->getHalfDepth());
				glVertex3f(m_polyCollider->getHalfWidth(), m_polyCollider->getHalfHeight(), -m_polyCollider->getHalfDepth());
				glVertex3f(m_polyCollider->getHalfWidth(), -m_polyCollider->getHalfHeight(), -m_polyCollider->getHalfDepth());
				glVertex3f(-m_polyCollider->getHalfWidth(), m_polyCollider->getHalfHeight(), -m_polyCollider->getHalfDepth());
				glVertex3f(-m_polyCollider->getHalfWidth(), -m_polyCollider->getHalfHeight(), -m_polyCollider->getHalfDepth());
				glPopMatrix();

				//Draw the sphere collider of the polygon
				for (float height = 0.0f; height < 180.0f; height += 1.0f)
				{
					for (float theta = 0.0f; theta < 180.0f; theta += 1.0f)
					{
						glPushMatrix();
						glVertex3f(
							m_polyCollider->getRadiusSphere() * cosf(height) * cosf(theta * 2 * 3.14159625f / 180.0f),
							m_polyCollider->getRadiusSphere() * sinf(height),
							m_polyCollider->getRadiusSphere()  * cosf(height) * sinf(theta * 2 * 3.14159625f / 180.0f));
						glPopMatrix();
					}
				}
			}
			else if (m_multiCollider != nullptr)
			{
				//m_multiCollider;
			}
			glEnd();
		}
	}

	/// <summary>
	/// Checks collision with this rigidbody and vectors of gameobjects.
	/// </summary>
	/// <param name="rotation">The vectors of gameobjects to check collision.</param>
	std::vector<GameObject*> checkCollision(std::vector<GameObject*> collisionCheckObject)
	{
		//The vector of collided gameojects this rigidbody collided with
		std::vector<GameObject*> collidedObject;
		
		//Loop through the vector of gameobjects
		for (size_t i = 0; i < collisionCheckObject.size(); i++)
		{
			//Check collision with rigidbody and this specific gameobject rigidbody
			if (collisionCheckObject[i]->getGameComponent<RigidBody>()->getCollider()->checkCollision(getCollider()))
			{
				//Collided is true so add it to the vector of collided gameobjects
				collidedObject.push_back(collisionCheckObject[i]);
			}
		}
		//Return the vector of collided gameobjects
		return collidedObject;
	}

	/// <summary>
	/// Gets the position of the collider.
	/// </summary>
	/// <returns></returns>
	PxVec3 getPosition()
	{
		if (m_sphereCollider != nullptr)
		{
			return m_sphereCollider->getPosition();
		}
		else if (m_polyCollider != nullptr)
		{
			return m_polyCollider->getPosition();
		}
		else if (m_multiCollider != nullptr)
		{
			return m_multiCollider->getPosition();
		}
		return PxVec3(PxIdentity);
	}
	
	/// <summary>
	/// Gets the velocity of the collider.
	/// </summary>
	/// <returns></returns>
	PxVec3 getVelocity()
	{
		return getCollider()->getVelocity();
	}

	/// <summary>
	/// Gets the rotation of the collider.
	/// </summary>
	/// <returns></returns>
	PxQuat getRotation()
	{
		if (m_sphereCollider != nullptr)
		{
			return m_sphereCollider->getRotation();
		}
		else if (m_polyCollider != nullptr)
		{
			return m_polyCollider->getRotation();
		}
		else if (m_multiCollider != nullptr)
		{
			return m_multiCollider->getRotation();
		}
		return PxQuat(PxIdentity);
	}

	/// <summary>
	/// Gets the boolean flag of the collider colliding.
	/// </summary>
	/// <returns></returns>
	bool getCollided()
	{
		if (m_sphereCollider != nullptr)
		{
			return m_sphereCollider->getCollided();
		}
		else if (m_polyCollider != nullptr)
		{
			return m_polyCollider->getCollided();
		}
		else if (m_multiCollider != nullptr)
		{
			return m_multiCollider->getCollided();
		}
		return false;
	}

	/// <summary>
	/// Gets the collider.
	/// </summary>
	/// <returns></returns>
	Collider* getCollider()
	{
		if (m_sphereCollider != nullptr)
		{
			return m_sphereCollider;
		}
		else if (m_polyCollider != nullptr)
		{
			return m_polyCollider;
		}
		else if (m_multiCollider != nullptr)
		{
			return m_multiCollider;
		}
		return nullptr;
	}

	/// <summary>
	/// Sets the debug draw mode.
	/// </summary>
	/// <param name="debugDraw">if set to <c>true</c> [debug draw].</param>
	void setDebugDraw(bool debugDraw)
	{
		m_debugDraw = debugDraw;
	}

	/// <summary>
	/// Sets the position of the collider.
	/// </summary>
	/// <param name="rotation">The position.</param>
	void setPosition(PxVec3 position)
	{
		if (m_sphereCollider != nullptr)
		{
			return m_sphereCollider->setPosition(position);
		}
		else if (m_polyCollider != nullptr)
		{
			return m_polyCollider->setPosition(position);
		}
		else if (m_multiCollider != nullptr)
		{
			return m_multiCollider->setPosition(position);
		}
	}

	/// <summary>
	/// Sets the rotation of the collider.
	/// </summary>
	/// <param name="rotation">The rotation.</param>
	void setRotation(PxQuat rotation)
	{
		if (m_sphereCollider != nullptr)
		{
			m_sphereCollider->setRotation(rotation);
		}
		else if (m_polyCollider != nullptr)
		{
			m_polyCollider->setRotation(rotation);
		}
		else if (m_multiCollider != nullptr)
		{
			m_multiCollider->setRotation(rotation);
		}
	}

private:

	/// <summary>
	/// The sphere collider
	/// </summary>
	SphereCollider * m_sphereCollider;
	/// <summary>
	/// The poly collider
	/// </summary>
	PolygonCollider * m_polyCollider;
	/// <summary>
	/// The multi collider
	/// </summary>
	MultiCollider * m_multiCollider;

	/// <summary>
	/// The position of this collider
	/// </summary>
	//glm::vec3 m_position;
	/// <summary>
	/// The rotation of this collider
	/// </summary>
	//glm::quat m_rotation;

	/// <summary>
	/// The zero variable
	/// </summary>
	PxVec3 m_zero = PxVec3(0.0f, 0.0f, 0.0f);

	/// <summary>
	/// The debug draw boolean set this to true to draw the colliders
	/// </summary>
	bool m_debugDraw = false;
};

