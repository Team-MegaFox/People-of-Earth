#include "DirectionalLight.h"
#include "Utility.h"

DirectionalLight::DirectionalLight(const glm::vec3 & color, float intensity, int shadowMapSizeAsPowerOf2,
	float shadowArea, float shadowSoftness, float lightBleedReductionAmount, float minVariance) :
	BaseLight(color, intensity, Shader("forward-directional")),
	m_halfShadowArea(shadowArea / 2.0f)
{
	if (shadowMapSizeAsPowerOf2 != 0)
	{
			setShadowInfo(ShadowInfo(glm::ortho(-m_halfShadowArea, m_halfShadowArea, -m_halfShadowArea, m_halfShadowArea, -m_halfShadowArea, m_halfShadowArea),
			true, shadowMapSizeAsPowerOf2, shadowSoftness, lightBleedReductionAmount, minVariance));
	}
}


ShadowCameraTransform DirectionalLight::calcShadowCameraTransform(const glm::vec3 & mainCameraPos, const glm::quat & mainCameraRot) const
{
	glm::vec3 resultPos = mainCameraPos + getForward(mainCameraRot) * getHalfShadowArea();
	glm::quat resultRot = getTransform().getTransformedRot();

	float worldTexelSize = (getHalfShadowArea() * 2) / ((float)(1 << getShadowInfo().getShadowMapSizeAsPowerOf2()));

	glm::vec3 lightSpaceCameraPos = rotateQuatByVec(glm::conjugate(resultRot), resultPos);
	lightSpaceCameraPos.x = (worldTexelSize * glm::floor(lightSpaceCameraPos.x / worldTexelSize));
	lightSpaceCameraPos.y = (worldTexelSize * glm::floor(lightSpaceCameraPos.y / worldTexelSize));

	resultPos = rotateQuatByVec(resultRot, resultPos);

	return ShadowCameraTransform(resultPos, resultRot);
}
