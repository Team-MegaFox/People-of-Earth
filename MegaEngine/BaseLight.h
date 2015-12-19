#pragma once

#include "GameComponents.h"
#include "Shader.h"
#include <glm/glm.hpp>

class CoreEngine;

class ShadowCameraTransform
{
public:
	ShadowCameraTransform(const glm::vec3 & pos, const glm::quat & rot) :
		m_pos(pos),
		m_rot(rot) {}

	inline const glm::vec3 & getPos()   const { return m_pos; }
	inline const glm::quat & getRot() const { return m_rot; }
private:
	glm::vec3 m_pos;
	glm::quat m_rot;
	
};

class ShadowInfo
{
public:
	ShadowInfo(const glm::mat4 & projection = glm::mat4(1.0f), bool flipFaces = false, int shadowMapSizeAsPowerOf2 = 0, float shadowSoftness = 1.0f, float lightBleedReductionAmount = 0.2f, float minVariance = 0.00002f) :
		m_projection(projection),
		m_flipFaces(flipFaces),
		m_shadowMapSizeAsPowerOf2(shadowMapSizeAsPowerOf2),
		m_shadowSoftness(shadowSoftness),
		m_lightBleedReductionAmount(lightBleedReductionAmount),
		m_minVariance(minVariance) {}

	inline const glm::mat4 & getProjection()      const { return m_projection; }
	inline bool getFlipFaces()                  const { return m_flipFaces; }
	inline int getShadowMapSizeAsPowerOf2()     const { return m_shadowMapSizeAsPowerOf2; }
	inline float getShadowSoftness()            const { return m_shadowSoftness; }
	inline float getMinVariance()               const { return m_minVariance; }
	inline float getLightBleedReductionAmount() const { return m_lightBleedReductionAmount; }
protected:
private:
	glm::mat4 m_projection;
	bool m_flipFaces;
	int m_shadowMapSizeAsPowerOf2;
	float m_shadowSoftness;
	float m_lightBleedReductionAmount;
	float m_minVariance;
};

class BaseLight 
	: public GameComponent
{
public:
	BaseLight(const glm::vec3 & color, float intensity, const Shader & shader) :
		m_color(color),
		m_intensity(intensity),
		m_shader(shader),
		m_shadowInfo(ShadowInfo()) {}

	virtual ShadowCameraTransform calcShadowCameraTransform(const glm::vec3 & mainCameraPos, const glm::quat & mainCameraRot) const;
	virtual void addToEngine(CoreEngine * engine) const;

	inline const glm::vec3 & getColor()        const { return m_color; }
	inline const float getIntensity()        const { return m_intensity; }
	inline const Shader & getShader()         const { return m_shader; }
	inline const ShadowInfo & getShadowInfo() const { return m_shadowInfo; }
protected:
	inline void setShadowInfo(const ShadowInfo & shadowInfo) { m_shadowInfo = shadowInfo; }
private:
	glm::vec3    m_color;
	float       m_intensity;
	Shader      m_shader;
	ShadowInfo  m_shadowInfo;
};