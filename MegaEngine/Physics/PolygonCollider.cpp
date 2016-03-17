// ***********************************************************************
// Author           : Christopher Maeda
// Created          : 09-15-2015
//
// Last Modified By : Christopher Maeda
// Last Modified On : 03-13-2016
// ***********************************************************************
// <copyright file="PolygonCollider.cpp" company="">
//     Copyright (c) . All rights reserved.
// </copyright>
// <summary>
// A derived class of SphereCollider.
// This class will handle sphere to sphere collision from base class then handle
// Separating Axis Theorm collision check.
// </summary>
// ***********************************************************************
#include "PolygonCollider.h"
#include "MultiCollider.h"

#include <iostream>

PolygonCollider::PolygonCollider()
{
}

PolygonCollider::PolygonCollider(PolygonCollider& collider)
{
    m_shapeCollider = collider.m_shapeCollider;
	m_radiusSphere = collider.m_radiusSphere; 
	m_position = collider.m_position;
	m_rotation = collider.m_rotation; 
	m_scale = collider.m_scale;
	m_mass = collider.m_mass;
	m_velocity = collider.m_velocity;
	m_acceleration = m_acceleration;
    m_halfWidth = collider.m_halfWidth;
    m_halfHeight = collider.m_halfHeight;
    m_halfDepth = collider.m_halfDepth;
    m_id = collider.m_id; 
}

PolygonCollider::~PolygonCollider()
{
}

void PolygonCollider::init(
		PxVec3 position,
		PxQuat rotation,
		float scale,
		float mass,
		PxVec3 velocity,
		PxVec3 acceleration,
		float halfWidth,
        float halfHeight,
        float halfDepth,
		int id
		)
{
	//Set the radius of the sphere to the hightest half length
    if (halfWidth >= halfHeight && halfWidth >= halfDepth)
    {
        m_radiusSphere = halfWidth;
    }
	else if (halfHeight >= halfWidth && halfHeight >= halfDepth)
    {
        m_radiusSphere = halfHeight;
    }
    else if (halfDepth >= halfWidth && halfDepth >= halfHeight)
    {
        m_radiusSphere = halfDepth;
    }

	m_halfWidth = halfWidth;
	m_halfHeight  = halfHeight; 
	m_halfDepth = halfDepth;

	//Initialize the rest in the base class
	SphereCollider::init(position, rotation, scale, mass, velocity, acceleration, m_radiusSphere, id);
	m_shapeCollider = ShapeCollider::QUAD;
}

std::vector<Collider*> PolygonCollider::checkCollision( std::vector<Collider*> collidableObjects )
{
	//Create a vector of collided object it collided with
	std::vector<Collider*> collidedObject;
	std::vector<Collider*> trueCollidedObject;
	//Call base class collision check to take out any unnecessary collision check 
	collidedObject = SphereCollider::checkCollision(collidableObjects);
	//Loop through all the collided objects
	for (size_t i = 0; i < collidedObject.size() ; i++)
	{
		//Only check the collision if the other collider is also a polygon
		if (collidedObject[i]->getShapeCollider() == QUAD)
		{
            //Check collision using Separating Axis Theorm
            if (checkSATCollision(dynamic_cast<PolygonCollider*>(collidedObject[i])))
			{
                //Push back the collided object to the return collided object
				trueCollidedObject.push_back(collidedObject[i]);
                //std::cout << "Polygon Collided\n";
			}
		}
        //if the collider is a multi-collider then
        else if (collidedObject[i]->getShapeCollider() == OTHER)
        {
            //Check collision with this Collider with the Multi Colliders colliders
            if (checkCollision(dynamic_cast<MultiCollider*>(collidedObject[i])->getMultiCollider()).size() > 0) 
            {
                //Push back the collided object to the return collided object
                trueCollidedObject.push_back(collidedObject[i]);
                //std::cout << "Multi Collided\n";
            }
        }
        //if the collider is a sphere
        else
        {
			float timeOfCollision;
			//Check collision with rays
			if (collidedObject[i]->checkCollision(m_position + PxVec3(m_halfWidth, m_halfHeight, -m_halfDepth),
				m_rotation.rotate(PxVec3(0.0f, 0.0f, 1.0f)), timeOfCollision))
			{
				//Push back the collided object to the return collided object
				trueCollidedObject.push_back(collidedObject[i]);
			}
			else if (collidedObject[i]->checkCollision(m_position + PxVec3(m_halfWidth, -m_halfHeight, -m_halfDepth),
				m_rotation.rotate(PxVec3(0.0f, 0.0f, 1.0f)), timeOfCollision))
			{
				//Push back the collided object to the return collided object
				trueCollidedObject.push_back(collidedObject[i]);
			}
			else if (collidedObject[i]->checkCollision(m_position + PxVec3(-m_halfWidth, -m_halfHeight, -m_halfDepth),
				m_rotation.rotate(PxVec3(0.0f, 0.0f, 1.0f)), timeOfCollision))
			{
				//Push back the collided object to the return collided object
				trueCollidedObject.push_back(collidedObject[i]);
			}
			else if (collidedObject[i]->checkCollision(m_position + PxVec3(-m_halfWidth, m_halfHeight, -m_halfDepth),
				m_rotation.rotate(PxVec3(0.0f, 0.0f, 1.0f)), timeOfCollision))
			{
				//Push back the collided object to the return collided object
				trueCollidedObject.push_back(collidedObject[i]);
			}
        }
	}

    //If the return collided object is more than 0 then 
	if (trueCollidedObject.size() > 0)
	{
		//std::cout << "Collisions\n";
		m_collided = true;
	}
    //No return collided objects meaning no collision
	else
	{
		m_collided = false;
		//std::cout << "No Collisions\n";
	}

	//Return the collided objects
	return trueCollidedObject;
}

bool PolygonCollider::checkCollision(Collider* collidableObject)
{
	//Call base class collision check to take out any unnecessary collision check 
	if (SphereCollider::checkCollision(collidableObject))
	{
		//Only check the collision if the other collider is also a polygon
		if (collidableObject->getShapeCollider() == QUAD)
		{
			//Check collision using Separating Axis Theorm
			if (checkSATCollision(dynamic_cast<PolygonCollider*>(collidableObject)))
			{
				//Push back the collided object to the return collided object
				return true;
			}
		}
		//if the collider is a multi-collider then
		else if (collidableObject->getShapeCollider() == OTHER)
		{
			//Check collision with this Collider with the Multi Colliders colliders
			if (checkCollision(dynamic_cast<MultiCollider*>(collidableObject)->getMultiCollider()).size() > 0)
			{
				//Push back the collided object to the return collided object
				return true;
			}
		}
		//if the collider is a sphere
		else
		{
			//Push back the collided object to the return collided object
			return true;
		}
	}
	//No collision
	return false;
}

//bool PolygonCollider::checkCollision(PxVec3 rayPosition, PxVec3 rayDirection, float &timeOfCollision)
//{
//	//Used the tutorial to help code the collision
//	//http://www.opengl-tutorial.org/miscellaneous/clicking-on-objects/picking-with-custom-ray-obb-function/
//
//	PxVec3 delta = m_position - rayPosition;
//	PxVec3 xaxis = m_rotation.rotate(PxVec3(1, 0, 0));
//	PxVec3 yaxis = m_rotation.rotate(PxVec3(0, 1, 0));
//	PxVec3 zaxis = m_rotation.rotate(PxVec3(0, 0, 1));
//	float axisCollision = 0.0f;
//
//	if (!checkRayAxisCollision(rayDirection, xaxis, delta, axisCollision))
//	{
//		return false;
//	}
//	if (axisCollision != 0.0f)
//		timeOfCollision = axisCollision;
//
//	if (!checkRayAxisCollision(rayDirection, yaxis, delta, axisCollision))
//	{
//		return false;
//	}
//	if (axisCollision > timeOfCollision && axisCollision != 0.0f)
//	{
//		timeOfCollision = axisCollision;
//	}
//
//	if (!checkRayAxisCollision(rayDirection, zaxis, delta, axisCollision))
//	{
//		return false;
//	}
//	if (axisCollision > timeOfCollision && axisCollision != 0.0f)
//	{
//		timeOfCollision = axisCollision;
//	}
//
//	return true;
//}

bool PolygonCollider::checkSATCollision(PolygonCollider* collidableObject)
{
	//Check collision with Seperating Axis Theorm
	//Must check 15 axis of the polygon
	//3 Axis of first polygon, 3 Axis of second polygon, and 9 which are cross product of each axis in polygon ex Ax x Bx, Ax x By
	//Check statement:
	//Projection Axis > 
	//|Projection (Polygon1.dir_x * Polygon1.width) | + |Projection (Polygon1.dir_y * Polygon1.height) | + |Projection (Polygon1.dir_z * Polygon1.depth) | + 
	//Same with the second polygon
	//Projection calcuation = Point dot product Axis
	//Porjection Axis calculation  (Position2 - Position1) dot product axis
	//If the any of the check statement is true then the 2 polygon do not intersect has to be all false to intersect
	//Could break out earlier

    //Create a necessary variable for the collision check 
	PxVec3 rightDirection1, upDirection1, forwardDirection1;
	PxVec3 rightDirection2, upDirection2, forwardDirection2;
	PxVec3 axis;	

    //Get all the direction vectors of the this Collider
    rightDirection1 = GetRightVector(m_rotation).getNormalized(); 
	upDirection1 = GetUpVector(m_rotation).getNormalized();
	forwardDirection1 = GetForwardVector(m_rotation).getNormalized();
	
    //Get all the direction vectors of the other Collider
	rightDirection2 = GetRightVector(collidableObject->getRotation()).getNormalized();
	upDirection2 = GetUpVector(collidableObject->getRotation()).getNormalized();
	forwardDirection2 = GetForwardVector(collidableObject->getRotation()).getNormalized();

    //Get the Vector from this Collider Position to the other Collider Position
	PxVec3 tPosition = collidableObject->getPosition() - m_position;

	//Now is the big long check statement of each axis
	//The first polygon X axis
	axis = rightDirection1;
	if (!checkAxisCollision(tPosition, axis, rightDirection1, upDirection1, forwardDirection1,
		rightDirection2 ,upDirection2, forwardDirection2, collidableObject))
	{
		return false;
	}
	//The first polygon Y axis
	axis = upDirection1;
	if (!checkAxisCollision(tPosition, axis, rightDirection1, upDirection1, forwardDirection1,
		rightDirection2 ,upDirection2, forwardDirection2, collidableObject))
	{
		return false;
	}
	//The first polygon Z axis
	axis = forwardDirection1;
	if (!checkAxisCollision(tPosition, axis, rightDirection1, upDirection1, forwardDirection1,
		rightDirection2 ,upDirection2, forwardDirection2, collidableObject))
	{
		return false;
	}
	//The second polygon X axis
	axis = rightDirection2;
	if (!checkAxisCollision(tPosition, axis, rightDirection1, upDirection1, forwardDirection1,
		rightDirection2 ,upDirection2, forwardDirection2, collidableObject))
	{
		return false;
	}
	//The second polygon Y axis
	axis = upDirection2;
	if (!checkAxisCollision(tPosition, axis, rightDirection1, upDirection1, forwardDirection1,
		rightDirection2 ,upDirection2, forwardDirection2, collidableObject))
	{
		return false;
	}
	//The second polygon Z axis
	axis = forwardDirection2;
	if (!checkAxisCollision(tPosition, axis, rightDirection1, upDirection1, forwardDirection1,
		rightDirection2 ,upDirection2, forwardDirection2, collidableObject))
	{
		return false;
	}
	//The cross product of first polygon X axis with second polygon X axis
	axis = rightDirection1.cross(rightDirection2);
	if (!checkAxisCollision(tPosition, axis, rightDirection1, upDirection1, forwardDirection1,
		rightDirection2 ,upDirection2, forwardDirection2, collidableObject))
	{
		return false;
	}
	//The cross product of first polygon X axis with second polygon Y axis
	axis = rightDirection1.cross(upDirection2);
	if (!checkAxisCollision(tPosition, axis, rightDirection1, upDirection1, forwardDirection1,
		rightDirection2 ,upDirection2, forwardDirection2, collidableObject))
	{
		return false;
	}
	//The cross product of first polygon X axis with second polygon Z axis
	axis = rightDirection1.cross(forwardDirection2);
	if (!checkAxisCollision(tPosition, axis, rightDirection1, upDirection1, forwardDirection1,
		rightDirection2 ,upDirection2, forwardDirection2, collidableObject))
	{
		return false;
	}
	//The cross product of first polygon Y axis with second polygon X axis
	axis = upDirection1.cross(rightDirection2);
	if (!checkAxisCollision(tPosition, axis, rightDirection1, upDirection1, forwardDirection1,
		rightDirection2 ,upDirection2, forwardDirection2, collidableObject))
	{
		return false;
	}
	//The cross product of first polygon Y axis with second polygon Y axis
	axis = upDirection1.cross(upDirection2);
	if (!checkAxisCollision(tPosition, axis, rightDirection1, upDirection1, forwardDirection1,
		rightDirection2 ,upDirection2, forwardDirection2, collidableObject))
	{
		return false;
	}
	//The cross product of first polygon Y axis with second polygon Z axis
	axis = upDirection1.cross(forwardDirection2);
	if (!checkAxisCollision(tPosition, axis, rightDirection1, upDirection1, forwardDirection1,
		rightDirection2 ,upDirection2, forwardDirection2, collidableObject))
	{
		return false;
	}
		//The cross product of first polygon Z axis with second polygon X axis
	axis = forwardDirection1.cross(rightDirection2);
	if (!checkAxisCollision(tPosition, axis, rightDirection1, upDirection1, forwardDirection1,
		rightDirection2 ,upDirection2, forwardDirection2, collidableObject))
	{
		return false;
	}
	//The cross product of first polygon Z axis with second polygon Y axis
	axis = forwardDirection1.cross(upDirection2);
	if (!checkAxisCollision(tPosition, axis, rightDirection1, upDirection1, forwardDirection1,
		rightDirection2 ,upDirection2, forwardDirection2, collidableObject))
	{
		return false;
	}
	//The cross product of first polygon Z axis with second polygon Z axis
	axis = forwardDirection1.cross(forwardDirection2);
	if (!checkAxisCollision(tPosition, axis, rightDirection1, upDirection1, forwardDirection1,
		rightDirection2 ,upDirection2, forwardDirection2, collidableObject))
	{
		return false;
	}

	//The polygons collide
	return true;
}

bool PolygonCollider::checkAxisCollision(
	PxVec3 tPosition, 
	PxVec3 axis, 
	PxVec3 rightDirection1, 
	PxVec3 upDirection1, 
	PxVec3 forwardDirection1, 
	PxVec3 rightDirection2, 
	PxVec3 upDirection2, 
	PxVec3 forwardDirection2, 
	PolygonCollider* collidableObject)
{
    //Axis Collision check
	if (PxAbs(tPosition.dot(axis)) >

		PxAbs((rightDirection1 * m_halfWidth).dot(axis)) +
		PxAbs((upDirection1 * m_halfHeight).dot(axis)) +
		PxAbs((forwardDirection1 * m_halfDepth).dot(axis)) +

		PxAbs((rightDirection2 * collidableObject->getHalfWidth()).dot(axis)) +
		PxAbs((upDirection2 * collidableObject->getHalfHeight()).dot(axis)) +
		PxAbs((forwardDirection2 * collidableObject->getHalfDepth()).dot(axis))

		)
	{
        //No collision
		return false;
	}

    //Axis collided
	return true;
}

bool PolygonCollider::checkRayAxisCollision(PxVec3 rayDirection, PxVec3 axis, PxVec3 delta, float &timeOfCollision)
{
	float tMin = 0.0f;
	float tMax = 100000.0f;
	PxVec3 aabb_min(-1.0f, -1.0f, -1.0f);
	aabb_min = PxVec3(aabb_min.x * axis.x, aabb_min.y * axis.y, aabb_min.z * axis.z);
	PxVec3 aabb_max(1.0f, 1.0f, 1.0f);
	aabb_max = PxVec3(aabb_max.x * axis.x, aabb_max.y * axis.y, aabb_max.z * axis.z);

	float e = axis.dot(delta);
	float f = rayDirection.dot(axis);

	if (f > 0)
	{
		// Beware, don't do the division if f is near 0 ! See full source code for details.
		float t1;
		if (aabb_min.x != 0)
		{
			t1 = (e + aabb_min.x) / f; // Intersection with the "left" plane
		}
		else if (aabb_min.y != 0)
		{
			t1 = (e + aabb_min.y) / f; // Intersection with the "left" plane
		}
		else
		{
			t1 = (e + aabb_min.z) / f; // Intersection with the "left" plane
		}
		float t2;
		if (aabb_max.x != 0)
		{
			t2 = (e + aabb_max.x) / f; // Intersection with the "right" plane
		}
		else if (aabb_max.y != 0)
		{
			t2 = (e + aabb_max.y) / f; // Intersection with the "left" plane
		}
		else
		{
			t2 = (e + aabb_max.z) / f; // Intersection with the "left" plane
		}

		// if wrong order
		if (t1>t2)
		{ 
			float w = t1; t1 = t2; t2 = w; // swap t1 and t2
		}

		// tMax is the nearest "far" intersection (amongst the X,Y and Z planes pairs)
		if (t2 < tMax)
		{
			tMax = t2;
		}
		// tMin is the farthest "near" intersection (amongst the X,Y and Z planes pairs)
		if (t1 > tMin)
		{
			tMin = t1;
		}
		
		if (tMax < tMin)
		{
			return false;
		}
		
	}

	timeOfCollision = tMin;
	return true;
}

bool PolygonCollider::checkDistance(PolygonCollider* collidableObject)
{
	PxVec3 directionToCollider = collidableObject->getPosition() - m_position;

	return false;
}