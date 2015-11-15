#pragma once
#include <vector>
#include "Vertex.h"
#include <glew\glew.h>
#include <string>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>


struct MeshEntry
{

private:
	MeshEntry();
	~MeshEntry();

	void init(const std::vector<Vertex> & vertices, const std::vector<unsigned int> & indices);

	GLuint m_VB;
	GLuint m_IB;
	unsigned int m_numIndices;
	unsigned int m_materialIndex;
};

class ModelMesh
{
public:
	ModelMesh() {}
	~ModelMesh() {}

	bool loadMesh(const std::string & filePath, const std::string & imagesFilePath);
	void render();

private:
	bool initFromScene(const aiScene * scene, const std::string & filePath, const std::string & imagesFilePath);
	void initMesh(unsigned int index, const aiMesh * mesh);
	bool initMaterials(const aiScene * scene, const std::string & filePath, const std::string & imagesFilePath);
	void clear();
};

