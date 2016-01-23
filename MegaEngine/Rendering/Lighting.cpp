#include "Lighting.h"
#include "RenderingEngine.h"
#include "..\Core\CoreEngine.h"

#define COLOR_DEPTH 256

void BaseLight::addToEngine(CoreEngine * engine) const
{
	engine->getRenderingEngine()->addLight(*this);
}

ShadowCameraTransform BaseLight::calcShadowCameraTransform(const glm::vec3 & mainCameraPos, const glm::quat & mainCameraRot) const
{
	return ShadowCameraTransform(getTransform().getTransformedPos(), getTransform().getTransformedRot());
}

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

PointLight::PointLight(const glm::vec3 & color, float intensity, const Attenuation& attenuation, const Shader& shader) :
BaseLight(color, intensity, shader),
m_attenuation(attenuation)
{
	float a = m_attenuation.getExponent();
	float b = m_attenuation.getLinear();
	float c = m_attenuation.getConstant() - COLOR_DEPTH * intensity * max(color);

	m_range = (-b + sqrtf(b*b - 4 * a*c)) / (2 * a);
}

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
