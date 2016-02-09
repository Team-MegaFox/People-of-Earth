#pragma once
#include <MegaEngine.h>
#include "PopMenu2Scene.h"

class PopupMenuScene : public Scene
{
public:
	PopupMenuScene() : Scene("PopupMenu") { }
	~PopupMenuScene() { }

	void init(const Viewport& window)
	{
		addToRoot((new GameObject("Pop menu container"))
			->addGUIComponent(new GUIContainer(glm::vec4(0.3f, 0.1f, 0.3f, 0.5f), glm::vec4(0.0f)))
			->addChild((new GameObject("Stuff in Container"))
			->addGUIComponent(new GUILabel(glm::vec4(0.1f, 0.1f, 0.5f, 0.05f), glm::vec4(0.0f), "pop up text"))
			->addGUIComponent(new GUIButton(glm::vec4(0.1f, 0.4f, 0.5f, 0.1f), glm::vec4(0.0f), "pop up button",
			std::bind(&PopupMenuScene::onButtonClick, this, std::placeholders::_1)))
			->addGUIComponent(new GUIButton(glm::vec4(0.1f, 0.6f, 0.5f, 0.1f), glm::vec4(0.0f), "Exit",
			std::bind(&PopupMenuScene::onQuitClick, this, std::placeholders::_1)))));
	}

private:
	bool onButtonClick(const GameObject& obj)
	{
		getCoreEngine()->getSceneManager()->push(new PopupMenu2Scene, Modality::Popup);
		return true;
	}

	bool onQuitClick(const GameObject& obj)
	{
		getCoreEngine()->getSceneManager()->pop();
		return true;
	}

};