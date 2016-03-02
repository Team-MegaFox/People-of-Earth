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
#pragma once
#include "..\Components\GameComponents.h"
#include "Shader.h"
#include <PhysX\PxPhysicsAPI.h>
using namespace physx;

class CoreEngine;

/// <summary>
/// The position and rotation of the shadow from the camera's point of view.
/// </summary>
class ShadowCameraTransform
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="ShadowCameraTransform"/> class.
	/// </summary>
	/// <param name="pos">The position.</param>
	/// <param name="rot">The rot.</param>
	ShadowCameraTransform(const PxVec3& pos, const PxQuat& rot) :
		m_pos(pos),
		m_rot(rot) {}

	/// <summary>
	/// Gets the position.
	/// </summary>
	/// <returns>The position vector.</returns>
	inline const PxVec3& getPosition()   const { return m_pos; }
	/// <summary>
	/// Gets the rot.
	/// </summary>
	/// <returns>The rotation.</returns>
	inline const PxQuat& GetRotation() const { return m_rot; }
private:
	/// <summary>
	/// The position vector of the shadow from the camera.
	/// </summary>
	PxVec3 m_pos;
	/// <summary>
	/// The rotation quaternion of the shadow from the camera.
	/// </summary
	PxQuat m_rot;
};

/// <summary>
/// Information about the shadow such as how soft the edges are and how it is projected onto a surface.
/// </summary>
class ShadowInfo
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="ShadowInfo"/> class.
	/// </summary>
	/// <param name="projection">The projection matrix.</param>
	/// <param name="flipFaces">If to flip the faces of the shadow.</param>
	/// <param name="shadowMapSizeAsPowerOf2">The shadow map size as power of 2.</param>
	/// <param name="shadowSoftness">The shadow softness.</param>
	/// <param name="lightBleedReductionAmount">The light bleed reduction amount.</param>
	/// <param name="minVariance">The minimum variance.</param>

	ShadowInfo(const PxMat44& projection = PxMat44(PxVec4(1,1,1,1)), bool flipFaces = false, int shadowMapSizeAsPowerOf2 = 0, float shadowSoftness = 1.0f, float lightBleedReductionAmount = 0.2f, float minVariance = 0.00002f) :
		m_projection(projection),
		m_flipFaces(flipFaces),
		m_shadowMapSizeAsPowerOf2(shadowMapSizeAsPowerOf2),
		m_shadowSoftness(shadowSoftness),
		m_lightBleedReductionAmount(lightBleedReductionAmount),
		m_minVariance(minVariance) {}

	/// <summary>
	/// Gets the projection.
	/// </summary>
	/// <returns>A const refernce to the projection view matrix of the shadow.</returns>
	inline const PxMat44& getProjection()       const { return m_projection; }
	/// <summary>
	/// Gets the flip faces.
	/// </summary>
	/// <returns>if the shadow has flipped faces./returns>
	inline bool getFlipFaces()                  const { return m_flipFaces; }
	/// <summary>
	/// Gets the shadow map size as power of 2.
	/// </summary>
	/// <returns>The size of the map to the power of 2.</returns>
	inline int getShadowMapSizeAsPowerOf2()     const { return m_shadowMapSizeAsPowerOf2; }
	/// <summary>
	/// Gets the shadow softness.
	/// </summary>
	/// <returns>How soft the shadows are.</returns>
	inline float getShadowSoftness()            const { return m_shadowSoftness; }
	/// <summary>
	/// Gets the minimum variance.
	/// </summary>
	/// <returns>The minimum variance value.</returns>
	inline float getMinVariance()               const { return m_minVariance; }
	/// <summary>
	/// Gets the light bleed reduction amount.
	/// </summary>
	/// <returns>The light bleed amount.</returns>
	inline float getLightBleedReductionAmount() const { return m_lightBleedReductionAmount; }
protected:
private:
	/// <summary>
	/// The projection view matrix of the shadow.
	/// </summary>
	PxMat44 m_projection;
	/// <summary>
	/// Wheather to flip faces.
	/// </summary>
	bool m_flipFaces;
	/// <summary>
	/// The shadow map size as power of 2.
	/// </summary>
	int m_shadowMapSizeAsPowerOf2;
	/// <summary>
	/// The shadow softness.
	/// </summary>
	float m_shadowSoftness;
	/// <summary>
	/// The light bleed reduction amount.
	/// </summary>
	float m_lightBleedReductionAmount;
	/// <summary>
	/// The minimum variance amount.
	/// </summary>
	float m_minVariance;
};

/// <summary>
/// The base class for the different types of light. It stores the colour, intensity, shadow info and the current shader.
/// It also inherits <see cref="GameComponent"/> so the lights can be attached to a GameObject and added to a scene.
/// </summary>
/// <seealso cref="GameComponent" />
class BaseLight : public GameComponent
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="BaseLight"/> class.
	/// </summary>
	/// <param name="color">The color.</param>
	/// <param name="intensity">The intensity.</param>
	/// <param name="shader">The current shader.</param>
	BaseLight(const PxVec3& color, float intensity, const Shader& shader) :
		m_color(color),
		m_intensity(intensity),
		m_shader(shader),
		m_shadowInfo(ShadowInfo()) {}

	/// <summary>
	/// A virtual function to be implemented differently based on the type of light.
	/// The default beahviour is to use the attached GameObject's position and rotation for the Shadow's position and rotation.
	/// </summary>
	/// <param name="mainCameraPos">The main camera position.</param>
	/// <param name="mainCameraRot">The main camera rotation.</param>
	/// <returns>The resulting transform of the shadow.</returns>
	virtual ShadowCameraTransform calcShadowCameraTransform(const PxVec3& mainCameraPos, const PxQuat& mainCameraRot) const;
	/// <summary>
	/// Adds to Core Engine.
	/// </summary>
	/// <param name="engine">The Core Engine.</param>
	virtual void addToEngine(CoreEngine* engine) const;

	/// <summary>
	/// Gets the color.
	/// </summary>
	/// <returns>A const reference of the colour RBG values.</returns>
	inline const PxVec3& getColor()          const { return m_color; }
	/// <summary>
	/// Gets the intensity.
	/// </summary>
	/// <returns>The amount of light intensity.</returns>
	inline const float getIntensity()        const { return m_intensity; }
	/// <summary>
	/// Gets the current shader.
	/// </summary>
	/// <returns>A const reference to the current shader program.</returns>
	inline const Shader& getShader()         const { return m_shader; }
	/// <summary>
	/// Gets the shadow information.
	/// </summary>
	/// <returns>A const reference to the shadow information.</returns>
	inline const ShadowInfo& getShadowInfo() const { return m_shadowInfo; }
protected:
	/// <summary>
	/// Sets the shadow information.
	/// </summary>
	/// <param name="shadowInfo">The shadow information of this light.</param>
	inline void setShadowInfo(const ShadowInfo& shadowInfo) { m_shadowInfo = shadowInfo; }
private:
	/// <summary>
	/// The color RBG values.
	/// </summary>
	PxVec3      m_color;
	/// <summary>
	/// The light intensity.
	/// </summary>
	float       m_intensity;
	/// <summary>
	/// The current shader program for this light.
	/// </summary>
	Shader      m_shader;
	/// <summary>
	/// The light's shadow information.
	/// </summary>

	ShadowInfo  m_shadowInfo;
};

/// <summary>
/// A traditional Directional light that simulates light from one direction so all 
/// the shadows are parallel to direction it is facing. 
/// It inherits <see cref="BaseLight"/>.
/// </summary>
/// <seealso cref="BaseLight" />
class DirectionalLight : public BaseLight
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="DirectionalLight"/> class.
	/// </summary>
	/// <param name="color">The RBG colour values.</param>
	/// <param name="intensity">The light intensity.</param>
	/// <param name="shadowMapSizeAsPowerOf2">The shadow map size as power of 2.</param>
	/// <param name="shadowArea">The shadow area.</param>
	/// <param name="shadowSoftness">The amount of shadow softness.</param>
	/// <param name="lightBleedReductionAmount">The light bleed reduction amount.</param>
	/// <param name="minVariance">The minimum variance amount.</param>
	DirectionalLight(const PxVec3& color = PxVec3(0, 0, 0), float intensity = 0, int shadowMapSizeAsPowerOf2 = 0,
		float shadowArea = 80.0f, float shadowSoftness = 1.0f, float lightBleedReductionAmount = 0.2f, float minVariance = 0.00002f);

	/// <summary>
	/// Virtually overridden function to calculate the Transform of the shadow from the camera's point of view.
	/// Calculates the shadow's position and rotation but limits the shadow area so it doesn't have a large shadow area.
	/// </summary>
	/// <param name="mainCameraPos">The main camera position.</param>
	/// <param name="mainCameraRot">The main camera rotation.</param>
	/// <returns>The transform of the shadow from the Directional Light's point of view.</returns>
	virtual ShadowCameraTransform calcShadowCameraTransform(const PxVec3& mainCameraPos, const PxQuat& mainCameraRot) const;

	/// <summary>
	/// Gets the half shadow area.
	/// </summary>
	/// <returns>The half of the shadow area.</returns>
	inline float getHalfShadowArea() const { return m_halfShadowArea; }
private:
	/// <summary>
	/// The area where the directional light will cast shadows in.
	/// </summary>
	float m_halfShadowArea;
};

/// <summary>
/// The Attenuation of a light. Used for <see cref="SpotLight"/> and <see cref="PointLight"/>.
/// </summary>
class Attenuation
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Attenuation"/> class.
	/// </summary>
	/// <param name="constant">The constant factor.</param>
	/// <param name="linear">The linear factor.</param>
	/// <param name="exponent">The exponent factor.</param>
	Attenuation(float constant = 0, float linear = 0, float exponent = 1) :
		m_constant(constant),
		m_linear(linear),
		m_exponent(exponent) {}

	/// <summary>
	/// Gets the constant factor.
	/// </summary>
	/// <returns>The constant factor.</returns>
	inline float getConstant() const { return m_constant; }
	/// <summary>
	/// Gets the linear factor.
	/// </summary>
	/// <returns>The linear factor.</returns>
	inline float getLinear()   const { return m_linear; }
	/// <summary>
	/// Gets the exponent factor.
	/// </summary>
	/// <returns>The exponent factor.</returns>
	inline float getExponent() const { return m_exponent; }
private:
	/// <summary>
	/// The constant factor.
	/// </summary>
	float m_constant;
	/// <summary>
	/// The linear factor.
	/// </summary>
	float m_linear;
	/// <summary>
	/// The exponent factor.
	/// </summary>
	float m_exponent;
};

/// <summary>
/// A traditional Point Light where light is emitted from all directions from a point in space.
/// </summary>
/// <seealso cref="BaseLight" /
class PointLight : public BaseLight
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="PointLight"/> class.
	/// </summary>
	/// <param name="color">The RBG color values. Defaults to black.</param>
	/// <param name="intensity">The light intensity. Defaults to 0.</param>
	/// <param name="atten">The attenuation. Defaults to a constant and linear of 0 and exponent of 1.</param>
	/// <param name="shader">The current shader. Defaults to forward-point shader.</param>
	PointLight(const PxVec3& color = PxVec3(0, 0, 0), float intensity = 0, const Attenuation& atten = Attenuation(),
		const Shader& shader = Shader("forward-point"));

	/// <summary>
	/// Gets the attenuation information of the point light.
	/// </summary>
	/// <returns>A reference to the attenuation object.</returns>
	inline const Attenuation& getAttenuation() const { return m_attenuation; }
	/// <summary>
	/// Gets the light range.
	/// </summary>
	/// <returns>The light range.</returns>
	inline const float getRange()              const { return m_range; }
private:
	/// <summary>
	/// The light's attenuation.
	/// </summary>
	Attenuation m_attenuation;
	/// <summary>
	/// The light's reach distance.
	/// </summary>
	float m_range;
};

/// <summary>
/// A traditional Spot Light where light is emitted from a point in space in a cone shape.
/// </summary>
/// <seealso cref="PointLight" />
class SpotLight : public PointLight
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="SpotLight"/> class.
	/// </summary>
	/// <param name="color">The RBG color values. Defaults to black.</param>
	/// <param name="intensity">The light intensity. Defaults to 0.</param>
	/// <param name="atten">The light's attenuation. Defaults to a constant and linear of 0 and exponent of 1.</param>
	/// <param name="viewAngle">The light's view angle. Defaults to 170 degrees.</param>
	/// <param name="shadowMapSizeAsPowerOf2">The shadow map size as power of 2. Defaults to 0.</param>
	/// <param name="shadowSoftness">The shadow softness. Defualts to 1.</param>
	/// <param name="lightBleedReductionAmount">The light bleed reduction amount. Defaults to 0.2.</param>
	/// <param name="minVariance">The amount of minimum variance. Defaults to 0.00002.</param>
	SpotLight(const PxVec3& color = PxVec3(0, 0, 0), float intensity = 0, const Attenuation& atten = Attenuation(), float viewAngle = ToRadians(170.0f),
		int shadowMapSizeAsPowerOf2 = 0, float shadowSoftness = 1.0f, float lightBleedReductionAmount = 0.2f, float minVariance = 0.00002f);

	/// <summary>
	/// Gets the cutoff distnace.
	/// </summary>
	/// <returns>The distance from the light's position where the light cuts off.</returns>
	inline float getCutoff() const { return m_cutoff; }
private:
	/// <summary>
	/// The cutoff distance from the light's position in space.
	/// </summary>
	float m_cutoff;
};