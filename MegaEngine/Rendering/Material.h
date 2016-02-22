// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 01-24-2016
// ***********************************************************************
// <copyright file="Material.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once 

#include "..\Core\MappedValues.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <map>

/// <summary>
/// Holds the data for the material. This class itself doesn't have any member variables 
/// but inherits from <see cref="MappedValues"/> and <see cref="RefernceCounter"/>.
/// </summary>
/// <seealso cref="ReferenceCounter" />
/// <seealso cref="MappedValues" />
class MaterialData
	:	public ReferenceCounter, 
		public MappedValues
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="MaterialData"/> class.
	/// </summary>
	MaterialData() { }
	/// <summary>
	/// Finalizes an instance of the <see cref="MaterialData"/> class.
	/// </summary>
	~MaterialData() { }
private:
};

/// <summary>
/// Holds a pointer to <see cref="MaterialData"/> and maps material information to a map.
/// </summary>
class Material
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Material"/> class.
	/// </summary>
	/// <param name="materialName">Name of the material.</param>
	Material(const std::string & materialName = "");
	/// <summary>
	/// Initializes a new instance of the <see cref="Material"/> class.
	/// </summary>
	/// <param name="other">The other.</param>
	Material(const Material & other);
	/// <summary>
	/// Finalizes an instance of the <see cref="Material"/> class.
	/// </summary>
	virtual ~Material();
	//void operator=(const Material other) { m_materialName = other.m_materialName; m_materialData = other.m_materialData; }

	/// <summary>
	/// Initializes a new instance of the <see cref="Material"/> class.
	/// </summary>
	/// <param name="materialName">Name of the material.</param>
	/// <param name="specularIntensity">The amount of specular intensity.</param>
	/// <param name="specularPower">The specular power.</param>
	/// <param name="diffuse">The diffuse texture. Defaults to "defaultTexture.png".</param>
	/// <param name="normalMap">The normal map texture. Defaults to "default_normal.jpg".</param>
	/// <param name="dispMap">The displacement map texture. Defaults to "default_disp.png"</param>
	/// <param name="dispMapScale">The displacement map scale. Defaults to 0.</param>
	/// <param name="dispMapOffset">The displacement map offset. Defaults to 0.</param>
	Material(const std::string & materialName,
		float specularIntensity, float specularPower, const Texture & diffuse = Texture("defaultTexture.png"),
		const Texture & normalMap = Texture("default_normal.jpg"),
		const Texture & dispMap = Texture("default_disp.png"), float dispMapScale = 0.0f, float dispMapOffset = 0.0f);

	Material(const std::string & materialName, const Texture & skyboxTex);

	/// <summary>
	/// Sets the 3D vector with a name to the material data map.
	/// </summary>
	/// <param name="name">The name.</param>
	/// <param name="value">The vector value.</param>
	inline void setVector3f(const std::string & name, const glm::vec3 & value) { m_materialData->setVec3(name, value); }
	/// <summary>
	/// Sets the float with a name to the material data map.
	/// </summary>
	/// <param name="name">The name.</param>
	/// <param name="value">The float value.</param>
	inline void setFloat(const std::string & name, float value)              { m_materialData->setFloat(name, value); }
	/// <summary>
	/// Sets the texture with a name to the material data map.
	/// </summary>
	/// <param name="name">The name.</param>
	/// <param name="value">The texture value.</param>
	inline void setTexture(const std::string & name, const Texture& value)   { m_materialData->setTexture(name, value); }

	/// <summary>
	/// Gets the 3D vector value by name from the material data map.
	/// </summary>
	/// <param name="name">The name.</param>
	/// <returns>A const reference to the 3D vector from the material data map.</returns>
	inline const glm::vec3 & getVec3(const std::string & name) const { return m_materialData->getVec3(name); }
	/// <summary>
	/// Gets the float value by name from the material data map.
	/// </summary>
	/// <param name="name">The name.</param>
	/// <returns>A const reference to the float from the material data map.</returns>
	inline float getFloat(const std::string & name)              const { return m_materialData->getFloat(name); }
	/// <summary>
	/// Gets the texture value by name from the material data map.
	/// </summary>
	/// <param name="name">The name.</param>
	/// <returns>A const reference to the texture from the material data map.</returns>
	inline const Texture & getTexture(const std::string & name)   const { return m_materialData->getTexture(name); }
protected:
private:
	static std::map<std::string, MaterialData *> s_resourceMap;
	/// <summary>
	/// The material data.
	/// </summary>
	MaterialData* m_materialData;
	/// <summary>
	/// The material's name.
	/// </summary>
	std::string m_materialName;

};
