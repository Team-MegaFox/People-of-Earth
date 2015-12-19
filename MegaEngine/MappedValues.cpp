#include "MappedValues.h"

const glm::vec3& MappedValues::getVec3(const std::string& name) const
{
	auto it = m_vector3fMap.find(name);
	if (it != m_vector3fMap.end())
	{
		return it->second;
	}

	return m_defaultVector3f;
}

float MappedValues::getFloat(const std::string& name) const
{
	auto it = m_floatMap.find(name);
	if (it != m_floatMap.end())
	{
		return it->second;
	}

	return 0;
}

const Texture& MappedValues::getTexture(const std::string& name) const
{
	auto it = m_textureMap.find(name);
	if (it != m_textureMap.end())
	{
		return it->second;
	}

	return m_defaultTexture;
}