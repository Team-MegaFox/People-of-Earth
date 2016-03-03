// ***********************************************************************
// Author           : Christopher Maeda
// Created          : 02-25-2016
//
// Last Modified By : Christopher Maeda
// Last Modified On : 02-25-2016
// ***********************************************************************
// <copyright file="ShipStats.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
//</summary>
// *********

#pragma once
#include <Components\GameComponents.h>

class ShipStats : public GameComponent
{
public: 
	ShipStats() : m_health(1.0f), m_fuel(1.0f), m_energy(1.0f) {}
	~ShipStats() {}

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
			destroy(getParent());
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
};