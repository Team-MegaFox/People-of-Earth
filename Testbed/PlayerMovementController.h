
#pragma once
#include <MegaEngine.h>

class PlayerMovementController : public GameComponent
{
public:
	PlayerMovementController(float velocityValue = 30.0f, float accelerationValue = 500.0f, int forwardKey = SDLK_w, int backKey = SDLK_s, int leftKey = SDLK_a, int rightKey = SDLK_d, int upKey = SDLK_z, int downKey = SDLK_x);
	~PlayerMovementController();

	virtual void onStart() override;

	virtual void processInput(const InputManager& input, float delta) override;

	void lookAround(const InputManager& input);

	void movement(const InputManager& input, float delta);

	void returnToActualRotation();

	void showVisualShipRotation();

	void checkLerp(const InputManager& input);

	void lerp();

private:
	RigidBody* m_rigidBody;
	CameraComponent* m_camera;

	int m_forwardKey;
	int m_backKey;
	int m_leftKey;
	int m_rightKey;
	int m_upKey;
	int m_downKey;

	float m_accelerationValue;
	float m_distance;
	float m_velocityValue;

	glm::vec3 m_shipsVisualRotation = glm::vec3(0);
	bool m_lerp_X_Axis_Ship;
	bool m_lerp_Y_Axis_Ship;
	glm::vec3 m_forwardDirection = glm::vec3(0);
};

