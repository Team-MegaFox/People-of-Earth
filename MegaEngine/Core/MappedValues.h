#pragma once

#include <map>
#include <glm/glm.hpp>
#include <iostream>

#include "..\Rendering\Texture.h"

/// <summary>
/// Stores values in a map for ease of access.
/// This class is meant to be inherited but you can make an object of it.
///	</summary>
class MappedValues
{
public:
	/// <summary>Constructs MappedValues and sets defualt value for texture to "defaultTexture.png" and for vector to 0.0f.</summary>
	MappedValues() :
		m_defaultTexture(Texture("defaultTexture.png")),
		m_defaultVector3f(glm::vec3(0.0f)) { }
	~MappedValues() { }

	/// <summary>Adds a vector to the map.</summary>
	/// <param name='name'>The name of the float vector.</param>
	/// <param name='value'>The value of the vector to store in the map.</param>
	inline void setVec3(const std::string& name, const glm::vec3& value) { m_vector3fMap[name] = value; }
	/// <summary>Adds a float to the map.</summary>
	/// <param name='name'>The name of the float value.</param>
	/// <param name='value'>The value of the float to store in the map.</param>
	inline void setFloat(const std::string& name, float value)           { m_floatMap[name] = value; }
	/// <summary>Adds a texture to the map.</summary>
	/// <param name='name'>The name of the texture.</param>
	/// <param name='value'>The texture to store in the map.</param>
	inline void setTexture(const std::string& name, const Texture& value){ m_textureMap[name] = value; }

	/// <summary>Gets a vector by name from the map.</summary>
	/// <returns>The vector by name from the map.</returns>
	const glm::vec3 & getVec3(const std::string & name) const;
	/// <summary>Gets a float by name from the map.</summary>
	/// <returns>The float value by name from the map.</returns>
	float getFloat(const std::string & name) const;
	/// <summary>Gets a texture by name from the map.</summary>
	/// <returns>The texutre by name from the map.</returns>
	const Texture & getTexture(const std::string & name) const;
protected:
private:
	/// <summary>A map of vectors.</summary>
	std::map<std::string, glm::vec3> m_vector3fMap;
	/// <summary>A map of floats.</summary>
	std::map<std::string, float> m_floatMap;
	/// <summary>A map of textures.</summary>
	std::map<std::string, Texture> m_textureMap;

	Texture m_defaultTexture;
	glm::vec3 m_defaultVector3f;
};