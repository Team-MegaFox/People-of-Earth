#include "SpotLight.h"


SpotLight::SpotLight(const glm::vec3 & color, float intensity, const Attenuation& attenuation, float viewAngle,
	int shadowMapSizeAsPowerOf2, float shadowSoftness, float lightBleedReductionAmount, float minVariance) :
	PointLight(color, intensity, attenuation, Shader("forward-spot")),
	m_cutoff(cos(viewAngle / 2))
{
	if (shadowMapSizeAsPowerOf2 != 0)
	{

		setShadowInfo(ShadowInfo(glm::perspective(viewAngle, 1.0f, 0.1f, getRange()), false, shadowMapSizeAsPowerOf2,
			shadowSoftness, lightBleedReductionAmount, minVariance));
		
	}
}
