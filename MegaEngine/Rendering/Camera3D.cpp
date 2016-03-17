// ***********************************************************************
// Author           : Pavan Jakhu, Jesse Derochie, and Christopher Maeda
// Created          : 09-15-2015
//
// Last Modified By : Christopher Maeda
// Last Modified On : 03-17-2016
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

EnclosureType Camera3D::isInisde(const PxVec3& centre, const float radius) const
{
	float distance;
	EnclosureType result = EnclosureType::INSIDE;

	for (size_t i = 0; i < m_frustum.size(); i++)
	{
		distance = (m_frustum[i].distance(centre));
		if (distance < -radius) return EnclosureType::OUTSIDE;
		else if (distance < radius) result = EnclosureType::OVERLAP;
	}
	return result;
}

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

void Camera3D::setFrustum()
{
	PxReal tang = tanf(m_fov * 0.5f);
	PxReal nearHt = m_near * tang;
	PxReal nearWd = nearHt * m_aspect;
	PxReal farHt = m_far * tang;
	PxReal farWd = farHt * m_aspect;

	//Our view of the game is backward which is why we are rotating 180
	PxVec3 viewDirection = Utility::getForward(getTransform()->getTransformedRot() * PxQuat(PxSin(0.5f * ToRadians(180.0f)), 0, 0, PxCos(0.5f * ToRadians(180.0f))));
	PxVec3 rightDirection = Utility::getRight(getTransform()->getTransformedRot() * PxQuat(PxSin(0.5f * ToRadians(180.0f)), 0, 0, PxCos(0.5f * ToRadians(180.0f))));
	PxVec3 upDirection = Utility::getUp(getTransform()->getTransformedRot() * PxQuat(PxSin(0.5f * ToRadians(180.0f)), 0, 0, PxCos(0.5f * ToRadians(180.0f))));

	PxVec3 nearCentre = getTransform()->getTransformedPos() - (viewDirection * m_near);
	PxVec3 farCentre = getTransform()->getTransformedPos() - (viewDirection * m_far);

	PxVec3 ntl = nearCentre + upDirection * nearHt - rightDirection * nearWd;
	PxVec3 ntr = nearCentre + upDirection * nearHt + rightDirection * nearWd;
	PxVec3 nbl = nearCentre - upDirection * nearHt - rightDirection * nearWd;
	PxVec3 nbr = nearCentre - upDirection * nearHt + rightDirection * nearWd;

	PxVec3 ftl = farCentre + upDirection * farHt - rightDirection * farWd;
	PxVec3 ftr = farCentre + upDirection * farHt + rightDirection * farWd;
	PxVec3 fbl = farCentre - upDirection * farHt - rightDirection * farWd;
	PxVec3 fbr = farCentre - upDirection * farHt + rightDirection * farWd;

	m_frustum[0] = PxPlane(ntl, ntr, nbr);
	m_frustum[1] = PxPlane(ftr, ftl, fbl);
	m_frustum[2] = PxPlane(ntr, ntl, ftl);
	m_frustum[3] = PxPlane(nbl, nbr, fbr);
	m_frustum[4] = PxPlane(ntl, nbl, fbl);
	m_frustum[5] = PxPlane(nbr, ntr, fbr);
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