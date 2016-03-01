#include "Transform.h"

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

	if (m_scale != m_scale)
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
		m_oldPos = m_pos + glm::vec3(1.0f);
		m_oldRot = m_rot * 0.5f;
		m_oldScale = m_scale + 1.0f;
		m_initializedOldStuff = true;
	}
}

void Transform::rotate(const glm::vec3& axis, float angle)
{
	rotate(glm::angleAxis(angle, axis));
}

void Transform::rotate(const glm::quat& rotation)
{
	m_rot = glm::quat(glm::normalize(rotation * m_rot));
}

void Transform::lookAt(const glm::vec3& point, const glm::vec3& up)
{
	m_rot = getLookAtRotation(point, up);
}

glm::mat4 Transform::getTransformation() const
{
	glm::mat4 translationMatrix;
	glm::mat4 scaleMatrix;

	translationMatrix = Utility::initTranslation(m_pos);
	scaleMatrix = Utility::initScale(m_scale);

	glm::mat4 result = translationMatrix * glm::mat4_cast(m_rot) * scaleMatrix;

	return getParentMatrix() * result;
}

const glm::mat4& Transform::getParentMatrix() const
{
	if (m_parent != 0 && m_parent->hasChanged())
	{
		m_parentMatrix = m_parent->getTransformation();
	}

	return m_parentMatrix;
}

glm::quat Transform::getTransformedRot() const
{
	glm::quat parentRot = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

	if (m_parent)
	{
		parentRot = m_parent->getTransformedRot();
	}
	return parentRot * m_rot;
}