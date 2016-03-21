// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 01-24-2016
// ***********************************************************************
// <copyright file="CoreEngine.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once

class PhysicsEngine;
class RenderingEngine;
class GUIEngine;
class SceneManager;
class Viewport;
class AudioEngine;

/// <summary>
/// The class that links all the different engines together. It also starts and ends the game loop
/// </summary>
class CoreEngine
{
public:
	/// <summary>
	/// Contructs CoreEngine and initilaizes the starting scene.
	/// </summary>
	/// <param name='frameRate'>The frame rate cap.</param>
	/// <param name='viewport'>The screen viewport object.</param>
	/// <param name='renderingEngine'>The rendering engine object.</param>
	/// <param name='physicsEngine'>The physics engine object.</param>
	/// <param name='audioEngine'>The audio engine object.</param>
	/// <param name='guiEngine'>The GUI engine object.</param>
	/// <param name='sceneManager'>The scene manager object.</param>
	CoreEngine(double frameRate, Viewport* viewport, 
		RenderingEngine* renderingEngine, PhysicsEngine* physicsEngine, AudioEngine* audioEngine, GUIEngine* guiEngine, 
		SceneManager* sceneManager);

	/// <summary>
	/// Starts the game loop.
	/// </summary>
	void start();
	/// <summary>
	/// Stops the game loop.
	/// </summary>
	void stop();

	/// <summary>
	/// Gets the scene manager object from the core engine.
	/// </summary>
	/// <returns>A pointer to the scene manager.</returns>
	inline SceneManager* getSceneManager() const { return m_sceneManager; }
	/// <summary>
	/// Gets the rendering engine from the core engine.
	/// </summary>
	/// <returns>A ponter to the rendering engine.</returns>
	inline RenderingEngine* getRenderingEngine() const { return m_renderingEngine; }
	/// <summary>
	/// Gets the physics engine from the core engine.
	/// </summary>
	/// <returns>A pointer to the physics engine.</returns>
	inline PhysicsEngine* getPhysicsEngine() const { return m_physicsEngine; }
	/// <summary>
	/// Gets the audio engine from the core engine.
	/// </summary>
	/// <returns>A pointer to the physics engine.</returns>
	inline AudioEngine* getAudioEngine() const { return m_audioEngine; }
	/// <summary>
	/// Gets the GUI engine from the core engine.
	/// </summary>
	/// <returns>A pointer to the GUI engine</returns>
	inline GUIEngine* getGUIEngine() const { return m_guiEngine; }
	/// <summary>
	/// Gets the viewport screen from the core engine.
	/// </summary>
	/// <returns>A pointer to the viewport screen.</returns>
	inline Viewport* getViewport() const { return m_viewport; }

private:
	/// <summary>
	/// If the engine is running.
	/// </summary>
	bool m_running = false;
	/// <summary>
	/// Holds the frame rate cap.
	/// </summary>
	double m_frameTime = 60.0;

	/// <summary>
	/// Points to the viewport object.
	/// </summary>
	Viewport* m_viewport = nullptr;
	/// <summary>
	/// Points to the scene manager object.
	/// </summary>
	SceneManager* m_sceneManager = nullptr;
	/// <summary>
	/// Points to the rendering engine object.
	/// </summary>
	RenderingEngine* m_renderingEngine = nullptr;
	/// <summary>
	/// Points to the physics engine object.
	/// </summary>
	PhysicsEngine* m_physicsEngine = nullptr;
	/// <summary>
	/// Points to the audio engine object.
	/// </summary>
	AudioEngine* m_audioEngine = nullptr;
	/// <summary>
	/// Points to the GUI engine object.
	/// </summary>
	GUIEngine* m_guiEngine = nullptr;

};

