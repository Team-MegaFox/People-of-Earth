#pragma once
#include <MegaEngine.h>

#include "PauseScene.h"

class PauseExit : public GameComponent
{
public:
	PauseExit() { }
	~PauseExit() { }

	/// <summary>
	/// Virtual function for custom input processing.
	/// </summary>
	/// <param name="input">The input manager.</param>
	/// <param name="delta">The frame time delta.</param>
	virtual void processInput(const InputManager& input, float delta)
	{
		if (input.KeyPress(SDLK_e))
		{
			getCoreEngine()->getSceneManager()->popTo(0);
		}
	}

private:

};