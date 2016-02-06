#pragma once
#include <MegaEngine.h>
#include <glm\glm.hpp>
#include <iostream>

#include "FreeLook.h"
#include "FreeMove.h"
#include "PlanetSpin.h"
#include "Listener.h"
#include "Audio.h"

class TestScene : public Scene
{
public:
	TestScene() : Scene("Hello World") { }
	~TestScene() { }

	virtual void init(const Viewport& window) override
	{
		//getPhysicsWorld().init(glm::vec3(0, 0, 0), 100);
		Material humanShip("human_ship", 0.5f, 4, Texture("Human-Ship-UVWs.png"));
		Material alienShip("alien_ship", 0.5f, 4, Texture("AlienshipUVWs.png"));
		Material skySphereTex("skySphereTexture", 0.5f, 4, Texture("night_sky.png"));
		Material earthTex("earthTexture", 0.5f, 4, Texture("earth.png"));
		Material moonTex("moonTexture", 0.5f, 4, Texture("moon.jpg"));

		GameObject* fighterShip =
			(new GameObject("PlayerFighterShip", glm::vec3(-2.0f, -4.0f, -10.0f), glm::quat(glm::angleAxis(glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f)))))
			->addGameComponent(new MeshRenderer(Mesh("HumanFighter_Final.obj", 0.1f), Material("human_ship")));

		//Rigidbody Polygon Collider rB1
		RigidBody * rB1 = new RigidBody(
			*fighterShip->getTransform()->getPosition(), 
			glm::quat(glm::angleAxis(glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f))), 
			200.0f, 
			100.0f, 
			100.0f, 
			100.0f);

		//Rigidbody Polygon Collider rb2
		RigidBody * rB2 = new RigidBody(
			glm::vec3(0.0f, -5.0f, 80.0f), 
			glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 
			400.0f, 
			100.0f, 
			100.0f, 
			100.0f);

		// The human fighter ship and camera
		GameObject* camera =
			(new GameObject("Camera"))
			->addGameComponent(new CameraComponent(glm::perspective(glm::radians(75.0f), window.getAspectRatio(), 0.1f, 1000.0f)))
			->addGameComponent(new FreeLook(window.getCenter()))
			->addGameComponent(new FreeMove(50.0f))
			->addGameComponent(new Listener())
			->addGameComponent(rB1);

		camera->addChild(fighterShip);
		addToRoot(camera);

		Audio * stream = new Audio("./Assets/Music/music.mp3", AudioType::STREAM);

		// the alien fighter ship
		addToRoot((new GameObject("AlienFighterShip_1",glm::vec3(0.0f, -5.0f, 80.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(4.0f)))
			->addGameComponent(new MeshRenderer(Mesh("AlienFighter_FINAL.obj", 0.1f), Material("alien_ship")))
			->addGameComponent(stream)
			->addGameComponent(rB2));

		// The skysphere
		addToRoot((new GameObject("Skysphere", glm::vec3(0.0f, -5.0f, 80.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(4000.0f)))
			->addGameComponent(new MeshRenderer(Mesh("sphere2.obj", 0.1f), Material("skySphereTexture")))
			->addGameComponent(new FreeMove()));

		// The Earth
		addToRoot((new GameObject("Earth", glm::vec3(0.0f, -5.0f, 550.0f), glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(400.0f)))
			->addGameComponent(new MeshRenderer(Mesh("sphere.obj", 0.1f), Material("earthTexture")))
			->addGameComponent(new PlanetSpin));

		addToRoot((new GameObject("DirectionalLight_1", glm::vec3(0.0f), glm::quat(glm::angleAxis(glm::radians(45.0f), glm::vec3(1, 0, 0)))))
			->addGameComponent(new DirectionalLight(glm::vec3(1.0f), 0.02f, 7, 8.0f, 1.0f)));

		stream->setPosition(glm::vec3(0.0f, -5.0f, 550.0f));
		stream->play(true);

		CameraComponent* cc = camera->getGameComponent<CameraComponent>();
		if (cc != nullptr)
		{
			std::cout << "There is a camera component!" << std::endl;
		}
	}
};

