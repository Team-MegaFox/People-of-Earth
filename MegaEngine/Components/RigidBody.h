#pragma once

#include "GameComponents.h"
#include "..\Physics\MultiCollider.h"
#include "..\Physics\PolygonCollider.h"
#include "..\Physics\SphereCollider.h"

class RigidBody : public GameComponent
{
public:
	RigidBody(ShapeCollider type)
	{
		m_sphe = new PolygonCollider();
	}
	~RigidBody();

private:
	MultiCollider m_collider;
	PolygonCollider* m_poly;
	SphereCollider* m_sphe;
};

