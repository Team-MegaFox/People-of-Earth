#pragma once
#include "GameObject.h"
#include <string>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
using namespace CEGUI;

class GUIComponent
{
public:
	GUIComponent() {}
	GUIComponent(
		const std::string & type, 
		const std::string & name, 
		const glm::vec4 & destRectPerc, 
		const glm::vec4 & destRectPix);

	void setParent(GameObject * gameObject);
	bool isActive();
	void setActive(const bool & enabled);
	void setSize(const glm::vec4 & destRectPerc, const glm::vec4 & destRectPix);

	inline Window * getWidget() { return m_widget; }

private:
	GameObject * m_gameObject;
	Window * m_widget;
	bool m_enabled;
	glm::vec4 m_destRectPerc;
	glm::vec4 m_destRectPix;

};

