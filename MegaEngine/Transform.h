#pragma once
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\quaternion.hpp>

class GameObject;

class Transform
{
public:

	Transform(const glm::vec3 & position = glm::vec3(0.0f),
		const glm::vec3 & rotation = glm::vec3(0.0f),
		const glm::vec3 & scale = glm::vec3(1.0f)) :
		m_position(position),
		m_rotation(rotation),
		m_scale(scale)
	{ /* Empty */
	}

	glm::mat4 getModel() const
	{
		glm::mat4 posMatrix = glm::translate(m_position);
		glm::mat4 scaleMatrix = glm::scale(m_scale);

		return posMatrix * glm::mat4_cast(m_rotation) * scaleMatrix;
	}

	const glm::mat4 getParentMatrix()
	{
		return glm::mat4(0);
	}

	glm::quat getTransformedRot()
	{
		return glm::quat();
	}

	// Getters
	glm::vec3 & getPosition() { return m_position; }
	glm::quat & getRotation() { return m_rotation; }
	inline glm::vec3 & getScale() { return m_scale; }
	GameObject* getParent() { return m_parent; }

	// Setters
	void setPosition(const glm::vec3 & pos) { m_position = pos; }
	void setRotation(const glm::quat & rot) { m_rotation = rot; }
	void setScale(const glm::vec3 & scale) { m_scale = scale; }
	void setParent(GameObject* parent) { m_parent = parent; }

private:
	glm::vec3 m_position, m_scale;
	glm::quat m_rotation;

	GameObject* m_parent;

};