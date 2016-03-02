#pragma once
#include <MegaEngine.h>
#include <iostream>

#include "FreeLook.h"
#include "FreeMove.h"
#include "PlanetSpin.h"
#include "FireProjectile.h"
#include "EnemyFighterShipAI.h"
#include <PhysX/PxPhysicsAPI.h>
using namespace physx;

class TestScene : public Scene
{
public:
	TestScene() : Scene("Hello World") { }
	~TestScene() { }

	virtual void init(const Viewport& window) override
	{
		Material bricks("bricks", 0.5f, 4, Texture("bricks.jpg"), Texture("bricks_normal.jpg"), Texture("bricks_disp.png"));

		Material ship1("ship1", 0.5f, 4, Texture("Ships/AF-SS01/AF-SS01_White.png"), Texture("Ships/AF-SS01/AF-SS01_Normalmap.png"));
		//Material ship2("ship2", 0.5f, 4, Texture("Ships/AF-SS01/AF-SS01_Navy.png"), Texture("Ships/AF-SS01/AF-SS01_Normalmap.png"));
		//Material ship3("ship3", 0.5f, 4, Texture("Ships/AF-SS01/AF-SS01_Black.png"), Texture("Ships/AF-SS01/AF-SS01_Normalmap.png"));

		Material motherShip("motherShip", 0.5f, 4, Texture("Ships/MotherShip/MotherShip.png"));
		Material humanShip("human_ship", 1.0f, 10, Texture("Ships/Eric/HumanShip.png"), Texture("Ships/Eric/HumanShip_NORM.png"), Texture("Ships/Eric/HumanShip_DISP.png"));
		Material alienShip("alien_ship", 5.0f, 4, Texture("Ships/Eric/Alienship.png"), Texture("Ships/Eric/Alienship_NORM.png"), Texture("Ships/Eric/Alienship_DISP.png"));

		//Material asteroidA("aster1", 0.5f, 4, Texture("Asteroids/Asteroid_A.png"), Texture("Asteroids/Asteroid_NORM.png"));
		//Material asteroidB("aster2", 0.5f, 4, Texture("Asteroids/Asteroid_B.png"), Texture("Asteroids/Asteroid_NORM.png"));
		//Material asteroidC("aster3", 0.5f, 4, Texture("Asteroids/Asteroid_C.png"), Texture("Asteroids/Asteroid_NORM.png"));
		//Material asteroidD("aster4", 0.5f, 4, Texture("Asteroids/Asteroid_D.png"), Texture("Asteroids/Asteroid_NORM.png"));
		//Material planetA("plan1", 1.0f, 10, Texture("Planets/Planet_A.png"), Texture("Planets/Planet_A_NORM.png"));

		Material planetA("plan1", 0.5f, 4, Texture("Planets/Planet_A.png"), Texture("Planets/Planet_A_NORM.png"));
		Material planetB("plan2", 0.5f, 4, Texture("Planets/Planet_B.png"), Texture("Planets/Planet_B_NORM.png"));
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

		GameObject* fighterShip =
			(new GameObject("Fighter Ship", PxVec3(0.0f, 0.0f, 0.0f), PxQuat(ToRadians(180.0f), PxVec3(0.0f, 1.0f, 0.0f))))
			->addGameComponent(new MeshRenderer(Mesh("Ships/AF-SS01.obj", 1.0f), Material("ship1")))
			->addGameComponent(new RigidBody(PxVec3(1.0f, 1.0f, 1.0f), PxQuat(PxIdentity), 1.0f, 2.0f, 2.0f, 8.0f))
			->addGameComponent(new FireProjectile("268168__shaun105__laser.wav"))
			->addGameComponent(new PlayerShipMovementController("camera", 10.0f))
			->addGameComponent(new ShipStats)

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

		// the alien fighter ship
		addToRoot((new GameObject("enemyFighter", PxVec3(0.0f, -5.0f, 80.0f), PxQuat(0.0f, 0.0f, 0.0f, 1.0f), PxVec3(1.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Ships/AlienFighter_FINAL.obj", 0.5f), Material("alien_ship")))
			->addGameComponent(BGM)
			->addGameComponent(new RigidBody(PxVec3(0.0f, -5.0f, 80.0f), PxQuat(PxIdentity), 1.0f, 4.0f, 4.0f, 16.0f))
			->addGameComponent(new EnemyFighterShipAI)
			->addGameComponent(new ShipStats)
			);

		addToRoot((new GameObject("planet1", PxVec3(10.0f, 15.0f, 20000.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_A.obj", 400.0f), Material("plan1")))
			);

		addToRoot((new GameObject("DrLight", PxVec3(0.0f, 0.0f, 0.0f), PxQuat(ToRadians(45.0f), PxVec3(1.0f, 1.0f, 0.0f))))
			->addGameComponent(new DirectionalLight(PxVec3(1.0f, 1.0f, 1.0f), 0.5f, 8)));

		//BGM->play(true);
	}
};

