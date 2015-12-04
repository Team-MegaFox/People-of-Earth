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

		Material testSphere("testSphere", Texture("defaultTexture1.png"), 1.5f, 200, Texture("default_normal.jpg"), Texture("default_disp.png"), 0.03f, -0.5f);
		addToRoot((new GameObject(glm::vec3(0.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(4.0f)))
			->addGameComponent(new MeshRenderer(Mesh("sphere.obj"), Material("testSphere")))
			->addGameComponent(new FreeLook(window.getCenter()))

			// can't parent gameobjects, children inherit every aspect of their parent (position, scale, rotation) 
			//and the children's values can not change from that.

			//->addChild(new GameObject(glm::vec3(110.0f), glm::quat(ToRadians(30.0f), glm::vec3(0, 1, 0)), glm::vec3(0.25f)))
			//->addGameComponent(new MeshRenderer(Mesh("cube.obj"), Material("bricks")))
			);


		addToRoot((new GameObject(glm::vec3(7, 0, 7)))
			->addGameComponent(new PointLight(glm::vec3(0, 1, 0), 1.0f, Attenuation(0, 0, 1))));

		addToRoot((new GameObject(glm::vec3(-7, 0, -7)))
			->addGameComponent(new PointLight(glm::vec3(1, 0, 0.5), 20.0f, Attenuation(0, 0, 1))));

		//Spotlights don't work 
		//addToRoot((new GameObject(glm::vec3(10, 1.0f, 5), glm::quat(ToRadians(60.0f), glm::vec3(1, 0, 0)) * glm::quat(ToRadians(90.0f), glm::vec3(0, 1, 0))))
		//	->addGameComponent(new SpotLight(glm::vec3(0, 1, 1), 1.0f, Attenuation(0, 0, 0.02f), ToRadians(-91.1f), 7, 1.0f, 0.5f)));

		addToRoot((new GameObject)
			->addGameComponent(new CameraComponent(glm::perspective(ToRadians(75.0f), window.getAspectRatio(), 0.1f, 1000.0f)))
			->addGameComponent(new FreeMove()));

		addToRoot((new GameObject(glm::vec3(0.0f), glm::quat(ToRadians(45.0f), glm::vec3(1, 0, 0))))
			->addGameComponent(new DirectionalLight(glm::vec3(1.0f), 0.02f, 7, 8.0f, 1.0f)));

		

	}
};

