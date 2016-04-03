// ***********************************************************************
// Author           : Christopher Maeda & Jesse Derochie
// Created          : 02-25-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 03-30-2016
// ***********************************************************************
// <copyright file="ShipStats.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary> yellow [colour='FFFFFF00'] red [colour='FFFF0000'] green [colour='FF00FF00'] blue [colour='FF0000FF']
//</summary>
// *********

#pragma once
#include "ShipStats.h"
#include "MissileAI.h"

	
void ShipStats::onStart()
{
	m_passengerShip = getGameObjectByName("passengerShip")->getGameComponent<RigidBody>();
	m_dialogueBox = getGameObjectByName("DialogueBox")->getGameComponent<DialogueBox>();
	m_rechargeSound = getGameObjectByName("Recharge sound")->getGameComponent<AudioSource>();
}

void ShipStats::updateHealth(float health)
{
	if (health < 0.0f)
	{
		// if this ship is the player, warn the player they are taking damage
		if (getParent()->getName() == "player1")
		{
			m_dialogueBox->sendMessage("Message From [colour='FFFFFF00']Terra 1 :\n[colour='FFFF0000']You're taking damage, be careful out there!", Importance::MEDIUM, false);
		}

		// if the passenger is taking damage from the enemy mother ship
		if (health == -0.7f)
		{
			m_dialogueBox->sendMessage("Message From [colour='FFFFFF00']Terra 1 :\n[colour='FF0000FF']We're taking heavy damage!! Where's our support!!", Importance::HIGH, false);
		}
	}
	
	if (m_health > 0.0f)
	{
		m_health += health;
	}

	// if this ship is the player, warn the player they are low on health
	if (getParent()->getName() == "player1")
	{
		if (m_health < m_dangerlevel && !m_healthWarnOnce)
		{
			m_dialogueBox->sendMessage("Message From [colour='FFFFFF00']Terra 1 :\n[colour='FFFF0000']Our systems indicate your[colour='FF00FF00']HEALTH[colour='FFFF0000']\nreserves are[colour='FF0000FF']dangerously low[colour='FF0000FF']!!!", Importance::HIGH, false);
			m_healthWarnOnce = true;
		}
	}

	// if this ship is the passenger ship and its low on health
	// warn the player only once
	if (getParent()->getName() == "passengerShip1")
	{
		if (!m_warnOnce && m_health < (m_dangerlevel * 2))
		{
			m_dialogueBox->sendMessage("Message From [colour='FFFFFF00']Terra 1 :\n[colour='FFFF0000']We're not going to make survive unless\nyou can disable that[colour='FF00FF00']Mother Ship", Importance::CRITICAL, false);
			m_warnOnce = true;
		}
	}

	// if an enemy ship has been destroyed
	if (getParent()->getName() == "enemyFighter")
	{
		if (m_health <= 0.0f)
		{
			m_dialogueBox->sendMessage("Message From [colour='FFFFFF00']Terra 1 :\n[colour='FFFFA500']That ought to teach him!\nWay to go Fighter 1!!", Importance::CRITICAL, false);
		}
	}

	// if the enemy mother has been destroyed
	if (getParent()->getName() == "EnemyMother")
	{
		if (m_health <= 0.0f)
		{
			m_dialogueBox->sendMessage("Message From [colour='FFFFFF00']Terra 1 :\n[colour='FFFFA500']That ought to teach him!\nWay to go Fighter 1!!", Importance::CRITICAL, false);
		}
	}
}

void ShipStats::updateFuel(float fuel)
{
	if (m_fuel > 0.0f)
	{
		m_fuel += fuel;
	}

	// if this ship is the player, warn the player they are low on fuel
	if (getParent()->getName() == "player1")
	{
		if (m_fuel < m_dangerlevel && !m_fuelWarnOnce)
		{
			m_dialogueBox->sendMessage("Message From [colour='FFFFFF00']Terra 1 :\n[colour='FFFF0000']Our systems indicate your[colour='FFFFFF00']FUEL[colour='FFFF0000']\n reserves are [colour='FF0000FF']dangerously low[colour='FF0000FF']!!!", Importance::HIGH, false);
			m_fuelWarnOnce = true;
		}
	}
}

void ShipStats::updateEnergy(float energy)
{
	if (m_energy > 0.0f)
	{
		m_energy += energy;
	}

	// if this ship is the player, warn the player they are low on energy
	if (getParent()->getName() == "player1")
	{
		if (m_energy < m_dangerlevel && !m_energyWarnOnce)
		{
			m_dialogueBox->sendMessage("Message From [colour='FFFFFF00']Terra 1 :\n[colour='FFFF0000']Our systems indicate your[colour='FF0000FF']ENERGY[colour='FFFF0000']\n reserves are [colour='FF0000FF']dangerously low[colour='FF0000FF']!!!", Importance::HIGH, false);
			m_energyWarnOnce = true;
		}
	}
}

void ShipStats::update(float timestep)
{
	// If this ship is the player ship and it is within proximity of the passenger ship
	// if its health, energy or fuel are low, begin replenishing and let the player know
	// they are being replenished
	if (getParent()->getName() == "player1")
	{
		if (Utility::getDistance(m_passengerShip->getPosition(), *getTransform()->getPosition()) <= 500.0f)
		{
			m_dialogueBox->sendMessage("Message From [colour='FFFFFF00']Terra 1 :\n[colour='FFFFFFFF']Stay close,\n we'll replenish your reserves.", Importance::LOW, false);

			if (m_playRechargeSound)
			{
				m_rechargeSound->play();
				m_playRechargeSound = false;
			}

			if (m_health < 1.0f)
			{
				updateHealth(0.0005f);
				if (!m_healing)
				{
					m_healing = true;
					if (m_health > m_dangerlevel)
					{
						m_healthWarnOnce = false;
					}
				}
			}
			else
			{
				m_healing = false;
			}

			if (m_energy < 1.0f)
			{
				updateEnergy(0.0005f);
				if (!m_energizing)
				{
					m_energizing = true;
					if (m_energy > m_dangerlevel)
					{
						m_energyWarnOnce = false;
					}
				}
			}
			else
			{
				m_energizing = false;
			}

			if (m_fuel < 1.0f)
			{
				updateFuel(0.0005f);
				if (!m_fueling)
				{
					m_fueling = true;
					if (m_fuel > m_dangerlevel)
					{
						m_fuelWarnOnce = false;
					}
				}
			}
			else
			{
				m_fueling = false;
			}
		}
		else
		{
			m_playRechargeSound = true;
		}
	}


	if (m_health <= 0.0f)
	{
		//Remove gameobject from the minimap
		MiniMap * map;
		map = getGameObjectByName("MiniMap")->getGameComponent<MiniMap>();
		map->deleteMapMarker(getParent()->getName());

		//Remove the homing missile target of this gameobject
		std::vector<GameObject*> missiles = getGameObjectsByName("Missile");
		//MissileAI* missileAIComponent;
		for (size_t i = 0; i < missiles.size(); i++)
		{
			/*for (size_t j = 0; j < missiles[i]->getAllGameComponents().size(); j++)
			{
				missileAIComponent = dynamic_cast<MissileAI*>(missiles[j]->getAllGameComponents()[j]);
				if (missileAIComponent != nullptr)
				{
					missileAIComponent->removeTarget(getParent()->getName());
					break;
				}
			}*/
			//MissileAI* missileAI = missiles[i]->getGameComponent<MissileAI>();
			//missileAI->removeTarget(getParent()->getName());

			missiles[i]->getGameComponent<MissileAI>()->removeTarget(getParent()->getName());
		}

		destroy(getParent());
	}
}

float ShipStats::getHealth()
{
	return m_health;
}

float ShipStats::getFuel()
{
	return m_fuel;
}

float ShipStats::getEnergy()
{
	return m_energy;
}

void ShipStats::setHealth(float health)
{
	m_health = health;
}

void ShipStats::setFuel(float fuel)
{
	m_fuel = fuel;
}

void ShipStats::setEnergy(float energy)
{
	m_energy = energy;
}
