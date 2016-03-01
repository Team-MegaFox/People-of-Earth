#pragma once
#include <glm\glm.hpp>
#include "Utility.h"

class GameObject;

class Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(0.0f), const glm::quat& rot = glm::quat(1.0f, 0.0f, 0.0f, 0.0f), const glm::vec3& scale = glm::vec3(1.0f)) :
		m_pos(pos),
		m_rot(rot),
		m_scale(scale),
		m_parent(0),
		m_parentMatrix(glm::mat4(1.0f)),
		m_initializedOldStuff(false) {}

	glm::mat4 getTransformation() const;
	bool hasChanged();
	void update();
	void rotate(const glm::vec3& axis, float angle);
	void rotate(const glm::quat& rotation);
	void lookAt(const glm::vec3& point, const glm::vec3& up);

	glm::quat getLookAtRotation(const glm::vec3& point, const glm::vec3& up)
	{
		glm::mat4 mat = glm::mat4(Utility::initRotationFromDirection(glm::normalize((point - m_pos)), up));
		return glm::quat_cast(glm::mat3(mat));
	}

	inline glm::vec3* getPosition()                   { return &m_pos; }
	inline const glm::vec3& getPosition()       const { return m_pos; }
	inline glm::quat* getRotation()                 { return &m_rot; }
	inline const glm::quat& getRotation()     const { return m_rot; }
	inline glm::vec3* getScale()                { return &m_scale; }
	inline const glm::vec3& getScale()               const { return m_scale; }
	inline glm::vec3 getTransformedPos()   const { return glm::vec3(getParentMatrix() * glm::vec4(m_pos, 1.0f)); }
	glm::quat getTransformedRot()        const;
	GameObject* getAttachedGameObject() { return m_attachedObject; }
	Transform* getParent() { return m_parent; }

	inline void setPosition(const glm::vec3& pos) { m_pos = pos; }
	inline void setRotation(const glm::quat& rot) { m_rot = rot; }
	inline void setScale(const glm::vec3& scale) { m_scale = scale; }
	inline void setParent(Transform* parent) { m_parent = parent; }
	inline void setAttachedGameObject(GameObject* gameobject) { m_attachedObject = gameobject; }
protected:
private:
	const glm::mat4& getParentMatrix() const;

	glm::vec3 m_pos;
	glm::quat m_rot;
	glm::vec3 m_scale;

	Transform* m_parent;
	mutable glm::mat4 m_parentMatrix;

	mutable glm::vec3 m_oldPos;
	mutable glm::quat m_oldRot;
	mutable glm::vec3 m_oldScale;
	mutable bool m_initializedOldStuff;

	GameObject* m_attachedObject;
};