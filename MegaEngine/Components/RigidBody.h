// ***********************************************************************
// Author           : Christopher Maeda and Jesse Derochie
// Created          : 02-04-2016
//
// Last Modified By : Christopher Maeda
// Last Modified On : 02-22-2016
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
	RigidBody(glm::vec3 position, glm::quat rotation, float mass, float radius, glm::vec3 velocity = glm::vec3(0), glm::vec3 acceleration = glm::vec3(0), int id = 0)
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
	RigidBody(glm::vec3 position, glm::quat rotation, float mass, float halfWidth, float halfHeight, float halfDepth, glm::vec3 velocity = glm::vec3(0), glm::vec3 acceleration = glm::vec3(0), int id = 0)
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
	RigidBody(glm::vec3 position, glm::quat rotation, float mass, glm::vec3 velocity = glm::vec3(0), glm::vec3 acceleration = glm::vec3(0), int id = 0)
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
		}
		else if (m_polyCollider != nullptr)
		{
			PhysicsEngine::getPhysicsWorld()->removeCollidableObject(m_polyCollider);
		}
		else if (m_multiCollider != nullptr)
		{
			PhysicsEngine::getPhysicsWorld()->removeCollidableObject(m_multiCollider);
		}
		delete m_sphereCollider;
		delete m_polyCollider;
		delete m_multiCollider;
	}

	/// <summary>
	/// Initializes the rigidbody <see cref="RigidBody"/> class
	/// </summary>
	/// <param name="mass">The position.</param>
	/// <param name="radius">The rotation.</param>
	/// <param name="id">The velocity.</param>
	/// <param name="id">The acceleration.</param>
	void init(glm::vec3 position, glm::quat rotation, glm::vec3 velocity, glm::vec3 acceleration)
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
			glm::vec3 pos = m_polyCollider->getPosition();
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
	void updateVelocity(glm::vec3 velocity)
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
	void updateAcceleration(glm::vec3 acceleration)
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
	void updateRotation(glm::quat rotation)
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
				for (float height = 0.0f; height < 180.0f; height += 0.0f)
				{
					for (float theta = 0.0f; theta < 180.0f; theta += 0.0f)
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
				for (float height = 0.0f; height < 180.0f; height += 0.0f)
				{
					for (float theta = 0.0f; theta < 180.0f; theta += 0.0f)
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
	/// Gets the position of the collider.
	/// </summary>
	/// <returns></returns>
	glm::vec3 getPosition()
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
		return glm::vec3();
	}

	/// <summary>
	/// Gets the rotation of the collider.
	/// </summary>
	/// <returns></returns>
	glm::quat getRotation()
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
		return glm::quat();
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
	void setPosition(glm::vec3 position)
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
	void setRotation(glm::quat rotation)
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
	glm::vec3 m_zero = glm::vec3(0.0f);

	/// <summary>
	/// The debug draw boolean set this to true to draw the colliders
	/// </summary>
	bool m_debugDraw = false;
};

