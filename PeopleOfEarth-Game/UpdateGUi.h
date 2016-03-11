#pragma once
#include "ShipStats.h"
#include <Components\GameComponents.h>

class UpdateGUI 
	: public GameComponent
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="UpdateGUI"/> class.
	/// </summary>
	UpdateGUI() {}

	/// <summary>
	/// Finalizes an instance of the <see cref="UpdateGUI"/> class.
	/// </summary>
	~UpdateGUI()
	{
		delete m_shipStats;
	}

	/// <summary>
	/// Sets variables for this class
	/// </summary>
	virtual void onStart() override
	{
		m_shipStats = getGameObjectByName("Fighter Ship")->getGameComponent<ShipStats>();
	}

	/// <summary>
	/// Gets the health level of the ship.
	/// </summary>
	/// <returns></returns>
	float getHealth() { return m_shipStats->getHealth(); }
	/// <summary>
	/// Gets the energy level of the ship.
	/// </summary>
	/// <returns></returns>
	float getEnergy() { return m_shipStats->getEnergy(); }
	/// <summary>
	/// Gets the fuel level of the ship.
	/// </summary>
	/// <returns></returns>
	float getFuel() { return m_shipStats->getFuel(); }

	/// <summary>
	/// Sets the health level of the ship.
	/// </summary>
	/// <param name="newHealth">The new health.</param>
	void setHealth(float newHealth) { m_shipStats->setHealth(newHealth); }
	/// <summary>
	/// Sets the energy level of the ship.
	/// </summary>
	/// <param name="newEnergy">The new energy.</param>
	void setEnergy(float newEnergy) { m_shipStats->setEnergy(newEnergy); }
	/// <summary>
	/// Sets the fuel level of the ship.
	/// </summary>
	/// <param name="newFuel">The new fuel.</param>
	void setFuel(float newFuel) { m_shipStats->setFuel(newFuel); }

private:

	/// <summary>
	/// The player ship stats
	/// </summary>
	ShipStats * m_shipStats;
};