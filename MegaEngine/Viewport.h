#pragma once
#include <SDL2\SDL.h>
#include <string>

class GUIEngine;

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

	void setScreenWidth(int screenWidth);
	void setScreenHeight(int screenHeight);

private:
	SDL_Window* m_window = nullptr;
	SDL_GLContext m_glContext;
	bool m_isClosed = false;
	int m_screenWidth = 0;
	int m_screenHeight = 0;
	std::string m_screenName = "";

	unsigned int getWindowFlags(unsigned int windowFlags);
};

