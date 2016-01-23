#pragma once
#include "GameComponents.h"
#include "..\Rendering\Material.h"
#include "..\Rendering\Mesh.h"
#include "..\Rendering\Shader.h"


class MeshRenderer 
	: public GameComponent
{
public:
	MeshRenderer(const Mesh & mesh, const Material & material) : 
		m_mesh(mesh), m_material(material) { }
	virtual void render(const Shader & shader, const RenderingEngine & renderingEngine, const Camera3D & camera) const
	{
		shader.bind();
		shader.updateUniforms(getTransform(), m_material, renderingEngine, camera);
		m_mesh.render();
	}

private:
	Mesh m_mesh;
	Material m_material;
};

