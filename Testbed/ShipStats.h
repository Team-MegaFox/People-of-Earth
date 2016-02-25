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
	ShipStats() {}
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
		
	}

protected:
	float m_health = 1.0f;
	float m_fuel = 1.0f;
	float m_energy = 1.0f;
};