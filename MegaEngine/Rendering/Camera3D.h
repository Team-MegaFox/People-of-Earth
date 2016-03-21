// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Jesse Derochie
// Last Modified On : 02-08-2016
// ***********************************************************************
// <copyright file="Camera3D.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once
#include <GLM/glm.hpp>

#include "..\Core\Transform.h"
#include "..\Components\GameComponents.h"

/// <summary>
/// A camera class that holds the projection matrix and its Transform.
/// </summary>
class Camera3D
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Camera3D"/> class.
	/// </summary>
	Camera3D() { }
	/// <summary>
	/// Initializes a new instance of the <see cref="Camera3D"/> class.
	/// </summary>
	/// <param name="projection">The projection matrix.</param>
	/// <param name="transform">The transform object.</param>
	Camera3D(const glm::mat4& projection, Transform * transform) :
		m_projection(projection), m_transform(transform) { }
	/// <summary>
	/// Finalizes an instance of the <see cref="Camera3D"/> class.
	/// </summary>
	~Camera3D() { }

	/// <summary>
	/// Gets the view projection matrix.
	/// </summary>
	/// <returns>The view projection matrix.</returns>
	glm::mat4 getViewProjection() const;

	/// <summary>
	/// Gets the view.
	/// </summary>
	/// <returns></returns>
	glm::mat4 getView() const;

	/// <summary>
	/// Gets the transform.
	/// </summary>
	/// <returns>A pointer to the Transform object.</returns>
	inline Transform* getTransform() { return m_transform; }
	/// <summary>
	/// Gets the transform.
	/// </summary>
	/// <returns>A const reference to the Transform object.</returns>
	inline const Transform& getTransform() const { return *m_transform; }

	/// <summary>
	/// Sets the projection matrix.
	/// </summary>
	/// <param name="projection">The projection matrix.</param>
	inline void setProjection(const glm::mat4& projection) { m_projection = projection; }
	/// <summary>
	/// Sets the transform.
	/// </summary>
	/// <param name="transform">The transform.</param>
	inline void setTransform(Transform * transform) { m_transform = transform; }

private:
	/// <summary>
	/// The projection view matrix.
	/// </summary>
	glm::mat4 m_projection;
	/// <summary>
	/// The transform object.
	/// </summary>
	Transform * m_transform;

};

/// <summary>
/// Class CameraComponent.
/// </summary>
/// <seealso cref="GameComponent" />
class CameraComponent : public GameComponent
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="CameraComponent"/> class.
	/// </summary>
	/// <param name="projection">The projection.</param>
	CameraComponent(const glm::mat4 & projection) :
		m_camera(projection, nullptr) { }
	/// <summary>
	/// Finalizes an instance of the <see cref="CameraComponent"/> class.
	/// </summary>
	~CameraComponent() { }

	/// <summary>
	/// Adds to engine.
	/// </summary>
	/// <param name="engine">The engine.</param>
	virtual void addToEngine(CoreEngine * engine) const;

	/// <summary>
	/// Gets the view projection.
	/// </summary>
	/// <returns>glm.mat4.</returns>
	inline glm::mat4 getViewProjection() const { m_camera.getViewProjection(); }

	/// <summary>
	/// Sets the projection.
	/// </summary>
	/// <param name="projection">The projection.</param>
	inline void setProjection(const glm::mat4& projection) { m_camera.setProjection(projection); }
	/// <summary>
	/// Sets the parent.
	/// </summary>
	/// <param name="parent">The parent.</param>
	virtual void setParent(GameObject* parent);

private:
	/// <summary>
	/// The m_camera
	/// </summary>
	Camera3D m_camera;

};