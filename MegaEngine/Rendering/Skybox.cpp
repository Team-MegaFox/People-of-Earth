#include "Skybox.h"
#include "..\Core\CoreEngine.h"
#include "RenderingEngine.h"

Skybox::Skybox(const std::string& fileName) :
m_cubeShader("skybox"), 
m_cubeTexture(Utility::split(fileName, '.')[0].substr(0, Utility::split(fileName, '.')[0].length()) + "." + Utility::split(fileName, '.')[1],
GL_TEXTURE_CUBE_MAP, GL_LINEAR, GL_RGBA, GL_RGBA, true)
{
	// Manually creating the cube since when I was trying to use .obj's the texture
	// coordinates would have a weird effect on the bottom side of the cube.
	// You can try doing it though.
	IndexedModel cube;
	{
		cube.addVertex(-1.0f, 1.0f, -1.0f);
		cube.addVertex(-1.0f, -1.0f, -1.0f);
		cube.addVertex(1.0f, -1.0f, -1.0f);
		cube.addFace(0, 1, 2);
		cube.addVertex(1.0f, -1.0f, -1.0f);
		cube.addVertex(1.0f, 1.0f, -1.0f);
		cube.addVertex(-1.0f, 1.0f, -1.0f);
		cube.addFace(3, 4, 5);

		cube.addVertex(-1.0f, -1.0f, 1.0f);
		cube.addVertex(-1.0f, -1.0f, -1.0f);
		cube.addVertex(-1.0f, 1.0f, -1.0f);
		cube.addFace(6, 7, 8);
		cube.addVertex(-1.0f, 1.0f, -1.0f);
		cube.addVertex(-1.0f, 1.0f, 1.0f);
		cube.addVertex(-1.0f, -1.0f, 1.0f);
		cube.addFace(9, 10, 11);

		cube.addVertex(1.0f, -1.0f, -1.0f);
		cube.addVertex(1.0f, -1.0f, 1.0f);
		cube.addVertex(1.0f, 1.0f, 1.0f);
		cube.addFace(12, 13, 14);
		cube.addVertex(1.0f, 1.0f, 1.0f);
		cube.addVertex(1.0f, 1.0f, -1.0f);
		cube.addVertex(1.0f, -1.0f, -1.0f);
		cube.addFace(15, 16, 17);
		
		cube.addVertex(-1.0f, -1.0f, 1.0f);
		cube.addVertex(-1.0f, 1.0f, 1.0f);
		cube.addVertex(1.0f, 1.0f, 1.0f);
		cube.addFace(18, 19, 20);
		cube.addVertex(1.0f, 1.0f, 1.0f);
		cube.addVertex(1.0f, -1.0f, 1.0f);
		cube.addVertex(-1.0f, -1.0f, 1.0f);
		cube.addFace(21, 22, 23);

		cube.addVertex(-1.0f, 1.0f, -1.0f);
		cube.addVertex(1.0f, 1.0f, -1.0f);
		cube.addVertex(1.0f, 1.0f, 1.0f);
		cube.addFace(24, 25, 26);
		cube.addVertex(1.0f, 1.0f, 1.0f);
		cube.addVertex(-1.0f, 1.0f, 1.0f);
		cube.addVertex(-1.0f, 1.0f, -1.0f);
		cube.addFace(27, 28, 29);

		cube.addVertex(-1.0f, -1.0f, -1.0f);
		cube.addVertex(-1.0f, -1.0f, 1.0f);
		cube.addVertex(1.0f, -1.0f, -1.0f);
		cube.addFace(30, 31, 32);
		cube.addVertex(1.0f, -1.0f, -1.0f);
		cube.addVertex(-1.0f, -1.0f, 1.0f);
		cube.addVertex(1.0f, -1.0f, 1.0);
		cube.addFace(33, 35, 35);
	}
	m_cubeMesh = new Mesh("SkyboxCube", cube.finalize());
}	

Skybox::~Skybox()
{
}

void Skybox::render(const RenderingEngine& renderingEngine, const Camera3D & camera) const
{
	m_cubeShader.bind();
	m_cubeShader.updateUniforms(m_cubeTransform, Material("skyboxMaterial", m_cubeTexture), renderingEngine, camera);
	m_cubeMesh->render();
}

void SkyboxRenderer::addToEngine(CoreEngine* engine) const
{
	engine->getRenderingEngine()->setSkybox(m_skybox);
}
