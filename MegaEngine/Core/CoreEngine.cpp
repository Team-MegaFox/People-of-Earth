// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 01-24-2016
// ***********************************************************************
// <copyright file="CoreEngine.cpp" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#include "CoreEngine.h"
#include <SDL2\SDL.h>

#include "..\Rendering\Viewport.h"
#include "..\Physics\PhysicsEngine.h"
#include "Time.h"
#include "SceneManager.h"
#include "Scene.h"
#include "..\GUI\GUIEngine.h"

CoreEngine::CoreEngine(double frameRate, Viewport* viewport, 
	RenderingEngine* renderingEngine, PhysicsEngine* physicsEngine, AudioEngine* audioEngine, GUIEngine* guiEngine, 
	SceneManager* sceneManager) :
m_running(false),
m_frameTime(1.0 / frameRate),
m_viewport(viewport),
m_renderingEngine(renderingEngine),
m_physicsEngine(physicsEngine),
m_audioEngine(audioEngine),
m_guiEngine(guiEngine),
m_sceneManager(sceneManager)
{
	if (m_sceneManager)
	{
		m_sceneManager->setEngine(this);

		m_sceneManager->getCurrentScene()->init(*m_viewport);
	}
}

void CoreEngine::start()
{
	if (m_running)
	{
		return;
	}

	m_running = true;

	double lastTime = Time::getTime();
	double frameCounter = 0;
	double unprocessedTime = 0;
	int frames = 0;

	while (m_running)
	{
		bool render = false;

		double startTime = Time::getTime();
		double passedTime = startTime - lastTime;
		lastTime = startTime;

		unprocessedTime += passedTime;
		frameCounter += passedTime;

		while (unprocessedTime > m_frameTime)
		{
			m_guiEngine->update();
			m_viewport->update(m_guiEngine);
			if (m_viewport->isClosed())
			{
				stop();
			}

			m_sceneManager->processInput(*m_viewport->getInput(), (float)m_frameTime);
			m_sceneManager->update((float)m_frameTime);

			//Call the physics engine update
			m_physicsEngine->updatePhysicsEngine((float)m_frameTime);

			render = true;

			unprocessedTime -= m_frameTime;
		}

		if (render)
		{
			m_sceneManager->render(m_renderingEngine);

			m_guiEngine->render();

			m_viewport->swapBuffers();

			frames++;
		}
		else
		{
			SDL_Delay(1);
		}
	}

}

void CoreEngine::stop()
{
	m_running = false;
}
