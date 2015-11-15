#pragma once
#include "GameObject.h"
#include "GameComponents.h"
#include "CoreEngine.h"

class CameraComponent :
	public GameComponent
{
public:

	CameraComponent() {}
	CameraComponent(float horizontalAngle, float verticalangle, float fov, float nearPlane, float farPlane, float aspectRatio);

	virtual void setToMainCamera(CoreEngine engine) = 0;
	virtual glm::mat4 getViewProjection() = 0;
	virtual void setParent(GameObject gameObject) = 0;

};

