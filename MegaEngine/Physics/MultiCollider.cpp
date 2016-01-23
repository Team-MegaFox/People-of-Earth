#include "MultiCollider.h"
#include <iostream>

MultiCollider::MultiCollider()
{
}

MultiCollider::MultiCollider(MultiCollider& collider)
{
    m_position = collider.m_position;
	m_rotation = collider.m_rotation;
	m_scale = collider.m_scale;
	m_mass = collider.m_mass;
	m_velocity = collider.m_velocity;
	m_acceleration = collider.m_acceleration;
    m_multipleCollider = collider.m_multipleCollider;
	m_id = collider.m_id;
}

MultiCollider::~MultiCollider()
{
}

void MultiCollider::init(
		glm::vec3 position,
		glm::quat rotation,
		float scale,
		float mass,
		glm::vec3 velocity,
		glm::vec3 acceleration,
        int id)
{
	Collider::init(position, rotation, scale, mass, velocity, acceleration, id);
    m_radiusSphere = 0.0f;
    m_shapeCollider = ShapeCollider::OTHER;
}

void MultiCollider::addColliderToObject(Collider* collider)
{
    //Set the collider id so it is part of the Multi Collider 
    collider->setID(m_id);
    m_multipleCollider.push_back(collider);

    //Calculate the highest radius of the multiple collider object
    m_radiusSphere = 0.0f;
    for (size_t i = 0; i < m_multipleCollider.size(); i++)
    {
        //if the current radius sphere is smaller then the specific collider disance from Multi Collider position and specific collider radius then
        if (m_radiusSphere < glm::length(m_multipleCollider[i]->getPosition() - m_position) + m_multipleCollider[i]->getRadiusSphere())
        {
            //Update the value of the radius
            m_radiusSphere = glm::length(m_multipleCollider[i]->getPosition() - m_position) + m_multipleCollider[i]->getRadiusSphere();
        }
    }

    
}

std::vector<Collider*> MultiCollider::checkCollision( std::vector<Collider*> collidableObjects ) 
{
    //Create a vector of collided object it collided with
	std::vector<Collider*> collidedObject;
    std::vector<Collider*> collidedPartObject;
    std::vector<Collider*> trueCollidedObject;

    //Call base class collision check to take out any unnecessary collision check 
    collidedObject = SphereCollider::checkCollision(collidableObjects);

    //If there were any collision then
    if (collidedObject.size() > 0)
    {
        //Loop through all the parts in the multi-collider and check collision with the ones that passed the collision
        for (size_t i = 0; i < m_multipleCollider.size(); i++)
        {
            //Get the collision of this specific collider
            collidedPartObject = m_multipleCollider[i]->checkCollision(collidedObject);
            //Loop through all the collided objects of this specific collider
            for (size_t j = 0; j < collidedPartObject.size(); j++)
            {
                //If type of collider is another multi then
                if (collidedPartObject[j]->getShapeCollider() == ShapeCollider::OTHER)
                {
                    //Check collision with this Collider with the Multi Colliders colliders
                    if (!multiMultiCollisionCheck(m_multipleCollider[i], dynamic_cast<MultiCollider*>(collidedPartObject[j])))
                    {
                        //Remove the multi collider from the colllided part objects
                        collidedPartObject.erase(collidedPartObject.begin() + j);
                        j--;
                    }
                }
            }
            //If there were any collision then
            if (collidedPartObject.size() > 0)
            {
                std::cout << "Multi Collided" << std::endl;
                //Push back all the collided object
                for (size_t i = 0; i < collidedPartObject.size(); i++)
                {
                    //Add all the collider that collided with the specific multi collider to the return collided object 
                    trueCollidedObject.push_back(collidedPartObject[i]);
                }
            }
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

bool MultiCollider::multiMultiCollisionCheck(Collider* mulitSpecficCollider, MultiCollider* multiCollider)
{
    //Create a vector of collided object it collided with
    std::vector<Collider*> collidedObjects;
    //Check collision with this Collider with the Multi Colliders colliders
    collidedObjects = mulitSpecficCollider->checkCollision(multiCollider->getMultiCollider());
    //if there are any collider in the vector then collision was true
    if (collidedObjects.size() > 0)
    {
        return true;
    }
    //No collision then return false
    return false;
}

void MultiCollider::applyRotation(glm::quat rotation)
{
    //Apply the rotation on all the collider in the multi collider
    for (size_t i = 0; i < m_multipleCollider.size(); i++)
    {
        m_multipleCollider[i]->applyRotation(rotation);
    }
    //Apply rotation on the multi collider
    Collider::applyRotation(m_rotation);
}

void MultiCollider::applyForce(glm::vec3 force) 
{
    //Apply the force on all the collider in the multi collider
    for (size_t i = 0; i < m_multipleCollider.size(); i++)
    {
        m_multipleCollider[i]->applyForce(force);
    }
    //Apply force on the multi collider
    Collider::applyForce(force);
}

void MultiCollider::applyAcceleration(glm::vec3 accel) 
{
    //Apply the acceleration on all the collider in the multi collider
    for (size_t i = 0; i < m_multipleCollider.size(); i++)
    {
        m_multipleCollider[i]->applyAcceleration(accel);
    }
    //Apply acceleration on the multi collider
    Collider::applyAcceleration(accel);
}

void MultiCollider::update(float timeStep)
{
    //Update all the collider in the multi collider
	for (size_t i = 0; i < m_multipleCollider.size(); i++)
    {
        m_multipleCollider[i]->update(timeStep);
    }
    //Update the multi collider
    Collider::update(timeStep);
}
