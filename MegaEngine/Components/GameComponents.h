#pragma once

#include "..\Core\Transform.h"
#include "..\Core\GameObject.h"
#include "..\Core\InputManager.h"
class RenderingEngine;
class Shader;

class GameComponent
{
public:
	GameComponent() :
		m_parent(0) {}
	virtual ~GameComponent() {}

	virtual void processInput(const InputManager& input, float delta) {}
	virtual void update(float delta) {}
	virtual void render(const Shader& shader, const RenderingEngine& renderingEngine, const Camera3D & camera) const {}

	virtual void addToEngine(CoreEngine* engine) const { }

	inline Transform * getTransform()             { return m_parent->getTransform(); }
	inline const Transform & getTransform() const { return *m_parent->getTransform(); }
	virtual void setParent(GameObject* parent) { m_parent = parent; }
private:
	GameObject* m_parent;

	GameComponent(const GameComponent& other) {}
	void operator=(const GameComponent& other) {}
};