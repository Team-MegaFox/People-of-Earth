#pragma once
#include <MegaEngine.h>
#include <glm\glm.hpp>
#include <iostream>

#include "FreeLook.h"
#include "FreeMove.h"
#include "PlanetSpin.h"
#include "Listener.h"
#include "FireProjectile.h"


class TestScene : public Scene
{
public:
	TestScene() : Scene("Hello World") { }
	~TestScene() { }

	virtual void init(const Viewport& window) override
	{

		Material ship1("ship1", 0.5f, 4, Texture("Ships/AF-SS01/AF-SS01_White.png"), Texture("Ships/AF-SS01/AF-SS01_Normalmap.png"));
		Material ship2("ship2", 0.5f, 4, Texture("Ships/AF-SS01/AF-SS01_Navy.png"), Texture("Ships/AF-SS01/AF-SS01_Normalmap.png"));
		Material ship3("ship3", 0.5f, 4, Texture("Ships/AF-SS01/AF-SS01_Black.png"), Texture("Ships/AF-SS01/AF-SS01_Normalmap.png"));

		Material motherShip("motherShip", 0.5f, 4, Texture("Ships/MotherShip/MotherShip.png"));
		Material humanShip("human_ship", 1.0f, 10, Texture("Ships/Eric/HumanShip.png"));
		Material alienShip("alien_ship", 5.0f, 4, Texture("Ships/Eric/Alienship.png"), Texture("Ships/Eric/Alienship_NORM.png"), Texture("Ships/Eric/Alienship_DISP.png"));

		Material asteroidA("aster1", 0.5f, 4, Texture("Asteroids/Asteroid_A.png"), Texture("Asteroids/Asteroid_NRM.png"));
		Material asteroidB("aster2", 0.5f, 4, Texture("Asteroids/Asteroid_B.png"), Texture("Asteroids/Asteroid_NRM.png"));
		Material asteroidC("aster3", 0.5f, 4, Texture("Asteroids/Asteroid_C.png"), Texture("Asteroids/Asteroid_NRM.png"));
		Material asteroidD("aster4", 0.5f, 4, Texture("Asteroids/Asteroid_D.png"), Texture("Asteroids/Asteroid_NRM.png"));

		Material planetA("plan1", 0.5f, 4, Texture("Planets/Planet_A.png"), Texture("Planets/Planet_A_NRM.png"));
		Material planetB("plan2", 0.5f, 4, Texture("Planets/Planet_B.png"), Texture("Planets/Planet_B_NRM.png"));
		Material planetC("plan3", 0.5f, 4, Texture("Planets/Planet_C.png"), Texture("Planets/Planet_C_NRM.png"));
		Material planetD("plan4", 0.5f, 4, Texture("Planets/Planet_D.png"), Texture("Planets/Planet_D_NRM.png"));

		Material nebulaTex("nebula1", 0.5f, 4, Texture("NebulaeAndGalaxies/Nebula_A.png"));
		Material GalaxyTex("galaxy1", 0.5f, 4, Texture("NebulaeAndGalaxies/Galaxy_A.png"));

		addToRoot((new GameObject("skybox"))
			->addGameComponent(new SkyboxRenderer("Skybox/drake/drake.tga")));

		// The human fighter ship and camera
		GameObject* camera =
			(new GameObject("camera"))
			->addGameComponent(new CameraComponent(glm::perspective(glm::radians(60.0f), window.getAspectRatio(), 0.1f, 1000.0f)))
			->addGameComponent(new FreeLook(window.getCenter()))
			->addGameComponent(new FreeMove(50.0f))
			->addGameComponent(new FireProjectile)
			//->addGameComponent(new PlanetSpin)
			->addGameComponent(new Listener());

		GameObject* fighterShip =
			(new GameObject("Fighter Ship", glm::vec3(-2.0f, -4.0f, -10.0f), glm::quat(glm::angleAxis(glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f)))))
			->addGameComponent(new MeshRenderer(Mesh("Ships/HumanFighter_Final.obj", 0.1f), Material("human_ship")));

		//fighterShip->addGameComponent(new PlanetSpin);

		addToRoot(fighterShip);
		//camera->addChild(fighterShip);
		addToRoot(camera);

		Audio * stream = new Audio("./Assets/Music/rightNow.mp3", AudioType::STREAM);

		// the alien fighter ship
		addToRoot((new GameObject("enemyFighter", glm::vec3(0.0f, -5.0f, 80.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(4.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Ships/AlienFighter_FINAL.obj", 0.1f), Material("alien_ship")))
			->addGameComponent(stream));

		addToRoot((new GameObject("shipWhite", glm::vec3(0.0f, -5.0f, 450.0f), glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(400.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Ships/AF-SS01.obj", 0.01f), Material("ship1")))
);

		addToRoot((new GameObject("shipNavy", glm::vec3(0.0f, -5.0f, 550.0f), glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(400.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Ships/AF-SS01.obj", 0.01f), Material("ship2")))
);

		addToRoot((new GameObject("shipBlack", glm::vec3(0.0f, -5.0f, 650.0f), glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(400.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Ships/AF-SS01.obj", 0.01f), Material("ship3")))
);

		addToRoot((new GameObject("mother", glm::vec3(0.0f, -5.0f, 650.0f), glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(400.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Ships/MotherShip.obj", 0.1f), Material("motherShip")))
);
		addToRoot((new GameObject("asteroid1", glm::vec3(0.0f, 0.0f, 450.0f), glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(400.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Asteroids/Asteroid_A.obj", 0.1f), Material("aster1")))
);

		addToRoot((new GameObject("asteroid2", glm::vec3(0.0f, 0.0f, 550.0f), glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(400.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Asteroids/Asteroid_B.obj", 0.1f), Material("aster2")))
);

		addToRoot((new GameObject("asteroid3", glm::vec3(0.0f, 0.0f, 250.0f), glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(400.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Asteroids/Asteroid_C.obj", 0.1f), Material("aster3")))
);

		addToRoot((new GameObject("asteroid4", glm::vec3(0.0f, 0.0f, 350.0f), glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(400.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Asteroids/Asteroid_D.obj", 0.1f), Material("aster4")))
);

		addToRoot((new GameObject("planet1", glm::vec3(10.0f, 15.0f, 450.0f), glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(400.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_A.obj", 0.01f), Material("plan1")))
);

		addToRoot((new GameObject("planet2", glm::vec3(10.0f, 15.0f, 550.0f), glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(400.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_B.obj", 0.01f), Material("plan2")))
);

		addToRoot((new GameObject("planet3", glm::vec3(10.0f, 15.0f, 250.0f), glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(400.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_C.obj", 0.01f), Material("plan3")))
);

		addToRoot((new GameObject("planet4", glm::vec3(10.0f, 15.0f, 350.0f), glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(400.0f)))
			->addGameComponent(new MeshRenderer(Mesh("Planets/Planet_D.obj", 0.01f), Material("plan4")))
);

		addToRoot((new GameObject("nebula", glm::vec3(10.0f, 45.0f, 350.0f), glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(400.0f)))
			->addGameComponent(new MeshRenderer(Mesh("NebulaeAndGalaxies/Nebula_Large.obj", 0.01f), Material("nebula1")))
);

		addToRoot((new GameObject("galaxy", glm::vec3(10.0f, 45.0f, 650.0f), glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(400.0f)))
			->addGameComponent(new MeshRenderer(Mesh("NebulaeAndGalaxies/Galaxy_Large.obj", 0.01f), Material("galaxy1")))
);

		addToRoot((new GameObject("DrLight", glm::vec3(0.0f), glm::quat(glm::angleAxis(glm::radians(45.0f), glm::vec3(1, 0, 0)))))
			->addGameComponent(new DirectionalLight(glm::vec3(1.0f, 0.5f, 0.0f), 0.2f, 7, 8.0f, 1.0f)));

		stream->setPosition(glm::vec3(0.0f, -5.0f, 550.0f));
		//stream->play(true);

	}
};

