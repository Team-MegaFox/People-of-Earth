#include "GUIComponent.h"


GUIComponent::GUIComponent(
	const std::string & type, 
	const std::string & name, 
	const glm::vec4 & destRectPerc, 
	const glm::vec4 & destRectPix)
{
	m_widget = WindowManager::getSingleton().createWindow(type, name);
	setSize(destRectPerc, destRectPix);
}

void GUIComponent::setParent(GameObject * gameObject)
{
	gameObject->addGUIComponent(this);
}

bool GUIComponent::isActive()
{
	return m_enabled;
}

void GUIComponent::setActive(const bool & enabled)
{
	m_enabled = enabled;
}

void GUIComponent::setSize(const glm::vec4 & destRectPerc, const glm::vec4 & destRectPix)
{
	m_widget->setPosition(
		UVector2(UDim(destRectPerc.x, destRectPix.x), 
		UDim(destRectPerc.y, destRectPix.y)));

	m_widget->setSize(
		USize(UDim(destRectPerc.z, destRectPix.z), 
		UDim(destRectPerc.w, destRectPix.w)));
}

