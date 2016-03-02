// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 03-01-2016
// ***********************************************************************
// <copyright file="Lighting.cpp" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#include "Lighting.h"
#include "RenderingEngine.h"
#include "..\Core\CoreEngine.h"

#define COLOR_DEPTH 256

void BaseLight::addToEngine(CoreEngine* engine) const
{
	engine->getRenderingEngine()->addLight(*this);
}

ShadowCameraTransform BaseLight::calcShadowCameraTransform(const PxVec3& mainCameraPos, const PxQuat& mainCameraRot) const
{
	return ShadowCameraTransform(getTransform().getTransformedPos(), getTransform().getTransformedRot());
}

DirectionalLight::DirectionalLight(const PxVec3& color, float intensity, int shadowMapSizeAsPowerOf2,
	float shadowArea, float shadowSoftness, float lightBleedReductionAmount, float minVariance) :
	BaseLight(color, intensity, Shader("forward-directional")),
	m_halfShadowArea(shadowArea / 2.0f)
{
	if (shadowMapSizeAsPowerOf2 != 0)
	{
		setShadowInfo(ShadowInfo(Utility::initOrthographic(-m_halfShadowArea, m_halfShadowArea, -m_halfShadowArea,
			m_halfShadowArea, -m_halfShadowArea, m_halfShadowArea),
			true, shadowMapSizeAsPowerOf2, shadowSoftness, lightBleedReductionAmount, minVariance));
	}
}


ShadowCameraTransform DirectionalLight::calcShadowCameraTransform(const PxVec3& mainCameraPos, const PxQuat& mainCameraRot) const
{
	PxVec3 resultPos = mainCameraPos + Utility::getForward(mainCameraRot) * getHalfShadowArea();
	PxQuat resultRot = getTransform().getTransformedRot();

	float worldTexelSize = (getHalfShadowArea() * 2) / ((float)(1 << getShadowInfo().getShadowMapSizeAsPowerOf2()));

	PxVec3 lightSpaceCameraPos = resultRot.getConjugate().rotate(resultPos);

	lightSpaceCameraPos.x = (worldTexelSize * floor(lightSpaceCameraPos.x / worldTexelSize));
	lightSpaceCameraPos.y = (worldTexelSize * floor(lightSpaceCameraPos.y / worldTexelSize));

	resultPos = resultRot.rotate(lightSpaceCameraPos);

	return ShadowCameraTransform(resultPos, resultRot);
}

PointLight::PointLight(const PxVec3& color, float intensity, const Attenuation& attenuation, const Shader& shader) :
BaseLight(color, intensity, shader),
m_attenuation(attenuation)
{
	float a = m_attenuation.getExponent();
	float b = m_attenuation.getLinear();
	float c = m_attenuation.getConstant() - COLOR_DEPTH * intensity * Utility::maxVec3(color);

	m_range = (-b + sqrtf(b*b - 4 * a*c)) / (2 * a);
}

SpotLight::SpotLight(const PxVec3& color, float intensity, const Attenuation& attenuation, float viewAngle,
	int shadowMapSizeAsPowerOf2, float shadowSoftness, float lightBleedReductionAmount, float minVariance) :
	PointLight(color, intensity, attenuation, Shader("forward-spot")),
	m_cutoff(cos(viewAngle / 2))
{
	if (shadowMapSizeAsPowerOf2 != 0)
	{
		setShadowInfo(ShadowInfo(Utility::initPerspective(viewAngle, 1.0f, 0.1f, getRange()), false, shadowMapSizeAsPowerOf2,
			shadowSoftness, lightBleedReductionAmount, minVariance));
	}
}