// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Deroiche
// Created          : 09-15-2015
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 01-24-2016
// ***********************************************************************
// <copyright file="InputManager.cpp" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#include "InputManager.h"
#include "..\Rendering\Viewport.h"
#include <string>

InputManager::InputManager(Viewport* window)
	: m_window(window)
{
	controller = SDL_GameControllerOpen(0);
	if (controller == nullptr)
	{

	}
}

InputManager::~InputManager()
{
	SDL_GameControllerClose(controller);
	controller = nullptr;
}

bool InputManager::Update(SDL_Event& _inputEvent)
{
	// takes care of setting the previouskey, button, and gamepad states.
	//stes the mouse and thumbstick movement to false
	keyDownState = keyUpState = false;
	keyCode = -1;
	for (auto& it : currKeyStates)
	{
		prevKeyStates[it.first] = it.second;
	}
	for (int i = 0; i < 5; i++)
	{
		prevMouseButtonStates[i] = currMouseButtonStates[i];
	}
	mouseDownState = mouseUpState = false;
	mouseMoved = false;
	for (auto& it : currPadButtonStates)
	{
		prevPadButtonStates[it.first] = it.second;
	}
	thumbLMoved = false;
	thumbRMoved = false;
	text = nullptr;
	textInputState = false;

	//checks to see if an input event has occurred and then checks the type of key or button pressed
	//also checks in case the mouse has moved and sets it to true
	while (SDL_PollEvent(&_inputEvent))
	{
		switch (_inputEvent.type)
		{
		case SDL_QUIT:
			return true;
		case SDL_KEYDOWN:
			keyDownState = true;
			keyCode = _inputEvent.key.keysym.sym;
			currKeyStates[_inputEvent.key.keysym.sym] = true;
			break;
		case SDL_KEYUP:
			keyUpState = true;
			keyCode = _inputEvent.key.keysym.sym;
			currKeyStates[_inputEvent.key.keysym.sym] = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			mouseButton = _inputEvent.button.button;
			mouseDownState = true;
			currMouseButtonStates[_inputEvent.button.button - 1] = true;
			break;
		case SDL_MOUSEBUTTONUP:
			mouseButton = _inputEvent.button.button;
			mouseUpState = true;
			currMouseButtonStates[_inputEvent.button.button - 1] = false;
			break;
		case SDL_MOUSEMOTION:
			mouseMoved = true;
			mousePos.x = (float)_inputEvent.motion.x;
			mousePos.y = (float)_inputEvent.motion.y;
			break;
		case SDL_CONTROLLERBUTTONDOWN:
			currPadButtonStates[_inputEvent.cbutton.button - 1] = true;
			break;
		case SDL_CONTROLLERBUTTONUP:
			currPadButtonStates[_inputEvent.cbutton.button - 1] = false;
			break;
			//sets the thumbstick motion to true and then finds the position of the thumbstick movement.
			//does this also for the triggers
		case SDL_CONTROLLERAXISMOTION:
			thumbLMoved = true;
			thumbRMoved = true;
			thumbLPos.x = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX) / 32767.0f;
			thumbLPos.y = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY) / -32767.0f;
			thumbRPos.x = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX) / 32767.0f;
			thumbRPos.y = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY) / -32767.0f;
			rightTrigger = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT) / 32767.0f;
			leftTrigger = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT) / 32767.0f;
			break;
		case SDL_TEXTINPUT:
			text = _inputEvent.text.text;
			textInputState = true;
			break;
		default:
			break;
		}
	}
	return false;
}

const bool InputManager::getKeyDownState()
{
	return keyDownState;
}

const bool InputManager::getKeyUpState()
{
	return keyUpState;
}

SDL_Keycode InputManager::getKeyCode()
{
	return keyCode;
}

const bool InputManager::KeyDown(Uint8 _key) const
{
	if (!currKeyStates.empty())
		if (currKeyStates.find(_key) != currKeyStates.end())
			return currKeyStates.at(_key);
		else return false;
	else return false;
}

const bool InputManager::KeyUp(Uint8 _key) const
{
	if (!currKeyStates.empty())
		if (currKeyStates.find(_key) != currKeyStates.end())
			return !currKeyStates.at(_key);
		else return false;
	else return false;
}

const bool InputManager::KeyPress(Uint8 _key) const
{
	if (!currKeyStates.empty() && !prevKeyStates.empty())
		if (currKeyStates.find(_key) != currKeyStates.end() && prevKeyStates.find(_key) != prevKeyStates.end())
			return prevKeyStates.at(_key) && !currKeyStates.at(_key);
		else return false;
	else return false;
}

const bool InputManager::getMouseUpState()
{
	return mouseUpState;
}

const bool InputManager::getMouseDownState()
{
	return mouseDownState;
}

Uint8 InputManager::getMouseButton()
{
	return mouseButton;
}

const bool InputManager::MouseButtonDown(Uint8 _button) const
{
	return currMouseButtonStates[_button - 1];
}

const bool InputManager::MouseButtonUp(Uint8 _button) const
{
	return !currMouseButtonStates[_button - 1];
}

const bool InputManager::MouseButtonPress(Uint8 _button) const
{
	return prevMouseButtonStates[_button - 1] && !currMouseButtonStates[_button - 1];
}

const bool InputManager::MouseMoved() const
{
	return mouseMoved;
}

const glm::vec2 InputManager::GetMousePosition() const
{
	return mousePos;
}

void InputManager::SetCursor(bool visible) const
{
	if (visible)
		SDL_ShowCursor(1);
	else
		SDL_ShowCursor(0);
	

}

void InputManager::SetMousePosition(const glm::vec2& pos) const
{
	SDL_WarpMouseInWindow(m_window->getWindow(), (int)pos.x, (int)pos.y);
}

const bool InputManager::PadButtonDown(Uint8 _button) const
{
	if (!currPadButtonStates.empty())
		return currPadButtonStates.at(_button - 1);
	else return false;
}

const bool InputManager::PadButtonUp(Uint8 _button) const
{
	if (!currPadButtonStates.empty())
		return !currPadButtonStates.at(_button - 1);
	else return false;
}

const bool InputManager::PadButtonPress(Uint8 _button) const
{
	if (!currPadButtonStates.empty() && !prevPadButtonStates.empty())
		return prevPadButtonStates.at(_button - 1) && !currPadButtonStates.at(_button - 1);
	else return false;
}

const bool InputManager::ThumbLMoved() const
{
	return thumbLMoved;
}

const glm::vec2 InputManager::GetThumbLPosition() const
{
	return thumbLPos;
}

const bool InputManager::ThumbRMoved() const
{
	return thumbRMoved;
}

const glm::vec2 InputManager::GetThumbRPosition() const
{
	return thumbRPos;
}

const float InputManager::GetLeftTrigger() const
{
	return leftTrigger;
}

const float InputManager::GetRightTrigger() const
{
	return rightTrigger;
}

char* InputManager::getTextInput()
{
	return text;
}

const bool InputManager::getTextInputState()
{
	return textInputState;
}
