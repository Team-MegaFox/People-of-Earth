#include "Camera3D.h"
#include "..\Core\CoreEngine.h"
#include "RenderingEngine.h"

glm::mat4 Camera3D::getViewProjection() const
{
	glm::mat4 cameraRot(glm::conjugate(getTransform().getTransformedRot()));
	glm::mat4 cameraTrans = initTranslation(-getTransform().getTransformedPos());

	return m_projection * cameraRot * cameraTrans;
}

void CameraComponent::addToEngine(CoreEngine * engine) const
{
	engine->getRenderingEngine()->setMainCamera(m_camera);
}

void CameraComponent::setParent(GameObject* parent)
{
	GameComponent::setParent(parent);
	m_camera.setTransform(getTransform());
}
