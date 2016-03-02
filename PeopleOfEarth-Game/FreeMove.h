#pragma once

#include <Components\GameComponents.h>
#include <SDL2\SDL.h>
#include <PhysX\PxPhysicsAPI.h>
using namespace physx;

class FreeMove : public GameComponent
{
public:
	FreeMove(float speed = 10.0f, int forwardKey = SDLK_w, int backKey = SDLK_s, int leftKey = SDLK_a, int rightKey = SDLK_d) :
		m_speed(speed),
		m_forwardKey(forwardKey),
		m_backKey(backKey),
		m_leftKey(leftKey),
		m_rightKey(rightKey) {}

	virtual void processInput(const InputManager& input, float delta) override;
protected:
private:
	void Move(const PxVec3& direction, float amt);

	float m_speed;
	int m_forwardKey;
	int m_backKey;
	int m_leftKey;
	int m_rightKey;
};
