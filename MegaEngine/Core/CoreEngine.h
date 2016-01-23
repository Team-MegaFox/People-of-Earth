#pragma once

class PhysicsEngine;
class RenderingEngine;
class GUIEngine;
class SceneManager;
class Viewport;
class AudioEngine;

class CoreEngine
{
public:
	CoreEngine(double frameRate, Viewport* viewport, 
		RenderingEngine* renderingEngine, PhysicsEngine* physicsEngine, AudioEngine* audioEngine, GUIEngine* guiEngine, 
		SceneManager* sceneManager);

	void start();
	void stop();

	inline SceneManager* getSceneManager() const { return m_sceneManager; }
	inline RenderingEngine* getRenderingEngine() const { return m_renderingEngine; }
	inline PhysicsEngine* getPhysicsEngine() const { return m_physicsEngine; }
	inline AudioEngine* getAudioEngine() const { return m_audioEngine; }
	inline GUIEngine* getGUIEngine() const { return m_guiEngine; }
	inline Viewport* getViewport() const { return m_viewport; }

private:
	bool m_running = false;
	double m_frameTime = 60.0;

	Viewport* m_viewport = nullptr;
	SceneManager* m_sceneManager = nullptr;
	RenderingEngine* m_renderingEngine = nullptr;
	PhysicsEngine* m_physicsEngine = nullptr;
	AudioEngine* m_audioEngine = nullptr;
	GUIEngine* m_guiEngine = nullptr;

};

