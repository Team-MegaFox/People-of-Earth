#pragma once
#include "PointLight.h"

class SpotLight : public PointLight
{
public:
	SpotLight(const glm::vec3 & color = glm::vec3(0.0f), float intensity = 0, const Attenuation& atten = Attenuation(), float viewAngle = ToRadians(170.0f),
		int shadowMapSizeAsPowerOf2 = 0, float shadowSoftness = 1.0f, float lightBleedReductionAmount = 0.2f, float minVariance = 0.00002f);

	inline float getCutoff() const { return m_cutoff; }
private:
	float m_cutoff;
};

