#pragma once
#include <MegaEngine.h>
class GUIOnCamera : public GameComponent
{
public:
	GUIOnCamera() { }
	~GUIOnCamera() { }

	virtual void onStart() override;
	virtual void update(float delta) override;

private:
	GameObject* m_mainCamera;
	CameraComponent* m_mainCameraComponent;

	GameObject* m_top;
	GameObject* m_bottom;
	GameObject* m_right;
	GameObject* m_left;

	GameObject* m_topRight;
	GameObject* m_topLeft;
	GameObject* m_bottomRight;
	GameObject* m_bottomLeft;

	GUIImage* m_image;
};

