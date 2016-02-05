// ***********************************************************************
// Author           : Christopher Maeda and Jesse Derochie
// Created          : 02-04-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 02-04-2016
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
#include "..\Physics\World.h"

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
	RigidBody(World * world, glm::vec3 position, glm::quat rotation, float mass, float radius, int id = 0)
	{
		m_sphereCollider = new SphereCollider();

		m_sphereCollider->init(
			position,
			rotation,
			0.0f,// *getTransform()->getScale(),		// TODO: This needs to be a vec3 in the sphere collider class
			mass,
			glm::vec3(0.0f),						// TODO: Currently there is no place in the engine that can give you the velocity
			glm::vec3(0.0f),						// TODO: Currently there is no place in the engine that can give you acceleration
			radius,
			id);

		world->addCollidableObject(m_sphereCollider);
	}

	/// <summary>
	/// Initializes a new instance of the <see cref="RigidBody"/> class.
	/// This instance specialized for Polygonal Collider
	/// </summary>
	/// <param name="halfWidth">Width of the half.</param>
	/// <param name="halfHeight">Height of the half.</param>
	/// <param name="halfDepth">The half depth.</param>
	/// <param name="id">The identifier.</param>
	RigidBody(World * world, float mass, float halfWidth, float halfHeight, float halfDepth, int id = 0)
	{
		m_polyCollider = new PolygonCollider();

		m_polyCollider->init(
			*getTransform()->getPosition(),
			*getTransform()->getRotation(),
			0,// *getTransform()->getScale(),		// TODO: This needs to be a vec3 in the polygon collider class
			mass,
			glm::vec3(0.0f),						// TODO: Currently there is no place in the engine that can give you the velocity
			glm::vec3(0.0f),						// TODO: Currently there is no place in the engine that can give you acceleration
			halfWidth,
			halfHeight,
			halfDepth,
			id);

		world->addCollidableObject(m_polyCollider);
	}

	/// <summary>
	/// Initializes a new instance of the <see cref="RigidBody"/> class.
	/// This instance specialized for Multi Colliders
	/// </summary>
	/// <param name="mass">The mass.</param>
	/// <param name="id">The identifier.</param>
	RigidBody(World * world, float mass, int id = 0)
	{
		m_multiCollider = new MultiCollider();

		m_multiCollider->init(
			*getTransform()->getPosition(),
			*getTransform()->getRotation(),
			0,// *getTransform()->getScale(),		// TODO: This needs to be a vec3 in the multi Collider class
			mass,
			glm::vec3(0.0f),						// TODO: Currently there is no place in the engine that can give you the velocity
			glm::vec3(0.0f),						// TODO: Currently there is no place in the engine that can give you acceleration
			id);

		world->addCollidableObject(m_multiCollider);
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

private:

	/// <summary>
	/// Gets this RigidBody's collider.
	/// </summary>
	/// <returns></returns>
	Collider * getCollider()
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
	}

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

};

