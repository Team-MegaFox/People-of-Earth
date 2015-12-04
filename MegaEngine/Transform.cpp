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

	if (m_scale != m_oldScale)
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
		m_oldPos = m_pos + glm::vec3(1.0f, 1.0f, 1.0f);
		m_oldRot = m_rot * 0.5f;
		m_oldScale = m_scale + glm::vec3(1.0f);
		m_initializedOldStuff = true;
	}
}

glm::mat4 Transform::getTransformation() const
{
	glm::mat4 translationMatrix = initTranslation(m_pos);
	glm::mat4 scaleMatrix = initScale(m_scale);
	glm::mat4 result = translationMatrix * glm::mat4_cast(m_rot) * scaleMatrix;

	return getParentMatrix() * result;
}

const glm::mat4 Transform::getParentMatrix() const
{
	if (m_parent != 0 && m_parent->hasChanged())
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
	
	return parentRot * m_rot;
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
	printf("------------Before the rotation-------\nrot.w = %f\nrot.x = %f\nrot.y = %f\nrot.z = %f\n-------------------------------\n", 
		m_rot.w,
		m_rot.x,
		m_rot.y,
		m_rot.z);
	m_rot = glm::normalize(m_rot * rotation);
	printf("------------After the rotation---------\nrot.w = %f\nrot.x = %f\nrot.y = %f\nrot.z = %f\n-------------------------------\n",
		m_rot.w,
		m_rot.x,
		m_rot.y,
		m_rot.z);
}
