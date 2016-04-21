#pragma once
#include <MegaEngine.h>
#include <iostream>

#include "FreeLook.h"
#include "FreeMove.h"
#include "PlanetSpin.h"
#include "FireProjectile.h"
#include "EnemyFighterShipAI.h"
#include "PassengerShipAI.h"
#include "AsteroidField.h"
#include "GUIOnCamera.h"

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

	/*	Material asteroidA("aster1", 0.5f, 4, Texture("Asteroids/Asteroid_A.png"), Texture("Asteroids/Asteroid_NORM.png"));
		Material asteroidB("aster2", 0.5f, 4, Texture("Asteroids/Asteroid_B.png"), Texture("Asteroids/Asteroid_NORM.png"));
		Material asteroidC("aster3", 0.5f, 4, Texture("Asteroids/Asteroid_C.png"), Texture("Asteroids/Asteroid_NORM.png"));*/
		//Material asteroidD("aster4", 0.5f, 4, Texture("Asteroids/Asteroid_D.png"), Texture("Asteroids/Asteroid_NORM.png"));


		Material earth("earth", 1.0f, 10, Texture("Planets/earth.png"));
		Material mars("mars", 1.0f, 10, Texture("Planets/mars.jpg"), Texture("Planets/mars_NORM.jpg"));
		Material jupiter("jupiter", 1.0f, 10, Texture("Planets/jupiter.jpg"), Texture("Planets/jupiter_NORM.jpg"));
		Material sun("sun", 10.0f, 100, Texture("Planets/sun.jpg"));
		Material moon("moon", 1.0f, 10, Texture("Planets/moon.jpg"));

		Material fireTex("fireTexture", 0.5f, 4, Texture("fireTexture1.png"));
		Material particleMatA("particleMatA", 0.5f, 4.0f, Texture("defaultParticleTexture.png"));
		Material particleMatB("particleMatB", 0.5f, 4.0f, Texture("fireTexture.png"));
		Material particleMatC("particleMatC", 0.5f, 4.0f, Texture("fireTexture.png"));
		Material particleMatD("particleMatD", 0.5f, 4.0f, Texture("star.png"));

		Material alienShip("alien_ship", 5.0f, 4,
			Texture("Ships/Alien/astra_elements2_c.png"),
			Texture("Ships/Alien/astraBattleship_Normals.png"),
			Texture("Ships/Alien/astra_elements2_i.png"));

		Material enemyMotherShip("enemyMother", 0.5f, 4,
			Texture("Ships/Alien/astra_elements1_c.png"),
			Texture("Ships/Alien/astraHeavyCruiser_Normals.png"),
			Texture("Ships/Alien/astra_elements1_i.png"));

		//Material planetA("plan1", 0.5f, 4, Texture("Planets/Planet_A.png"), Texture("Planets/Planet_A_NORM.png"));
		//Material planetB("plan2", 0.5f, 4, Texture("Planets/Planet_B.png"), Texture("Planets/Planet_B_NORM.png"));
		//Material planetC("plan3", 0.5f, 4, Texture("Planets/Planet_C.png"), Texture("Planets/Planet_C_NORM.png"));
		//Material planetD("plan4", 0.5f, 4, Texture("Planets/Planet_D.png"), Texture("Planets/Planet_D_NORM.png"));

		//Material nebulaTex("nebula1", 0.5f, 4, Texture("NebulaeAndGalaxies/Nebula_A.png"));
		//Material GalaxyTex("galaxy1", 0.5f, 4, Texture("Ships/AF-SS01/AF-SS01_White - Copy.png"));

		AudioSource * BGM = new AudioSource("music.mp3", AudioType::STREAM);

		addToRoot((new GameObject("skybox"))
			->addGameComponent(new SkyboxRenderer("Skybox/drake/drake.tga")));
			//->addGameComponent(new SkyboxRenderer("Skybox/sky/sky.jpg")));

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

		//GameObject * starBoardLight = new GameObject("starBoardPointLight", PxVec3(7.0f, 1.0f, -3.5f));
		//starBoardLight->addGameComponent(new PointLight(PxVec3(0.0f, 1.0f, 0.0f), 0.5f));

		//GameObject * portLight = new GameObject("portPointLight", PxVec3(-7.0f, 1.0f, -3.5f));
		//portLight->addGameComponent(new PointLight(PxVec3(1.0f, 0.0f, 0.0f), 0.5f));

		//GameObject * rearLight = new GameObject("rearPointLight", PxVec3(0.0f, 1.0f, -6.0f));
		//rearLight->addGameComponent(new PointLight(PxVec3(0.1f, 0.1f, 0.1f), 0.5f));

		//GameObject * thrusterLight = new GameObject("thrusdterPointLight", PxVec3(0.0f, 0.0f, -8.0f));
		//thrusterLight->addGameComponent(new PointLight(PxVec3(1.0f, 0.75f, 0.0f), 0.5f));

		//GameObject* fighterShip =
		//	(new GameObject("Fighter Ship", PxVec3(0.0f, 0.0f, 0.0f), PxQuat(ToRadians(180.0f), PxVec3(0.0f, 1.0f, 0.0f))))
		//	->addGameComponent(new MeshRenderer(Mesh("Ships/AF-SS01.obj", 1.0f), Material("ship1")))
		//	->addGameComponent(new RigidBody(PxVec3(1.0f, 1.0f, 1.0f), PxQuat(PxIdentity), 1.0f, 7.0f, 1.0f, 5.0f))
		//	->addGameComponent(new FireProjectile("268168__shaun105__laser.wav"))
		//	->addGameComponent(new PlayerShipMovementController("camera", 50.0f))
		//	->addChild(starBoardLight)
		//	->addChild(portLight)
		//	->addChild(rearLight)
		//	->addChild(thrusterLight)
		//	;
		//addToRoot(fighterShip);

		RigidBody* fighterRB = new RigidBody(PxVec3(1.0f, 1.0f, 1.0f), PxQuat(PxIdentity), 1.0f, 7.0f, 1.0f, 5.0f);
		//fighterRB->setDebugDraw(true);
		GameObject* fighterShip =
			(new GameObject("player", PxVec3(0.0f, 0.0f, 0.0f), PxQuat(ToRadians(180.0f), PxVec3(0.0f, 1.0f, 0.0f))))
			//->addGameComponent(new MeshRenderer(Mesh("Ships/AF-SS01.obj", 1.0f), Material("ship1")))
			->addGameComponent(fighterRB)
			->addGameComponent(new PlayerShipMovementController("camera", 50.0f));
		addToRoot(fighterShip);

		// The human fighter ship and camera
		GameObject* camera =
			//(new GameObject("camera", PxVec3(0, 0, 0)))
			(new GameObject("camera",
			*fighterShip->getTransform()->getPosition() - Utility::getForward(*fighterShip->getTransform()->getRotation()) * 30.0f + PxVec3(0.0f, 5.0f, 0.0f)))
			//->addGameComponent(new FreeMove)
			//->addGameComponent(new FreeLook(window.getCenter()))
			->addGameComponent(new CameraComponent(ToRadians(75.0f), window.getAspectRatio(), 0.1f, 200000.0f));
			//->addGameComponent(new Listener());
		addToRoot(camera);

		/*addToRoot((new GameObject("earth", PxVec3(-1000.0f, 0.0f, 0.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_A.obj", 100.0f), Material("earth")))
			);*/

		/*addToRoot((new GameObject("earth", PxVec3(0, 0.0f, -1000.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_A.obj", 100.0f), Material("earth")))
			);*/

		/*addToRoot((new GameObject("mars", PxVec3(7500.0f, 0.0f, 7500.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_A.obj", 35.0f), Material("mars")))
			);*/

		/*addToRoot((new GameObject("jupiter", PxVec3(0.0f, 0.0f, 10000.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_A.obj", 250.0f), Material("jupiter")))
			);*/


		addToRoot((new GameObject("moon", PxVec3(1000.0f, 0.0f, 1000.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_A.obj", 32.0f), Material("moon")))
			);

		/*addToRoot((new GameObject("sun", PxVec3(20000.0f, 5000.0f, 20000.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_A.obj", 600.0f), Material("sun")))
			);*/


		//// the alien fighter ship
		//addToRoot((new GameObject("enemyFighter_", PxVec3(0.0f, -5.0f, 80.0f), PxQuat(0.0f, 0.0f, 0.0f, 1.0f), PxVec3(1.0f)))
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

		//RigidBody* rigidBody = new RigidBody(PxVec3(0.0f, -5.0f, 80.0f), PxQuat(PxIdentity), 1.0f, 5.0f, 3.0f, 6.0f);
		////rigidBody->setDebugDraw(true);
		//// the alien fighter ship
		//addToRoot((new GameObject("enemyFighter_", PxVec3(0.0f, -5.0f, 80.0f), PxQuat(0.0f, 0.0f, 0.0f, 1.0f), PxVec3(1.0f)))
		//	->addGameComponent(new MeshRenderer(Mesh("Ships/enemyBattleShip.obj", 10.0f), Material("alien_ship")))
		//	->addGameComponent(rigidBody)
		//	);

		RigidBody* motherShipRigidBody = new RigidBody(PxVec3(0.0f, 0.0f, 100.0f), PxQuat(PxIdentity), 1.0f, 600.0f, 250.0f, 750.0f);
		//motherShipRigidBody->setDebugDraw(true);
		addToRoot((new GameObject("EnemyMother", PxVec3(0.0f, 0.0f, 0.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Ships/enemy_HeavyCruiser.obj", 100.0f), Material("enemyMother")))
			->addGameComponent(motherShipRigidBody)
			);

		addToRoot((new GameObject("DrLight", PxVec3(0.0f, 0.0f, 0.0f), PxQuat(ToRadians(180.0f), PxVec3(0.0f, 1.0f, 0.0f))))
			->addGameComponent(new DirectionalLight(PxVec3(1.0f, 1.0f, 1.0f), 0.5f, 8)));

		//addToRoot((new GameObject("particleMatA", PxVec3(0.0f, 0.0f, 10.0f)))
		//	->addGameComponent(new ParticleSystem(Material("particleMatA"), 10.0f, ToRadians(45.0f), CONE, 5.0f, 2.0f, 1000.0f)));
		//addToRoot((new GameObject("particlesB", PxVec3(10.0f, 0.0f, 0.0f)))
		//	->addGameComponent(new ParticleSystem(Material("particleMatB"), EXPLOSION, 10.0f)));
		//addToRoot((new GameObject("particlesC", PxVec3(-10.0f, 0.0f, 0.0f)))
		//	->addGameComponent(new ParticleSystem(Material("particleMatC"), EXPLOSION)));

		//addToRoot((new GameObject("particlesD", PxVec3(0.0f, 0.0f, -10.0f)))
		//	->addGameComponent(new ParticleSystem(Material("particleMatD"), AMBIENT)));

		//addToRoot((new GameObject("plane", PxVec3(0.0f, -10.0f, 0.0f), PxIdentity, PxVec3(100.0f)))
		//	->addGameComponent(new MeshRenderer(Mesh("Environment/plane.obj"), Material("particleMatA"))));

	}
};

