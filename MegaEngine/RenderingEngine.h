#pragma once
#include "Viewport.h"
#include "Texture.h"
#include "Shader.h"
#include <glm\glm.hpp>
#include "Camera3D.h"
#include <vector>
#include <map>
#include <string>
#include "MappedValues.h"
#include "Material.h"
#include "GUIEngine.h"

class GameObject;
class BaseLight;

class RenderingEngine 
	: public MappedValues
{
public:
	RenderingEngine(Viewport viewport, GUIEngine & guiEngine);

	void render(GameObject & gameObject);
	inline void setMainCamera(Camera3D & camera);
	inline void addLight(const BaseLight & light);
	
	// Getters
	BaseLight & getActiveLight() const { return *m_activeLight; }
	inline unsigned int getSamplerSlot(const std::string & samplerName) const { return m_samplerMap.find(samplerName)->second; }
	glm::mat4 getLightMatrix() const { return m_lightMatrix; }

	virtual void updateUniformStruct(const Transform & transform, const Material & material, const Shader & shader,
		const std::string& uniformName, const std::string & uniformType) const
	{
		throw uniformType + " is not supported by the rendering engine";
	}

private:
	void applyFilter(const Shader & filter, const TextureImage & src, const TextureImage * dst);
	void blurShadowMap(int shadowMapIndex, float blurAmount);

	static const int NUM_SHADOW_MAPS = 10;
	static const glm::mat4 BIAS_MATRIX;
	Viewport * m_viewport;
	TextureImage m_shadowMaps[NUM_SHADOW_MAPS];
	TextureImage m_shadowMapTempTargets[NUM_SHADOW_MAPS];
	Shader m_defaultShader;
	Shader m_shadowMapShader;
	Shader m_guassFilter;
	Shader m_fxaaFilter;
	Shader m_gausBlurFilter;
	glm::mat4 m_lightMatrix;
	Camera3D m_altCamera;
	Camera3D m_mainCamera;
	BaseLight * m_activeLight;
	std::vector<BaseLight*> m_lights;
	std::map<std::string, unsigned int> m_samplerMap;
	GUIEngine * m_guiEngine;

protected:
	void setSamplerSlot(std::string name, GLuint value);
};

