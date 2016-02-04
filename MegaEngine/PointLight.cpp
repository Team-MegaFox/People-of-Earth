#include "PointLight.h"

#define COLOR_DEPTH 256

PointLight::PointLight(const glm::vec3 & color, float intensity, const Attenuation& attenuation, const Shader& shader) :
BaseLight(color, intensity, shader),
m_attenuation(attenuation)
{
	float a = m_attenuation.getExponent();
	float b = m_attenuation.getLinear();
	float c = m_attenuation.getConstant() - COLOR_DEPTH * intensity * max(color);

	m_range = (-b + sqrtf(b*b - 4 * a*c)) / (2 * a);
}
