// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 01-24-2016
// ***********************************************************************
// <copyright file="Viewport.cpp" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#include "Viewport.h"
#include <glew\glew.h>
#include "..\GUI\GUIEngine.h"

Viewport::Viewport(const std::string& name, const int& screenWidth, const int& screenHeight, unsigned int windowFlags) : 
m_input(this),
m_screenWidth(screenWidth),
m_screenHeight(screenHeight),
m_screenName(name)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		//Error handle
		assert(0 != 0);
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	Uint32 flags = SDL_WINDOW_OPENGL;

	if (windowFlags & INVISIBLE)
	{
		flags |= SDL_WINDOW_HIDDEN;
	}
	else if (windowFlags & FULLSCREEN)
	{
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	else if (windowFlags & BORDERLESS)
	{
		flags |= SDL_WINDOW_BORDERLESS;
	}

	m_window = SDL_CreateWindow(m_screenName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_screenWidth, m_screenHeight, flags);
	if (m_window == nullptr)
	{
		//Error handle
	}
	m_glContext = SDL_GL_CreateContext(m_window);

	SDL_GL_SetSwapInterval(1);

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(err));
	}

}

Viewport::~Viewport()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Viewport::update(GUIEngine* guiEngine)
{
	SDL_Event e;
	if (m_input.Update(e))
	{
		m_isClosed = true;
	}
	guiEngine->processInput(e);
}

void Viewport::clearScreen()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Viewport::swapBuffers()
{
	SDL_GL_SwapWindow(m_window);
}

void Viewport::bindAsRenderTarget() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, (GLsizei)m_screenWidth, (GLsizei)m_screenHeight);
}