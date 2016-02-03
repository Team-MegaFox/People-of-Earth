// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
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
	/// <summary>
	/// Initializes a new instance of the <see cref="GUIEngine"/> class.
	/// </summary>
	/// <param name="resDir">The resource dir.</param>
	GUIEngine(const std::string& resDir, 
		const std::string& schemeFile = "TaharezLook.scheme", 
		const std::string& fontFile = "DejaVuSans-10",
		const std::string& mouseImageFile = "TaharezLook/MouseArrow");
	/// <summary>
	/// Finalizes an instance of the <see cref="GUIEngine"/> class.
	/// </summary>
	~GUIEngine();

	/// <summary>
	/// Processes the input.
	/// </summary>
	/// <param name="input">The input.</param>
	void processInput(InputManager* input);
	/// <summary>
	/// Updates this instance.
	/// </summary>
	void update();
	/// <summary>
	/// Renders this instance.
	/// </summary>
	void render();

	/// <summary>
	/// Sets the mouse cursor.
	/// </summary>
	/// <param name="imageFile">The image file.</param>
	void setMouseCursor(const std::string& imageFile);
	/// <summary>
	/// Shows the mouse cursor.
	/// </summary>
	/// <param name="value">if set to <c>true</c> [value].</param>
	void showMouseCursor(bool value);

	/// <summary>
	/// Loads the scheme.
	/// </summary>
	/// <param name="schemeFile">The scheme file.</param>
	void loadScheme(const std::string& schemeFile);
	/// <summary>
	/// Sets the font.
	/// </summary>
	/// <param name="fontFile">The font file.</param>
	void setFont(const std::string& fontFile);

	/// <summary>
	/// Adds the widget.
	/// </summary>
	/// <param name="type">The type.</param>
	/// <param name="destRectPerc">The dest rect perc.</param>
	/// <param name="destRectPix">The dest rect pix.</param>
	/// <param name="name">The name.</param>
	/// <returns></returns>
	CEGUI::Window* addWidget(const std::string& type, const glm::vec4& destRectPerc, const glm::vec4& destRectPix, const std::string& name = "");
	/// <summary>
	/// Adds the widget.
	/// </summary>
	/// <param name="parent">The parent.</param>
	/// <param name="type">The type.</param>
	/// <param name="destRectPerc">The dest rect perc.</param>
	/// <param name="destRectPix">The dest rect pix.</param>
	/// <param name="name">The name.</param>
	/// <returns></returns>
	CEGUI::Window* addWidget(CEGUI::Window* parent, const std::string& type, const glm::vec4& destRectPerc, const glm::vec4& destRectPix, const std::string& name = "");
	/// <summary>
	/// Sets the widget dest rect.
	/// </summary>
	/// <param name="widget">The widget.</param>
	/// <param name="destRectPerc">The dest rect perc.</param>
	/// <param name="destRectPix">The dest rect pix.</param>
	static void setWidgetDestRect(CEGUI::Window* widget, const glm::vec4& destRectPerc, const glm::vec4& destRectPix);

	/// <summary>
	/// Gets the renderer.
	/// </summary>
	/// <returns></returns>
	CEGUI::OpenGL3Renderer* getRenderer() { return m_renderer; }
	/// <summary>
	/// Gets the context.
	/// </summary>
	/// <returns></returns>
	const CEGUI::GUIContext* getContext() const { return m_context; }
	/// <summary>
	/// Gets the scheme style.
	/// </summary>
	/// <returns></returns>
	const std::string& getSchemeStyle() { return m_schemeStyle; }

private:
	/// <summary>
	/// The m_renderer
	/// </summary>
	CEGUI::OpenGL3Renderer* m_renderer;
	/// <summary>
	/// The m_context
	/// </summary>
	CEGUI::GUIContext* m_context = nullptr;
	/// <summary>
	/// The m_root
	/// </summary>
	CEGUI::Window* m_root = nullptr;
	/// <summary>
	/// The m_scheme style
	/// </summary>
	std::string m_schemeStyle = "TaharezLook";
	/// <summary>
	/// The m_last time
	/// </summary>
	double m_lastTime = 0;
};

