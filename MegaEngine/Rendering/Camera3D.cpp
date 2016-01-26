// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Deroiche
// Created          : 09-15-2015
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 01-24-2016
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
