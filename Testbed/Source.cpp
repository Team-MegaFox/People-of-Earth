#include <iostream>
#include <MegaEngine.h>
#include <Rendering\RenderingEngine.h>
#include <Core\SceneManager.h>
#include <Physics\PhysicsEngine.h>
#include <Audio\AudioEngine.h>
#include <GUI\GUIEngine.h>
#include "TestScene.h"


int main(int argc, char** argv)
{
	Viewport window("The People of Earth TestBed ***Demo***", 800, 600/*1920, 1080*/, 0);
	GUIEngine guiEngine("Assets/GUI");
	RenderingEngine renderingEngine(window);
	SceneManager sceneManager(&window);
	PhysicsEngine physicsEngine;
	physicsEngine.getPhysicsWorld()->init(PxVec3(0.0f, 0.0f, 0.0f), 20000.0f);
	AudioEngine audioEngine;

	CoreEngine core(60.0, &window, &renderingEngine, &physicsEngine, &audioEngine, &guiEngine, &sceneManager);

	sceneManager.push(new TestScene, Modality::Exclusive);

	core.start();

	return 0;

}