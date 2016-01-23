#include <iostream>
#include <CoreEngine.h>
#include <Viewport.h>
#include <SceneManager.h>
#include <RenderingEngine.h>
#include <GUIEngine.h>
#include <AudioEngine.h>
#include <PhysicsEngine.h>
#include "TestScene.h"

int main(int argc, char** argv)
{
	Viewport window("Project Management Demo", 800, 600, 0);
	GUIEngine guiEngine;
	RenderingEngine renderingEngine(window, guiEngine);
	SceneManager sceneManager;
	TestScene testscene;
	PhysicsEngine physicsEngine;
	AudioEngine audioEngine;

	sceneManager.addScene(&testscene);
	sceneManager.switchScene(testscene.getName());

	CoreEngine core(60.0, &window, &renderingEngine, &physicsEngine, &audioEngine, &guiEngine, &sceneManager);

	core.start();

	return 0;

}