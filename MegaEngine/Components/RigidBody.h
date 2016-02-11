// ***********************************************************************
// Author           : Christopher Maeda and Jesse Derochie
// Created          : 02-04-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 02-05-2016
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
	RigidBody(glm::vec3 position, glm::quat rotation, float mass, float radius, int id = 0)// :
		//m_position(position),
		//m_rotation(rotation)
	{
		m_sphereCollider = new SphereCollider();

		m_sphereCollider->init(
			position,
			rotation,
			0.0f,// *getTransform()->getScale(),		// TODO: This needs to be a vec3 in the sphere collider class
			mass,
			m_zero,						// TODO: Currently there is no place in the engine that can give you the velocity
			m_zero,						// TODO: Currently there is no place in the engine that can give you acceleration
			radius,
			id);

		PhysicsEngine::getPhysicsWorld()->addCollidableObject(m_sphereCollider);
		m_checkInput = false;
	}

	/// <summary>
	/// Initializes a new instance of the <see cref="RigidBody"/> class.
	/// This instance specialized for Polygonal Collider
	/// </summary>
	/// <param name="halfWidth">Width of the half.</param>
	/// <param name="halfHeight">Height of the half.</param>
	/// <param name="halfDepth">The half depth.</param>
	/// <param name="id">The identifier.</param>
	RigidBody(glm::vec3 position, glm::quat rotation, float mass, float halfWidth, float halfHeight, float halfDepth, int id = 0)// :
		//m_position(position),
		//m_rotation(rotation)
	{
		m_polyCollider = new PolygonCollider();

		m_polyCollider->init(
			position,
			rotation,
			0,// *getTransform()->getScale(),		// TODO: This needs to be a vec3 in the polygon collider class
			mass,
			m_zero,						// TODO: Currently there is no place in the engine that can give you the velocity
			m_zero,						// TODO: Currently there is no place in the engine that can give you acceleration
			halfWidth,
			halfHeight,
			halfDepth,
			id);

		PhysicsEngine::getPhysicsWorld()->addCollidableObject(m_polyCollider);
		m_checkInput = false;
	}

	/// <summary>
	/// Initializes a new instance of the <see cref="RigidBody"/> class.
	/// This instance specialized for Multi Colliders
	/// </summary>
	/// <param name="mass">The mass.</param>
	/// <param name="id">The identifier.</param>
	RigidBody(glm::vec3 position, glm::quat rotation, float mass, int id = 0) //:
		//m_position(position),
		//m_rotation(rotation)
	{
		m_multiCollider = new MultiCollider();

		m_multiCollider->init(
			position,
			rotation,
			0,// *getTransform()->getScale(),		// TODO: This needs to be a vec3 in the multi Collider class
			mass,
			m_zero,						// TODO: Currently there is no place in the engine that can give you the velocity
			m_zero,						// TODO: Currently there is no place in the engine that can give you acceleration
			id);

		PhysicsEngine::getPhysicsWorld()->addCollidableObject(m_multiCollider);
		m_checkInput = false;
	}

	/// <summary>
	/// Finalizes an instance of the <see cref="RigidBody"/> class.
	/// </summary>
	~RigidBody()
	{
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

	void setKeyInput(int forwardKey = SDLK_w, int backKey = SDLK_s, int leftKey = SDLK_a, int rightKey = SDLK_d, int upKey = SDLK_z, int downKey = SDLK_x)
	{
		m_forwardKey = forwardKey;
		m_backKey = backKey;
		m_leftKey = leftKey;
		m_rightKey = rightKey;
		m_upKey = upKey;
		m_downKey = downKey;
		m_checkInput = true;
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
			//printf("%f\t%f\t%f\n", getTransform()->getPosition()->x, getTransform()->getPosition()->y, getTransform()->getPosition()->z);
		}
		else if (m_multiCollider != nullptr)
		{
			getTransform()->setPosition(m_multiCollider->getPosition());
			getTransform()->setRotation(m_multiCollider->getRotation());
		}
		//m_position = *getTransform()->getPosition();
		//m_rotation = *getTransform()->getRotation();
	}

	virtual void processInput(const InputManager& input, float delta) override
	{
		if (m_checkInput)
		{
			if (input.KeyDown(m_forwardKey))
			{
				//m_polyCollider->applyRotation(glm::quat(glm::angleAxis(glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f))));
				updateVelocity(Utility::getForward(*getTransform()->getRotation()) * delta * 1000.0f);
			}
			if (input.KeyDown(m_backKey))
			{
				updateVelocity(Utility::getBack(*getTransform()->getRotation()) * delta * 1000.0f);
			}
			if (input.KeyDown(m_leftKey))
			{
				updateVelocity(Utility::getLeft(*getTransform()->getRotation()) * delta * 1000.0f);
			}
			if (input.KeyDown(m_rightKey))
			{
				updateVelocity(Utility::getRight(*getTransform()->getRotation()) * delta * 1000.0f);
			}	
			if (input.KeyDown(m_upKey))
			{
				updateVelocity(Utility::getUp(*getTransform()->getRotation()) * delta * 1000.0f);
			}
			if (input.KeyDown(m_downKey))
			{
				updateVelocity(Utility::getDown(*getTransform()->getRotation()) * delta * 1000.0f);
			}
		}
	}

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

	void updateAcceleration(glm::vec3 acceleration)
	{
		if (m_sphereCollider != nullptr)
		{
			m_sphereCollider->applyAcceleration(acceleration);
		}
		else if (m_polyCollider != nullptr)
		{
			m_polyCollider->applyAcceleration(acceleration);
			//printf("%f\t%f\t%f\n", acceleration.x, acceleration.y, acceleration.z);
		}
		else if (m_multiCollider != nullptr)
		{
			m_multiCollider->applyAcceleration(acceleration);
		}
	}

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

	//Debug Draw
	virtual void render(const Shader& shader, const RenderingEngine& renderingEngine, const Camera3D & camera) const 
	{
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glBegin(GL_LINES);
		
			if (m_sphereCollider != nullptr)
			{
				//GLUquadricObj *quadric = gluNewQuadric();
				//gluQuadricNormals(quadric, GLU_SMOOTH);
				//glPushMatrix();
				//	glTranslatef(m_sphereCollider->getPosition().x, m_sphereCollider->getPosition().y, m_sphereCollider->getPosition().z);
				//	gluSphere(quadric, m_sphereCollider->getRadiusSphere(), 100, 100);
				//glPopMatrix();
			}
			else if (m_polyCollider != nullptr)
			{
				glPushMatrix();
				//glTranslatef(m_sphereCollider->getPosition().x, m_sphereCollider->getPosition().y, m_sphereCollider->getPosition().z);
					glVertex3f(m_polyCollider->getHalfWidth(), m_polyCollider->getHalfHeight(), m_polyCollider->getHalfDepth());
					glVertex3f(m_polyCollider->getHalfWidth(), -m_polyCollider->getHalfHeight(), m_polyCollider->getHalfDepth());
				
					glVertex3f(-m_polyCollider->getHalfWidth(), m_polyCollider->getHalfHeight(), m_polyCollider->getHalfDepth());
					glVertex3f(-m_polyCollider->getHalfWidth(), -m_polyCollider->getHalfHeight(), m_polyCollider->getHalfDepth());
					glVertex3f(m_polyCollider->getHalfWidth(), m_polyCollider->getHalfHeight(), -m_polyCollider->getHalfDepth());
					glVertex3f(m_polyCollider->getHalfWidth(), -m_polyCollider->getHalfHeight(), -m_polyCollider->getHalfDepth());
					glVertex3f(-m_polyCollider->getHalfWidth(), m_polyCollider->getHalfHeight(), -m_polyCollider->getHalfDepth());
					glVertex3f(-m_polyCollider->getHalfWidth(), -m_polyCollider->getHalfHeight(), -m_polyCollider->getHalfDepth());
				glPopMatrix();
			}
			else if (m_multiCollider != nullptr)
			{
				//m_multiCollider;
			}
		glEnd();
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

	int m_forwardKey;
	int m_backKey;
	int m_leftKey;
	int m_rightKey;
	int m_upKey;
	int m_downKey;
	bool m_checkInput;
};

