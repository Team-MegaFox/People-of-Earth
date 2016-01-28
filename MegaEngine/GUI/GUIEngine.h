// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Deroiche
// Created          : 09-15-2015
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 01-24-2016
// ***********************************************************************
// <copyright file="GUIEngine.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once
#include <SDL2\SDL_events.h>
#include <glm\glm.hpp>
#include <CEGUI\CEGUI.h>
#include <CEGUI\RendererModules\OpenGL\GL3Renderer.h>

#include "..\Core\InputManager.h"

class GUIEngine
{
public:
	GUIEngine(const std::string& resDir);
	~GUIEngine();

	void processInput(InputManager* input);
	void update();
	void render();

	void setMouseCursor(const std::string& imageFile);
	void showMouseCursor(bool value);

	void loadScheme(const std::string& schemeFile);
	void setFont(const std::string& fontFile);

	CEGUI::Window* addWidget(const std::string& type, const glm::vec4& destRectPerc, const glm::vec4& destRectPix, const std::string& name = "");
	CEGUI::Window* addWidget(CEGUI::Window* parent, const std::string& type, const glm::vec4& destRectPerc, const glm::vec4& destRectPix, const std::string& name = "");
	static void setWidgetDestRect(CEGUI::Window* widget, const glm::vec4& destRectPerc, const glm::vec4& destRectPix);

	static CEGUI::OpenGL3Renderer* getRenderer() { return m_renderer; }
	const CEGUI::GUIContext* getContext() const { return m_context; }
	const std::string& getSchemeStyle() { return m_schemeStyle; }

private:
	static CEGUI::OpenGL3Renderer* m_renderer;
	CEGUI::GUIContext* m_context = nullptr;
	CEGUI::Window* m_root = nullptr;
	std::string m_schemeStyle = "TaharezLook";
	double m_lastTime = 0;
};

