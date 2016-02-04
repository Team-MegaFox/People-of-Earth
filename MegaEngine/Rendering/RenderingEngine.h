// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 01-24-2016
// ***********************************************************************
// <copyright file="RenderingEngine.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once
#include <glm\glm.hpp>
#include <vector>
#include <map>
#include <string>

#include "..\Core\MappedValues.h"
#include "..\GUI\GUIEngine.h"
#include "Viewport.h"
#include "Texture.h"
#include "Shader.h"
#include "Material.h"
#include "Camera3D.h"
#include "Mesh.h"

class GameObject;
class BaseLight;

/// <summary>
/// The Rendering Engine class where it manages all the lights and cameras. 
/// The class also renders the GameObjects by passing its self, the current shader program and the main camera.
/// It renders the lights individually one at a time to calculate the shadows, also know as Forward Rendering.
/// </summary>
/// <seealso cref="MappedValues" />
class RenderingEngine
	: public MappedValues
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="RenderingEngine"/> class by setting the 
	/// default values and setting the textures and shaders to their appropriate values.
	/// It also initializes the number of shadow map textures.
	/// </summary>
	/// <param name="viewport">The viewport.</param>
	/// <param name="guiEngine">The GUI engine.</param>
	RenderingEngine(Viewport& viewport, GUIEngine& guiEngine);
	/// <summary>
	/// Finalizes an instance of the <see cref="RenderingEngine"/> class.
	/// </summary>
	~RenderingEngine() { }

	/// <summary>
	/// Renders the specified game object.
	/// </summary>
	/// <param name="gameObject">The game object.</param>
	void render(GameObject & gameObject);

	/// <summary>
	/// Adds a light.
	/// </summary>
	/// <param name="light">The light.</param>
	inline void addLight(const BaseLight & light) { m_lights.push_back(&light); }
	/// <summary>
	/// Sets the main camera.
	/// </summary>
	/// <param name="camera">The camera.</param>
	inline void setMainCamera(const Camera3D & camera) { m_mainCamera = &camera; }
	
	// Getters
	/// <summary>
	/// Gets the active light.
	/// </summary>
	/// <returns>A const reference to the active light.</returns>
	const BaseLight & getActiveLight() const { return *m_activeLight; }
	/// <summary>
	/// Gets the sampler slot.
	/// </summary>
	/// <param name="samplerName">Name of the sampler.</param>
	/// <returns>The position where the sample is stored in the graphics card..</returns>
	inline unsigned int getSamplerSlot(const std::string & samplerName) const { return m_samplerMap.find(samplerName)->second; }
	/// <summary>
	/// Gets the light matrix.
	/// </summary>
	/// <returns>The light matrix.</returns>
	glm::mat4 getLightMatrix() const { return m_lightMatrix; }

	/// <summary>
	/// Updates the uniform structure.
	/// </summary>
	/// <param name="transform">The transform.</param>
	/// <param name="material">The material.</param>
	/// <param name="shader">The shader program.</param>
	/// <param name="uniformName">Name of the uniform.</param>
	/// <param name="uniformType">Type of the uniform.</param>
	virtual void updateUniformStruct(const Transform & transform, const Material & material, const Shader & shader,
		const std::string& uniformName, const std::string & uniformType) const
	{
		throw uniformType + " is not supported by the rendering engine";
	}

private:
	/// <summary>
	/// The number of shadow maps.
	/// </summary>
	static const int NUM_SHADOW_MAPS = 10;
	static const glm::mat4 BIAS_MATRIX;

	/// <summary>
	/// The viewport.
	/// </summary>
	const Viewport * m_viewport;
	/// <summary>
	/// The GUI engine.
	/// </summary>
	const GUIEngine * m_guiEngine;

	/// <summary>
	/// The shadow map textures.
	/// </summary>
	Texture m_shadowMaps[NUM_SHADOW_MAPS];
	/// <summary>
	/// The shadow map texure temporary targets.
	/// </summary>
	Texture m_shadowMapTempTargets[NUM_SHADOW_MAPS];

	/// <summary>
	/// The filter plane's transform.
	/// </summary>
	Transform m_filterPlaneTransform;
	/// <summary>
	/// The filter plane mesh.
	/// </summary>
	Mesh m_filterPlane;
	/// <summary>
	/// The temporary target texture.
	/// </summary>
	Texture m_tempTarget;
	/// <summary>
	/// The filter plane's material.
	/// </summary>
	Material m_filterPlaneMaterial;

	/// <summary>
	/// The default shader program.
	/// </summary>
	Shader m_defaultShader;
	/// <summary>
	/// The shadow map shader program.
	/// </summary>
	Shader m_shadowMapShader;
	/// <summary>
	/// The null filter shader program.
	/// </summary>
	Shader m_nullFilter;
	/// <summary>
	/// The guass filter shader program.
	/// </summary>
	Shader m_guassFilter;
	/// <summary>
	/// The fxaa (anti-alias) filter shader program.
	/// </summary>
	Shader m_fxaaFilter;
	/// <summary>
	/// The gaus blur filter shader program.
	/// </summary>
	Shader m_gausBlurFilter;
	/// <summary>
	/// The light matrix.
	/// </summary>
	glm::mat4 m_lightMatrix;
	
	/// <summary>
	/// The alternate camera's transform.
	/// Usually used for calculating shadows.
	/// </summary>
	Transform m_altCameraTransform;
	/// <summary>
	/// The alteranate camera.
	/// Usually used for calculating shadows.
	/// </summary>
	Camera3D m_altCamera;
	/// <summary>
	/// The main camera.
	/// </summary>
	const Camera3D * m_mainCamera;
	
	/// <summary>
	/// The active light.
	/// </summary>
	const BaseLight * m_activeLight;
	/// <summary>
	/// The vector of lights in the engine.
	/// </summary>
	std::vector<const BaseLight*> m_lights;
	/// <summary>
	/// The sampler map.
	/// </summary>
	std::map<std::string, unsigned int> m_samplerMap;

	/// <summary>
	/// Applies the filter.
	/// </summary>
	/// <param name="filter">The filter.</param>
	/// <param name="src">The source texture.</param>
	/// <param name="dst">The destination texture.</param>
	void applyFilter(const Shader & filter, const Texture & src, const Texture * dst);
	/// <summary>
	/// Blurs the shadow map.
	/// </summary>
	/// <param name="shadowMapIndex">Index of the shadow map.</param>
	/// <param name="blurAmount">The blur amount.</param>
	void blurShadowMap(int shadowMapIndex, float blurAmount);

protected:
	/// <summary>
	/// Sets the sampler slot.
	/// </summary>
	/// <param name="name">The name.</param>
	/// <param name="value">The value.</param>
	void setSamplerSlot(std::string name, GLuint value);
};

