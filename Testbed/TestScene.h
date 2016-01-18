#pragma once
#include <Scene.h>



class TestScene : public Scene
{
public:
	TestScene() : Scene("Hello World") { }
	~TestScene() { }

	virtual void init() override
	{
		//getPhysicsWorld().init(glm::vec3(0, 0, 0), 100);
		

	}
};

