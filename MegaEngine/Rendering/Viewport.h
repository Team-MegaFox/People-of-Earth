// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Deroiche
// Created          : 09-15-2015
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 01-24-2016
// ***********************************************************************
// <copyright file="Viewport.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once
#include <SDL2\SDL.h>
#include <string>

#include "..\Core\InputManager.h"

class GUIEngine;

/// <summary>
/// An enum for the window to be either invisible, fullscreen and/or borderless.
/// </summary>
enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

/// <summary>
/// The Viewport class is the window of the game. This is where eveything will be rendered to.
/// </summary>
class Viewport
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Viewport"/> class.
	/// </summary>
	/// <param name="name">The name of the window.</param>
	/// <param name="screenWidth">Width of the screen.</param>
	/// <param name="screenHeight">Height of the screen.</param>
	/// <param name="windowFlags">The window flags using <see cref='WindowFlags'/>.</param>
	Viewport(const std::string& name, const int& screenWidth, const int& screenHeight, unsigned int windowFlags);
	/// <summary>
	/// Finalizes an instance of the <see cref="Viewport"/> class.
	/// </summary>
	~Viewport();

	/// <summary>
	/// Swaps the buffers.
	/// </summary>
	void swapBuffers();
	/// <summary>
	/// Updates input from the window.
	/// </summary>
	/// <param name="guiEngine">The GUI engine.</param>
	void update();
	
	/// <summary>
	/// Determines whether this window is closed.
	/// </summary>
	/// <returns>If the window is closed.</returns>
	inline bool isClosed() const { return m_isClosed; }
	/// <summary>
	/// Gets the width of the screen.
	/// </summary>
	/// <returns>THe screen width.</returns>
	inline const int getScreenWidth() const { return m_screenWidth; }
	/// <summary>
	/// Gets the height of the screen.
	/// </summary>
	/// <returns>The screen height.</returns>
	inline const int getScreenHeight() const { return m_screenHeight; }
	/// <summary>
	/// Gets the aspect ratio of the screen.
	/// </summary>
	/// <returns>The screen's aspect ratio.</returns>
	inline const float getAspectRatio() const { return (float)m_screenWidth / (float)m_screenHeight; }
	/// <summary>
	/// Gets the center position of the window.
	/// </summary>
	/// <returns>The center point of the window.</returns>
	inline const glm::vec2 getCenter() const { return glm::vec2((float)m_screenWidth / 2.0f, (float)m_screenHeight / 2.0f); }
	/// <summary>
	/// Gets the name of the screen.
	/// </summary>
	/// <returns>The name of the window.</returns>
	inline const std::string getScreenName() const { return m_screenName; }
	/// <summary>
	/// Gets the window.
	/// </summary>
	/// <returns>A pointer to the <see cref='SDL_Window'/>.</returns>
	inline SDL_Window* getWindow() const { return m_window; }

	/// <summary>
	/// Gets the input manager.
	/// </summary>
	/// <returns>A copy of the Inout Manager object.</returns>
	InputManager* getInput() { return &m_input; }

	/// <summary>
	/// Sets the width of the screen.
	/// </summary>
	/// <param name="screenWidth">Width of the screen.</param>
	void setScreenWidth(int screenWidth);
	/// <summary>
	/// Sets the height of the screen.
	/// </summary>
	/// <param name="screenHeight">Height of the screen.</param>
	void setScreenHeight(int screenHeight);
	/// <summary>
	/// Binds the render target to the screen.
	/// </summary>
	void bindRenderTarget() const;

private:
	/// <summary>
	/// The pointer to the SDL_Window.
	/// </summary>
	SDL_Window* m_window = nullptr;
	/// <summary>
	/// The OpenGL context in the window.
	/// </summary>
	SDL_GLContext m_glContext;
	/// <summary>
	/// The input manager.
	/// </summary>
	InputManager m_input;
	/// <summary>
	/// If the window is closed.
	/// </summary>
	bool m_isClosed = false;
	/// <summary>
	/// The screen width.
	/// </summary>
	int m_screenWidth = 0;
	/// <summary>
	/// The screen height.
	/// </summary>
	int m_screenHeight = 0;
	/// <summary>
	/// The window's name.
	/// </summary>
	std::string m_screenName = "";
};

