#pragma once
#include <MegaEngine.h>

#include "FreeLook.h"
#include "FreeMove.h"
#include "ShowPauseComp.h"
#include "FireProjectile.h"
#include "EnemyFighterShipAI.h"
#include "PassengerShipAI.h"
#include "AsteroidField.h"
#include "UpdateGUi.h"
#include "MiniMap.h"
#include <PhysX/PxPhysicsAPI.h>
using namespace physx;

class MissionOneScene : public Scene
{
public:
	MissionOneScene() : Scene("Mission 1") { }
	~MissionOneScene() { }

	virtual void init(const Viewport& window) override
	{
		//Material humanShip("human_ship", 1.0f, 10, Texture("Ships/Eric/HumanShip.png"));
		Material ship1("ship1", 0.5f, 4, Texture("Ships/AF-SS01/AF-SS01_White.png"), Texture("Ships/AF-SS01/AF-SS01_Normalmap.png"));
		Material alienShip("alien_ship", 5.0f, 4,
			Texture("Ships/Alien/astra_elements2_c.png"),
			Texture("Ships/Alien/astraBattleship_Normals.png"),
			Texture("Ships/Alien/astra_elements2_i.png"));

		Material motherShip("passengerShip", 0.5f, 4, Texture("Ships/MotherShip/MotherShip.png"));
		Material earth("earth", 1.0f, 10, Texture("Planets/earth.png"));
		Material mars("mars", 1.0f, 10, Texture("Planets/mars.jpg"));
		Material jupiter("jupiter", 1.0f, 10, Texture("Planets/jupiter.jpg"));
		Material sun("sun", 10.0f, 100, Texture("Planets/sun.jpg"));
		Material moon("moon", 1.0f, 10, Texture("Planets/moon.jpg"));

		addToRoot((new GameObject("Skybox"))
			->addGameComponent(new SkyboxRenderer("Skybox/Starfield/starfield.tga")));

		GameObject * starBoardLight = new GameObject("starBoardPointLight", PxVec3(7.0f, 1.0f, -3.5f));
		starBoardLight->addGameComponent(new PointLight(PxVec3(0.0f, 1.0f, 0.0f), 0.5f));

		GameObject * portLight = new GameObject("portPointLight", PxVec3(-7.0f, 1.0f, -3.5f));
		portLight->addGameComponent(new PointLight(PxVec3(1.0f, 0.0f, 0.0f), 0.5f));

		GameObject * rearLight = new GameObject("rearPointLight", PxVec3(0.0f, 1.0f, -6.0f));
		rearLight->addGameComponent(new PointLight(PxVec3(0.1f, 0.1f, 0.1f), 0.5f));

		GameObject * thrusterLight = new GameObject("thrusterPointLight", PxVec3(0.0f, 0.0f, -8.0f));
		thrusterLight->addGameComponent(new PointLight(PxVec3(1.0f, 0.75f, 0.0f), 0.5f));

		GameObject* fighterShip =
			(new GameObject("Fighter Ship", PxVec3(0.0f, 0.0f, 0.0f), PxQuat(ToRadians(180.0f), PxVec3(0.0f, 1.0f, 0.0f))))
			->addGameComponent(new MeshRenderer(Mesh("Ships/AF-SS01.obj", 1.0f), Material("ship1")))
			->addGameComponent(new RigidBody(PxVec3(1.0f, 1.0f, 1.0f), PxQuat(PxIdentity), 1.0f, 7.0f, 1.0f, 5.0f))
			->addGameComponent(new FireProjectile("(laser_fired)268168__shaun105__laser.wav"))
			->addGameComponent(new PlayerShipMovementController("camera", 50.0f))
			->addChild(starBoardLight)
			->addChild(portLight)
			->addChild(rearLight)
			->addChild(thrusterLight)
			->addGameComponent(new ShipStats)
			->addGameComponent(new UpdateGUI);

		// The human fighter ship and camera
		GameObject* camera =
			(new GameObject("camera",
			*fighterShip->getTransform()->getPosition() - Utility::getForward(*fighterShip->getTransform()->getRotation()) * 30.0f
			+ PxVec3(0.0f, 5.0f, 0.0f)))
			->addGameComponent(new CameraComponent(ToRadians(75.0f), window.getAspectRatio(), 0.1f, 200000.0f))
			->addGameComponent(new Listener());
		addToRoot(fighterShip);
		addToRoot(camera);


		addToRoot((new GameObject("DirectionalLight", PxVec3(0.0f, 0.0f, 0.0f), PxQuat(ToRadians(180.0f), PxVec3(0.0f, 1.0f, 0.0f).getNormalized())))
			->addGameComponent(new DirectionalLight(PxVec3(1.0f, 1.0f, 1.0f), 0.6f, 8)));

		// the passenger ship
		addToRoot((new GameObject("passengerShip", PxVec3(0.0f, 0.0f, 300.0f), PxQuat(0.0f, 0.0f, 0.0f, 1.0f), PxVec3(1.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Ships/MotherShip.obj", 50.0f), Material("passengerShip")))
			->addGameComponent(new RigidBody(PxVec3(0.0f, 0.0f, 300.0f), PxQuat(PxIdentity), 1.0f, 50.0f, 40.0f, 275.0f))
			->addGameComponent(new PassengerShipAI)
			->addGameComponent(new ShipStats)
			);


		//addToRoot((new GameObject("GameOver"))
		//	->addGUIComponent(new GUIButton(PxVec4(0.35f, 0.5f, 0.3f, 0.05f), PxVec4(0.0f), "Return To Mission Select",
		//	std::bind(&MissionOneScene::onRetryClick, this, std::placeholders::_1)))
		//	);

		addArea1OfMission1();

		//addArea2OfMission1();

		addGUI();
	}

private:
	void addGUI()
	{
		float barXPos = 0.02f;
		float barWidth = 0.25f;
		float barHeight = 0.1f;

		addToRoot((new GameObject("Health Bar Background"))
			->addGUIComponent(new GUIImage(PxVec4(barXPos, 0.05f, barWidth, barHeight), PxVec4(0.0f), "Images/BarBackground.png", 287.0f / 20.0f))
			->addChild((new GameObject("Health Bar"))
			->addGUIComponent(new GUIImage(PxVec4(0.05f, 0.18f, 12.7f, 0.62f), PxVec4(0.0f), "Images/healthbar.png"))));

		addToRoot((new GameObject("Energy Bar Background"))
			->addGUIComponent(new GUIImage(PxVec4(barXPos, 0.09f, barWidth, barHeight), PxVec4(0.0f), "Images/BarBackground.png", 287.0f / 20.0f))
			->addChild((new GameObject("Energy Bar"))
			->addGUIComponent(new GUIImage(PxVec4(0.05f, 0.18f, 12.7f, 0.62f), PxVec4(0.0f), "Images/energybar.png"))));

		addToRoot((new GameObject("Fuel Bar Background"))
			->addGUIComponent(new GUIImage(PxVec4(barXPos, 0.13f, barWidth, barHeight), PxVec4(0.0f), "Images/BarBackground.png", 287.0f / 20.0f))
			->addChild((new GameObject("Fuel Bar"))
			->addGUIComponent(new GUIImage(PxVec4(0.05f, 0.18f, 12.7f, 0.62f), PxVec4(0.0f), "Images/fuelbar.png"))));
	

		addToRoot((new GameObject("MiniMap"))
			->addGUIComponent(new GUIImage(PxVec4(0.0f, 0.70f, 0.3f, 0.3f), PxVec4(0.0f), "Images/minimap_graphics/GUI_MiniMap.png"))
			->addGameComponent(new MiniMap(PxVec2(0.15f, 0.15f), 3000.0f))
			);
	}

	void addArea1OfMission1()
	{
		// the alien fighter ship
		addToRoot((new GameObject("enemyFighter", PxVec3(20.0f, 0.0f, 1000.0f), PxQuat(0.0f, 0.0f, 0.0f, 1.0f), PxVec3(1.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Ships/enemyBattleShip.obj", 10.0f), Material("alien_ship")))
			->addGameComponent(new RigidBody(PxVec3(0.0f, -5.0f, 80.0f), PxQuat(PxIdentity), 1.0f, 10.0f, 6.0f, 24.0f))
			->addGameComponent(new EnemyFighterShipAI)
			->addGameComponent(new ShipStats)
			);
		// //the alien fighter ship
		//addToRoot((new GameObject("enemyFighter", PxVec3(-20.0f, 0.0f, 3000.0f), PxQuat(0.0f, 0.0f, 0.0f, 1.0f), PxVec3(1.0f)))
		//	->addGameComponent(new MeshRenderer(Mesh("Ships/enemyBattleShip.obj", 10.0f), Material("alien_ship")))
		//	->addGameComponent(new RigidBody(PxVec3(0.0f, -5.0f, 80.0f), PxQuat(PxIdentity), 1.0f, 10.0f, 6.0f, 24.0f))
		//	->addGameComponent(new EnemyFighterShipAI)
		//	->addGameComponent(new ShipStats)
		//	);
		// //the alien fighter ship
		//addToRoot((new GameObject("enemyFighter", PxVec3(0.0f, 20.0f, 1000.0f), PxQuat(0.0f, 0.0f, 0.0f, 1.0f), PxVec3(1.0f)))
		//	->addGameComponent(new MeshRenderer(Mesh("Ships/enemyBattleShip.obj", 10.0f), Material("alien_ship")))
		//	->addGameComponent(new RigidBody(PxVec3(0.0f, -5.0f, 80.0f), PxQuat(PxIdentity), 1.0f, 10.0f, 6.0f, 24.0f))
		//	->addGameComponent(new EnemyFighterShipAI)
		//	->addGameComponent(new ShipStats)
		//	);
		//// the alien fighter ship
		//addToRoot((new GameObject("enemyFighter", PxVec3(0.0f, -20.0f, 3000.0f), PxQuat(0.0f, 0.0f, 0.0f, 1.0f), PxVec3(1.0f)))
		//	->addGameComponent(new MeshRenderer(Mesh("Ships/enemyBattleShip.obj", 10.0f), Material("alien_ship")))
		//	->addGameComponent(new RigidBody(PxVec3(0.0f, -5.0f, 80.0f), PxQuat(PxIdentity), 1.0f, 10.0f, 6.0f, 24.0f))
		//	->addGameComponent(new EnemyFighterShipAI)
		//	->addGameComponent(new ShipStats)
		//	);

		//// Planets and Moons
		//addToRoot((new GameObject("moon", PxVec3(1000.0f, 0.0f, 1000.0f)))
		//	->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_A.obj", 32.0f), Material("moon")))
		//	);

		//addToRoot((new GameObject("earth", PxVec3(-1000.0f, 0.0f, 0.0f)))
		//	->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_B.obj", 100.0f), Material("earth")))
		//	);

		//addToRoot((new GameObject("mars", PxVec3(7500.0f, 0.0f, 7500.0f)))
		//	->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_C.obj", 35.0f), Material("mars")))
		//	);

	}

	void addArea2OfMission1()
	{
		// TODO : Optimize AsteroidField class

		// Asteroids
		//addToRoot((new GameObject("Asteroid Field", PxVec3(0.0f, 0.0f, 4000.0f)))
		//	->addGameComponent(new AsteroidField())
		//	);
		//addToRoot((new GameObject("Asteroid Field", PxVec3(0.0f, 5.0f, 4500.0f)))
		//	->addGameComponent(new AsteroidField())
		//	);

		addToRoot((new GameObject("jupiterMoon1", PxVec3(1000.0f, 0.0f, 10300.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_D.obj", 75.0f), Material("moon")))
			);

		addToRoot((new GameObject("jupiterMoon2", PxVec3(-900.0f, 0.0f, 9800.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_E.obj", 20.0f), Material("mars")))
			);

		addToRoot((new GameObject("jupiterMoon3", PxVec3(-800.0f, 0.0f, 11000.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_F.obj", 32.0f), Material("moon")))
			);

		addToRoot((new GameObject("jupiter", PxVec3(0.0f, 0.0f, 10000.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_G.obj", 200.0f), Material("jupiter")))
			);

		addToRoot((new GameObject("sun", PxVec3(20000.0f, 5000.0f, 20000.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_A.obj", 400.0f), Material("sun")))
			);
	}

private:

	//bool onRetryClick(const GameObject& go)
	//{
	//	getCoreEngine()->getSceneManager()->pop();
	//	return true;
	//}
};
