// ***********************************************************************
// Author           : Christopher Maeda & Jesse Derochie
// Created          : 03-11-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 04-20-2016
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
		m_playerGameObject = getGameObjectByName("player");
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
		//Destination Moon
		m_destinationGameObject = getGameObjectByName("destinationMoon");
		getParent()->addChild(
			(new GameObject(m_destinationGameObject->getName() + "_GUI"))
			->addGUIComponent(new GUIImage(PxVec4(0.0f, 0.70f, 0.1f, 0.1f), PxVec4(0.0f), "Images/minimap_graphics/destination_marker.png"))
			);
		//Enemy Mother Ship
		m_enemyMotherGameObject = getGameObjectByName("EnemyMother");
		getParent()->addChild(
			(new GameObject(m_enemyMotherGameObject->getName() + "_GUI"))
			->addGUIComponent(new GUIImage(PxVec4(0.0f, 0.70f, 0.1f, 0.1f), PxVec4(0.0f), "Images/minimap_graphics/enemy_mother_ship_marker.png"))
			);
		//Adding Enemy Fighter Ship
		m_allEnemyGameObjects = getGameObjectsByName("enemyFighter_");
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
		//	if (allGameObjects[i]->getName() == "enemyFighter_")
		//	{
		//		getParent()->addChild(
		//			(new GameObject(allGameObjects[i]->getName() + "_GUI"))
		//			->addGUIComponent(new GUIImage(PxVec4(0.0f, 0.70f, 0.3f, 0.3f), PxVec4(0.0f), "Images/space.png"))
		//			);
		//	}
		//}
	}

	void deleteMapMarker(const std::string & objectName)
	{
		if (objectName == "player1")
		{
			// remove map marker for player
			getParent()->removeChild(getParent()->getAllChildren()[0]);
			// remove reference to the player object
			m_playerGameObject = nullptr;
		}
		else if (objectName == "passengerShip1")
		{
			// remove map marker for passenger
			getParent()->removeChild(getParent()->getAllChildren()[1]);
			// remove reference to the passenger object
			m_passengerGameObject = nullptr;
		}
		else if (objectName == "EnemyMother1")
		{
			// remove map marker for Enemy Mother
			getParent()->removeChild(getParent()->getAllChildren()[2]);
			// remove reference to the Enemy Mother object
			m_enemyMotherGameObject = nullptr;
		}
		else
		{
			for (size_t i = 1; i < m_allEnemyGameObjects.size() + 1; i++)
			{
				if (objectName == "enemyFighter_" + std::to_string(i))
				{
					//If enemy mother ship is dead then
					if (m_enemyMotherGameObject == nullptr)
					{
						getParent()->removeChild(getParent()->getAllChildren()[i + 2]);
					}
					//Mother ship is still alive
					else
					{
						getParent()->removeChild(getParent()->getAllChildren()[i + 3]);
					}
					m_allEnemyGameObjects[i - 1] = nullptr;
					m_allEnemyGameObjects.erase(m_allEnemyGameObjects.begin() + (i - 1));
					break;
				}
			}
		}

	}

	virtual void update(float delta) override
	{
		//Updates all the GUI Gameobjects in the scene from the Scene GameObjects
		bool dead;

		m_allEnemyGameObjects = getGameObjectsByName("enemyFighter_");

		// for all the game objects in the scene 
		for (size_t i = 0; i < getParent()->getAllChildren().size(); i++)
		{
			// label all game objects as dead
			dead = true;
			// if the game object is the player game object
			if (getParent()->getAllChildren()[i]->getName() == m_playerGameObject->getName() + "_GUI")
			{
				// set the position of the parent of this map to be centered on the player
				getParent()->getAllChildren()[i]->getTransform()->setPosition(*m_playerGameObject->getTransform()->getPosition());
				getParent()->getAllChildren()[i]->getTransform()->setRotation(*m_playerGameObject->getTransform()->getRotation());
				// label the player ship as not dead
				dead = false;
			}
			// if the gameobject is the passenger ship
			else if (getParent()->getAllChildren()[i]->getName() == m_passengerGameObject->getName() + "_GUI")
			{
				// set the position of this game object on the map to be realted to the position of the assenger ship in the world
				getParent()->getAllChildren()[i]->getTransform()->setPosition(*m_passengerGameObject->getTransform()->getPosition());
				getParent()->getAllChildren()[i]->getTransform()->setRotation(*m_passengerGameObject->getTransform()->getRotation());
				// label the passenger ship as not dead
				dead = false;
			}
			// if the gameobject is the enemy mother ship
			else if (getParent()->getAllChildren()[i]->getName() == m_destinationGameObject->getName() + "_GUI")
			{
				// set the position of this game object on the map to be realted to the position of the assenger ship in the world
				getParent()->getAllChildren()[i]->getTransform()->setPosition(*m_destinationGameObject->getTransform()->getPosition());
				getParent()->getAllChildren()[i]->getTransform()->setRotation(*m_destinationGameObject->getTransform()->getRotation());
				// label the passenger ship as not dead
				dead = false;
			}
			// if the gameobject is the enemy mother ship
			else if (getParent()->getAllChildren()[i]->getName() == m_enemyMotherGameObject->getName() + "_GUI")
			{
				// set the position of this game object on the map to be realted to the position of the assenger ship in the world
				getParent()->getAllChildren()[i]->getTransform()->setPosition(*m_enemyMotherGameObject->getTransform()->getPosition());
				getParent()->getAllChildren()[i]->getTransform()->setRotation(*m_enemyMotherGameObject->getTransform()->getRotation());
				// label the passenger ship as not dead
				dead = false;
			}
			else
			{
				// we assume the game objects remaining are enemy fighter ships
				for (size_t j = 0; j < m_allEnemyGameObjects.size(); j++)
				{
					if (m_allEnemyGameObjects[j] != nullptr)
					{
						// if they are 
						if (getParent()->getAllChildren()[i]->getName() == m_allEnemyGameObjects[j]->getName() + "_GUI")
						{
							// set the position of these gameobjects on the minimap to be related to their position in the world
							getParent()->getAllChildren()[i]->getTransform()->setPosition(*m_allEnemyGameObjects[j]->getTransform()->getPosition());
							getParent()->getAllChildren()[i]->getTransform()->setRotation(*m_allEnemyGameObjects[j]->getTransform()->getRotation());
							// label the game object as not dead
							dead = false;
							break;
						}
					}
				}
			}
			//if the gameobject is still labelled as dead in the scene then
			if (dead)
			{
				//getParent()->getAllChildren()[i]->setEnabled(false);
				//delete getParent()->getAllChildren()[i];
				destroy(getParent()->getAllChildren()[i]);
				//getParent()->getAllChildren().erase(getParent()->getAllChildren().begin() + i);
			}
		}

		// set the positions gathered with this method onto the minimap
		setMiniMapPosition();
	}

	virtual void processInput(const InputManager& input, float delta) override
	{
		if (input.PadButtonDown(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER))
		{
			m_angleRotationZ += 0.025f;
			checkToResetCalculations();
		}
		if (input.PadButtonDown(SDL_CONTROLLER_BUTTON_LEFTSHOULDER))
		{
			m_angleRotationZ -= 0.025f;
			checkToResetCalculations();
		}

		if (input.GetThumbRPosition().x > 0.3f)
		{
			if ((PxAbs(m_angleRotationZ) > 1.57f && PxAbs(m_angleRotationZ) < 3.14f)
				|| (PxAbs(m_angleRotationZ) > 4.71f && PxAbs(m_angleRotationZ) < 6.28f))
			{
				m_angleRotationY -= 0.025f;
			}
			else
			{
				m_angleRotationY += 0.025f;
			}
			checkToResetCalculations();
		}
		if (input.GetThumbRPosition().x < -0.3f)
		{
			if ((PxAbs(m_angleRotationZ) > 1.57f && PxAbs(m_angleRotationZ) < 3.14f)
				|| (PxAbs(m_angleRotationZ) > 4.71f && PxAbs(m_angleRotationZ) < 6.28f))
			{
				m_angleRotationY += 0.025f;
			}
			else
			{
				m_angleRotationY -= 0.025f;
			}
			checkToResetCalculations();
		}
		if (input.GetThumbRPosition().y > 0.3f)
		{
			//m_angleRotationX -= 0.025f;
			if (PxAbs(m_angleRotationZ) > 1.57f && PxAbs(m_angleRotationZ) < 4.71f)
			{
				m_angleRotationX -= 0.025f;
			}
			else
			{
				m_angleRotationX += 0.025f;
			}
			checkToFlipMapDirection();
			checkToResetCalculations();
		}
		if (input.GetThumbRPosition().y < -0.3f)
		{
			//m_angleRotationX += 0.025f;
			if (PxAbs(m_angleRotationZ) > 1.57f && PxAbs(m_angleRotationZ) < 4.71f)
			{
				m_angleRotationX += 0.025f;
			}
			else
			{
				m_angleRotationX -= 0.025f;
			}
			checkToFlipMapDirection();
			checkToResetCalculations();
		}
	}

	void checkToFlipMapDirection()
	{
		float absRotationXValue = PxAbs(m_angleRotationX);
		if (absRotationXValue > 1.57f && absRotationXValue < 4.71f)
		{
			m_flipDirection = true;
		}
		else if (absRotationXValue > 4.71f && absRotationXValue < 6.28f)
		{
			m_flipDirection = false;
		}
		else
		{
			m_flipDirection = false;
		}
	}

	void checkToResetCalculations()
	{
		float absRotationValue = PxAbs(m_angleRotationX);
		if (absRotationValue > 6.28f)
		{
			if (m_angleRotationX > 0)
			{
				m_angleRotationX -= 6.28f;
			}
			else
			{
				m_angleRotationX += 6.28f;
			}
		}
		absRotationValue = PxAbs(m_angleRotationY);
		if (absRotationValue > 6.28f)
		{
			if (m_angleRotationY > 0)
			{
				m_angleRotationY -= 6.28f;
			}
			else
			{
				m_angleRotationY += 6.28f;
			}
		}
		absRotationValue = PxAbs(m_angleRotationZ);
		if (absRotationValue > 6.28f)
		{
			if (m_angleRotationZ > 0)
			{
				m_angleRotationZ -= 6.28f;
			}
			else
			{
				m_angleRotationZ += 6.28f;
			}
		}
		/*if (absRotationZValue > 1.57f && absRotationZValue < 4.71f)
		{
		m_flipDirection = true;
		}
		else if (absRotationZValue > 4.71f && absRotationZValue < 6.28f)
		{
		m_flipDirection = false;
		}
		else if (absRotationZValue > 6.28f)
		{
		if (m_angleRotationZ > 0)
		{
		m_angleRotationZ -= 6.28f;
		}
		else
		{
		m_angleRotationZ += 6.28f;
		}
		}*/
	}

	void setMiniMapPosition()
	{
		//Get the origin of the map in the scene
		playerPosition = *getParent()->getAllChildren()[0]->getTransform()->getPosition();
		//Checks to see if the GUI component needs to be rendered
		float distance;

		// For all the gameobjects added to this map
		for (size_t i = 0; i < getParent()->getAllChildren().size(); i++)
		{
			
			//Get the direction
			PxVec3 direction = *getParent()->getAllChildren()[i]->getTransform()->getPosition() - playerPosition;
			direction.y = 0.0f;
			direction.normalize();

			PxVec3 playerDir = Utility::getForward(*m_playerGameObject->getTransform()->getRotation());
			playerDir.y = 0.0f;
			playerDir.normalize();

			float angle = PxAcos(playerDir.dot(PxVec3(0.0f, 0.0f, 1.0f)));

			if ((playerDir.x > 0.0f && playerDir.z < 0.0f) || (playerDir.x > 0.0f && playerDir.z > 0.0f))
			{
				angle = ToRadians(360.0f) - angle;
			}

			//Rotate
			PxVec3 tempDirection = direction;
			direction.z = tempDirection.z * cos(angle) - tempDirection.x * sin(angle);
			direction.x = tempDirection.z * sin(angle) + tempDirection.x * cos(angle);
			
			// get their distance from the player
			distance = Utility::getDistance(playerPosition, *getParent()->getAllChildren()[i]->getTransform()->getPosition());

			// do a distance check
			if (distance < m_miniMapRadius)
			{
				direction *= distance / (2 * m_miniMapRadius);
				direction.z *= -1;
			}
			else
			{
				//Off the minimap
				direction.z *= -1;
				direction *= 0.5f;
				//getParent()->getAllChildren()[i]->setEnabled(false);
			}

			//To make it inside the circle of the minimap
			direction *= 0.9f;

			//Update on the GUI Image
			getParent()->getAllChildren()[i]->getGUIComponent<GUIImage>()->setPercentPosition(
				PxVec2(0.5f, 0.5f) +
				PxVec2(direction.x, direction.z)
				- getParent()->getAllChildren()[i]->getGUIComponent<GUIImage>()->getPercentSize() / 2);

		}
	}

private:
	GameObject* m_playerGameObject;
	GameObject* m_passengerGameObject;
	GameObject * m_enemyMotherGameObject;
	GameObject* m_destinationGameObject;
	std::vector<GameObject*> m_allEnemyGameObjects;
	PxVec3 playerPosition;
	float m_miniMapRadius;
	PxVec2 m_miniMapCenterPosition;

	float m_angleRotationY = 0.0f;
	float m_angleRotationX = 0.0f;
	float m_angleRotationZ = 0.0f;
	bool m_flipDirection = false;
	bool m_flipCalculations = false;
};