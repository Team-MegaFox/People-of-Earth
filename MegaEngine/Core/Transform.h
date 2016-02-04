// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 01-24-2016
// ***********************************************************************
// <copyright file="Transform.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\quaternion.hpp>
#include "Utility.h"

class GameObject;

/// <summary>
/// Stores the position, rotation and scale of an object.
/// </summary>
class Transform
{
public:

	/// <summary>
	/// Initializes a new instance of the <see cref="Transform"/> class.
	/// </summary>
	/// <param name="position">The position.</param>
	/// <param name="rotation">The rotation.</param>
	/// <param name="scale">The scale.</param>
	Transform(const glm::vec3 & position = glm::vec3(0.0f),
		const glm::quat & rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
		const glm::vec3 & scale = glm::vec3(1.0f));

	/// <summary>
	/// Determines whether this instance has changed.
	/// </summary>
	/// <returns>If the instance has changed.</returns>
	bool hasChanged();
	/// <summary>
	/// Gets the transformation matrix.
	/// </summary>
	/// <returns>The transformation matrix.</returns>
	glm::mat4 getTransformation() const;
	/// <summary>
	/// Gets the parent matrix.
	/// </summary>
	/// <returns>The parent's tranformation matrix.</returns>
	const glm::mat4 getParentMatrix() const;
	/// <summary>
	/// Gets the transformed rotation.
	/// </summary>
	/// <returns>The transfomred roation quaternion.</returns>
	glm::quat getTransformedRot() const;
	/// <summary>
	/// Gets the transformed position.
	/// </summary>
	/// <returns>The transformed position vector.</returns>
	glm::vec3 getTransformedPos() const;
	/// <summary>
	/// Rotates the Transform by a specified axis.
	/// </summary>
	/// <param name="axis">The axis.</param>
	/// <param name="angle">The angle.</param>
	void rotate(const glm::vec3& axis, float angle);
	/// <summary>
	/// Rotates the Transform by a specified rotation.
	/// </summary>
	/// <param name="rotation">The rotation.</param>
	void rotate(const glm::quat& rotation);
	/// <summary>
	/// Updates this instance.
	/// </summary>
	void update();

	// Getters
	/// <summary>
	/// Gets the attached game object.
	/// </summary>
	/// <returns>Attached GameObject pointers.</returns>
	GameObject * getAttachedGameObject() { return m_attached; }
	/// <summary>
	/// Gets the parent Transform.
	/// </summary>
	/// <returns>A pointer to the parent's Transform.</returns>
	Transform * getParent() { return m_parent; }
	/// <summary>
	/// Gets the position.
	/// </summary>
	/// <returns>A pointer to the position vector.</returns>
	glm::vec3 * getPosition() { return &m_pos; }
	/// <summary>
	/// Gets the position.
	/// </summary>
	/// <returns>A const refernce to the position vector.</returns>
	const glm::vec3 & getPosition() const { return m_pos; }
	/// <summary>
	/// Gets the rotation.
	/// </summary>
	/// <returns>A pointer to the rotation quaternion.</returns>
	glm::quat * getRotation() { return &m_rot; }
	/// <summary>
	/// Gets the rotation.
	/// </summary>
	/// <returns>A const reference to the roation quaternion.</returns>
	const glm::quat & getRotation() const { return m_rot; }
	/// <summary>
	/// Gets the scale.
	/// </summary>
	/// <returns>A pointer to the scale vector.</returns>
	glm::vec3 * getScale() { return &m_scale; }
	/// <summary>
	/// Gets the scale.
	/// </summary>
	/// <returns>A const reference to the scale vector.</returns>
	const glm::vec3 & getScale() const { return m_scale; }

	// Setters
	/// <summary>
	/// Sets the attached game object.
	/// </summary>
	/// <param name="attach">The attach.</param>
	void setAttachedGameObject(GameObject* attach) { m_attached = attach; }
	/// <summary>
	/// Sets the parent.
	/// </summary>
	/// <param name="parent">The parent.</param>
	void setParent(Transform* parent) { m_parent = parent; }
	/// <summary>
	/// Sets the position.
	/// </summary>
	/// <param name="pos">The position.</param>
	void setPosition(const glm::vec3 & pos) { m_pos = pos; }
	/// <summary>
	/// Sets the rotation.
	/// </summary>
	/// <param name="rot">The rot.</param>
	void setRotation(const glm::quat & rot) { m_rot = rot; }
	/// <summary>
	/// Sets the scale.
	/// </summary>
	/// <param name="scale">The scale.</param>
	void setScale(const glm::vec3 & scale) { m_scale = scale; }

private:
	/// <summary>
	/// The position vector.
	/// </summary>
	glm::vec3 m_pos;
	/// <summary>
	/// The rotation quaternion.
	/// </summary>
	glm::quat m_rot;
	/// <summary>
	/// The scale vector.
	/// </summary>
	glm::vec3 m_scale;;

	/// <summary>
	/// The attached GameObject.
	/// </summary>
	GameObject* m_attached;
	/// <summary>
	/// The parent Transform.
	/// </summary>
	Transform* m_parent;
	/// <summary>
	/// The parent transformation matrix.
	/// </summary>
	mutable glm::mat4 m_parentMatrix;

	/// <summary>
	/// The old position vector.
	/// </summary>
	mutable glm::vec3 m_oldPos;
	/// <summary>
	/// The old rotation quaternion.
	/// </summary>
	mutable glm::quat m_oldRot;
	/// <summary>
	/// The old scale vector.
	/// </summary>
	mutable glm::vec3 m_oldScale;
	/// <summary>
	/// The initialized old stuff.
	/// </summary>
	mutable bool m_initializedOldStuff;

};