#include "DirectionalLight.h"


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
	//glm::vec3 resultPos = mainCameraPos + getForward(mainCameraRot) * getHalfShadowArea();
	//glm::quat resultRot = getTransform().getTransformedRot();

	//float worldTexelSize = (getHalfShadowArea() * 2) / ((float)(1 << getShadowInfo().getShadowMapSizeAsPowerOf2()));


	//// TODO : GLM quaternions work differently than PhysX quaternions, we need to fix this code.

	//glm::vec3 lightSpaceCameraPos = resultRot.getConjugate().rotate(resultPos);

	//lightSpaceCameraPos.x = (worldTexelSize * floor(lightSpaceCameraPos.x / worldTexelSize));
	//lightSpaceCameraPos.y = (worldTexelSize * floor(lightSpaceCameraPos.y / worldTexelSize));

	//resultPos = resultRot.rotate(lightSpaceCameraPos);

	//return ShadowCameraTransform(resultPos, resultRot);

	// Maybe this fixes it???

	glm::vec3 resultPos = mainCameraPos + getForward(mainCameraRot) * getHalfShadowArea();
	glm::quat resultRot = getTransform().getTransformedRot();

	float worldTexelSize = (getHalfShadowArea() * 2) / ((float)(1 << getShadowInfo().getShadowMapSizeAsPowerOf2()));


	// TODO : GLM quaternions work differently than PhysX quaternions, we need to fix this code.
	//glm::quat temp = glm::conjugate(resultRot);
	//glm::quat temp2 = glm::rotate(temp, temp.w, resultPos);

	//::vec3 lightSpaceCameraPos = glm::vec3(temp2.x, temp2.y, temp2.z);

	//lightSpaceCameraPos.x = (worldTexelSize * floor(lightSpaceCameraPos.x / worldTexelSize));
	//lightSpaceCameraPos.y = (worldTexelSize * floor(lightSpaceCameraPos.y / worldTexelSize));

	//glm::quat temp3 = glm::rotate(resultRot, resultRot.w, lightSpaceCameraPos);
	//resultPos = glm::vec3(temp3.x, temp3.y, temp3.z);
	
	
	
	//This will develop a quaternion that is the rotation of the resultRot and on the axis of resultPos
	glm::quat rotation = glm::quat();
	rotation.w = cos(0.5f * resultRot.w);
	rotation.x = resultPos.x * sin(0.5f * resultRot.w);
	rotation.y = resultPos.y * sin(0.5f * resultRot.w);
	rotation.z = resultPos.z * sin(0.5f * resultRot.w);
	
	glm::vec3 lightSpaceCameraPos = glm::vec3(rotation.x, rotation.y, rotation.z);

	lightSpaceCameraPos.x = (worldTexelSize * floor(lightSpaceCameraPos.x / worldTexelSize));
	lightSpaceCameraPos.y = (worldTexelSize * floor(lightSpaceCameraPos.y / worldTexelSize));

	glm::quat temp3 = glm::rotate(resultRot, resultRot.w, lightSpaceCameraPos);
	resultPos = glm::vec3(temp3.x, temp3.y, temp3.z);

	return ShadowCameraTransform(resultPos, resultRot);

}
