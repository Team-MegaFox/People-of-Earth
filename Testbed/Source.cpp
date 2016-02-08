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
	Viewport window("Some demo", 800, 600, 0);
	GUIEngine guiEngine("Assets/GUI");
	RenderingEngine renderingEngine(window, guiEngine);
	SceneManager sceneManager;
	TestScene testscene;
	PhysicsEngine physicsEngine;
	physicsEngine.getPhysicsWorld()->init(glm::vec3(0), 1000.0f);
	AudioEngine audioEngine;

	sceneManager.addScene(&testscene);
	sceneManager.switchScene(testscene.getName());

	CoreEngine core(60.0, &window, &renderingEngine, &physicsEngine, &audioEngine, &guiEngine, &sceneManager);

	core.start();

	return 0;

}