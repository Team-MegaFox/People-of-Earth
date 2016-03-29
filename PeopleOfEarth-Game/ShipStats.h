// ***********************************************************************
// Author           : Christopher Maeda & Jesse Derochie
// Created          : 02-25-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 03-29-2016
// ***********************************************************************
// <copyright file="ShipStats.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
//</summary>
// *********

#pragma once
#include <MegaEngine.h>
#include "MiniMap.h"
#include "DialogueBox.h"

class ShipStats : public GameComponent
{
public: 
	ShipStats() : m_health(1.0f), m_fuel(1.0f), m_energy(1.0f) {}
	~ShipStats() {}

	virtual void onStart() override
	{
		m_passengerShip = getGameObjectByName("passengerShip")->getGameComponent<RigidBody>();
		m_dialogueBox = getGameObjectByName("DialogueBox")->getGameComponent<DialogueBox>();
	}

	void updateHealth(float health)
	{
		m_health += health;
	}

	void updateFuel(float fuel)
	{
		m_fuel += fuel;
	}

	void updateEnergy(float energy)
	{
		m_energy += energy;
	}

	virtual void update(float timestep) override
	{
		if (m_health <= 0.0f)
		{
			//MiniMap * map;
			map = getGameObjectByName("MiniMap")->getGameComponent<MiniMap>();
			map->deleteMapMarker(getParent()->getName());

			destroy(getParent());
		}
		if (Utility::getDistance(m_passengerShip->getPosition(), *getTransform()->getPosition()) <= 500.0f)
		{
			if (m_health < 1.0f)
			{
				updateHealth(0.0005f);
				if (!m_healing)
				{
					m_dialogueMessage += "Health Regenerating... \n";
					m_messageChanged = true;
					m_healing = true;
				}
			}
			else
			{
				m_healing = false;
				m_messageChanged = false;
			}

			if (m_energy < 1.0f)
			{
				updateEnergy(0.0005f);
				if (!m_energizing)
				{
					m_dialogueMessage += "Energy Regenerating... \n";
					m_messageChanged = true;
					m_energizing = true;
				}
			}
			else
			{
				m_energizing = false;
				m_messageChanged = false;
			}

			if (m_fuel < 1.0f)
			{
				updateFuel(0.0005f);
				if (!m_fueling)
				{
					m_dialogueMessage += "Fuel Replenishing... \n";
					m_messageChanged = true;
					m_fueling = true;
				}
			}
			else
			{
				m_fueling = false;
				m_messageChanged = false;
			}
			if (m_messageChanged)
			{
				m_dialogueBox->sendMessage(m_dialogueMessage, Importance::LOW);
				m_dialogueMessage = "";
				m_messageChanged = false;
			}
		}
	}

	float getHealth()
	{
		return m_health;
	}

	float getFuel()
	{
		return m_fuel;
	}

	float getEnergy()
	{
		return m_energy;
	}

	void setHealth(float health)
	{
		m_health = health;
	}

	void setFuel(float fuel)
	{
		m_fuel = fuel;
	}

	void setEnergy(float energy)
	{
		m_energy = energy;
	}

private:
	float m_health = 1.0f;
	float m_fuel = 1.0f;
	float m_energy = 1.0f;
	MiniMap * map;
	RigidBody * m_passengerShip;
	std::string m_dialogueMessage = "";
	DialogueBox * m_dialogueBox;
	bool m_healing = false; 
	bool m_energizing = false; 
	bool m_fueling = false; 
	bool m_messageChanged = false;
};