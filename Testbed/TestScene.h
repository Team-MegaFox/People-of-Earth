#pragma once
#include <MegaEngine.h>
#include <iostream>

#include "FreeLook.h"
#include "FreeMove.h"
#include "PlanetSpin.h"
#include "FireProjectile.h"
#include "EnemyFighterShipAI.h"
#include "PassengerShipAI.h"
#include <PhysX/PxPhysicsAPI.h>
using namespace physx;

class TestScene : public Scene
{
public:
	TestScene() : Scene("Hello World") { }
	~TestScene() { }

	virtual void init(const Viewport& window) override
	{
		//Material bricks("bricks", 0.5f, 4, Texture("bricks.jpg"), Texture("bricks_normal.jpg"), Texture("bricks_disp.png"));

		Material ship1("ship1", 0.5f, 4, Texture("Ships/AF-SS01/AF-SS01_White.png"), Texture("Ships/AF-SS01/AF-SS01_Normalmap.png"));
		//Material ship2("ship2", 0.5f, 4, Texture("Ships/AF-SS01/AF-SS01_Navy.png"), Texture("Ships/AF-SS01/AF-SS01_Normalmap.png"));
		//Material ship3("ship3", 0.5f, 4, Texture("Ships/AF-SS01/AF-SS01_Black.png"), Texture("Ships/AF-SS01/AF-SS01_Normalmap.png"));

		//Material motherShip("motherShip", 0.5f, 4, Texture("Ships/MotherShip/MotherShip.png"));
		//Material humanShip("human_ship", 1.0f, 10, Texture("Ships/Eric/HumanShip.png"), Texture("Ships/Eric/HumanShip_NORM.png"), Texture("Ships/Eric/HumanShip_DISP.png"));
		//Material alienShip("alien_ship", 5.0f, 4, Texture("Ships/Eric/Alienship.png"), Texture("Ships/Eric/Alienship_NORM.png"), Texture("Ships/Eric/Alienship_DISP.png"));

		Material asteroidA("aster1", 0.5f, 4, Texture("Asteroids/Asteroid_A.png"), Texture("Asteroids/Asteroid_NORM.png"));
		Material asteroidB("aster2", 0.5f, 4, Texture("Asteroids/Asteroid_B.png"), Texture("Asteroids/Asteroid_NORM.png"));
		Material asteroidC("aster3", 0.5f, 4, Texture("Asteroids/Asteroid_C.png"), Texture("Asteroids/Asteroid_NORM.png"));
		Material asteroidD("aster4", 0.5f, 4, Texture("Asteroids/Asteroid_D.png"), Texture("Asteroids/Asteroid_NORM.png"));


		//Material planetA("plan1", 1.0f, 10, Texture("Planets/Planet_A.png"), Texture("Planets/Planet_A_NORM.png"));

		//Material planetA("plan1", 0.5f, 4, Texture("Planets/Planet_A.png"), Texture("Planets/Planet_A_NORM.png"));
		//Material planetB("plan2", 0.5f, 4, Texture("Planets/Planet_B.png"), Texture("Planets/Planet_B_NORM.png"));
		//Material planetC("plan3", 0.5f, 4, Texture("Planets/Planet_C.png"), Texture("Planets/Planet_C_NORM.png"));
		//Material planetD("plan4", 0.5f, 4, Texture("Planets/Planet_D.png"), Texture("Planets/Planet_D_NORM.png"));

		//Material nebulaTex("nebula1", 0.5f, 4, Texture("NebulaeAndGalaxies/Nebula_A.png"));
		//Material GalaxyTex("galaxy1", 0.5f, 4, Texture("Ships/AF-SS01/AF-SS01_White - Copy.png"));

		Audio * BGM = new Audio("music.mp3", AudioType::STREAM, true);

		addToRoot((new GameObject("skybox"))
			->addGameComponent(new SkyboxRenderer("Skybox/drake/drake.tga")));

		//GameObject* pointlight =
		//	(new GameObject("pointLight", PxVec3(0.0f, 1.0f, 0.0f)))
		//	->addGameComponent(new PointLight(PxVec3(1.0f, 0.0f, 0.0f), 0.4f))
		//	;

		//GameObject* plane =
		//	(new GameObject("plane", PxVec3(10.0f, 10.0f, 10.0f)))
		//	->addGameComponent(new MeshRenderer(Mesh("Environment/plane.obj", 100.0f), Material("bricks")))
		//	->addGameComponent(new PlanetSpin())

		//	;

		//addToRoot(plane);

		GameObject * starBoardLight = new GameObject("starBoardPointLight", PxVec3(7.0f, 1.0f, -3.5f));
		starBoardLight->addGameComponent(new PointLight(PxVec3(0.0f, 1.0f, 0.0f), 0.5f));

		GameObject * portLight = new GameObject("portPointLight", PxVec3(-7.0f, 1.0f, -3.5f));
		portLight->addGameComponent(new PointLight(PxVec3(1.0f, 0.0f, 0.0f), 0.5f));

		GameObject * rearLight = new GameObject("rearPointLight", PxVec3(0.0f, 1.0f, -6.0f));
		rearLight->addGameComponent(new PointLight(PxVec3(0.1f, 0.1f, 0.1f), 0.5f));

		GameObject * thrusterLight = new GameObject("thrusdterPointLight", PxVec3(0.0f, 0.0f, -8.0f));
		thrusterLight->addGameComponent(new PointLight(PxVec3(1.0f, 0.75f, 0.0f), 0.5f));

		GameObject* fighterShip =
			(new GameObject("Fighter Ship", PxVec3(0.0f, 0.0f, 0.0f), PxQuat(ToRadians(180.0f), PxVec3(0.0f, 1.0f, 0.0f))))
			->addGameComponent(new MeshRenderer(Mesh("Ships/AF-SS01.obj", 1.0f), Material("ship1")))
			->addGameComponent(new RigidBody(PxVec3(1.0f, 1.0f, 1.0f), PxQuat(PxIdentity), 1.0f, 7.0f, 1.0f, 5.0f))
			->addGameComponent(new FireProjectile("268168__shaun105__laser.wav"))
			->addGameComponent(new PlayerShipMovementController("camera", 50.0f))
			->addChild(starBoardLight)
			->addChild(portLight)
			->addChild(rearLight)
			->addChild(thrusterLight)
			;

		// The human fighter ship and camera
		GameObject* camera =
			(new GameObject("camera",
			*fighterShip->getTransform()->getPosition() - Utility::getForward(*fighterShip->getTransform()->getRotation()) * 30.0f
			+ PxVec3(0.0f, 5.0f, 0.0f)))
			->addGameComponent(new CameraComponent(Utility::initPerspective(ToRadians(75.0f), window.getAspectRatio(), 0.1f, 200000.0f)))
			->addGameComponent(new Listener());
		addToRoot(fighterShip);
		addToRoot(camera);


		// Asteroids
		GameObject * asteroid1 = new GameObject("asteroid1", PxVec3(7.0f, 1.0f, -3.5f));
		asteroid1->addGameComponent(new MeshRenderer(Mesh("Asteroids/Asteroid_A.obj", 10.0f), Material("aster1")));
		asteroid1->addGameComponent(new PlanetSpin());

		GameObject * asteroid2 = new GameObject("asteroid2", PxVec3(-7.0f, 1.0f, -3.5f));
		asteroid2->addGameComponent(new MeshRenderer(Mesh("Asteroids/Asteroid_B.obj", 10.0f), Material("aster2")));
		asteroid2->addGameComponent(new PlanetSpin());

		GameObject * asteroid3 = new GameObject("asteroid3", PxVec3(0.0f, 1.0f, -6.0f));
		asteroid3->addGameComponent(new MeshRenderer(Mesh("Asteroids/Asteroid_C.obj", 10.0f), Material("aster3")));
		asteroid3->addGameComponent(new PlanetSpin());

		GameObject * asteroid4 = new GameObject("asteroid4", PxVec3(0.0f, 0.0f, -8.0f));
		asteroid4->addGameComponent(new MeshRenderer(Mesh("Asteroids/Asteroid_D.obj", 10.0f), Material("aster4")));
		asteroid4->addGameComponent(new PlanetSpin());

		GameObject * asteroid5 = new GameObject("asteroid5", PxVec3(15.0f, 1.0f, -3.5f));
		asteroid5->addGameComponent(new MeshRenderer(Mesh("Asteroids/Asteroid_A.obj", 20.0f), Material("aster1")));
		asteroid5->addGameComponent(new PlanetSpin());

		GameObject * asteroid6 = new GameObject("asteroid6", PxVec3(-9.0f, -7.0f, -5.0f));
		asteroid6->addGameComponent(new MeshRenderer(Mesh("Asteroids/Asteroid_B.obj", 5.0f), Material("aster2")));
		asteroid6->addGameComponent(new PlanetSpin());

		GameObject * asteroid7 = new GameObject("asteroid7", PxVec3(4.0f, 6.0f, -16.0f));
		asteroid7->addGameComponent(new MeshRenderer(Mesh("Asteroids/Asteroid_C.obj", 7.5f), Material("aster3")));
		asteroid7->addGameComponent(new PlanetSpin());

		GameObject * asteroid8 = new GameObject("asteroid8", PxVec3(0.0f, 20.0f, -16.0f));
		asteroid8->addGameComponent(new MeshRenderer(Mesh("Asteroids/Asteroid_D.obj", 25.0f), Material("aster4")));
		asteroid8->addGameComponent(new PlanetSpin());

		addToRoot((new GameObject("AsteroidGroup1", PxVec3(0.0f, 0.0f, 30.0f)))
			->addChild(asteroid1)
			->addChild(asteroid2)
			->addChild(asteroid3)
			->addChild(asteroid4)
			->addChild(asteroid5)
			->addChild(asteroid6)
			->addChild(asteroid7)
			->addChild(asteroid8)
			);

		//// the alien fighter ship
		//addToRoot((new GameObject("enemyFighter", PxVec3(0.0f, -5.0f, 80.0f), PxQuat(0.0f, 0.0f, 0.0f, 1.0f), PxVec3(1.0f)))
		//	->addGameComponent(new MeshRenderer(Mesh("Ships/AlienFighter_FINAL.obj", 0.5f), Material("alien_ship")))
		//	->addGameComponent(BGM)
		//	->addGameComponent(new RigidBody(PxVec3(0.0f, -5.0f, 80.0f), PxQuat(PxIdentity), 1.0f, 10.0f, 6.0f, 24.0f))
		//	->addGameComponent(new EnemyFighterShipAI)
		//	->addGameComponent(new ShipStats)
		//	);

		//// the passenger ship
		//addToRoot((new GameObject("passengerShip", PxVec3(0.0f, 0.0f, 0.0f), PxQuat(0.0f, 0.0f, 0.0f, 1.0f), PxVec3(1.0f)))
		//	->addGameComponent(new MeshRenderer(Mesh("Ships/MotherShip.obj", 50.0f), Material("motherShip")))
		//	->addGameComponent(new RigidBody(PxVec3(0.0f, 0.0f, 0.0f), PxQuat(PxIdentity), 1.0f, 25.0f, 60.0f, 50.0f))
		//	->addGameComponent(new PassengerShipAI)
		//	->addGameComponent(new ShipStats)
		//	);

		//addToRoot((new GameObject("planet", PxVec3(10.0f, 15.0f, 500.0f)))
		//	->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_A.obj", 10.0f), Material("plan1")))
		//	);

		//addToRoot((new GameObject("planet", PxVec3(300.0f, 15.0f, 1000.0f)))
		//	->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_B.obj", 10.0f), Material("plan2")))
		//	);

		//addToRoot((new GameObject("planet", PxVec3(150, 15.0f, 1500.0f)))
		//	->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_C.obj", 10.0f), Material("plan3")))
		//	);

		//addToRoot((new GameObject("planet", PxVec3(0.0f, 15.0f, 2000.0f)))
		//	->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_D.obj", 10.0f), Material("plan4")))
		//	);

		addToRoot((new GameObject("DrLight", PxVec3(0.0f, 0.0f, 0.0f), PxQuat(ToRadians(45.0f), PxVec3(1.0f, 1.0f, 0.0f))))
			->addGameComponent(new DirectionalLight(PxVec3(1.0f, 1.0f, 1.0f), 0.5f, 8)));

		//BGM->play(true);
	}
};

