#pragma once 

#include "Texture.h"
#include "MappedValues.h"
#include <glm/glm.hpp>
#include <map>


class MaterialData 
	:	public ReferenceCounter, 
		public MappedValues
{
public:
private:
};

class Material
{
public:
	Material(const std::string & materialName = "");
	Material(const Material & other);
	virtual ~Material();

	Material(const std::string & materialName, const Texture& diffuse, float specularIntensity, float specularPower,
		const Texture & normalMap = Texture("Textures/default_normal.jpg"),
		const Texture & dispMap = Texture("Textures/default_disp.png"), float dispMapScale = 0.0f, float dispMapOffset = 0.0f);

	inline void setVector3f(const std::string & name, const glm::vec3 & value) { m_materialData->setVec3(name, value); }
	inline void setFloat(const std::string & name, float value)              { m_materialData->setFloat(name, value); }
	inline void setTexture(const std::string & name, const Texture& value)   { m_materialData->setTexture(name, value); }

	inline const glm::vec3 & getVec3(const std::string & name) const { return m_materialData->getVec3(name); }
	inline float getFloat(const std::string & name)              const { return m_materialData->getFloat(name); }
	inline const Texture & getTexture(const std::string & name)   const { return m_materialData->getTexture(name); }
protected:
private:
	static std::map<std::string, MaterialData *> s_resourceMap;
	MaterialData* m_materialData;
	std::string   m_materialName;


	void operator=(const Material & other) {}
};
