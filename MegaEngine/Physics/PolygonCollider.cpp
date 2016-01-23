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
		glm::vec3 position,
		glm::quat rotation,
		float scale,
		float mass,
		glm::vec3 velocity,
		glm::vec3 acceleration,
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
                std::cout << "Polygon Collided\n";
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
                std::cout << "Multi Collided\n";
            }
        }
        //if the collider is a sphere
        else
        {
            //Push back the collided object to the return collided object
            trueCollidedObject.push_back(collidedObject[i]);
            std::cout << "Sphere Collided\n";
        }
	}

    //If the return collided object is more than 0 then 
	if (trueCollidedObject.size() > 0)
	{
		m_collided = true;
	}
    //No return collided objects meaning no collision
	else
	{
		m_collided = false;
	}

	//Return the collided objects
	return trueCollidedObject;
}

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
	glm::vec3 rightDirection1, upDirection1, forwardDirection1;
	glm::vec3 rightDirection2, upDirection2, forwardDirection2;
	glm::vec3 axis;	

    //Get all the direction vectors of the this Collider
    rightDirection1 = glm::normalize(GetRightVector(m_rotation)); 
    upDirection1 = glm::normalize(GetUpVector(m_rotation)); 
    forwardDirection1 = glm::normalize(GetForwardVector(m_rotation));
	
    //Get all the direction vectors of the other Collider
	rightDirection2 = glm::normalize(GetRightVector(collidableObject->getRotation())); 
    upDirection2 = glm::normalize(GetUpVector(collidableObject->getRotation())); 
    forwardDirection2 = glm::normalize(GetForwardVector(collidableObject->getRotation()));

    //Get the Vector from this Collider Position to the other Collider Position
	glm::vec3 tPosition = collidableObject->getPosition() - m_position;

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
	axis = glm::cross(rightDirection1, rightDirection2);
	if (!checkAxisCollision(tPosition, axis, rightDirection1, upDirection1, forwardDirection1,
		rightDirection2 ,upDirection2, forwardDirection2, collidableObject))
	{
		return false;
	}
	//The cross product of first polygon X axis with second polygon Y axis
	axis = glm::cross(rightDirection1, upDirection2);
	if (!checkAxisCollision(tPosition, axis, rightDirection1, upDirection1, forwardDirection1,
		rightDirection2 ,upDirection2, forwardDirection2, collidableObject))
	{
		return false;
	}
	//The cross product of first polygon X axis with second polygon Z axis
	axis = glm::cross(rightDirection1, forwardDirection2);
	if (!checkAxisCollision(tPosition, axis, rightDirection1, upDirection1, forwardDirection1,
		rightDirection2 ,upDirection2, forwardDirection2, collidableObject))
	{
		return false;
	}
	//The cross product of first polygon Y axis with second polygon X axis
	axis = glm::cross(upDirection1, rightDirection2);
	if (!checkAxisCollision(tPosition, axis, rightDirection1, upDirection1, forwardDirection1,
		rightDirection2 ,upDirection2, forwardDirection2, collidableObject))
	{
		return false;
	}
	//The cross product of first polygon Y axis with second polygon Y axis
	axis = glm::cross(upDirection1, upDirection2);
	if (!checkAxisCollision(tPosition, axis, rightDirection1, upDirection1, forwardDirection1,
		rightDirection2 ,upDirection2, forwardDirection2, collidableObject))
	{
		return false;
	}
	//The cross product of first polygon Y axis with second polygon Z axis
	axis = glm::cross(upDirection1, forwardDirection2);
	if (!checkAxisCollision(tPosition, axis, rightDirection1, upDirection1, forwardDirection1,
		rightDirection2 ,upDirection2, forwardDirection2, collidableObject))
	{
		return false;
	}
		//The cross product of first polygon Z axis with second polygon X axis
	axis = glm::cross(forwardDirection1, rightDirection2);
	if (!checkAxisCollision(tPosition, axis, rightDirection1, upDirection1, forwardDirection1,
		rightDirection2 ,upDirection2, forwardDirection2, collidableObject))
	{
		return false;
	}
	//The cross product of first polygon Z axis with second polygon Y axis
	axis = glm::cross(forwardDirection1, upDirection2);
	if (!checkAxisCollision(tPosition, axis, rightDirection1, upDirection1, forwardDirection1,
		rightDirection2 ,upDirection2, forwardDirection2, collidableObject))
	{
		return false;
	}
	//The cross product of first polygon Z axis with second polygon Z axis
	axis = glm::cross(forwardDirection1, forwardDirection2);
	if (!checkAxisCollision(tPosition, axis, rightDirection1, upDirection1, forwardDirection1,
		rightDirection2 ,upDirection2, forwardDirection2, collidableObject))
	{
		return false;
	}

	//The polygons collide
	return true;
}

bool PolygonCollider::checkAxisCollision(glm::vec3 tPosition, glm::vec3 axis, glm::vec3 rightDirection1, glm::vec3 upDirection1, glm::vec3 forwardDirection1, 
		glm::vec3 rightDirection2, glm::vec3 upDirection2, glm::vec3 forwardDirection2, PolygonCollider* collidableObject)
{
    //Axis Collision check
	if ( glm::abs(glm::dot(tPosition, axis)) >

		glm::abs(glm::dot((rightDirection1 * m_halfWidth), axis)) + 
		glm::abs(glm::dot((upDirection1 * m_halfHeight), axis)) +
		glm::abs(glm::dot((forwardDirection1 * m_halfDepth), axis)) + 

		glm::abs(glm::dot((rightDirection2 * collidableObject->getHalfWidth()), axis)) + 
		glm::abs(glm::dot((upDirection2 * collidableObject->getHalfHeight()), axis)) +
		glm::abs(glm::dot((forwardDirection2 * collidableObject->getHalfDepth()), axis)) 

	
		)
	{
        //No collision
		return false;
	}

    //Axis collided
	return true;
}

