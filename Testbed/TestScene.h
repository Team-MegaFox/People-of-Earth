#pragma once
#include <Scene.h>
class TestScene : public Scene
{
public:
	TestScene() : Scene("Hello World") { }
	~TestScene() { }

	virtual void init() override
	{

	}
};

