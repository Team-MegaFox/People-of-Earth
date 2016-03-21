// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Jesse Derochie
// Last Modified On : 02-08-2016
// ***********************************************************************
// <copyright file="Camera3D.cpp" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#include "Camera3D.h"
#include "..\Core\CoreEngine.h"
#include "RenderingEngine.h"

glm::mat4 Camera3D::getViewProjection() const
{
	glm::mat4 cameraRot(glm::conjugate(getTransform().getTransformedRot()));
	glm::mat4 cameraTrans = Utility::initTranslation(-getTransform().getTransformedPos());

	return m_projection * cameraRot * cameraTrans;
}

glm::mat4 Camera3D::getView() const
{
	return m_projection * glm::mat4(glm::conjugate(getTransform().getTransformedRot()));
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
