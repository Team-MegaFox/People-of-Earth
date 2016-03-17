// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 03-17-2016
// ***********************************************************************
// <copyright file="Camera3D.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once
#include <PhysX/PxPhysicsAPI.h>
using namespace physx;

#include "..\Components\GameComponents.h"
#include "..\Core\Utility.h"

enum class EnclosureType
{
	INSIDE, OUTSIDE, OVERLAP
};

/// <summary>
/// Cameras represent a location, orientation, and projection from
/// which the scene can be rendered.
/// </summary>
class Camera3D
{
public:
	/// <summary>
	/// Transform is passed in so the Camera doesn't need to be attached to a game object.
	/// That's useful for places such as the rendering engine which can use cameras
	/// without creating placeholder game objects.
	/// </summary>
	Camera3D(const PxReal& fov, const PxReal& aspect, const PxReal& near, const PxReal& far, Transform* transform) :
		m_projection(Utility::initPerspective(fov, aspect, near, far)),
		m_fov(fov), m_aspect(aspect), m_near(near), m_far(far),
		m_transform(transform),
		m_frustum(6) { }
	Camera3D(const PxMat44& projection, Transform* transform) :
		m_projection(projection),
		m_transform(transform),
		m_frustum(6) { }

	EnclosureType isInisde(const PxVec3& centre, const float radius) const;

	/// <summary>
	/// This is the primary function of the camera. Multiplying a point by the returned matrix
	/// will transform the point into it's location on the screen, where -1 represents the bottom/left
	/// of the screen, and 1 represents the top/right of the screen.
	/// </summary>
	/// <returns>The view projection matrix.</returns>
	PxMat44 getViewProjection() const;
	/// <summary>
	/// Gets the view with the rotation of the camera.
	/// </summary>
	/// <returns>The view matrix.</returns>
	PxMat44 getView() const;
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
	/// Gets frustum of the camera.
	/// </summary>
	/// <returns>A const reference to the Planes of the frustum.</returns>
	inline const std::vector<PxPlane> getFrustum() const { return m_frustum; }

	/// <summary>
	/// Sets the projection matrix.
	/// </summary>
	/// <param name="projection">The projection matrix.</param>
	inline void setProjection(const PxMat44& projection) { m_projection = projection; setFrustum(); }
	/// <summary>
	/// Sets the transform.
	/// </summary>
	/// <param name="transform">The transform.</param>
	inline void setTransform(Transform* transform)        { m_transform = transform; setFrustum(); }
protected:
private:
	/// <summary>
	/// The projection with which the camera sees the world (i.e. perspective, orthographic, identity, etc.)
	/// </summary>
	PxMat44 m_projection;
	/// <summary>
	/// The components of the camera.
	/// </summary>
	PxReal m_fov, m_aspect, m_near, m_far;
	/// <summary>
	/// The transform representing the position and orientation of the camera.
	/// </summary>
	Transform* m_transform;
	/// <summary>
	/// The 6 frustum planes.
	/// </summary>
	std::vector<PxPlane> m_frustum;
	
	/// <summary>
	/// Calculates the frustum planes and sets it to the member variable.
	/// </summary>
	void setFrustum();
};

/// <summary>
/// CameraComponents are an easy way to use a camera as a component
/// on a game object.
/// </summary>
class CameraComponent : public GameComponent
{
public:
	/// <summary>
	/// The camera's transform is initialized to 0 (null) because
	/// at construction, this isn't attached to a game object,
	/// and therefore doesn't have access to a valid transform.
	/// </summary>
	CameraComponent(const PxReal& fov, const PxReal& aspect, const PxReal& near, const PxReal& far) :
		m_camera(fov, aspect, near, far, 0) {}

	/// <summary>
	/// Adds to engine.
	/// </summary>
	/// <param name="engine">The engine.</param>
	virtual void addToEngine(CoreEngine* engine) const;

	/// <summary>
	/// Gets a reference to the camera object stored in the component.
	/// </summary>
	/// <returns>The reference to the camera object.</returns>
	inline Camera3D* getCamera3D() { return &m_camera; }
	/// <summary>
	/// Gets the view projection.
	/// </summary>
	/// <returns>The view projection of of the camera.</returns>
	inline PxMat44 getViewProjection() const { return m_camera.getViewProjection(); }
	/// <summary>
	/// Gets frustum of the camera.
	/// </summary>
	/// <returns>A const reference to the Planes of the frustum.</returns>
	inline std::vector<PxPlane> getFrustum() const { return m_camera.getFrustum(); }

	/// <summary>
	/// Sets the projection.
	/// </summary>
	/// <param name="projection">The projection.</param>
	inline void setProjection(const PxMat44& projection) { m_camera.setProjection(projection); }
	/// <summary>
	/// Sets the parent.
	/// </summary>
	/// <param name="parent">The parent.</param>
	virtual void setParent(GameObject* parent);
protected:
private:
	/// <summary>
	/// The camera that's being used like a componentt.
	/// </summary>
	Camera3D m_camera;
};