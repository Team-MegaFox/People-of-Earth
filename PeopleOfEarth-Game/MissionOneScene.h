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
#include "RogueAsteroid.h"
#include "CrossHair.h"
#include <PhysX/PxPhysicsAPI.h>
#include "QuatRotator.h"
#include "MotherShipAI.h"
#include "DialogueBox.h"
#include "InGameMusic.h"
using namespace physx;

// TODO: Sounds like the one where we're replenishing at every message
// TODO: Collision Logic for ships and space bodies
// TODO: Missile GUI
// TODO: Replenish Missile if they are low
// TODO: Merge Particles into the develop branch
// TODO: Create a Game Over Scene

class MissionOneScene : public Scene
{
public:
	MissionOneScene() : Scene("Mission 1") { }
	~MissionOneScene() { }

	virtual void init(const Viewport& window) override
	{
		Material ship1("ship1", 0.5f, 4, Texture("Ships/AF-SS01/AF-SS01_White.png"), Texture("Ships/AF-SS01/AF-SS01_Normalmap.png"));
		Material alienShip("alien_ship", 5.0f, 4,
			Texture("Ships/Alien/astra_elements2_c.png"),
			Texture("Ships/Alien/astraBattleship_Normals.png"),
			Texture("Ships/Alien/astra_elements2_i.png"));

		Material passengerShip("passengerShip", 0.5f, 4, Texture("Ships/MotherShip/MotherShip.png"));
		Material enemyMotherShip("enemyMother", 0.5f, 4, 
			Texture("Ships/Alien/astra_elements1_c.png"),
			Texture("Ships/Alien/astraHeavyCruiser_Normals.png"),
			Texture("Ships/Alien/astra_elements1_i.png"));

		Material earth("earth", 1.0f, 10, Texture("Planets/earth.png"));
		Material mars("mars", 1.0f, 10, Texture("Planets/mars.jpg"));
		Material jupiter("jupiter", 1.0f, 10, Texture("Planets/jupiter.jpg"));
		Material sun("sun", 100.0f, 1000, Texture("Planets/sun.jpg"));
		Material moon("moon", 1.0f, 10, Texture("Planets/moon.jpg"));

		Material asteroid("asteroid", 1.0f, 1.0f, Texture("Asteroids/AM1.jpg"));


		//addToRoot((new GameObject("BloomObject", PxVec3(0.0f, 0.0f, 0.0f)))
		//	->addGameComponent(new BloomObjectRenderer(Mesh("Asteroids/Asteroid_D.obj", 10.0f), Texture("Planets/sun.jpg"))));


		addToRoot((new GameObject("Skybox"))
			->addGameComponent(new SkyboxRenderer("Skybox/Starfield/starfield.tga")));
			//->addGameComponent(new SkyboxRenderer("Skybox/sky/sky.jpg")));

		GameObject * starBoardLight_Fighter = new GameObject("starBoardLight_Fighter", PxVec3(7.0f, 1.0f, -3.5f));
		starBoardLight_Fighter->addGameComponent(new PointLight(PxVec3(0.0f, 1.0f, 0.0f), 0.5f));

		GameObject * portLight_Fighter = new GameObject("portLight_Fighter", PxVec3(-7.0f, 1.0f, -3.5f));
		portLight_Fighter->addGameComponent(new PointLight(PxVec3(1.0f, 0.0f, 0.0f), 0.5f));

		GameObject * rearLight_Fighter = new GameObject("rearLight_Fighter", PxVec3(0.0f, 1.0f, -6.0f));
		rearLight_Fighter->addGameComponent(new PointLight(PxVec3(0.1f, 0.1f, 0.1f), 0.5f));

		GameObject * thrusterLight_Fighter = new GameObject("thrusterLight_Fighter", PxVec3(0.0f, 0.0f, -8.0f));
		thrusterLight_Fighter->addGameComponent(new PointLight(PxVec3(1.0f, 0.75f, 0.0f), 0.5f));

		GameObject * spotLight_Fighter = 
			new GameObject("spotLight_Fighter", PxVec3(0.0f, 0.0f, 7.5f), PxQuat(ToRadians(1.0f), PxVec3(0.0f, 1.0f, 0.0f)));
		spotLight_Fighter->addGameComponent(new SpotLight(PxVec3(1.0f), 150.0f, Attenuation(1.0f, 1.0f, 0.0f)));

		GameObject* fighterShip =
			(new GameObject("player", PxVec3(0.0f, 0.0f, 0.0f), PxQuat(ToRadians(180.0f), PxVec3(0.0f, 1.0f, 0.0f))))
			->addGameComponent(new MeshRenderer(Mesh("Ships/AF-SS01.obj", 1.0f), Material("ship1")))
			->addGameComponent(new RigidBody(PxVec3(1.0f, 1.0f, 1.0f), PxQuat(PxIdentity), 1.0f, 7.0f, 1.0f, 5.0f))
			->addGameComponent(new FireProjectile)
			->addGameComponent(new PlayerShipMovementController("camera", 50.0f))
			//->addGameComponent(new InGameMusic)
			->addGameComponent(new ShipStats)
			->addGameComponent(new UpdateGUI)
			->addChild(starBoardLight_Fighter)
			->addChild(portLight_Fighter)
			->addChild(rearLight_Fighter)
			->addChild(thrusterLight_Fighter)
			->addChild(spotLight_Fighter)
			->addChild((new GameObject("CrossHair"))
			->addGameComponent(new CrossHair(100.0f)));
		addToRoot(fighterShip);

		// The human fighter ship and camera
		GameObject* camera =
			(new GameObject("camera",
			*fighterShip->getTransform()->getPosition() - Utility::getForward(*fighterShip->getTransform()->getRotation()) * 30.0f
			+ PxVec3(0.0f, 5.0f, 0.0f)))
			->addGameComponent(new CameraComponent(ToRadians(75.0f), window.getAspectRatio(), 0.1f, 200000.0f))
			->addGameComponent(new AudioListener);
		addToRoot(camera);


		addToRoot((new GameObject("DirectionalLight1", PxVec3(0.0f, 0.0f, 0.0f), PxQuat(ToRadians(45.0f), PxVec3(0.0f, 1.0f, 0.0f).getNormalized())))
			->addGameComponent(new DirectionalLight(PxVec3(1.0f, 0.65f, 0.0f), 0.6f, 8)));

		addPassengerShip();		

		addToRoot((new GameObject("Asteroid", PxVec3(0.0f, 0.0f, 0.0f), PxQuat(ToRadians(180.0f), PxVec3(0.0f, 1.0f, 0.0f).getNormalized())))
			->addGameComponent(new MeshRenderer(Mesh("Asteroids/Asteroid_C.obj", 50.0f), Material("asteroid")))
			->addGameComponent(new RigidBody(PxVec3(0), PxQuat(0.0f, 0.0f, 0.0f, 1.0f), 1.0f, 1.0f))
			->addGameComponent(new RogueAsteroid(10.0f, 0.005f)));

		addToRoot((new GameObject("EnemyMother", PxVec3(-1500.0f, 0.0f, 15000.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Ships/enemy_HeavyCruiser.obj", 100.0f), Material("enemyMother")))
			->addGameComponent(new RigidBody(PxVec3(-1500.0f, 0.0f, 15000.0f), PxQuat(PxIdentity), 1.0f, 50.0f, 40.0f, 275.0f))
			->addGameComponent(new MotherShipAI)
			->addGameComponent(new ShipStats)
			);

		//addToRoot((new GameObject("GameOver"))
		//	->addGUIComponent(new GUIButton(PxVec4(0.35f, 0.5f, 0.3f, 0.05f), PxVec4(0.0f), "Return To Mission Select",
		//	std::bind(&MissionOneScene::onRetryClick, this, std::placeholders::_1)))
		//	);

		addArea1OfMission1();

		addArea2OfMission1();

		addGUI();

		addAudio();
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

		// Health Bar Label
		addToRoot(((new GameObject("Health Bar Label")))
			->addGUIComponent(new GUIImage(PxVec4(0.005f, 0.04f, 0.04f, 0.04f), PxVec4(0.0f), "Images/HealthMarker.png")));

		addToRoot((new GameObject("Energy Bar Background"))
			->addGUIComponent(new GUIImage(PxVec4(barXPos, 0.09f, barWidth, barHeight), PxVec4(0.0f), "Images/BarBackground.png", 287.0f / 20.0f))
			->addChild((new GameObject("Energy Bar"))
			->addGUIComponent(new GUIImage(PxVec4(0.05f, 0.18f, 12.7f, 0.62f), PxVec4(0.0f), "Images/energybar.png"))));

		// Energy Bar Label
		addToRoot(((new GameObject("Energy Bar Label")))
			->addGUIComponent(new GUIImage(PxVec4(0.005f, 0.08f, 0.04f, 0.04f), PxVec4(0.0f), "Images/EnergyMarker.png")));

		addToRoot((new GameObject("Fuel Bar Background"))
			->addGUIComponent(new GUIImage(PxVec4(barXPos, 0.13f, barWidth, barHeight), PxVec4(0.0f), "Images/BarBackground.png", 287.0f / 20.0f))
			->addChild((new GameObject("Fuel Bar"))
			->addGUIComponent(new GUIImage(PxVec4(0.05f, 0.18f, 12.7f, 0.62f), PxVec4(0.0f), "Images/fuelbar.png"))));
	
		// Fuel Bar Label
		addToRoot(((new GameObject("Fuel Bar Label")))
			->addGUIComponent(new GUIImage(PxVec4(0.005f, 0.12f, 0.04f, 0.04f), PxVec4(0.0f), "Images/FuelMarker.png")));
		
		addToRoot((new GameObject("MiniMap"))
			->addGUIComponent(new GUIImage(PxVec4(0.0f, 0.70f, 0.3f, 0.3f), PxVec4(0.0f), "Images/minimap_graphics/GUI_MiniMap.png"))
			->addGameComponent(new MiniMap(PxVec2(0.15f, 0.15f), 3000.0f))
			);

		// DialogueBox
		addToRoot((new GameObject("DialogueBox"))
			->addGUIComponent(new GUILabel(PxVec4(0.75f, 0.03f, 0.25f, 0.125f), PxVec4(PxZero), ""))
			->addGameComponent(new DialogueBox));

		DialogueBox * welcomeLabel = new DialogueBox();
		welcomeLabel->sendLastingMessage("[colour='FFFFFFFF'][font='SaucerBB-16'][padding='l:5 t:0 r:5 b:0']Hello! Welcome to[colour='FF00FF00']The People of Earth Demo!\n[colour='FFFFFFFF']We hope you enjoy your time with us.\n[colour='FFFFAF00']Feel free to ask us any questions you have.",
			Importance::LOW, false);
		// Welcome label
		addToRoot((new GameObject("WelcomeLabel"))
			->addGUIComponent(new GUILabel(PxVec4(0.05f, 0.85f, 0.90f, 0.125f),
			PxVec4(PxZero), ""))
			->addGameComponent(welcomeLabel));

		/*addToRoot((new GameObject("MissileGUI"))
			->addGUIComponent(new GUIImage(PxVec4(0.0f, 0.70f, 0.3f, 0.3f), PxVec4(0.0f), "Images/minimap_graphics/GUI_MiniMap.png"))

			);*/
	}

	void addPassengerShip()
	{
		// PassengerShip Lights

		// Tower North Bottom East
		GameObject * spotLight1_Passenger =
			new GameObject("spotLight1_Passenger",
			PxVec3(17.0f, 0.0f, -50.0f),
			PxQuat(ToRadians(45.0f), PxVec3(0.0f, 1.0f, 0.0f)));
		spotLight1_Passenger->addGameComponent(
			new SpotLight(
			PxVec3(1.0f), 100.0f, Attenuation(1.0f, 1.0f, 0.0f)));
		spotLight1_Passenger->addGameComponent(new PointLight(
			PxVec3(1.0f), 100.0f));

		// Tower North Bottom West
		GameObject * spotLight2_Passenger =
			new GameObject("spotLight2_Passenger",
			PxVec3(-17.0f, 0.0f, -50.0f),
			PxQuat(ToRadians(-45.0f), PxVec3(0.0f, 1.0f, 0.0f)));
		spotLight2_Passenger->addGameComponent(
			new SpotLight(
			PxVec3(1.0f), 100.0f, Attenuation(1.0f, 1.0f, 0.0f)));
		spotLight2_Passenger->addGameComponent(new PointLight(
			PxVec3(1.0f), 100.0f));

		// Tower South Bottom West
		GameObject * spotLight3_Passenger =
			new GameObject("spotLight3_Passenger",
			PxVec3(-17.0f, 0.0f, -140.0f),
			PxQuat(ToRadians(-135.0f), PxVec3(0.0f, 1.0f, 0.0f)));
		spotLight3_Passenger->addGameComponent(
			new SpotLight(
			PxVec3(1.0f), 100.0f, Attenuation(1.0f, 1.0f, 0.0f)));
		spotLight3_Passenger->addGameComponent(new PointLight(
			PxVec3(1.0f), 100.0f));

		// Tower South Bottom East
		GameObject * spotLight4_Passenger =
			new GameObject("spotLight4_Passenger",
			PxVec3(17.0f, 0.0f, -140.0f),
			PxQuat(ToRadians(135.0f), PxVec3(0.0f, 1.0f, 0.0f)));
		spotLight4_Passenger->addGameComponent(
			new SpotLight(
			PxVec3(1.0f), 100.0f, Attenuation(1.0f, 1.0f, 0.0f)));
		spotLight4_Passenger->addGameComponent(new PointLight(
			PxVec3(1.0f), 100.0f));

		// Tower North Top West
		GameObject * spotLight5_Passenger =
			new GameObject("spotLight5_Passenger",
			PxVec3(17.0f, 45.0f, -62.0f),
			PxQuat(ToRadians(45.0f), PxVec3(0.0f, 1.0f, 0.0f)));
		spotLight5_Passenger->addGameComponent(
			new SpotLight(
			PxVec3(1.0f), 100.0f, Attenuation(1.0f, 1.0f, 0.0f)));
		spotLight5_Passenger->addGameComponent(new PointLight(
			PxVec3(1.0f), 100.0f));

		// Tower North Top East
		GameObject * spotLight6_Passenger =
			new GameObject("spotLight6_Passenger",
			PxVec3(-17.0f, 45.0f, -62.0f),
			PxQuat(ToRadians(-45.0f), PxVec3(0.0f, 1.0f, 0.0f)));
		spotLight6_Passenger->addGameComponent(
			new SpotLight(
			PxVec3(1.0f), 100.0f, Attenuation(1.0f, 1.0f, 0.0f)));
		spotLight6_Passenger->addGameComponent(new PointLight(
			PxVec3(1.0f), 100.0f));

		// Off North of Ship to the West 
		GameObject * spotLight7_Passenger =
			new GameObject("spotLight7_Passenger",
			PxVec3(100.0f, 0.0f, 370.0f),
			PxQuat(ToRadians(-135.0f), PxVec3(0.0f, 1.0f, 0.0f)));
		spotLight7_Passenger->addGameComponent(
			new SpotLight(
			PxVec3(1.0f), 150.0f, Attenuation(1.0f, 1.0f, 0.0f)));

		// Off North of Ship to the East
		GameObject * spotLight8_Passenger =
			new GameObject("spotLight8_Passenger",
			PxVec3(-100.0f, 0.0f, 370.0f),
			PxQuat(ToRadians(135.0f), PxVec3(0.0f, 1.0f, 0.0f)));
		spotLight8_Passenger->addGameComponent(
			new SpotLight(
			PxVec3(1.0f), 100.0f, Attenuation(1.0f, 1.0f, 0.0f)));

		// Thruster South Bottom East
		PxVec3 thruster1(53.0f, -40.0f, -84.0f);
		GameObject * passenger_Thruster1 =
			new GameObject("passenger_Thruster1",
			thruster1,
			PxQuat(ToRadians(-45.0f), PxVec3(0.0f, 1.0f, 0.0f)));
		passenger_Thruster1->addGameComponent(new QuatRotator(thruster1));
		passenger_Thruster1->addGameComponent(
			new PointLight(
			PxVec3(1.0f, 0.5f, 0.0f), 150.0f));
		passenger_Thruster1->addGameComponent(
			new SpotLight(
			PxVec3(1.0f, 0.5f, 0.0f), 150.0f));

		// Thruster South Bottom West
		PxVec3 thruster2(-53.0f, -40.0f, -84.0f);
		GameObject * passenger_Thruster2 =
			new GameObject("passenger_Thruster2",
			thruster2,
			PxQuat(ToRadians(-45.0f), PxVec3(0.0f, 1.0f, 0.0f)));
		passenger_Thruster2->addGameComponent(new QuatRotator(thruster2));
		passenger_Thruster2->addGameComponent(
			new PointLight(
			PxVec3(1.0f, 0.5f, 0.0f), 150.0f));
		passenger_Thruster2->addGameComponent(
			new SpotLight(
			PxVec3(1.0f, 0.5f, 0.0f), 150.0f));

		//Passenger RigidBody
		RigidBody* passengerShipRigidBody = new RigidBody(PxVec3(0.0f, 0.0f, 300.0f), PxQuat(PxIdentity), 1.0f);
		PolygonCollider* baseShip = new PolygonCollider();
		baseShip->init(PxVec3(0.0f, -20.0f, 300.0f), PxQuat(0.0f, 0.0f, 0.0f, 1.0f), 1.0f, 1.0f, PxVec3(0), PxVec3(0), 
			50.0f, 20.0f, 275.0f);
		passengerShipRigidBody->addCollider(*baseShip);

		PolygonCollider* cockpitShip = new PolygonCollider();
		cockpitShip->init(PxVec3(0.0f, 30.0f, 200.0f), PxQuat(PxIdentity), 1.0f, 1.0f, PxVec3(0), PxVec3(0),
			35.0f, 30.0f, 25.0f);
		passengerShipRigidBody->addCollider(*cockpitShip);

		//passengerShipRigidBody->setDebugDraw(true);

		// the passenger ship
		addToRoot((new GameObject("passengerShip", PxVec3(0.0f, 0.0f, 300.0f), PxQuat(PxIdentity), PxVec3(1.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Ships/MotherShip.obj", 50.0f), Material("passengerShip")))
			//->addGameComponent(new RigidBody(PxVec3(0.0f, 0.0f, 300.0f), PxQuat(PxIdentity), 1.0f, 50.0f, 40.0f, 275.0f))
			->addGameComponent(passengerShipRigidBody)			
			->addGameComponent(new PassengerShipAI)
			->addGameComponent(new ShipStats)
			->addGameComponent(new AudioSource("Music/sci-fi_spaceship_background_room_tone_hum_loop_03.WAV", AudioType::SOUND, true, 1.0f, false, true, AudioDimension::THREED))
			->addChild(spotLight1_Passenger)
			->addChild(spotLight2_Passenger)
			->addChild(spotLight3_Passenger)
			->addChild(spotLight4_Passenger)
			->addChild(spotLight5_Passenger)
			->addChild(spotLight6_Passenger)
			->addChild(spotLight7_Passenger)
			->addChild(spotLight8_Passenger)
			->addChild(passenger_Thruster1)
			->addChild(passenger_Thruster2)
			);
	}

	void addArea1OfMission1()
	{
		// the alien fighter ship
		addToRoot((new GameObject("enemyFighter", PxVec3(20.0f, 0.0f, 1000.0f), PxQuat(0.0f, 0.0f, 0.0f, 1.0f), PxVec3(1.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Ships/enemyBattleShip.obj", 10.0f), Material("alien_ship")))
			->addGameComponent(new RigidBody(PxVec3(0.0f, -5.0f, 80.0f), PxQuat(PxIdentity), 1.0f, 10.0f, 6.0f, 24.0f))
			->addGameComponent(new ShipStats)
			->addGameComponent(new EnemyFighterShipAI)
			);
		//// //the alien fighter ship
		//addToRoot((new GameObject("enemyFighter", PxVec3(-20.0f, 0.0f, 3000.0f), PxQuat(0.0f, 0.0f, 0.0f, 1.0f), PxVec3(1.0f)))
		//	->addGameComponent(new MeshRenderer(Mesh("Ships/enemyBattleShip.obj", 10.0f), Material("alien_ship")))
		//	->addGameComponent(new RigidBody(PxVec3(0.0f, -5.0f, 80.0f), PxQuat(PxIdentity), 1.0f, 10.0f, 6.0f, 24.0f))
		//	->addGameComponent(new ShipStats)
		//	->addGameComponent(new EnemyFighterShipAI)
		//	);
		 //the alien fighter ship
		addToRoot((new GameObject("enemyFighter", PxVec3(0.0f, 20.0f, 1000.0f), PxQuat(0.0f, 0.0f, 0.0f, 1.0f), PxVec3(1.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Ships/enemyBattleShip.obj", 10.0f), Material("alien_ship")))
			->addGameComponent(new RigidBody(PxVec3(0.0f, -5.0f, 80.0f), PxQuat(PxIdentity), 1.0f, 10.0f, 6.0f, 24.0f))
			->addGameComponent(new ShipStats)
			->addGameComponent(new EnemyFighterShipAI)
			);
		//////// the alien fighter ship
		//addToRoot((new GameObject("enemyFighter", PxVec3(0.0f, -20.0f, 3000.0f), PxQuat(0.0f, 0.0f, 0.0f, 1.0f), PxVec3(1.0f)))
		//	->addGameComponent(new MeshRenderer(Mesh("Ships/enemyBattleShip.obj", 10.0f), Material("alien_ship")))
		//	->addGameComponent(new RigidBody(PxVec3(0.0f, -5.0f, 80.0f), PxQuat(PxIdentity), 1.0f, 10.0f, 6.0f, 24.0f))
		//	->addGameComponent(new EnemyFighterShipAI)
		//	->addGameComponent(new ShipStats)
		//	);

		//// the alien fighter ship
		//addToRoot((new GameObject("enemyFighter", PxVec3(20.0f, 0.0f, 10000.0f), PxQuat(0.0f, 0.0f, 0.0f, 1.0f), PxVec3(1.0f)))
		//	->addGameComponent(new MeshRenderer(Mesh("Ships/enemyBattleShip.obj", 10.0f), Material("alien_ship")))
		//	->addGameComponent(new RigidBody(PxVec3(0.0f, -5.0f, 80.0f), PxQuat(PxIdentity), 1.0f, 10.0f, 6.0f, 24.0f))
		//	->addGameComponent(new ShipStats)
		//	->addGameComponent(new EnemyFighterShipAI)
		//	);
		//// //the alien fighter ship
		//addToRoot((new GameObject("enemyFighter", PxVec3(-20.0f, 0.0f, 5000.0f), PxQuat(0.0f, 0.0f, 0.0f, 1.0f), PxVec3(1.0f)))
		//	->addGameComponent(new MeshRenderer(Mesh("Ships/enemyBattleShip.obj", 10.0f), Material("alien_ship")))
		//	->addGameComponent(new RigidBody(PxVec3(0.0f, -5.0f, 80.0f), PxQuat(PxIdentity), 1.0f, 10.0f, 6.0f, 24.0f))
		//	->addGameComponent(new ShipStats)
		//	->addGameComponent(new EnemyFighterShipAI)
		//	);
		////the alien fighter ship
		//addToRoot((new GameObject("enemyFighter", PxVec3(0.0f, 20.0f, 10000.0f), PxQuat(0.0f, 0.0f, 0.0f, 1.0f), PxVec3(1.0f)))
		//	->addGameComponent(new MeshRenderer(Mesh("Ships/enemyBattleShip.obj", 10.0f), Material("alien_ship")))
		//	->addGameComponent(new RigidBody(PxVec3(0.0f, -5.0f, 80.0f), PxQuat(PxIdentity), 1.0f, 10.0f, 6.0f, 24.0f))
		//	->addGameComponent(new ShipStats)
		//	->addGameComponent(new EnemyFighterShipAI)
		//	);
		//////// the alien fighter ship
		//addToRoot((new GameObject("enemyFighter", PxVec3(0.0f, -20.0f, 8000.0f), PxQuat(0.0f, 0.0f, 0.0f, 1.0f), PxVec3(1.0f)))
		//	->addGameComponent(new MeshRenderer(Mesh("Ships/enemyBattleShip.obj", 10.0f), Material("alien_ship")))
		//	->addGameComponent(new RigidBody(PxVec3(0.0f, -5.0f, 80.0f), PxQuat(PxIdentity), 1.0f, 10.0f, 6.0f, 24.0f))
		//	->addGameComponent(new EnemyFighterShipAI)
		//	->addGameComponent(new ShipStats)
		//	);

		//// Planets and Moons
		addToRoot((new GameObject("spaceBody", PxVec3(1000.0f, 0.0f, 1000.0f), PxQuat(PxIdentity), PxVec3(1.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_A.obj", 32.0f), Material("moon")))
			->addGameComponent(new RigidBody(PxVec3(1000.0f, 0.0f, 1000.0f), PxQuat(PxIdentity), 100.0f, 32.0f))
			);

		addToRoot((new GameObject("spaceBody", PxVec3(-1000.0f, 0.0f, 0.0f), PxQuat(PxIdentity), PxVec3(1.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_B.obj", 100.0f), Material("earth")))

			->addGameComponent(new RigidBody(PxVec3(-1000.0f, 0.0f, 0.0f), PxQuat(PxIdentity), 100.0f, 100.0f))
			);

		addToRoot((new GameObject("spaceBody", PxVec3(7500.0f, 0.0f, 7500.0f), PxQuat(PxIdentity), PxVec3(1.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_C.obj", 35.0f), Material("mars")))
			->addGameComponent(new RigidBody(PxVec3(7500.0f, 0.0f, 7500.0f), PxQuat(PxIdentity), 100.0f, 35.0f))
			);

	}

	void addArea2OfMission1()
	{

		addToRoot((new GameObject("spaceBody", PxVec3(2800.0f, 400.0f, 33300.0f), PxQuat(PxIdentity), PxVec3(1.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_D.obj", 45.0f), Material("moon")))
			->addGameComponent(new RigidBody(PxVec3(2800.0f, 400.0f, 33300.0f), PxQuat(PxIdentity), 100.0f, 75.0f))
			);

		addToRoot((new GameObject("destinationMoon", PxVec3(-1900.0f, 2700.0f, 28200.0f), PxQuat(PxIdentity), PxVec3(1.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_E.obj", 10.0f), Material("mars")))
			->addGameComponent(new RigidBody(PxVec3(-1900.0f, 2700.0f, 28200.0f), PxQuat(PxIdentity), 100.0f, 20.0f))
			);

		addToRoot((new GameObject("spaceBody", PxVec3(-800.0f, -1500.0f, 35500.0f), PxQuat(PxIdentity), PxVec3(1.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_F.obj", 22.0f), Material("moon")))
			->addGameComponent(new RigidBody(PxVec3(-800.0f, -1500.0f, 35500.0f), PxQuat(PxIdentity), 100.0f, 32.0f))
			);

		addToRoot((new GameObject("spaceBody", PxVec3(0.0f, 0.0f, 30000.0f), PxQuat(PxIdentity), PxVec3(1.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_G.obj", 200.0f), Material("jupiter")))
			->addGameComponent(new RigidBody(PxVec3(0.0f, 0.0f, 30000.0f), PxQuat(PxIdentity), 100.0f, 200.0f))
			);

		PxVec3 positionOfSunLight(19050.0f, 0.0f, 19050.0f);
		addToRoot((new GameObject("SunLight", positionOfSunLight, PxQuat(ToRadians(1.0f), PxVec3(0.0f, 1.0f, 0.0f).getNormalized())))
			->addGameComponent(new SpotLight(PxVec3(1.0f, 0.71f, 0.0f), 180000.0f, Attenuation(1.0f, 1.0f, 0.0f)))
			->addGameComponent(new QuatRotator(PxVec3(positionOfSunLight))));

		addToRoot((new GameObject("spaceBody", PxVec3(50000.0f, 0.0f, 50000.0f), PxQuat(PxIdentity), PxVec3(25.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_A.obj"), Material("sun")))
			->addGameComponent(new RigidBody(PxVec3(50000.0f, 0.0f, 50000.0f), PxQuat(PxIdentity), 100.0f, 10000.0f))
			);
	}

	void addAudio()
	{
		addToRoot((new GameObject("Recharge sound"))
			->addGameComponent(new AudioSource("Music/sci-fi_power_up_10.WAV", AudioType::SOUND, false, 0.1f)));
	}
};
