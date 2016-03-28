#include <iostream>
#include <MegaEngine.h>
#include <Rendering\RenderingEngine.h>
#include <Core\SceneManager.h>
#include <Physics\PhysicsEngine.h>
#include <Audio\AudioEngine.h>
#include <GUI\GUIEngine.h>
#include "MainMenuScene.h"
#include "MissionOneScene.h"

int main(int argc, char** argv)
{
	Viewport window("The People of Earth", 1024, 576, 0);
	//Viewport window("The People of Earth", 1366, 768, 0);
	//Viewport window("The People of Earth", 1920, 1080, BORDERLESS);
	GUIEngine guiEngine("Assets/GUI"); 
	RenderingEngine renderingEngine(window);
	SceneManager sceneManager(&window);
	PhysicsEngine physicsEngine;
	physicsEngine.getPhysicsWorld()->init(PxVec3(0), 200000.0f);
	AudioEngine audioEngine;

	CoreEngine core(60.0, &window, &renderingEngine, &physicsEngine, &audioEngine, &guiEngine, &sceneManager);

	sceneManager.push(new MainMenuScene);

	core.start();

	return 0;

}