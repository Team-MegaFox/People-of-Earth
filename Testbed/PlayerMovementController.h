#pragma once
#include <MegaEngine.h>

class PlayerMovementController : public GameComponent
{
public:
	PlayerMovementController(int forwardKey = SDLK_w, int backKey = SDLK_s, int leftKey = SDLK_a, int rightKey = SDLK_d, int upKey = SDLK_z, int downKey = SDLK_x);
	~PlayerMovementController();

	virtual void onStart() override;

	virtual void processInput(const InputManager& input, float delta) override;

private:
	RigidBody* m_rigidBody;

	int m_forwardKey;
	int m_backKey;
	int m_leftKey;
	int m_rightKey;
	int m_upKey;
	int m_downKey;
};

