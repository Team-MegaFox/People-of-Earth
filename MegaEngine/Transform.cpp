#include "Transform.h"

Transform::Transform(const glm::vec3 & position,
	const glm::quat & rotation,
	const glm::vec3 & scale) :
	m_pos(position),
	m_rot(rotation),
	m_scale(scale)
{ /* Empty */
}

bool Transform::hasChanged()
{
	if (m_parent && m_parent->hasChanged())
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

glm::mat4 Transform::getTransformation() const
{
	glm::mat4 posMatrix = initTranslation(m_pos);
	glm::mat4 scaleMatrix = initScale(m_scale);
	glm::mat4 result = posMatrix * glm::mat4_cast(m_rot) * scaleMatrix;

	return getParentMatrix() * result;
}

const glm::mat4 Transform::getParentMatrix() const
{
	if (m_parent && m_parent->hasChanged())
	{
		m_parentMatrix = m_parent->getTransformation();
	}
	return m_parentMatrix;
}

glm::quat Transform::getTransformedRot() const
{
	glm::quat parentRot(1.0f, 0.0f, 0.0f, 0.0f);

	if (m_parent)
	{
		parentRot = m_parent->getTransformedRot();
	}
	
	return parentRot;
}

glm::vec3 Transform::getTransformedPos() const
{
	return glm::vec3(getParentMatrix() * glm::vec4(m_pos, 1.0f));
}

void Transform::rotate(const glm::vec3& axis, float angle)
{
	rotate(glm::quat(angle, axis));
}

void Transform::rotate(const glm::quat& rotation)
{
	m_rot = glm::quat(glm::normalize(rotation * m_rot));
}
