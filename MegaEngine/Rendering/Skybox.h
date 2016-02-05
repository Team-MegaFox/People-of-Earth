#pragma once
#include <string>
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "..\Core\Transform.h"
#include "..\Components\GameComponents.h"

/*
Order of skybox textures:
right, left, top, bottom, back, front
*/

class Skybox
{
public:
	Skybox(const std::string& fileName);
	~Skybox();

	void render(const RenderingEngine& renderingEngine, const Camera3D & camera) const;

	const Shader& getShader() { return m_cubeShader; }

private:
	Shader m_cubeShader;

	Texture m_cubeTexture;

	Mesh m_cubeMesh;

	Transform m_cubeTransform;

};

class SkyboxRenderer : public GameComponent
{
public:
	SkyboxRenderer(const std::string& fileName) :
		m_skybox(fileName) { }
	~SkyboxRenderer() { }

	virtual void addToEngine(CoreEngine* engine) const;

private:
	Skybox m_skybox;
};

