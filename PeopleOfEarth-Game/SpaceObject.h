// ***********************************************************************
// Author           : Christopher Maeda
// Created          : 04-04-2016
//
// Last Modified By : Christopher Maeda
// Last Modified On : 04-04-2016
// ***********************************************************************
// <copyright file="SpaceObject.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary> yellow [colour='FFFFFF00'] red [colour='FFFF0000'] green [colour='FF00FF00'] blue [colour='FF0000FF']
//</summary>
// *********

#include <MegaEngine.h>
#include "ShipStats.h"

class SpaceObject : public GameComponent
{
public:
	SpaceObject() {}

	~SpaceObject() {}

	virtual void onStart() override
	{
		m_rigidBody = getParent()->getGameComponent<RigidBody>();
		m_playerFighterShipRigidBody = getGameObjectByName("player")->getGameComponent<RigidBody>();
	}

	virtual void update(float timestep) override
	{
		if (m_rigidBody->getCollided())
		{
			if (m_rigidBody->getCollider()->checkCollision(m_playerFighterShipRigidBody->getCollider()))
			{
				//getGameObjectByName("player")->getGameComponent<ShipStats>()->setHealth(0.0f);
				printf("Collision\n");
			}
		}
	}

private:
	RigidBody* m_playerFighterShipRigidBody;
	RigidBody* m_rigidBody;
};