#pragma once

#include <map>
#include <glm/glm.hpp>
#include "Texture.h"


class MappedValues
{
public:
	MappedValues() :
		m_defaultTexture(TextureImage("defaultTexture.png")),
		m_defaultVector3f(glm::vec3(0.0f)) {}

	inline void setVec3(const std::string& name, const glm::vec3& value) { m_vector3fMap[name] = value; }
	inline void setFloat(const std::string& name, float value)              { m_floatMap[name] = value; }
	inline void setTexture(const std::string& name, const TextureImage& value)   { m_textureMap[name] = value; }

	const glm::vec3 & getVec3(const std::string & name) const;
	float getFloat(const std::string & name)              const;
	const TextureImage & getTexture(const std::string & name)   const;
protected:
private:
	std::map<std::string, glm::vec3> m_vector3fMap;
	std::map<std::string, float> m_floatMap;
	std::map<std::string, TextureImage> m_textureMap;

	TextureImage m_defaultTexture;
	glm::vec3 m_defaultVector3f;
};