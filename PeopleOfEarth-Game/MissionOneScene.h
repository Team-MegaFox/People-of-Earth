#pragma once
#include <MegaEngine.h>

#include "FreeLook.h"
#include "FreeMove.h"
#include "ShowPauseComp.h"
#include "FireProjectile.h"
#include "EnemyFighterShipAI.h"
#include "PassengerShipAI.h"
#include <PhysX/PxPhysicsAPI.h>
using namespace physx;

class MissionOneScene : public Scene
{
public:
	MissionOneScene() : Scene("Misson 1") { }
	~MissionOneScene() { }

	virtual void init(const Viewport& window) override
	{
		//Material humanShip("human_ship", 1.0f, 10, Texture("Ships/Eric/HumanShip.png"));
		Material ship1("ship1", 0.5f, 4, Texture("Ships/AF-SS01/AF-SS01_White.png"), Texture("Ships/AF-SS01/AF-SS01_Normalmap.png"));
		Material alienShip("alien_ship", 5.0f, 4, Texture("Ships/Eric/Alienship.png"), Texture("Ships/Eric/Alienship_NORM.png"), Texture("Ships/Eric/Alienship_DISP.png"));

		addToRoot((new GameObject("Skybox"))
			->addGameComponent(new SkyboxRenderer("Skybox/drake/drake.tga")));

		//addToRoot((new GameObject("Directional Light"))
		//	->addGameComponent(new DirectionalLight(PxVec3(1.0f, 1.0f, 1.0f), 0.2f, 7, 8.0f, 1.0f)));

		GameObject* fighterShip =
			(new GameObject("Fighter Ship", PxVec3(0.0f, 0.0f, 0.0f), PxQuat(ToRadians(180.0f), PxVec3(0.0f, 1.0f, 0.0f))))
			->addGameComponent(new MeshRenderer(Mesh("Ships/AF-SS01.obj", 1.0f), Material("ship1")))
			->addGameComponent(new RigidBody(PxVec3(1.0f, 1.0f, 1.0f), PxQuat(PxIdentity), 1.0f, 7.0f, 1.0f, 5.0f))
			->addGameComponent(new FireProjectile("268168__shaun105__laser.wav"))
			->addGameComponent(new PlayerShipMovementController("camera", 50.0f))
			->addGameComponent(new ShipStats);

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
			->addGameComponent(new RigidBody(PxVec3(0.0f, -5.0f, 80.0f), PxQuat(PxIdentity), 1.0f, 10.0f, 6.0f, 24.0f))
			->addGameComponent(new EnemyFighterShipAI)
			->addGameComponent(new ShipStats)
			);

	}

private:

};
