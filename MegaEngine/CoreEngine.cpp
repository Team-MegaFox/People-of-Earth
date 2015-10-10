#include "CoreEngine.h"
#include <SDL2\SDL.h>

#include "Time.h"
#include "Viewport.h"

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
	//Set Engine for game
	//Call game's init function
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
			m_viewport->update(m_guiEngine);
			if (m_viewport->isClosed())
			{
				stop();
			}

			//Call game's processInput
			//Call game's update

			render = true;

			unprocessedTime -= m_frameTime;
		}

		if (render)
		{
			//Call game's render

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
