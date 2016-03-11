// ***********************************************************************
// Author           : Christopher Maeda
// Created          : 03-11-2016
//
// Last Modified By : Christopher Maeda
// Last Modified On : 03-11-2016
// ***********************************************************************
// <copyright file="MiniMap.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
//</summary>
// ***********************************************************************

#pragma once
#include <MegaEngine.h>
#include <PhysX/PxPhysicsAPI.h>
#include <vector>
using namespace physx;

class MiniMap : public GameComponent
{
public: 
	MiniMap(PxVec2 miniMapCenterPosition = PxVec2(0), float miniMapRadius = 1000.0f) :
		m_miniMapCenterPosition(miniMapCenterPosition),
		m_miniMapRadius(miniMapRadius) {}

	~MiniMap() {}

	virtual void onStart()
	{
		//Adding Figher Ships
		m_playerGameObject = getGameObjectByName("Fighter Ship");
		playerPosition = PxVec3(0);
		getParent()->addChild(
			(new GameObject(m_playerGameObject->getName() + "_GUI"))
			->addGUIComponent(new GUIImage(PxVec4(1.0f, 1.0f, 0.1f, 0.1f), PxVec4(0.0f), "Images/minimap_graphics/player_marker.png"))
			);
		//Adding Passenger Ship
		m_passengerGameObject = getGameObjectByName("passengerShip");
		getParent()->addChild(
			(new GameObject(m_passengerGameObject->getName() + "_GUI"))
			->addGUIComponent(new GUIImage(PxVec4(0.0f, 0.70f, 0.1f, 0.1f), PxVec4(0.0f), "Images/minimap_graphics/passenger_ship_marker.png"))
			);
		//Adding Enemy Fighter Ship
		m_allEnemyGameObjects = getGameObjectsByName("enemyFighter");
		for (size_t i = 0; i < m_allEnemyGameObjects.size(); i++)
		{
			getParent()->addChild(
				(new GameObject(m_allEnemyGameObjects[i]->getName() + "_GUI"))
				->addGUIComponent(new GUIImage(PxVec4(0.0f, 0.70f, 0.1f, 0.1f), PxVec4(0.0f), "Images/minimap_graphics/enemy_marker.png"))
				);
		}

		////Add child for all the GUI Components
		//for (size_t i = 0; i < allGameObjects.size(); i++)
		//{
		//	if (allGameObjects[i]->getName() == "Fighter Ship")
		//	{
		//		getParent()->addChild(
		//			(new GameObject(allGameObjects[i]->getName() + "_GUI"))
		//			->addGUIComponent(new GUIImage(PxVec4(0.0f, 0.70f, 0.3f, 0.3f), PxVec4(0.0f), "Images/healthbar.png"))
		//			);
		//	}
		//	if (allGameObjects[i]->getName() == "passengerShip")
		//	{
		//		getParent()->addChild(
		//			(new GameObject(allGameObjects[i]->getName() + "_GUI"))
		//			->addGUIComponent(new GUIImage(PxVec4(0.0f, 0.70f, 0.3f, 0.3f), PxVec4(0.0f), "Images/energybar.png"))
		//			);
		//	}
		//	if (allGameObjects[i]->getName() == "enemyFighter")
		//	{
		//		getParent()->addChild(
		//			(new GameObject(allGameObjects[i]->getName() + "_GUI"))
		//			->addGUIComponent(new GUIImage(PxVec4(0.0f, 0.70f, 0.3f, 0.3f), PxVec4(0.0f), "Images/space.png"))
		//			);
		//	}
		//}
	}

	virtual void update(float delta) override
	{
		//Updates all the GUI Gameobject in the scene from the Scene GameObjects
		bool dead;
		for (size_t i = 0; i < getParent()->getAllChildren().size(); i++)
		{
			dead = true;
			if (getParent()->getAllChildren()[i]->getName() == m_playerGameObject->getName() + "_GUI")
			{
				getParent()->getAllChildren()[i]->getTransform()->setPosition(*m_playerGameObject->getTransform()->getPosition());
				getParent()->getAllChildren()[i]->getTransform()->setRotation(*m_playerGameObject->getTransform()->getRotation());
				dead = false;
			}
			if (dead)
			{
				if (getParent()->getAllChildren()[i]->getName() == m_passengerGameObject->getName() + "_GUI")
				{
					getParent()->getAllChildren()[i]->getTransform()->setPosition(*m_passengerGameObject->getTransform()->getPosition());
					getParent()->getAllChildren()[i]->getTransform()->setRotation(*m_passengerGameObject->getTransform()->getRotation());
					dead = false;
				}
			}
			if (dead)
			{
				for (size_t j = 0; j < m_allEnemyGameObjects.size(); j++)
				{
					if (getParent()->getAllChildren()[i]->getName() == m_allEnemyGameObjects[j]->getName() + "_GUI")
					{
						getParent()->getAllChildren()[i]->getTransform()->setPosition(*m_allEnemyGameObjects[j]->getTransform()->getPosition());
						getParent()->getAllChildren()[i]->getTransform()->setRotation(*m_allEnemyGameObjects[j]->getTransform()->getRotation());
						dead = false;
						break;
					}
				}
			}
			//if the gameobject is dead in the scene then
			if (dead)
			{
				delete getParent()->getAllChildren()[i];
				getParent()->getAllChildren().erase(getParent()->getAllChildren().begin() + i);
			}
		}
		//Get the origin of the map in the scene
		playerPosition = *getParent()->getAllChildren()[0]->getTransform()->getPosition();
		//Checks to see if the GUI component needs to be rendered
		float distance;
		for (size_t i = 0; i < getParent()->getAllChildren().size(); i++)
		{
			distance = Utility::getDistance(playerPosition, *getParent()->getAllChildren()[i]->getTransform()->getPosition());
			//Distance check
			if (distance < m_miniMapRadius)
			{
				//Get the direction
				PxVec3 direction = *getParent()->getAllChildren()[i]->getTransform()->getPosition() - playerPosition;
				direction.normalize();
				direction *= distance / m_miniMapRadius;
				direction.z *= -1.0f;

				//Update on the GUI Image
				getParent()->getAllChildren()[i]->getGUIComponent<GUIImage>()->setPercentPosition(
					PxVec2(0.5f, 0.5f) +
					PxVec2(direction.x, direction.z)
					- getParent()->getAllChildren()[i]->getGUIComponent<GUIImage>()->getPercentSize() / 2);
			}
			else
			{
				//Off the minimap
				getParent()->getAllChildren()[i]->setEnabled(false);
			}

		}
	}

private:
	GameObject* m_playerGameObject;
	GameObject* m_passengerGameObject;
	std::vector<GameObject*> m_allEnemyGameObjects;
	PxVec3 playerPosition;
	float m_miniMapRadius;
	PxVec2 m_miniMapCenterPosition;
};