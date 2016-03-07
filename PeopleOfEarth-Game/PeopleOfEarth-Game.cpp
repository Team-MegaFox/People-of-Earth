#include <iostream>
#include <MegaEngine.h>
#include <Rendering\RenderingEngine.h>
#include <Core\SceneManager.h>
#include <Physics\PhysicsEngine.h>
#include <Audio\AudioEngine.h>
#include <GUI\GUIEngine.h>
#include "MainMenuScene.h"

int main(int argc, char** argv)
{
	Viewport window("People of Earth", 1024, 576, 0);
	GUIEngine guiEngine("Assets/GUI");
	RenderingEngine renderingEngine(window);
	SceneManager sceneManager(&window);
	PhysicsEngine physicsEngine;
	physicsEngine.getPhysicsWorld()->init(PxVec3(0), 1000.0f);
	AudioEngine audioEngine;

	CoreEngine core(60.0, &window, &renderingEngine, &physicsEngine, &audioEngine, &guiEngine, &sceneManager);

	sceneManager.push(new MainMenuScene, Modality::Exclusive);

	core.start();

	return 0;

}