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
#include "PlanetSpin.h"

class TestScene : public Scene
{
public:
	TestScene() : Scene("Hello World") { }
	~TestScene() { }

	virtual void init(const Viewport& window) override;

};

