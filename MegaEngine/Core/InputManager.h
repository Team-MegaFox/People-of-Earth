// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Jesse Derochie
// Last Modified On : 03-01-2016
// ***********************************************************************
// <copyright file="InputManager.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once
#include <unordered_map>
#include <SDL2\SDL.h>
#include <PhysX/PxPhysicsAPI.h>

class Viewport;
///<summary>
/// Stores all inputs into a manager for ease of access.
/// </summary>
class InputManager
{
public:
	/// <summary>
	/// Creates an InputManager and sets the gamepad controller.
	/// </summary>
	/// <param name='window'>The viewport window pointer</param>
	InputManager(Viewport* window);	
	/// <summary>
	/// Closes the controller, destroys it.
	/// </summary>
	~InputManager();
	/// <summary>
	/// Updates everything for inputs.
	/// </summmary>
	/// <param name='_inputEvent'>Reference to the input events.</param>
	bool Update(SDL_Event& _inputEvent);	
	/// <summary>
	/// If the key is down this frame.
	/// </summary>
	/// <returns>True if the key is down this frame.</returns>
	const bool getKeyDownState();
	/// <summary>
	/// If the key is up this frame.
	/// </summary>
	/// <returns>True if the key is up this frame.</returns>
	const bool getKeyUpState();
	/// <summary>
	/// Gets the key code.
	/// </summary>
	/// <returns>The SDL keycode that was pressed this frame.</returns>
	SDL_Keycode getKeyCode();
	/// <summary>
	/// Checks if the key is held down.
	/// </summary>
	/// <param name'_key'>A keyboard key.</param>
	/// <returns>If that key is dwon.</returns>
	const bool KeyDown(Uint8 _key) const;
	/// <summary>
	/// Checks if the key is up.
	/// </summary>
	/// <param name='_key'>A keyboard key.</param>
	/// <returns>If that key was up.</returns>
	const bool KeyUp(Uint8 _key) const;
	/// <summary>
	/// Checks if the key was pressed.
	/// </summary>
	/// <param name='_key'>A keyboard key.</param>
	/// <returns>If that key was pressed.</returns>
	const bool KeyPress(Uint8 _key) const;
	
	/// <summary>
	/// If the mouse button is up this frame.
	/// </summary>
	/// <returns>True if the mouse button is up this frame.</returns>
	const bool getMouseUpState();
	/// <summary>
	/// If the mouse button is down this frame.
	/// </summary>
	/// <returns>True if the mouse button is down this frame.</returns>
	const bool getMouseDownState();	
	/// <summary>
	/// Gets the mouse button up or down this frame..
	/// </summary>
	/// <returns>The mouse button up or down this frame.</returns>
	Uint8 getMouseButton();
	/// <summary>
	/// Checks if the mouse was held down.
	/// </summary>
	/// <param name='_button'>A mouse button.</param>
	/// <returns>If that mouse button was down.</returns>
	const bool MouseButtonDown(Uint8 _button) const;
	/// <summary>
	/// Checks if the mouse was held up.
	/// </summary>
	/// <param name='button'>A mouse button.</param>
	/// <returns>If that mouse button was up.</returns>
	const bool MouseButtonUp(Uint8 _button) const;
	/// <summary>
	/// Checks if the mouse was pressed.
	/// </summary>
	/// <param name='_button'>A mouse button.</param>
	/// <returns>If that mouse button was pressed.</returns>
	const bool MouseButtonPress(Uint8 _button) const;
	/// <summary>
	/// Checks if the mouse has moved.
	/// </summary>
	/// <returns>If the moved mouse.</returns>
	const bool MouseMoved() const;
	/// <summary>
	/// Gets the mouse position on screen.
	/// </summary>
	/// <returns>The mouse position.</returns>
	const physx::PxVec2 GetMousePosition() const;
	/// <summary>
	/// Sets the mouse position manually.
	/// </summary>
	/// <param name='pos'>The position where the mouse cursor should be.</param>
	void SetMousePosition(const physx::PxVec2& pos) const;
	/// <summary>
	/// Sets the mouse cursor to be visible.
	/// </summary>
	/// <param name='visible'>If the mouse cursor is visible or not.</param>
	void SetCursor(bool visible) const;

	/// <summary>
	/// Checks if the gamepad button was held down.
	/// </summary>
	/// <param name='_button'>A game pad button.</param>
	/// <returns>If the button was held down.</returns>
	const bool PadButtonDown(Uint8 _button) const;
	/// <summary>
	/// Checks if the gamepad button was up.
	/// </summary>
	/// <param name='_button'>A game pad button.</param>
	/// <returns>If the button was up.</returns>
	const bool PadButtonUp(Uint8 _button) const;
	/// <summary>
	/// Checks if the gamepad button was pressed.
	/// </summary>
	/// <param name='_button'>A game pad button.</param>
	/// <returns>If the button was pressed.</returns>
	const bool PadButtonPress(Uint8 _button) const;
	/// <summary>
	/// Checks if the left gamepad thumbstick moved.
	/// </summary>
	/// <returns>If the left gamepad thumbstick moved.</returns>
	const bool ThumbLMoved() const;
	/// <summary>
	/// Gets the left thumbstick position.
	/// </summary>
	/// <returns>The left thumbstick position.</returns>
	const physx::PxVec2 GetThumbLPosition() const;
	/// <summary>
	/// Checks if the right gamepad thumbstick moved.
	/// </summary>
	/// <returns>If the right gamepad thumbstick moved.</returns>
	const bool ThumbRMoved() const;
	/// <summary>
	/// Gets the right thumbstick position.
	/// </summary>
	/// <returns>The right thumbstick position.</returns>
	const physx::PxVec2 GetThumbRPosition() const;
	/// <summary>
	/// Gets the left trigger depth.
	/// </summary>
	/// <returns>The left trigger value.</returns>
	const float GetLeftTrigger() const;
	/// <summary>
	/// Gets the right trigger depth.
	/// </summary>
	/// <returns>he right trigger depth.</returns>
	const float GetRightTrigger() const;
	
	char* getTextInput();
	/// <summary>
	/// Determines whether there is text input.
	/// </summary>
	/// <returns>If there is text input.</returns>
	const bool getTextInputState();

private:	
	/// <summary>
	/// If a key is down this frame.
	/// </summary>
	bool keyDownState;	
	/// <summary>
	/// If a key is up this frame.
	/// </summary>
	bool keyUpState;	
	/// <summary>
	/// The key that is up or down this frame.
	/// </summary>
	SDL_Keycode keyCode;
	/// <summary>
	/// Map of the previous key states.
	/// </summary>
	std::unordered_map<Uint32, bool> prevKeyStates;
	/// <summary>
	/// Map of the current key states.
	/// </summary>
	std::unordered_map<Uint32, bool> currKeyStates;	
	
	/// <summary>
	/// If the mouse button is up this frame.
	/// </summary>
	bool mouseUpState;	
	/// <summary>
	/// If the mouse button is down this frame.
	/// </summary>
	bool mouseDownState;	
	/// <summary>
	/// The mouse button up or down this frame.
	/// </summary>
	Uint8 mouseButton;
	/// <summary>
	/// The previous mouse button states.
	/// </summary>
	bool prevMouseButtonStates[5];
	/// <summary>
	/// The current mouse button states.
	/// </summary>
	bool currMouseButtonStates[5];
	/// <summary>
	/// The mouse position.
	/// </summary>
	physx::PxVec2 mousePos;
	/// <summary>
	/// Returns true if the mouse has moved.
	/// </summary>
	bool mouseMoved;

	/// <summary>
	/// The controller.
	/// </summary>
	SDL_GameController* controller;
	/// <summary>
	/// Map of the previous gamepad button states.
	/// </summary>
	std::unordered_map<Uint32, bool> prevPadButtonStates;
	/// <summary>
	/// Map of the current gamepad button states.
	/// </summary>
	std::unordered_map<Uint32, bool> currPadButtonStates;
	/// <summary>
	/// Returns true if the left thumbstick was moved.
	/// </summary>
	bool thumbLMoved;
	/// <summary>
	/// Stores the left thumbstick position.
	/// </summary>
	physx::PxVec2 thumbLPos;
	/// <summary>
	/// Returns true if the right thumbstick has moved.
	/// </summary>
	bool thumbRMoved;
	/// <summary>
	/// Stores the right thumbstick position.
	/// </summary>
	physx::PxVec2 thumbRPos;
	/// <summary>
	/// Gets the left trigger.
	/// </summary>
	float leftTrigger;
	/// <summary>
	/// Gets the right trigger.
	/// </summary>
	float rightTrigger;
		
	/// <summary>
	/// The text inputted this frame.
	/// </summary>
	char* text;
	/// <summary>
	/// Is there text input this frame?
	/// </summary>
	bool textInputState;

	/// <summary>
	/// The pointer to a viewport window object.
	/// </summary>
	Viewport* m_window;

};
