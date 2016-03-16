#pragma once
#include <MegaEngine.h>

#include "PauseScene.h"

class ShowPuaseComp : public GameComponent
{
public:
	ShowPuaseComp() { }
	~ShowPuaseComp() { }

	/// <summary>
	/// Virtual function for custom input processing.
	/// </summary>
	/// <param name="input">The input manager.</param>
	/// <param name="delta">The frame time delta.</param>
	virtual void processInput(const InputManager& input, float delta) 
	{
		if (input.KeyPress(SDLK_ESCAPE))
		{
			getCoreEngine()->getSceneManager()->push(new PauseScene, Modality::Popup);
		}
	}

private:

};
