#include "Viewport.h"
#include <glew\glew.h>


Viewport::Viewport(const std::string& name, const int& screenWidth, const int& screenHeight, unsigned int windowFlags) : 
m_screenWidth(screenWidth),
m_screenHeight(screenHeight),
m_screenName(name)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC) != 0)
	{
		//Error handle
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	m_window = SDL_CreateWindow(m_screenName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_screenWidth, m_screenHeight, windowFlags);
	if (m_window == nullptr)
	{
		//Error handle
	}
	m_glContext = SDL_GL_CreateContext(m_window);

	SDL_GL_SetSwapInterval(1);

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		//Error handle
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
	//if around input's update
}

void Viewport::swapBuffers()
{
	SDL_GL_SwapWindow(m_window);
}
