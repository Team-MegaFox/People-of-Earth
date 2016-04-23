// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Jesse Derochie
// Last Modified On : 03-01-2016
// ***********************************************************************
// <copyright file="GUIEngine.cpp" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#include <glew\glew.h>
#include <SDL2\SDL.h>
#include <iostream>
#include <utf8\utf8.h>
#include "GUIEngine.h"
#include "..\Core\Time.h"
#include "..\Core\Utility.h"

// Disable logging in CEGUI for Release build
#ifndef _DEBUG
class CeguiNonLogger : public CEGUI::Logger{
	void logEvent(const CEGUI::String&, CEGUI::LoggingLevel){}
	void setLogFilename(const CEGUI::String&, bool){}
};
CeguiNonLogger g_ceguiNonLogger;
#endif

GUIEngine::GUIEngine(const std::string& resDir, 
	const std::string& schemeFile /*= "TaharezLook.scheme"*/,
	const std::string& mouseImageFile /*= "TaharezLook/MouseArrow"*/)
{
	if (m_renderer == nullptr)
	{
		m_renderer = &CEGUI::OpenGL3Renderer::bootstrapSystem();
		CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());
		rp->setResourceGroupDirectory("imagesets", resDir + "/imagesets/");
		rp->setResourceGroupDirectory("schemes", resDir + "/schemes/");
		rp->setResourceGroupDirectory("fonts", resDir + "/fonts/");
		rp->setResourceGroupDirectory("layouts", resDir + "/layouts/");
		rp->setResourceGroupDirectory("looknfeels", resDir + "/looknfeel/");
		rp->setResourceGroupDirectory("lua_scripts", resDir + "/lua_scripts/");

		CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
		CEGUI::Scheme::setDefaultResourceGroup("schemes");
		CEGUI::Font::setDefaultResourceGroup("fonts");
		CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
		CEGUI::WindowManager::setDefaultResourceGroup("layouts");
		CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
	}

	m_context = &CEGUI::System::getSingleton().createGUIContext(m_renderer->getDefaultRenderTarget());
	m_root = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "root");
	m_context->setRootWindow(m_root);

	loadScheme(schemeFile);
	addFont(m_defaultFontName, m_defaultFontSize);
	if (mouseImageFile != "")
	{
		setMouseCursor(mouseImageFile);
		showMouseCursor(true);
		SDL_ShowCursor(0);
	}
}

GUIEngine::~GUIEngine()
{
	CEGUI::System::getSingleton().destroyGUIContext(*m_context);
	CEGUI::WindowManager::getSingleton().destroyWindow(m_root);
	m_context = nullptr;
	m_root = nullptr;
}

CEGUI::Key::Scan SDLKeyToCEGUIKey(SDL_Keycode key) {
	using namespace CEGUI;
	switch (key) {
	case SDLK_BACKSPACE:    return Key::Backspace;
	case SDLK_TAB:          return Key::Tab;
	case SDLK_RETURN:       return Key::Return;
	case SDLK_PAUSE:        return Key::Pause;
	case SDLK_ESCAPE:       return Key::Escape;
	case SDLK_SPACE:        return Key::Space;
	case SDLK_COMMA:        return Key::Comma;
	case SDLK_MINUS:        return Key::Minus;
	case SDLK_PERIOD:       return Key::Period;
	case SDLK_SLASH:        return Key::Slash;
	case SDLK_0:            return Key::Zero;
	case SDLK_1:            return Key::One;
	case SDLK_2:            return Key::Two;
	case SDLK_3:            return Key::Three;
	case SDLK_4:            return Key::Four;
	case SDLK_5:            return Key::Five;
	case SDLK_6:            return Key::Six;
	case SDLK_7:            return Key::Seven;
	case SDLK_8:            return Key::Eight;
	case SDLK_9:            return Key::Nine;
	case SDLK_COLON:        return Key::Colon;
	case SDLK_SEMICOLON:    return Key::Semicolon;
	case SDLK_EQUALS:       return Key::Equals;
	case SDLK_LEFTBRACKET:  return Key::LeftBracket;
	case SDLK_BACKSLASH:    return Key::Backslash;
	case SDLK_RIGHTBRACKET: return Key::RightBracket;
	case SDLK_a:            return Key::A;
	case SDLK_b:            return Key::B;
	case SDLK_c:            return Key::C;
	case SDLK_d:            return Key::D;
	case SDLK_e:            return Key::E;
	case SDLK_f:            return Key::F;
	case SDLK_g:            return Key::G;
	case SDLK_h:            return Key::H;
	case SDLK_i:            return Key::I;
	case SDLK_j:            return Key::J;
	case SDLK_k:            return Key::K;
	case SDLK_l:            return Key::L;
	case SDLK_m:            return Key::M;
	case SDLK_n:            return Key::N;
	case SDLK_o:            return Key::O;
	case SDLK_p:            return Key::P;
	case SDLK_q:            return Key::Q;
	case SDLK_r:            return Key::R;
	case SDLK_s:            return Key::S;
	case SDLK_t:            return Key::T;
	case SDLK_u:            return Key::U;
	case SDLK_v:            return Key::V;
	case SDLK_w:            return Key::W;
	case SDLK_x:            return Key::X;
	case SDLK_y:            return Key::Y;
	case SDLK_z:            return Key::Z;
	case SDLK_DELETE:       return Key::Delete;
	case SDLK_KP_PERIOD:    return Key::Decimal;
	case SDLK_KP_DIVIDE:    return Key::Divide;
	case SDLK_KP_MULTIPLY:  return Key::Multiply;
	case SDLK_KP_MINUS:     return Key::Subtract;
	case SDLK_KP_PLUS:      return Key::Add;
	case SDLK_KP_ENTER:     return Key::NumpadEnter;
	case SDLK_KP_EQUALS:    return Key::NumpadEquals;
	case SDLK_UP:           return Key::ArrowUp;
	case SDLK_DOWN:         return Key::ArrowDown;
	case SDLK_RIGHT:        return Key::ArrowRight;
	case SDLK_LEFT:         return Key::ArrowLeft;
	case SDLK_INSERT:       return Key::Insert;
	case SDLK_HOME:         return Key::Home;
	case SDLK_END:          return Key::End;
	case SDLK_PAGEUP:       return Key::PageUp;
	case SDLK_PAGEDOWN:     return Key::PageDown;
	case SDLK_F1:           return Key::F1;
	case SDLK_F2:           return Key::F2;
	case SDLK_F3:           return Key::F3;
	case SDLK_F4:           return Key::F4;
	case SDLK_F5:           return Key::F5;
	case SDLK_F6:           return Key::F6;
	case SDLK_F7:           return Key::F7;
	case SDLK_F8:           return Key::F8;
	case SDLK_F9:           return Key::F9;
	case SDLK_F10:          return Key::F10;
	case SDLK_F11:          return Key::F11;
	case SDLK_F12:          return Key::F12;
	case SDLK_F13:          return Key::F13;
	case SDLK_F14:          return Key::F14;
	case SDLK_F15:          return Key::F15;
	case SDLK_RSHIFT:       return Key::RightShift;
	case SDLK_LSHIFT:       return Key::LeftShift;
	case SDLK_RCTRL:        return Key::RightControl;
	case SDLK_LCTRL:        return Key::LeftControl;
	case SDLK_RALT:         return Key::RightAlt;
	case SDLK_LALT:         return Key::LeftAlt;
	case SDLK_SYSREQ:       return Key::SysRq;
	case SDLK_MENU:         return Key::AppMenu;
	case SDLK_POWER:        return Key::Power;
	default:                return Key::Unknown;
	}
}

CEGUI::MouseButton SDLButtonToCEGUIButton(Uint8 sdlButton) {
	switch (sdlButton) {
	case SDL_BUTTON_LEFT: return CEGUI::MouseButton::LeftButton;
	case SDL_BUTTON_MIDDLE: return CEGUI::MouseButton::MiddleButton;
	case SDL_BUTTON_RIGHT: return CEGUI::MouseButton::RightButton;
	case SDL_BUTTON_X1: return CEGUI::MouseButton::X1Button;
	case SDL_BUTTON_X2: return CEGUI::MouseButton::X2Button;
	}
	return CEGUI::MouseButton::NoButton;
}

void GUIEngine::processInput(SDL_Event& e)
{
	CEGUI::utf32 codePoint;
	std::string evntText = std::string(e.text.text);
	std::vector<int> utf32result;
	switch (e.type)
	{
	case SDL_KEYDOWN:
		m_context->injectKeyDown(SDLKeyToCEGUIKey(e.key.keysym.sym));
		break;
	case SDL_KEYUP:
		m_context->injectKeyUp(SDLKeyToCEGUIKey(e.key.keysym.sym));
		break;
	case SDL_MOUSEBUTTONDOWN:
		m_context->injectMouseButtonDown(SDLButtonToCEGUIButton(e.button.button));
		break;
	case SDL_MOUSEBUTTONUP:
		m_context->injectMouseButtonUp(SDLButtonToCEGUIButton(e.button.button));
		break;
	case SDL_MOUSEMOTION:
		m_context->injectMousePosition((float)e.motion.x, (float)e.motion.y);
		break;
	case SDL_TEXTINPUT:
		utf8::utf8to32(e.text.text, e.text.text + evntText.size(), std::back_inserter(utf32result));
		codePoint = (CEGUI::utf32)utf32result[0];
		m_context->injectChar(codePoint);
		break;
	default:
		break;
	}
}

void GUIEngine::update()
{
	double elapsed;
	if (m_lastTime == 0)
	{
		elapsed = 0;
		m_lastTime = Time::getTime();
	}
	else
	{
		double nextTime = Time::getTime();
		elapsed = nextTime - m_lastTime;
		m_lastTime = nextTime;
	}
	m_context->injectTimePulse((float)elapsed / 1000.0f);
}

void GUIEngine::render()
{
	glDisable(GL_DEPTH_CLAMP);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	m_renderer->beginRendering();
	m_context->draw();
	m_renderer->endRendering();

	glBindVertexArray(0);
	glDisable(GL_SCISSOR_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);
}

void GUIEngine::setMouseCursor(const std::string& imageFile)
{
	m_context->getMouseCursor().setDefaultImage(imageFile);
}

void GUIEngine::showMouseCursor(bool value)
{
	if (value)
	{
		m_context->getMouseCursor().show();
	}
	else
	{
		m_context->getMouseCursor().hide();
	}
}

void GUIEngine::loadScheme(const std::string& schemeFile)
{
	CEGUI::SchemeManager::getSingleton().createFromFile(schemeFile);
	auto sp = Utility::split(schemeFile, '.');
	m_schemeStyle = sp[0];
}

void GUIEngine::addFont(const std::string& fontName, Uint8 size)
{
	m_defaultFontName = fontName;
	m_defaultFontSize = size;
	CEGUI::FontManager::getSingleton().createFromFile(m_defaultFontName + "-" + std::to_string(m_defaultFontSize) + ".font");
	m_context->setDefaultFont(m_defaultFontName + "-" + std::to_string(m_defaultFontSize));
}

void GUIEngine::setFontSize(Uint8 size /*= 10*/)
{
	m_defaultFontSize = size;
	CEGUI::FontManager::getSingleton().createFromFile(m_defaultFontName + "-" + std::to_string(m_defaultFontSize) + ".font");
	m_context->setDefaultFont(m_defaultFontName + "-" + std::to_string(m_defaultFontSize));
}

CEGUI::Window* GUIEngine::addWidget(const std::string& type, const PxVec4& destRectPerc, const PxVec4& destRectPix, const std::string& name/* = ""*/)
{
	CEGUI::Window* newWindow = CEGUI::WindowManager::getSingleton().createWindow(type, name);
	m_root->addChild(newWindow);
	setWidgetDestRect(newWindow, destRectPerc, destRectPix);
	return newWindow;
}

CEGUI::Window* GUIEngine::addWidget(CEGUI::Window* parent, const std::string& type, const PxVec4& destRectPerc, const PxVec4& destRectPix, const std::string& name/* = ""*/)
{
	CEGUI::Window* newWindow = CEGUI::WindowManager::getSingleton().createWindow(type, name);
	parent->addChild(newWindow);
	setWidgetDestRect(newWindow, destRectPerc, destRectPix);
	return newWindow;
}

void GUIEngine::setWidgetDestRect(CEGUI::Window* widget, const PxVec4& destRectPerc, const PxVec4& destRectPix)
{
	widget->setPosition(CEGUI::UVector2(CEGUI::UDim(destRectPerc.x, destRectPix.x), CEGUI::UDim(destRectPerc.y, destRectPix.y)));
	widget->setSize(CEGUI::USize(CEGUI::UDim(destRectPerc.z, destRectPix.z), CEGUI::UDim(destRectPerc.w, destRectPix.w)));
}
