#pragma once
#include <string>
#include "GameObject.h"
#include "GUIComponent.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>

using namespace CEGUI;

class GUIEngine
{

public:
	GUIEngine(const std::string & resourceDir);
	~GUIEngine();

	void update(const float & deltaTime, const GameObject & gameObject);
	void render();
	void processInput(SDL_Event & e);

	void setFont(const std::string & fontFile);
	void setToRoot(GUIComponent & component);
	void loadScheme(const std::string & scheme);

private:
	static OpenGL3Renderer * m_renderer;
	GUIContext * m_context;
	Window * m_root;

};


