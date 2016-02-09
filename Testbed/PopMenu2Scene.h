#pragma once
#include <MegaEngine.h>

class PopupMenu2Scene : public Scene
{
public:
	PopupMenu2Scene() : Scene("PopupMenu") { }
	~PopupMenu2Scene() { }

	void init(const Viewport& window)
	{
		addToRoot((new GameObject("Pop menu 2 container"))
			->addGUIComponent(new GUIContainer(glm::vec4(0.5f, 0.1f, 0.3f, 0.5f), glm::vec4(0.0f)))
			->addChild((new GameObject("Stuff 2 in Container"))
			->addGUIComponent(new GUILabel(glm::vec4(0.1f, 0.1f, 0.5f, 0.05f), glm::vec4(0.0f), "pop up text"))
			->addGUIComponent(new GUIButton(glm::vec4(0.1f, 0.4f, 0.5f, 0.1f), glm::vec4(0.0f), "pop up button",
			std::bind(&PopupMenu2Scene::onButtonClick, this, std::placeholders::_1)))));
	}

private:
	bool onButtonClick(const GameObject& obj)
	{
		getCoreEngine()->getSceneManager()->pop();
		return true;
	}

};