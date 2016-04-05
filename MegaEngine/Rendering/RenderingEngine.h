// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Jesse Derochie
// Last Modified On : 03-31-2016
// ***********************************************************************
// <copyright file="RenderingEngine.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once
#include "Camera3D.h"
#include "Lighting.h"
#include "Viewport.h"
#include "Material.h"
#include "Mesh.h"
#include "Skybox.h"
#include "BloomObject.h"
#include "..\Core\MappedValues.h"
#include <vector>
#include <map>
#include <algorithm>
class GameObject;
class ParticleSystem;

/// <summary>
/// The Rendering Engine class where it manages all the lights and cameras. 
/// The class also renders the GameObjects by passing its self, the current shader program and the main camera.
/// It renders the lights individually one at a time to calculate the shadows, also know as Forward Rendering.
/// </summary>
/// <seealso cref="MappedValues" />
class RenderingEngine : public MappedValues
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="RenderingEngine"/> class by setting the 
	/// default values and setting the textures and shaders to their appropriate values.
	/// It also initializes the number of shadow map textures.
	/// </summary>
	/// <param name="viewport">The viewport.</param>
	RenderingEngine(const Viewport& window);
	/// <summary>
	/// Finalizes an instance of the <see cref="RenderingEngine"/> class.
	/// </summary>
	virtual ~RenderingEngine() {}

	/// <summary>
	/// Renders the root game object of a scene and applies all shaders and filters to the final output on screen.
	/// </summary>
	/// <param name="gameObject">The root game object of the scene.</param>
	void render(const GameObject& object);

	/// <summary>
	/// Adds a light.
	/// </summary>
	/// <param name="light">The light to add to the rendering engine.</param>
	inline void addLight(const BaseLight& light) { m_lights.push_back(&light); }
	/// <summary>
	/// Adds a particle system to the rendering engine.
	/// </summary>
	/// <param name="light">The particle system to add to the rendering engine.</param>
	inline void addParticleSystem(const ParticleSystem& particles) { m_particleSystems.push_back(&particles); }
	/// <summary>
	/// Sets the main camera.
	/// </summary>
	/// <param name="camera">The camera.</param>
	inline void setMainCamera(const Camera3D& camera) { m_mainCamera = &camera; }
	/// <summary>
	/// Sets the skybox for the render.
	/// </summary>
	/// <param name="skybox">The skybox.</param>
	inline void setSkybox(const Skybox& skybox) { m_skybox = &skybox; }

	inline void setBloomObject(const BloomObject& bObject) { m_bloomObject = &bObject; }

	inline void removeBloomObject() { m_bloomObject = nullptr; }

	/// <summary>
	/// Removes a light.
	/// </summary>
	/// <param name="light">The light to remove.</param>
	void removeLight(const BaseLight* light) { m_lights.erase(std::remove(m_lights.begin(), m_lights.end(), light), m_lights.end()); }
	/// <summary>
	/// Removes the skybox from the rendering engine.
	/// </summary>
	inline void removeSkybox() { m_skybox = nullptr; }

	/// <summary>
	/// A virtual function that may be overriden.
	/// Throws an exception by default is used to tell the user that this uniform type is not supported.
	/// </summary>
	/// <param name="transform">The transform.</param>
	/// <param name="material">The material.</param>
	/// <param name="shader">The shader program.</param>
	/// <param name="uniformName">Name of the uniform.</param>
	/// <param name="uniformType">Type of the uniform.</param>
	virtual void updateUniformStruct(const Transform& transform, const Material& material, const Shader& shader,
		const std::string& uniformName, const std::string& uniformType) const
	{
		throw uniformType + " is not supported by the rendering engine";
	}

	// Getters
	/// <summary>
	/// Gets the active light.
	/// </summary>
	/// <returns>A const reference to the active light.</returns>
	inline const BaseLight& getActiveLight()                           const { return *m_activeLight; }
	/// <summary>
	/// Gets the sampler slot.
	/// </summary>
	/// <param name="samplerName">Name of the sampler.</param>
	/// <returns>The position where the sample is stored in the graphics card..</returns>
	inline unsigned int getSamplerSlot(const std::string& samplerName) const { return m_samplerMap.find(samplerName)->second; }
	/// <summary>
	/// Gets the light matrix.
	/// </summary>
	/// <returns>The light matrix.</returns>
	inline const PxMat44& getLightMatrix()                             const { return m_lightMatrix; }
protected:
	/// <summary>
	/// Sets the sampler slot.
	/// </summary>
	/// <param name="name">The name.</param>
	/// <param name="value">The value.</param>
	inline void setSamplerSlot(const std::string& name, unsigned int value) { m_samplerMap[name] = value; }
private:
	/// <summary>
	/// The number of shadow maps.
	/// </summary>
	static const int NUM_SHADOW_MAPS = 10;
	static const PxMat44 BIAS_MATRIX;

	/// <summary>
	/// The viewport.
	/// </summary>
	const Viewport*                     m_window;

	/// <summary>
	/// The filter plane's transform.
	/// </summary>
	Transform                           m_planeTransform;
	/// <summary>
	/// The filter plane mesh.
	/// </summary>
	Mesh                                m_plane;
	/// <summary>
	/// The temporary target texture.
	/// </summary>
	Texture                             m_tempTarget;
	/// <summary>
	/// The filter plane's material.
	/// </summary>
	Material                            m_planeMaterial;

	/// <summary>
	/// The shadow map textures.
	/// </summary>
	Texture                             m_shadowMaps[NUM_SHADOW_MAPS];
	/// <summary>
	/// The shadow map texure temporary targets.
	/// </summary>
	Texture                             m_shadowMapTempTargets[NUM_SHADOW_MAPS];

	/// <summary>
	/// The default shader program.
	/// </summary>
	Shader                              m_defaultShader;
	/// <summary>
	/// The shadow map shader program.
	/// </summary>
	Shader                              m_shadowMapShader;
	/// <summary>
	/// The null filter shader program.
	/// </summary>
	Shader                              m_nullFilter;
	/// <summary>
	/// The null filter shader program.
	/// </summary>
	Shader                              m_gausBlurFilter;
	/// <summary>
	/// The fxaa (anti-alias) filter shader program.
	/// </summary>
	Shader                              m_fxaaFilter;
	/// <summary>
	/// The particle shader program.
	/// </summary>
	Shader								m_particleShader;
	/// <summary>
	/// The light matrix.
	/// </summa
	PxMat44                             m_lightMatrix;

	/// <summary>
	/// The alternate camera's transform.
	/// Usually used for calculating shadows.
	/// </summary>
	Transform                           m_altCameraTransform;
	/// <summary>
	/// The alteranate camera.
	/// Usually used for calculating shadows.
	/// </summary>
	Camera3D                            m_altCamera;
	/// <summary>
	/// The main camera.
	/// </summary>
	const Camera3D*                     m_mainCamera;

	/// <summary>
	/// The active light.
	/// </summary>
	const BaseLight*                    m_activeLight;
	/// <summary>
	/// The array of lights in the engine.
	/// </summary>
	std::vector<const BaseLight*>       m_lights;
	/// <summary>
	/// The sampler map.
	/// </summary>
	std::map<std::string, unsigned int> m_samplerMap;

	/// <summary>
	/// A pointer to the Skybox in the current scene.
	/// </summary>
	const Skybox*						m_skybox;

	/// <summary>
	/// A pointer to the bloomObject in the current scene
	/// </summary>
	const BloomObject *				m_bloomObject;

	/// <summary>
	/// A vector of particle systems to render.
	/// </summary>
	std::vector<const ParticleSystem*> m_particleSystems;

	/// <summary>
	/// Blurs the shadow map.
	/// </summary>
	/// <param name="shadowMapIndex">Index of the shadow map.</param>
	/// <param name="blurAmount">The blur amount.</param>
	void blurShadowMap(int shadowMapIndex, float blurAmount);
	/// <summary>
	/// Applies a filter to a texture.
	/// </summary>
	/// <param name="filter">The filter.</param>
	/// <param name="src">The source texture.</param>
	/// <param name="dst">The destination texture.</param>
	void applyFilter(const Shader& filter, const Texture& source, const Texture* dest);

	RenderingEngine(const RenderingEngine& other) :
		m_altCamera(PxMat44(), 0){}
	void operator=(const RenderingEngine& other) {}
};