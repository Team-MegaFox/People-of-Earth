#pragma once
#include <MegaEngine.h>
#include <PhysX/PxPhysicsAPI.h>
using namespace physx;

class PopupMenu2Scene : public Scene
{
public:
	PopupMenu2Scene() : Scene("PopupMenu") { }
	~PopupMenu2Scene() { }

	void init(const Viewport& window)
	{
		addToRoot((new GameObject("Pop menu 2 container"))
			->addGUIComponent(new GUIContainer(PxVec4(0.5f, 0.1f, 0.3f, 0.5f), PxVec4(0.0f)))
			->addChild((new GameObject("Stuff 2 in Container"))
			->addGUIComponent(new GUILabel(PxVec4(0.1f, 0.1f, 0.5f, 0.05f), PxVec4(0.0f), "Some other Pause Menu"))
			->addGUIComponent(new GUIButton(PxVec4(0.1f, 0.4f, 0.5f, 0.1f), PxVec4(0.0f), "pop up button",
			std::bind(&PopupMenu2Scene::onButtonClick, this, std::placeholders::_1)))));
	}

private:
	bool onButtonClick(const GameObject& obj)
	{
		getCoreEngine()->getSceneManager()->pop();
		return true;
	}

};