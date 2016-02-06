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
	RigidBody(glm::vec3 position, glm::quat rotation, float mass, float radius, int id = 0) :
		m_position(position),
		m_rotation(rotation)
	{
		m_sphereCollider = new SphereCollider();

		m_sphereCollider->init(
			m_position,
			m_rotation,
			0.0f,// *getTransform()->getScale(),		// TODO: This needs to be a vec3 in the sphere collider class
			mass,
			m_zero,						// TODO: Currently there is no place in the engine that can give you the velocity
			m_zero,						// TODO: Currently there is no place in the engine that can give you acceleration
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
	RigidBody(glm::vec3 position, glm::quat rotation, float mass, float halfWidth, float halfHeight, float halfDepth, int id = 0) :
		m_position(position),
		m_rotation(rotation)
	{
		m_polyCollider = new PolygonCollider();

		m_polyCollider->init(
			m_position,
			m_rotation,
			0,// *getTransform()->getScale(),		// TODO: This needs to be a vec3 in the polygon collider class
			mass,
			m_zero,						// TODO: Currently there is no place in the engine that can give you the velocity
			m_zero,						// TODO: Currently there is no place in the engine that can give you acceleration
			halfWidth,
			halfHeight,
			halfDepth,
			id);

		PhysicsEngine::getPhysicsWorld()->addCollidableObject(m_polyCollider);
	}

	/// <summary>
	/// Initializes a new instance of the <see cref="RigidBody"/> class.
	/// This instance specialized for Multi Colliders
	/// </summary>
	/// <param name="mass">The mass.</param>
	/// <param name="id">The identifier.</param>
	RigidBody(glm::vec3 position, glm::quat rotation, float mass, int id = 0) :
		m_position(position),
		m_rotation(rotation)
	{
		m_multiCollider = new MultiCollider();

		m_multiCollider->init(
			m_position,
			m_rotation,
			0,// *getTransform()->getScale(),		// TODO: This needs to be a vec3 in the multi Collider class
			mass,
			m_zero,						// TODO: Currently there is no place in the engine that can give you the velocity
			m_zero,						// TODO: Currently there is no place in the engine that can give you acceleration
			id);

		PhysicsEngine::getPhysicsWorld()->addCollidableObject(m_multiCollider);
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
	/// Updates the collider every frame
	/// - updates the position and the rotation of the collider every frame
	/// </summary>
	/// <param name="deltaTime">The delta time.</param>
	virtual void update(float deltaTime) override
	{
		if (m_sphereCollider != nullptr)
		{
			m_sphereCollider->setPosition(m_position);
			m_sphereCollider->setRotation(m_rotation);
		}
		else if (m_polyCollider != nullptr)
		{
			m_polyCollider->setPosition(m_position);
			m_polyCollider->setRotation(m_rotation);
		}
		else if (m_multiCollider != nullptr)
		{
			m_multiCollider->setPosition(m_position);
			m_multiCollider->setRotation(m_rotation);
		}
		m_position = *getTransform()->getPosition();
		m_rotation = *getTransform()->getRotation();
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
	glm::vec3 m_position;
	/// <summary>
	/// The rotation of this collider
	/// </summary>
	glm::quat m_rotation;

	/// <summary>
	/// The zero variable
	/// </summary>
	glm::vec3 m_zero = glm::vec3(0.0f);

};

