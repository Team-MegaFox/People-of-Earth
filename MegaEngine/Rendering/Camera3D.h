#pragma once
#include <GLM/glm.hpp>

#include "..\Core\Transform.h"
#include "..\Components\GameComponents.h"

class Camera3D 
{
public:
	Camera3D() { }
	Camera3D(const glm::mat4& projection, Transform * transform) :
		m_projection(projection), m_transform(transform) { }
	~Camera3D() { }

	glm::mat4 getViewProjection() const;

	inline Transform* getTransform() { return m_transform; }
	inline const Transform& getTransform() const { return *m_transform; }

	inline void setProjection(const glm::mat4& projection) { m_projection = projection; }
	inline void setTransform(Transform * transform) { m_transform = transform; }

private:
	glm::mat4 m_projection;
	Transform * m_transform;

};

class CameraComponent : public GameComponent
{
public:
	CameraComponent(const glm::mat4 & projection) : 
		m_camera(projection, nullptr) { }
	~CameraComponent() { }

	virtual void addToEngine(CoreEngine * engine) const;

	inline glm::mat4 getViewProjection() const { m_camera.getViewProjection(); }

	inline void setProjection(const glm::mat4& projection) { m_camera.setProjection(projection); }
	virtual void setParent(GameObject* parent);

private:
	Camera3D m_camera;

};