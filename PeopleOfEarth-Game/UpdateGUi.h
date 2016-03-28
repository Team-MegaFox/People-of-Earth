#pragma once
#include "ShipStats.h"
#include <MegaEngine.h>

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
	~UpdateGUI() { }

	/// <summary>
	/// Sets variables for this class
	/// </summary>
	virtual void onStart() override
	{
		m_shipStats = getGameObjectByName("player")->getGameComponent<ShipStats>();

		m_healthBar = getGameObjectByName("Health Bar")->getGUIComponent<GUIImage>();
		m_healthOGSize = m_healthBar->getPercentSize();
		m_energyBar = getGameObjectByName("Energy Bar")->getGUIComponent<GUIImage>();
		m_energyOGSize = m_healthBar->getPercentSize();
		m_fuelBar = getGameObjectByName("Fuel Bar")->getGUIComponent<GUIImage>();
		m_fuelOGSize = m_healthBar->getPercentSize();
	}

	virtual void processInput(const InputManager& input, float delta) override
	{
		if (input.KeyPress(SDLK_i))
		{
			setHealth(getHealth() - 0.1f);
		}

		if (input.KeyPress(SDLK_k))
		{
			setEnergy(getEnergy() - 0.1f);
		}

		if (input.KeyPress(SDLK_m))
		{
			setFuel(getFuel() - 0.1f);
		}
	}

	virtual void update(float delta) override
	{
		m_healthBar->setPercentSize(PxVec2(getHealth() * m_healthOGSize.x, m_healthOGSize.y));
		m_healthBar->setAspectRatio((getHealth() * m_healthOGSize.x) / m_healthOGSize.y);

		m_energyBar->setPercentSize(PxVec2(getEnergy() * m_energyOGSize.x, m_energyOGSize.y));
		m_energyBar->setAspectRatio((getEnergy() * m_energyOGSize.x) / m_energyOGSize.y);

		m_fuelBar->setPercentSize(PxVec2(getFuel() * m_fuelOGSize.x, m_fuelOGSize.y));
		m_fuelBar->setAspectRatio((getFuel() * m_fuelOGSize.x) / m_fuelOGSize.y);
	}

private:

	/// <summary>
	/// The player ship stats
	/// </summary>
	ShipStats * m_shipStats;

	GUIImage* m_healthBar;
	PxVec2 m_healthOGSize;

	GUIImage* m_energyBar;
	PxVec2 m_energyOGSize;
	
	GUIImage* m_fuelBar;
	PxVec2 m_fuelOGSize;

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
};