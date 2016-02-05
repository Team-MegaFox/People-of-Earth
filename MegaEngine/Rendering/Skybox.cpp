#include "Skybox.h"
#include "..\Core\CoreEngine.h"
#include "RenderingEngine.h"

Skybox::Skybox(const std::string& fileName) :
m_cubeMesh("Primitives/Shape_Cube.OBJ"),
m_cubeShader("skybox"), 
m_cubeTexture(Utility::split(fileName, '.')[0].substr(0, Utility::split(fileName, '.')[0].length()) + "." + Utility::split(fileName, '.')[1],
GL_TEXTURE_CUBE_MAP, GL_LINEAR, GL_RGBA, GL_RGBA, true)
{
}	

Skybox::~Skybox()
{
}

void Skybox::render(const RenderingEngine& renderingEngine, const Camera3D & camera) const
{
	m_cubeShader.bind();
	m_cubeShader.updateUniforms(m_cubeTransform, Material("skyboxMaterial", m_cubeTexture), renderingEngine, camera);
	m_cubeMesh.render();
}

void SkyboxRenderer::addToEngine(CoreEngine* engine) const
{
	engine->getRenderingEngine()->setSkybox(m_skybox);
}
