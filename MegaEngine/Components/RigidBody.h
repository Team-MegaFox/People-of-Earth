#pragma once

#include "GameComponents.h"
#include "..\Physics\MultiCollider.h"
#include "..\Physics\PhysicsEngine.h"

class RigidBody : public GameComponent
{
public:
	RigidBody(ShapeCollider type)
	{
		if (type == ShapeCollider::SPHERE)
		{
			m_collider = SphereCollider();
		}
		else if (type == ShapeCollider::QUAD)
		{
			m_collider = PolygonCollider();
		}
		else
		{
			m_collider = MultiCollider();
		}
		isSleep = false;
	}
	~RigidBody();

	bool isSleeping()
	{
		return isSleep;
	}
	
	void setPosition(glm::vec3 pos)
	{
		if (m_collider.getShapeCollider() != ShapeCollider::OTHER)
		{
			m_collider.setPosition(pos);
		}
		else
		{
			//? type cast to a multi collider
		}
	}

	void setRotation(glm::quat rot)
	{
		if (m_collider.getShapeCollider() != ShapeCollider::OTHER)
		{
			m_collider.setRotation(rot);
		}
		else
		{
			//? type cast to a multi collider
		}
	}

	void setScale(float scale)
	{
		if (m_collider.getShapeCollider() != ShapeCollider::OTHER)
		{
			m_collider.setScale(scale);
		}
		else
		{
			//? type cast to a multi collider
		}
	}

	void setMass(float mass)
	{
		if (m_collider.getShapeCollider() != ShapeCollider::OTHER)
		{
			m_collider.setMass(mass);
		}
		else
		{
			//? type cast to a multi collider
		}	
	}
	
	void setVelocity(glm::vec3 vel)
	{
		if (m_collider.getShapeCollider() != ShapeCollider::OTHER)
		{
			m_collider.setVelocity(vel);
		}
		else
		{
			//? type cast to a multi collider
		}
	}

	void setAcceleration(glm::vec3 accel)
	{
		if (m_collider.getShapeCollider() != ShapeCollider::OTHER)
		{
			m_collider.setAcceleration(accel);
		}
		else
		{
			//? type cast to a multi collider
		}
	}

	void setSleepFlag(bool flag)
	{
		isSleep = flag;
	}

	/// <summary>
	/// Sets the parent GameObject.
	/// </summary>
	/// <param name="parent">The GameObject to be attached to.</param>
	virtual void setParent(GameObject* parent) { m_parent = parent; }

	void addToPhysicsWorld()
	{
		//m_parent->getPhysicsEngine().getWorld().addCollider(m_collider);
	}

	//Checks collision with all the colliders in the world
	std::pair<bool, std::vector<Collider*>> checkCollision()
	{
	
	}

	//Checks collision with only specify collider
	bool checkCollision(Collider& collider)
	{
	
	}

private:
	SphereCollider m_collider;

	/// <summary>
	/// The parent Game Object
	/// </summary>
	GameObject* m_parent;

	bool isSleep; 
};

