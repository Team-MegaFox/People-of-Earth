#include <iostream>
#include <CoreEngine.h>
#include <Viewport.h>
#include <SceneManager.h>
#include <RenderingEngine.h>
#include <GUIEngine.h>

#include "TestScene.h"

int main(int argc, char** argv)
{
	Viewport window("Testbed", 512, 512, 0);
	GUIEngine guiEngine;
	RenderingEngine renderingEngine(window, guiEngine);
	SceneManager sceneManager;
	TestScene testscene;
	sceneManager.addScene(&testscene);
	sceneManager.switchScene(testscene.getName());

	CoreEngine core(60.0, &window, &renderingEngine, nullptr, nullptr, &guiEngine, &sceneManager);

	core.start();

	return 0;

}