#pragma once
#include "..\Core\MappedValues.h"
#include "Skybox.h"
#include "Camera3D.h"
#include "Lighting.h"
#include "Material.h"
#include "Mesh.h"
#include "Viewport.h"
#include <vector>
#include <map>
class GameObject;

class RenderingEngine : public MappedValues
{
public:
	RenderingEngine(const Viewport& window);
	virtual ~RenderingEngine() {}

	void render(const GameObject& object);

	inline void addLight(const BaseLight& light) { m_lights.push_back(&light); }
	inline void setMainCamera(const Camera3D& camera) { m_mainCamera = &camera; }
	inline void setSkybox(const Skybox& skybox) { m_skybox = &skybox; }

	virtual void updateUniformStruct(const Transform& transform, const Material& material, const Shader& shader,
		const std::string& uniformName, const std::string& uniformType) const
	{
		throw uniformType + " is not supported by the rendering engine";
	}

	inline const BaseLight& getActiveLight()                           const { return *m_activeLight; }
	inline unsigned int getSamplerSlot(const std::string& samplerName) const { return m_samplerMap.find(samplerName)->second; }
	inline const glm::mat4& getLightMatrix()                            const { return m_lightMatrix; }
protected:
	inline void setSamplerSlot(const std::string& name, unsigned int value) { m_samplerMap[name] = value; }
private:
	static const int NUM_SHADOW_MAPS = 10;
	static const glm::mat4 BIAS_MATRIX;

	Transform                           m_planeTransform;
	Mesh                                m_plane;

	const Viewport*                       m_window;
	Texture                             m_tempTarget;
	Material                            m_planeMaterial;
	Texture                             m_shadowMaps[NUM_SHADOW_MAPS];
	Texture                             m_shadowMapTempTargets[NUM_SHADOW_MAPS];

	Shader                              m_defaultShader;
	Shader                              m_shadowMapShader;
	Shader                              m_nullFilter;
	Shader                              m_gausBlurFilter;
	Shader                              m_fxaaFilter;
	glm::mat4                           m_lightMatrix;

	Transform                           m_altCameraTransform;
	Camera3D                            m_altCamera;
	const Camera3D*                     m_mainCamera;
	const BaseLight*                    m_activeLight;
	std::vector<const BaseLight*>       m_lights;
	std::map<std::string, unsigned int> m_samplerMap;

	const Skybox*						m_skybox;

	void blurShadowMap(int shadowMapIndex, float blurAmount);
	void applyFilter(const Shader& filter, const Texture& source, const Texture* dest);

	RenderingEngine(const RenderingEngine& other) :
		m_altCamera(glm::mat4(), 0){}
	void operator=(const RenderingEngine& other) {}
};