#pragma once
#include <MegaEngine.h>
#include "PauseExit.h"

class PauseScene : public Scene
{
public:
	PauseScene() : Scene("Pause") { }
	~PauseScene() { }

	virtual void init(const Viewport& window) override
	{
		addToRoot((new GameObject("Pause Menu"))
			->addGUIComponent(new GUIContainer(glm::vec4(0.3f, 0.3f, 0.4f, 0.6f), glm::vec4(0.0f)))
			->addGameComponent(new PauseExit));
	}

private:

};
