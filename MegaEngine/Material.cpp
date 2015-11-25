#include "Material.h"
#include <iostream>
#include <cassert>

std::map<std::string, MaterialData *> Material::s_resourceMap;

Material::Material(const std::string & materialName) :
m_materialName(materialName)
{
	if (materialName.length() > 0)
	{
		std::map<std::string, MaterialData *>::const_iterator it = s_resourceMap.find(materialName);
		if (it == s_resourceMap.end())
		{
			std::cerr << "Error: Material " << materialName << " has not been initialized!" << std::endl;
			assert(0 != 0);
		}

		m_materialData = it->second;
		m_materialData->addReference();
	}
}

Material::Material(const Material & other) :
m_materialData(other.m_materialData),
m_materialName(other.m_materialName)
{
	m_materialData->addReference();
}

Material::~Material()
{
	if (m_materialData && m_materialData->removeReference())
	{
		if (m_materialName.length() > 0)
		{
			s_resourceMap.erase(m_materialName);
		}

		delete m_materialData;
	}
}

Material::Material(const std::string & materialName, const Texture & diffuse, float specularIntensity, float specularPower,
	const Texture & normalMap,
	const Texture & dispMap, float dispMapScale, float dispMapOffset) :
	m_materialName(materialName)
{
	m_materialData = new MaterialData();
	s_resourceMap[m_materialName] = m_materialData;

	m_materialData->setTexture("diffuse", diffuse);
	m_materialData->setFloat("specularIntensity", specularIntensity);
	m_materialData->setFloat("specularPower", specularPower);
	m_materialData->setTexture("normalMap", normalMap);
	m_materialData->setTexture("dispMap", dispMap);

	float baseBias = dispMapScale / 2.0f;
	m_materialData->setFloat("dispMapScale", dispMapScale);
	m_materialData->setFloat("dispMapBias", -baseBias + baseBias * dispMapOffset);
}