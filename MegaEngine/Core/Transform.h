// ***********************************************************************
// Author           : Pavan Jakhu, Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Jesse Derochie
// Last Modified On : 03-01-2016
// ***********************************************************************
// <copyright file="Transform.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once

#include <PhysX\PxPhysicsAPI.h>
using namespace physx;
#include "Utility.h"

class GameObject;

class Transform
{
public:
	Transform(const PxVec3& pos = PxVec3(0, 0, 0), const PxQuat& rot = PxQuat(0, 0, 0, 1), PxVec3 scale = PxVec3(0, 0, 0)) :
		m_pos(pos),
		m_rot(rot),
		m_scale(scale),
		m_parent(0),
		m_parentMatrix(PxMat44(PxVec4(1,1,1,1))),
		m_initializedOldStuff(false) {}

	PxMat44 getTransformation() const;
	bool hasChanged();
	void update();
	void rotate(const PxVec3& axis, float angle);
	void rotate(const PxQuat& rotation);
	void lookAt(const PxVec3& point, const PxVec3& up);

	PxQuat getLookAtRotation(const PxVec3& point, const PxVec3& up)
	{
		PxMat44 swag = PxMat44(Utility::initRotationFromDirection((point - m_pos).getNormalized(), up));
		return PxQuat(PxMat33(swag.column0.getXYZ(), swag.column1.getXYZ(), swag.column2.getXYZ()));
	}

	inline PxVec3* getPosition()					{ return &m_pos; }
	inline const PxVec3& getPosition()     const	{ return m_pos; }
	inline PxQuat* getRotation()					{ return &m_rot; }
	inline const PxQuat& getRotation()		const	{ return m_rot; }
	inline PxVec3* getScale()						{ return &m_scale; }
	inline const PxVec3& getScale()        const	{ return m_scale; }
	inline PxVec3 getTransformedPos()		const	{ return PxVec3(GetParentMatrix().transform(m_pos)); }
	PxQuat getTransformedRot()				const;
	Transform * getParent()					const	{ return m_parent; }
	GameObject * getAttachedGameObject()	const	{ return m_attachedGameObject; }

	inline void setPosition(const PxVec3& pos) { m_pos = pos; }
	inline void setRotation(const PxQuat& rot) { m_rot = rot; }
	inline void setScale(const PxVec3& scale) { m_scale = scale; }
	inline void setParent(Transform* parent) { m_parent = parent; }
	inline void setAttachedGameObject(GameObject * gameObject) { m_attachedGameObject = gameObject; }

protected:
private:
	const PxMat44& GetParentMatrix() const;

	PxVec3 m_pos;
	PxQuat m_rot;
	PxVec3 m_scale;

	Transform* m_parent;
	GameObject * m_attachedGameObject;
	mutable PxMat44 m_parentMatrix;

	mutable PxVec3 m_oldPos;
	mutable PxQuat m_oldRot;
	mutable PxVec3 m_oldScale;
	mutable bool m_initializedOldStuff;
};