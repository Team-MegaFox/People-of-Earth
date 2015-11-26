#include "InputManager.h"
#include "Viewport.h"
#include <string>
/*
* \brief Creates an InputManager and sets the gamepad controller.
*/
InputManager::InputManager(Viewport* window)
	: m_window(window)
{
	controller = SDL_GameControllerOpen(0);
	if (controller == nullptr)
	{

	}
}

/*
* \brief Closes the controller, destroys it.
*/
InputManager::~InputManager()
{
	SDL_GameControllerClose(controller);
	controller = nullptr;
}

/*
* \brief Updates everything for inputs.
* \param Reference to the input events.
*/
bool InputManager::Update(SDL_Event& _inputEvent)
{
	// takes care of setting the previouskey, button, and gamepad states.
	//stes the mouse and thumbstick movement to false
	for (auto& it : currKeyStates)
	{
		prevKeyStates[it.first] = it.second;
	}
	for (int i = 0; i < 5; i++)
	{
		prevMouseButtonStates[i] = currMouseButtonStates[i];
	}
	mouseMoved = false;
	for (auto& it : currPadButtonStates)
	{
		prevPadButtonStates[it.first] = it.second;
	}
	thumbLMoved = false;
	thumbRMoved = false;

	//checks to see if an input event has occurred and then checks the type of key or button pressed
	//also checks in case the mouse has moved and sets it to true
	while (SDL_PollEvent(&_inputEvent))
	{
		switch (_inputEvent.type)
		{
		case SDL_QUIT:
			return true;
		case SDL_KEYDOWN:
			currKeyStates[_inputEvent.key.keysym.sym] = true;
			break;
		case SDL_KEYUP:
			currKeyStates[_inputEvent.key.keysym.sym] = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			currMouseButtonStates[_inputEvent.button.button - 1] = true;
			break;
		case SDL_MOUSEBUTTONUP:
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
		default:
			break;
		}
	}
	return false;
}

/*
* \brief Checks if the key is held down.
* \param A keyboard key.
* \returns If that key was dwon.
*/
const bool InputManager::KeyDown(Uint8 _key) const
{
	if (!currKeyStates.empty())
		if (currKeyStates.find(_key) != currKeyStates.end())
			return currKeyStates.at(_key);
		else return false;
	else return false;
}

/*
* \brief Checks if the key is up.
* \param A keyboard key.
* \returns If that key was up.
*/
const bool InputManager::KeyUp(Uint8 _key) const
{
	if (!currKeyStates.empty())
		if (currKeyStates.find(_key) != currKeyStates.end())
			return !currKeyStates.at(_key);
		else return false;
	else return false;
}

/*
* \brief Checks if the key was pressed.
* \param A keyboard key.
* \returns If that key was pressed.
*/
const bool InputManager::KeyPress(Uint8 _key) const
{
	if (!currKeyStates.empty() && !prevKeyStates.empty())
		if (currKeyStates.find(_key) != currKeyStates.end() && prevKeyStates.find(_key) != prevKeyStates.end())
			return prevKeyStates.at(_key) && !currKeyStates.at(_key);
		else return false;
	else return false;
}

/*
* \brief Checks if the mouse was held down.
* \param A mouse button.
* \returns If that mouse button was down.
*/
const bool InputManager::MouseButtonDown(Uint8 _button) const
{
	return currMouseButtonStates[_button - 1];
}

/*
* \brief Checks if the mouse was held up.
* \param A mouse button.
* \returns If that mouse button was up.
*/
const bool InputManager::MouseButtonUp(Uint8 _button) const
{
	return !currMouseButtonStates[_button - 1];
}

/*
* \brief Checks if the mouse was pressed.
* \param A mouse button.
* \returns If that mouse button was pressed.
*/
const bool InputManager::MouseButtonPress(Uint8 _button) const
{
	return prevMouseButtonStates[_button - 1] && !currMouseButtonStates[_button - 1];
}

/*
*\brief Checks if the mouse has moved.
*\returns If the moved mouse.
*/
const bool InputManager::MouseMoved() const
{
	return mouseMoved;
}

/*
* \brief Gets the mouse position on screen.
* \returns The mouse position.
*/
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
	SDL_WarpMouseInWindow(m_window->getSDLWindow(), (int)pos.x, (int)pos.y);
}

/*
* \brief Checks if the gamepad button was held down.
* \param A game pad button.
* \returns If the button was held down.
*/
const bool InputManager::PadButtonDown(Uint8 _button) const
{
	if (!currPadButtonStates.empty())
		return currPadButtonStates.at(_button - 1);
	else return false;
}

/*
* \brief Checks if the gamepad button was up.
* \param A game pad button.
* \returns If the button was up.
*/
const bool InputManager::PadButtonUp(Uint8 _button) const
{
	if (!currPadButtonStates.empty())
		return !currPadButtonStates.at(_button - 1);
	else return false;
}

/*
* \brief Checks if the gamepad button was pressed.
* \param A game pad button.
* \returns If the button was pressed.
*/
const bool InputManager::PadButtonPress(Uint8 _button) const
{
	if (!currPadButtonStates.empty() && !prevPadButtonStates.empty())
		return prevPadButtonStates.at(_button - 1) && !currPadButtonStates.at(_button - 1);
	else return false;
}

/*
* \brief Checks if the left gamepad thumbstick moved.
* \returns If the left gamepad thumbstick moved.
*/
const bool InputManager::ThumbLMoved() const
{
	return thumbLMoved;
}

/*
* \brief Gets the left thumbstick position.
* \returns The left thumbstick position.
*/
const glm::vec2 InputManager::GetThumbLPosition() const
{
	return thumbLPos;
}

/*
* \brief Checks if the right gamepad thumbstick moved.
* \returns If the right gamepad thumbstick moved.
*/
const bool InputManager::ThumbRMoved() const
{
	return thumbRMoved;
}

/*
* \brief Gets the right thumbstick position.
* \returns The right thumbstick position.
*/
const glm::vec2 InputManager::GetThumbRPosition() const
{
	return thumbRPos;
}

/*
* \brief Gets the left trigger depth.
* \returns The left trigger value.
*/
const float InputManager::GetLeftTrigger() const
{
	return leftTrigger;
}

/*
* \brief Gets the right trigger depth.
* \returns The right trigger depth.
*/
const float InputManager::GetRightTrigger() const
{
	return rightTrigger;
}