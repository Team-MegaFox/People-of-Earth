#pragma once
#include <glm\glm.hpp>
#include <vector>
#include <map>
#include <string>

#include "MappedValues.h"
#include "Viewport.h"
#include "Texture.h"
#include "Shader.h"
#include "Material.h"
#include "Camera3D.h"
#include "Mesh.h"
#include "GUIEngine.h"

class GameObject;
class BaseLight;

class RenderingEngine 
	: public MappedValues
{
public:
	RenderingEngine(Viewport& viewport, GUIEngine& guiEngine);
	~RenderingEngine() { }

	void render(GameObject & gameObject);

	inline void addLight(const BaseLight & light) { m_lights.push_back(&light); }
	inline void setMainCamera(const Camera3D & camera) { m_mainCamera = &camera; }
	
	// Getters
	const BaseLight & getActiveLight() const { return *m_activeLight; }
	inline unsigned int getSamplerSlot(const std::string & samplerName) const { return m_samplerMap.find(samplerName)->second; }
	glm::mat4 getLightMatrix() const { return m_lightMatrix; }

	virtual void updateUniformStruct(const Transform & transform, const Material & material, const Shader & shader,
		const std::string& uniformName, const std::string & uniformType) const
	{
		throw uniformType + " is not supported by the rendering engine";
	}

private:
	static const int NUM_SHADOW_MAPS = 10;
	static const glm::mat4 BIAS_MATRIX;

	const Viewport * m_viewport;
	const GUIEngine * m_guiEngine;

	Texture m_shadowMaps[NUM_SHADOW_MAPS];
	Texture m_shadowMapTempTargets[NUM_SHADOW_MAPS];

	Transform m_filterPlaneTransform;
	Mesh m_filterPlane;
	Texture m_tempTarget;
	Material m_filterPlaneMaterial;

	Shader m_defaultShader;
	Shader m_shadowMapShader;
	Shader m_nullFilter;
	Shader m_guassFilter;
	Shader m_fxaaFilter;
	Shader m_gausBlurFilter;
	glm::mat4 m_lightMatrix;
	
	Transform m_altCameraTransform;
	Camera3D m_altCamera;
	const Camera3D * m_mainCamera;
	
	const BaseLight * m_activeLight;
	std::vector<const BaseLight*> m_lights;
	std::map<std::string, unsigned int> m_samplerMap;

	void applyFilter(const Shader & filter, const Texture & src, const Texture * dst);
	void blurShadowMap(int shadowMapIndex, float blurAmount);

protected:
	void setSamplerSlot(std::string name, GLuint value);
};

