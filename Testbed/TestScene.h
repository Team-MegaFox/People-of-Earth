#pragma once
#include <Scene.h>
#include <GameObject.h>
#include <MeshRenderer.h>
#include <DirectionalLight.h>
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
		Material bricks("bricks", Texture("bricks.jpg"), 0.5f, 4, Texture("bricks_normal.jpg"), Texture("bricks_disp.png"), 0.03f, -0.5f);

		addToRoot((new GameObject(glm::vec3(0.0f, -1.0f, 5.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(4.0f)))
			->addGameComponent(new MeshRenderer(Mesh("plane4.obj"), Material("bricks"))));
		
		//axis of rotation(x, y, z) = sin(0.5f * angle / 2.0f * 3.14159265f / 180.0f)
		//w = cos(0.5f * angle / 2.0f * 3.14159625f / 180.0f)

		Material Mega("Mega", Texture("MegaFox.png"), 0.5f, 4, Texture("bricks_normal.jpg"), Texture("bricks_disp.png"), 0.03f, -0.5f);

		addToRoot((new GameObject(
			glm::vec3(30.0f, -1.0f, 5.0f), 
			glm::quat(cos(ToRadians(0.5 * 180.0f / 2.0f)), 0.0f, 0.0f, sin(ToRadians(0.5 * 180.0f / 2.0f))),
			glm::vec3(4.0f)))
			->addGameComponent(new MeshRenderer(Mesh("plane4.obj"), Material("Mega"))));

		addToRoot((new GameObject(
			glm::vec3(-30.0f, -1.0f, 5.0f),
			glm::quat(cos(ToRadians(0.5 * 180.0f / 2.0f)), 0.0f, 0.0f, sin(ToRadians(0.5 * 180.0f / 2.0f))),
			glm::vec3(4.0f)))
			->addGameComponent(new MeshRenderer(Mesh("plane4.obj"), Material("bricks"))));

		addToRoot((new GameObject)
			->addGameComponent(new CameraComponent(glm::perspective(ToRadians(75.0f), window.getAspectRatio(), 0.1f, 1000.0f)))
			->addGameComponent(new FreeLook(window.getCenter()))
			->addGameComponent(new FreeMove()));

		addToRoot((new GameObject(glm::vec3(0.0f), glm::quat(ToRadians(-45.0f), glm::vec3(1, 0, 0))))
			->addGameComponent(new DirectionalLight(glm::vec3(1, 1, 1), 0.4f, 10, 80.0f, 1.0f)));

		

	}
};

