/*
A derived class of PolygonCollider.
This class will handle sphere to sphere collision as a whole collider object from all the collider it holds
then handles all the collider in the Mulit Collider Object with its own collision check.

Author: Christopher Maeda
Last Edit: November 18 2015
*/

#pragma once

#include "PolygonCollider.h"

class MultiCollider : public PolygonCollider
{
public:
    MultiCollider();
    MultiCollider(MultiCollider& collider);
    ~MultiCollider();
    
    /*
		Description: Initialize the member variable value of the Multi Collider
		Parameter: 
		@param position - Position of the Multi Collider
		@param rotation - Rotation of the Multi Collider 
		@param scale - Scale of the Multi Collider
		@param mass - Mass of the Multi Collider
		@param velocity - Starting Velocity of the Multi Collider
		@param acceleration - Starting Acceleration of the Multi Collider
		@param id - id of the Multi Collider
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
        Description: Add the specific collider to the Multi Collider 
        Parameter: 
        @param collider - The collider that will be added to the Multi Collider
        Return: None
    */
    void addColliderToObject(Collider* collider);

    /*
		Description: Check the collision with this Multi Collider with the vector of Colliders
		Parameter: 
		@param collidableObjects - Vectors of Colliders this Multi Collider will be checking
		Return: Vector of Collider this Multi Collider collided with
	*/
	virtual std::vector<Collider*> checkCollision( std::vector<Collider*> collidableObjects ) override;

     /*
		Description: Check the collision with the specific Collider in the Multi Collider with the other Multi Collider Object (Different Multi Collider objects)
		Parameter: 
		@param mulitSpecficCollider - Specific Collider in the Multi Collider
        @param multiCollider - Other Multi Collider this Collider is checking
		Return: Boolean telling if the specific collider in the Multi Collider collided with the other Multi Collider
	*/
    bool multiMultiCollisionCheck(Collider* mulitSpecficCollider , MultiCollider* multiCollider);

    /*
		Description: Rotate the Multi Collider and the collider in the Multi Collider
		Parameter: 
		@param rotation - Quaternion value of how much to rotate the Colliders
		Return: None
	*/
    virtual void applyRotation(glm::quat rotation) override;

	/*
		Description: Update force value of the Multi Collider and the collider in the Multi Collider
		Parameter: 
		@param force - A Force value of how much force is being applied to the Colliders
		Return: None
	*/
    virtual void applyForce(glm::vec3 force) override;

    /*
		Description: Update acceleration value of the Multi Collider and the collider in the Multi Collider
		Parameter:
		@param acceleration - A Acceleation value of how much acceleration is being applied to the Colliders
		Return: None
	*/
	virtual void applyAcceleration(glm::vec3 accel) override;

    /*
		Description: Update the values of the Multi Collider and the collider in the Multi Collider
		Parameter: 
		@param timeStep - Time step from last time update to current update time (displacement of the time)
		Return: None
	*/
    virtual void update(float timeStep) override;

    //Properties Getters
    std::vector<Collider*> getMultiCollider()
    {
        return m_multipleCollider;
    }

private:
    std::vector<Collider*> m_multipleCollider;
};

