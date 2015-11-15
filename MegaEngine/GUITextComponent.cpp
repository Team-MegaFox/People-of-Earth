#include "GUITextComponent.h"

GUITextComponent::GUITextComponent(
	const std::string & type,
	const std::string & name,
	const std::string & labelText,
	const glm::vec4 & destRectPerc,
	const glm::vec4 & destRectPix)
{
	Window * window = WindowManager::getSingleton().createWindow(type, name);
	this->getWidget()->addChild(window);
	this->setSize(destRectPerc, destRectPix);
}

