#include <iostream>
#include <CoreEngine.h>
#include <Viewport.h>
#include <SceneManager.h>

#include "TestScene.h"

int main(int argc, char** argv)
{
	Viewport window("Testbed", 512, 512, 0);

	SceneManager sceneManager;
	TestScene testscene;

	AudioEngine * audioEngine = AudioEngine::getInstance();

	sceneManager.addScene(&testscene);
	sceneManager.switchScene(testscene.getName());

	CoreEngine core(60.0, &window, nullptr, nullptr, audioEngine, nullptr, &sceneManager);

	core.start();

	return 0;

}