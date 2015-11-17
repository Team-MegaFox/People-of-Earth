#include <iostream>
#include <CoreEngine.h>
#include <Viewport.h>
#include <SceneManager.h>

#include "TestScene.h"

int main(int argc, char** argv)
{
	Viewport window("Testbed2", 512, 512, 0);

	SceneManager sceneManager;
	TestScene testscene;
	sceneManager.addScene(&testscene);
	sceneManager.switchScene(testscene.getName());

	CoreEngine core(60.0, &window, nullptr, nullptr, nullptr, nullptr, &sceneManager);

	core.start();

	return 0;

}