#pragma once
#include "BaseLight.h"

class DirectionalLight 
	: public BaseLight
{
public:
	DirectionalLight(const glm::vec3 & color = glm::vec3(0.0f), float intensity = 0, int shadowMapSizeAsPowerOf2 = 0,
		float shadowArea = 80.0f, float shadowSoftness = 1.0f, float lightBleedReductionAmount = 0.2f, float minVariance = 0.00002f);

	virtual ShadowCameraTransform calcShadowCameraTransform(const glm::vec3 & mainCameraPos, const glm::quat & mainCameraRot) const;

	inline float getHalfShadowArea() const { return m_halfShadowArea; }
private:
	float m_halfShadowArea;
};