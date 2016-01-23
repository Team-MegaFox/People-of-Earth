#pragma once
#include <unordered_map>
#include <SDL2\SDL.h>
#include <glm\glm.hpp>

class Viewport;
class InputManager
{
public:
	/*
	*\brief Creates an InputManager and sets the gamepad controller.
	*/
	InputManager(Viewport* window);
	/*
	brief Closes the controller, destroys it.
	*/
	~InputManager();
	/*
	* \brief Updates everything for inputs.
	* \param Reference to the input events.
	*/
	bool Update(SDL_Event& _inputEvent);
	/*
	* \brief Checks if the key is held down.
	* \param A keyboard key.
	* \returns If that key was dwon.
	*/
	const bool KeyDown(Uint8 _key) const;
	/*
	* \brief Checks if the key is up.
	* \param A keyboard key.
	* \returns If that key was up.
	*/
	const bool KeyUp(Uint8 _key) const;
	/*
	* \brief Checks if the key was pressed.
	* \param A keyboard key.
	* \returns If that key was pressed.
	*/
	const bool KeyPress(Uint8 _key) const;

	/*
	* \brief Checks if the mouse was held down.
	* \param A mouse button.
	* \returns If that mouse button was down.
	*/
	const bool MouseButtonDown(Uint8 _button) const;
	/*
	* \brief Checks if the mouse was held up.
	* \param A mouse button.
	* \returns If that mouse button was up.
	*/
	const bool MouseButtonUp(Uint8 _button) const;
	/*
	* \brief Checks if the mouse was pressed.
	* \param A mouse button.
	* \returns If that mouse button was pressed.
	*/
	const bool MouseButtonPress(Uint8 _button) const;
	/*
	*\brief Checks if the mouse has moved.
	*\returns If the moved mouse.
	*/
	const bool MouseMoved() const;
	/*
	* \brief Gets the mouse position on screen.
	* \returns The mouse position.
	*/
	const glm::vec2 GetMousePosition() const;
	void SetMousePosition(const glm::vec2& pos) const;
	void SetCursor(bool visible) const;

	/*
	* \brief Checks if the gamepad button was held down.
	* \param A game pad button.
	* \returns If the button was held down.
	*/
	const bool PadButtonDown(Uint8 _button) const;
	/*
	* \brief Checks if the gamepad button was up.
	* \param A game pad button.
	* \returns If the button was up.
	*/
	const bool PadButtonUp(Uint8 _button) const;
	/*
	* \brief Checks if the gamepad button was pressed.
	* \param A game pad button.
	* \returns If the button was pressed.
	*/
	const bool PadButtonPress(Uint8 _button) const;
	/*
	* \brief Checks if the left gamepad thumbstick moved.
	* \returns If the left gamepad thumbstick moved.
	*/
	const bool ThumbLMoved() const;
	/*
	* \brief Gets the left thumbstick position.
	* \returns The left thumbstick position.
	*/
	const glm::vec2 GetThumbLPosition() const;
	/*
	* \brief Checks if the right gamepad thumbstick moved.
	* \returns If the right gamepad thumbstick moved.
	*/
	const bool ThumbRMoved() const;
	/*
	* \brief Gets the right thumbstick position.
	* \returns The right thumbstick position.
	*/
	const glm::vec2 GetThumbRPosition() const;
	/*
	* \brief Gets the left trigger depth.
	* \returns The left trigger value.
	*/
	const float GetLeftTrigger() const;
	/*
	* \brief Gets the right trigger depth.
	* \returns The right trigger depth.
	*/
	const float GetRightTrigger() const;

private:
	//Map of the previous key states.
	std::unordered_map<Uint32, bool> prevKeyStates;
	//Map of the current key states.
	std::unordered_map<Uint32, bool> currKeyStates;
	//The previous mouse button states.
	bool prevMouseButtonStates[5];
	//The current mouse button states.
	bool currMouseButtonStates[5];
	//The mouse position.
	glm::vec2 mousePos;
	//Returns true if the mouse has moved.
	bool mouseMoved;

	//The controller.
	SDL_GameController* controller;
	//Map of the previous gamepad button states.
	std::unordered_map<Uint32, bool> prevPadButtonStates;
	//Map of the current gamepad button states.
	std::unordered_map<Uint32, bool> currPadButtonStates;
	//Returns true if the left thumbstick was moved.
	bool thumbLMoved;
	//Rets the left thumbstick position.
	glm::vec2 thumbLPos;
	//Returns true if the right thumbstick has moved.
	bool thumbRMoved;
	//Gets the right thumbstick position.
	glm::vec2 thumbRPos;
	//Gets the left trigger.
	float leftTrigger;
	//Gets the right trigger.
	float rightTrigger;

	Viewport* m_window;

};
