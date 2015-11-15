#include "GUIButtonComponent.h"


GUIButtonComponent::GUIButtonComponent(
	const std::string & type, 
	const std::string & name, 
	const std::string & buttonText, 
	const glm::vec4 & destRectPerc, 
	const glm::vec4 & destRectPix)
{
	Window * window = WindowManager::getSingleton().createWindow(type, name);
	this->getWidget()->addChild(window);
	this->setSize(destRectPerc, destRectPix);
}


bool GUIButtonComponent::isHovering()
{
	return this->isHovering();
}


bool GUIButtonComponent::isPushed()
{
	return this->isPushed();
}


void GUIButtonComponent::setOnClick(Event::Subscriber subscribe)
{
	this->setOnClick(subscribe);
}
