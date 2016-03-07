// ***********************************************************************
// Author           : Pavan Jakhu, Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Jesse Derochie
// Last Modified On : 03-01-2016
// ***********************************************************************
// <copyright file="Transform.cpp" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#include "transform.h"

bool Transform::hasChanged()
{
	if (m_parent != 0 && m_parent->hasChanged())
	{
		return true;
	}

	if (m_pos != m_oldPos)
	{
		return true;
	}

	if (m_rot.x != m_oldRot.x && m_rot.y != m_oldRot.y && m_rot.z != m_oldRot.z && m_rot.w != m_oldRot.w)
	{
		return true;
	}

	if (m_scale != m_scale)
	{
		return true;
	}

	return false;
}

void Transform::update()
{
	if (m_initializedOldStuff)
	{
		m_oldPos = m_pos;
		m_oldRot = m_rot;
		m_oldScale = m_scale;
	}
	else
	{
		m_oldPos = m_pos + PxVec3(1, 1, 1);
		m_oldRot = m_rot * 0.5f;
		m_oldScale = m_scale + PxVec3(1, 1, 1);
		m_initializedOldStuff = true;
	}
}

void Transform::rotate(const PxVec3& axis, float angle)
{
	rotate(PxQuat(angle, axis));
}

void Transform::rotate(const PxQuat& rotation)
{
	m_rot = PxQuat((rotation * m_rot).getNormalized());
}

void Transform::lookAt(const PxVec3& point, const PxVec3& up)
{
	m_rot = getLookAtRotation(point, up);
}

PxMat44 Transform::getTransformation() const
{
	PxMat44 translationMatrix;
	PxMat44 scaleMatrix;

	translationMatrix = Utility::initTranslation(m_pos);
	scaleMatrix = Utility::initScale(m_scale);

	PxMat44 result = translationMatrix * PxMat44(m_rot) * scaleMatrix;

	return GetParentMatrix() * result;
}

const PxMat44& Transform::GetParentMatrix() const
{
	if (m_parent != 0 && m_parent->hasChanged())
	{
		m_parentMatrix = m_parent->getTransformation();
	}

	return m_parentMatrix;
}

PxQuat Transform::getTransformedRot() const
{
	PxQuat parentRot = PxQuat(0, 0, 0, 1);

	if (m_parent)
	{
		parentRot = m_parent->getTransformedRot();
	}
	return parentRot * m_rot;
}