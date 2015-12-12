#pragma once
#include <Scene.h>
#include <GameObject.h>
#include <MeshRenderer.h>
#include <DirectionalLight.h>
#include <PointLight.h>
#include <SpotLight.h>
#include <Camera3D.h>
#include <glm\glm.hpp>

#include "FreeLook.h"
#include "FreeMove.h"

class TestScene : public Scene
{
public:
	TestScene() : Scene("Hello World") { }
	~TestScene() { }

	virtual void init(const Viewport& window) override
	{
		Material bricks("bricks", 0.5f, 4, Texture("bricks.jpg"), Texture("bricks_normal.jpg"), Texture("bricks_disp.png"), 0.03f, -0.5f);
		Material humanShip("human_ship", 0.5f, 4, Texture("Human-Ship-UVWs.png"));
		Material alienShip("alien_ship", 0.5f, 4, Texture("AlienshipUVWs.png"));
		Material skySphereTex("skySphereTexture", 0.5f, 4, Texture("night_sky.png"));
		Material earthTex("earthTexture", 0.5f, 4, Texture("earth.png"));
		Material sunTex("sunTexture", 0.5f, 4, Texture("sun.jpg"));
		Material moonTex("moonTexture", 0.5f, 4, Texture("moon.jpg"));

		// The human fighter ship
		addToRoot((new GameObject(glm::vec3(0.0f, -5.0f, -80.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(4.0f)))
			->addGameComponent(new MeshRenderer(Mesh("HumanFighter_Final.obj", 0.1f), Material("human_ship"))));

		// the alien fighter ship
		addToRoot((new GameObject(glm::vec3(0.0f, -5.0f, 80.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(4.0f)))
			->addGameComponent(new MeshRenderer(Mesh("AlienFighter_FINAL.obj", 0.1f), Material("alien_ship"))));

		// The skysphere
		addToRoot((new GameObject(glm::vec3(0.0f, -5.0f, 80.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(4000.0f)))
			->addGameComponent(new MeshRenderer(Mesh("sphere2.obj", 0.1f), Material("skySphereTexture")))
			->addGameComponent(new FreeMove()));


		// The Earth
		addToRoot((new GameObject(glm::vec3(0.0f, -5.0f, 550.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(400.0f)))
			->addGameComponent(new MeshRenderer(Mesh("sphere.obj", 0.1f), Material("earthTexture"))));

		addToRoot((new GameObject(glm::vec3(0.0f, -5.0f, 4550.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(150.0f)))
			->addGameComponent(new MeshRenderer(Mesh("sphere.obj", 0.1f), Material("moonTexture"))));

		// The Sun
		addToRoot((new GameObject(glm::vec3(0.0f, -5.0f, -55000.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(1000.0f)))
			->addGameComponent(new MeshRenderer(Mesh("sphere.obj", 0.1f), Material("sunTexture"))));

		addToRoot((new GameObject)
			->addGameComponent(new CameraComponent(glm::perspective(ToRadians(75.0f), window.getAspectRatio(), 0.1f, 1000.0f)))
			->addGameComponent(new FreeLook(window.getCenter()))
			->addGameComponent(new FreeMove())
			/*->addChild(new GameObject(glm::vec3(0.0f, -5.0f, 80.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(4000.0f)))
			->addGameComponent(new MeshRenderer(Mesh("sphere2.obj", 0.1f), Material("skySphereTexture")))*/);

		addToRoot((new GameObject(glm::vec3(0.0f), glm::quat(ToRadians(45.0f), glm::vec3(1, 0, 0))))
			->addGameComponent(new DirectionalLight(glm::vec3(1.0f), 0.02f, 7, 8.0f, 1.0f)));

		

	}
};

