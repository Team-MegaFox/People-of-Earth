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

const glm::vec4 & MappedValues::getVec4(const std::string & name) const
{
	auto it = m_vector4fMap.find(name);
	if (it != m_vector4fMap.end())
	{
		return it->second;
	}

	return m_defaultVector4f;
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