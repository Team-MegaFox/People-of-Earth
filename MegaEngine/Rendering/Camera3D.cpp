// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Jesse Derochie
// Last Modified On : 03-01-2016
// ***********************************************************************
// <copyright file="Camera3D.cpp" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#include "Camera3D.h"
#include "RenderingEngine.h"
#include "..\Core\CoreEngine.h"
#include "..\Physics\PhysicsEngine.h"

PxMat44 Camera3D::getViewProjection() const
{
	//This comes from the conjugate rotation because the world should appear to rotate
	//opposite to the camera's rotation.
	PxMat44 cameraRotation = PxMat44(getTransform().getTransformedRot().getConjugate());
	PxMat44 cameraTranslation;

	//Similarly, the translation is inverted because the world appears to move opposite
	//to the camera's movement.
	cameraTranslation = Utility::initTranslation(getTransform().getTransformedPos() * -1);

	return m_projection * cameraRotation * cameraTranslation;
}

PxMat44 Camera3D::getView() const
{
	return m_projection * PxMat44(getTransform().getTransformedRot().getConjugate());
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