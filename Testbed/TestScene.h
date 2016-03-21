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

#include <PhysX/PxPhysicsAPI.h>
using namespace physx;

class TestScene : public Scene
{
public:
	TestScene() : Scene("Hello World") { }
	~TestScene() { }

	virtual void init(const Viewport& window) override
	{
		//getPhysicsWorld().init(glm::vec3(0, 0, 0), 100);
		Material bricks("bricks", 0.5f, 4, Texture("bricks.jpg"), Texture("bricks_normal.jpg"), Texture("bricks_disp.png"), 0.03f, -0.5f);
		Material humanShip("human_ship", 0.5f, 4, Texture("Human-Ship-UVWs.png"));
		Material alienShip("alien_ship", 0.5f, 4, Texture("AlienshipUVWs.png"));
		Material skySphereTex("skySphereTexture", 0.5f, 4, Texture("night_sky.png"));
		Material earthTex("earthTexture", 0.5f, 4, Texture("earth.png"));
		Material sunTex("sunTexture", 0.5f, 4, Texture("sun.jpg"));
		Material moonTex("moonTexture", 0.5f, 4, Texture("moon.jpg"));
		Material fireTex("fireTexture", 0.5f, 4, Texture("fireTexture1.png"));
		Material particleMat("particleMat", 0.5f, 4.0f, Texture("colourTest.png"));

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

		GameObject* camera =
			(new GameObject("camera",
			*fighterShip->getTransform()->getPosition() - Utility::getForward(*fighterShip->getTransform()->getRotation()) * 30.0f
			+ PxVec3(0.0f, 5.0f, 0.0f)))
			->addGameComponent(new CameraComponent(ToRadians(75.0f), window.getAspectRatio(), 0.1f, 200000.0f))
			->addGameComponent(new Listener());
		addToRoot(fighterShip);
		addToRoot(camera);

		/*addToRoot((new GameObject("earth", PxVec3(-1000.0f, 0.0f, 0.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_A.obj", 100.0f), Material("earth")))
			);*/

		addToRoot((new GameObject("earth", PxVec3(0, 0.0f, -1000.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_A.obj", 100.0f), Material("earth")))
			);

		/*addToRoot((new GameObject("mars", PxVec3(7500.0f, 0.0f, 7500.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_A.obj", 35.0f), Material("mars")))
			);*/

		addToRoot((new GameObject("jupiter", PxVec3(0.0f, 0.0f, 10000.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_A.obj", 250.0f), Material("jupiter")))
			);


		addToRoot((new GameObject("moon", PxVec3(1000.0f, 0.0f, 1000.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_A.obj", 32.0f), Material("moon")))
			);

		/*addToRoot((new GameObject("sun", PxVec3(20000.0f, 5000.0f, 20000.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_A.obj", 600.0f), Material("sun")))
			);*/


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

		addToRoot((new GameObject("particles"))
			->addGameComponent(new ParticleSystem(Material("particleMat"))));
	}
};

