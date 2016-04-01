// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 01-24-2016
// ***********************************************************************
// <copyright file="MappedValues.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
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
	/// <summary>
	/// Constructs MappedValues and sets defualt value for texture to "defaultTexture.png" and for vector to 0.0f.
	/// </summary>
	MappedValues() :
		m_defaultTexture(Texture("defaultTexture.png")),
		m_defaultVector3f(glm::vec3(0.0f)),
		m_defaultVector4f(glm::vec4(0.0f)) { }
	~MappedValues() { }

	/// <summary>
	/// Adds a 3D vector to the map.
	/// </summary>
	/// <param name='name'>The name of the float vector.</param>
	/// <param name='value'>The value of the vector to store in the map.</param>
	inline void setVec3(const std::string& name, const glm::vec3& value) { m_vector3fMap[name] = value; }
	/// <summary>
	/// Adds a 4D vector to the map.
	/// </summary>
	/// <param name='name'>The name of the float vector.</param>
	/// <param name='value'>The value of the vector to store in the map.</param>
	inline void setVec4(const std::string& name, const glm::vec4& value) { m_vector4fMap[name] = value; }
	/// <summary>
	/// Adds a float to the map.
	/// </summary>
	/// <param name='name'>The name of the float value.</param>
	/// <param name='value'>The value of the float to store in the map.</param>
	inline void setFloat(const std::string& name, float value)           { m_floatMap[name] = value; }
	/// <summary>
	/// Adds a texture to the map.
	/// </summary>
	/// <param name='name'>The name of the texture.</param>
	/// <param name='value'>The texture to store in the map.</param>
	inline void setTexture(const std::string& name, const Texture& value){ m_textureMap[name] = value; }

	/// <summary>
	/// Gets a 3D vector by name from the map.
	/// </summary>
	/// <returns>The vector by name from the map.</returns>
	const glm::vec3 & getVec3(const std::string & name) const;
	/// <summary>
	/// Gets a 4D vector by name from the map.
	/// </summary>
	/// <returns>The vector by name from the map.</returns>
	const glm::vec4 & getVec4(const std::string & name) const;
	/// <summary>
	/// Gets a float by name from the map.
	/// </summary>
	/// <returns>The float value by name from the map.</returns>
	float getFloat(const std::string & name) const;
	/// <summary>
	/// Gets a texture by name from the map.
	/// </summary>
	/// <returns>The texutre by name from the map.</returns>
	const Texture & getTexture(const std::string & name) const;
protected:
private:
	/// <summary>
	/// A map of 3D vectors.
	/// </summary>
	std::map<std::string, glm::vec3> m_vector3fMap;
	/// <summary>
	/// A map of 4D vectors.
	/// </summary>
	std::map<std::string, glm::vec4> m_vector4fMap;
	/// <summary>
	/// A map of floats.
	/// </summary>
	std::map<std::string, float> m_floatMap;
	/// <summary>
	/// A map of textures.
	/// </summary>
	std::map<std::string, Texture> m_textureMap;
	
	/// <summary>
	/// The default texture.
	/// </summary>
	Texture m_defaultTexture;	
	/// <summary>
	/// The default 3d vector.
	/// </summary>
	glm::vec3 m_defaultVector3f;
	/// <summary>
	/// The default 4d vector.
	/// </summary>
	glm::vec4 m_defaultVector4f;
};