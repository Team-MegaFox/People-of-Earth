#pragma once
#include "BaseLight.h"

class Attenuation
{
public:
	Attenuation(float constant = 0, float linear = 0, float exponent = 1) :
		m_constant(constant),
		m_linear(linear),
		m_exponent(exponent) {}

	inline float getConstant() const { return m_constant; }
	inline float getLinear()   const { return m_linear; }
	inline float getExponent() const { return m_exponent; }
private:
	float m_constant;
	float m_linear;
	float m_exponent;
};

class PointLight 
	: public BaseLight
{
public:
	PointLight(const glm::vec3 & color = glm::vec3(0.0f), float intensity = 0, const Attenuation & atten = Attenuation(),
		const Shader& shader = Shader("forward-point"));

	inline const Attenuation & getAttenuation() const { return m_attenuation; }
	inline const float getRange()              const { return m_range; }
private:
	Attenuation m_attenuation;
	float m_range;
};