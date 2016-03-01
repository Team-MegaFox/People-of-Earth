#include "Camera3D.h"
#include "RenderingEngine.h"
#include "..\Core\CoreEngine.h"
#include "..\Core\Utility.h"
#include "..\Physics\PhysicsEngine.h"

glm::mat4 Camera3D::getViewProjection() const
{
	//This comes from the conjugate rotation because the world should appear to rotate
	//opposite to the camera's rotation.
	glm::mat4 cameraRotation = glm::mat4_cast(glm::conjugate(getTransform().getTransformedRot()));
	glm::mat4 cameraTranslation;

	//Similarly, the translation is inverted because the world appears to move opposite
	//to the camera's movement.
	cameraTranslation = Utility::initTranslation(getTransform().getTransformedPos() * -1.0f);

	return m_projection * cameraRotation * cameraTranslation;
}

glm::mat4 Camera3D::getView() const
{
	return m_projection * glm::mat4(glm::conjugate(getTransform().getTransformedRot()));
}

void CameraComponent::addToEngine(CoreEngine* engine) const
{
	//TODO: This is probably not the correct solution in the case of multiple cameras,
	//and should be investigated in the future.
	engine->getRenderingEngine()->setMainCamera(m_camera);
	engine->getPhysicsEngine()->setMainCamera(m_camera);
}

void CameraComponent::setParent(GameObject* parent)
{
	GameComponent::setParent(parent);

	//The camera's transform is initialized here because this is the first point where
	//there is a parent object with a transform.
	m_camera.setTransform(getTransform());
}