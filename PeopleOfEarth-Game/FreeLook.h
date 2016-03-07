#pragma once

#include <Components\GameComponents.h>
#include <Core\InputManager.h>

#include <SDL2\SDL.h>
#include <PhysX\PxPhysicsAPI.h>
using namespace physx;

class FreeLook : public GameComponent
{
public:
	FreeLook(const PxVec2& windowCenter, float sensitivity = 0.5f, int unlockMouseKey = SDLK_ESCAPE) :
		m_sensitivity(sensitivity),
		m_unlockMouseKey(unlockMouseKey),
		m_mouseLocked(false),
		m_windowCenter(windowCenter) {}

	virtual void processInput(const InputManager& input, float delta) override;

protected:
private:
	float    m_sensitivity;
	int      m_unlockMouseKey;
	bool     m_mouseLocked;
	PxVec2 m_windowCenter;
};

