#pragma once

#include "../Components/GameComponents.h"

#include <glm\glm.hpp>

//Cameras represent a location, orientation, and projection from
//which the scene can be rendered.
class Camera3D
{
public:
	//Transform is passed in so the Camera doesn't need to be attached to a game object.
	//That's useful for places such as the rendering engine which can use cameras
	//without creating placeholder game objects.
	Camera3D(const glm::mat4& projection, Transform* transform) :
		m_projection(projection),
		m_transform(transform) {}

	inline Transform* getTransform()             { return m_transform; }
	inline const Transform& getTransform() const { return *m_transform; }

	//This is the primary function of the camera. Multiplying a point by the returned matrix
	//will transform the point into it's location on the screen, where -1 represents the bottom/left
	//of the screen, and 1 represents the top/right of the screen.
	glm::mat4 getViewProjection()           const;

	glm::mat4 getView() const;

	inline void setProjection(const glm::mat4& projection) { m_projection = projection; }
	inline void setTransform(Transform* transform)        { m_transform = transform; }
protected:
private:
	glm::mat4   m_projection; //The projection with which the camera sees the world (i.e. perspective, orthographic, identity, etc.)
	Transform* m_transform;  //The transform representing the position and orientation of the camera.
};

//CameraComponents are an easy way to use a camera as a component
//on a game object.
class CameraComponent : public GameComponent
{
public:
	//The camera's transform is initialized to 0 (null) because
	//at construction, this isn't attached to a game object,
	//and therefore doesn't have access to a valid transform.
	CameraComponent(const glm::mat4& projection) :
		m_camera(projection, 0) {}

	virtual void addToEngine(CoreEngine* engine) const;

	inline glm::mat4 getViewProjection() const { return m_camera.getViewProjection(); }

	inline void setProjection(const glm::mat4& projection) { m_camera.setProjection(projection); }
	virtual void setParent(GameObject* parent);
protected:
private:
	Camera3D m_camera; //The camera that's being used like a component.
};