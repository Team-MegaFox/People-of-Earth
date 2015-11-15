#include "MappedValues.h"

const glm::vec3& MappedValues::getVec3(const std::string& name) const
{
	std::map<std::string, glm::vec3>::const_iterator it = m_vector3fMap.find(name);
	if (it != m_vector3fMap.end())
	{
		return it->second;
	}

	return m_defaultVector3f;
}

float MappedValues::getFloat(const std::string& name) const
{
	std::map<std::string, float>::const_iterator it = m_floatMap.find(name);
	if (it != m_floatMap.end())
	{
		return it->second;
	}

	return 0;
}

const TextureImage& MappedValues::getTexture(const std::string& name) const
{
	std::map<std::string, TextureImage>::const_iterator it = m_textureMap.find(name);
	if (it != m_textureMap.end())
	{
		return it->second;
	}

	return m_defaultTexture;
}