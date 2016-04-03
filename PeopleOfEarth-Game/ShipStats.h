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
#include <MegaEngine.h>
#include "MiniMap.h"
#include "DialogueBox.h"

class MissileAI;

class ShipStats : public GameComponent
{
public: 
	ShipStats() : m_health(1.0f), m_fuel(1.0f), m_energy(1.0f), m_playRechargeSound(false) {}
	~ShipStats() {}

	virtual void onStart() override;
	void updateHealth(float health);
	void updateFuel(float fuel);
	void updateEnergy(float energy);
	virtual void update(float timestep) override;
	float getHealth();
	float getFuel();
	float getEnergy();
	void setHealth(float health);
	void setFuel(float fuel);
	void setEnergy(float energy);

private:
	float m_health = 1.0f;
	float m_fuel = 1.0f;
	float m_energy = 1.0f;
	RigidBody * m_passengerShip;
	DialogueBox * m_dialogueBox;
	bool m_healing = false; 
	bool m_energizing = false; 
	bool m_fueling = false; 
	bool m_warnOnce = false;
	bool m_healthWarnOnce = false;
	bool m_energyWarnOnce = false;
	bool m_fuelWarnOnce = false;
	float m_dangerlevel = 0.3f;

	bool m_playRechargeSound;
	AudioSource* m_rechargeSound;
};