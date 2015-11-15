#pragma once
#include "Material.h"
#include "GameComponents.h"
#include "ModelMesh.h"


class MeshRenderer 
	: public GameComponent
{
public:
	MeshRenderer(const ModelMesh & mesh, const Material & material);
	virtual void render(const Shader & shader, const RenderingEngine & renderingEngine, const Camera3D & camera) const;

private:
	Material m_material;
};

