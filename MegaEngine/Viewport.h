#pragma once
#include <SDL2\SDL.h>
#include <string>

#include "InputManager.h"

class GUIEngine;

enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

class Viewport
{
public:
	Viewport(const std::string& name, const int& screenWidth, const int& screenHeight, unsigned int windowFlags);
	~Viewport();

	void swapBuffers();
	void update(GUIEngine* guiEngine);
	
	inline bool isClosed() { return m_isClosed; }
	inline const int getScreenWidth() { return m_screenWidth; }
	inline const int getScreenHeight() { return m_screenHeight; }
	inline const std::string getScreenName() { return m_screenName; }
	inline SDL_Window* getWindow() { return m_window; }

	SDL_Window* getSDLWindow() { return m_window; }
	InputManager getInput() { return m_input; }

	void setScreenWidth(int screenWidth);
	void setScreenHeight(int screenHeight);

private:
	SDL_Window* m_window = nullptr;
	SDL_GLContext m_glContext;
	InputManager m_input;
	bool m_isClosed = false;
	int m_screenWidth = 0;
	int m_screenHeight = 0;
	std::string m_screenName = "";
};

