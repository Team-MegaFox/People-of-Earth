// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 03-01-2016
// ***********************************************************************
// <copyright file="Mesh.cpp" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#include "Mesh.h"
#include <iostream>

#include <vector>
#include <cassert>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

std::map<std::string, MeshData*> Mesh::s_resourceMap;

bool IndexedModel::isValid() const
{
	return m_positions.size() == m_texCoords.size()
		&& m_texCoords.size() == m_normals.size()
		&& m_normals.size() == m_tangents.size();
}

void IndexedModel::addVertex(const PxVec3& vert)
{
	m_positions.push_back(vert);
}

void IndexedModel::addTexCoord(const PxVec2& texCoord)
{
	m_texCoords.push_back(texCoord);
}

void IndexedModel::addNormal(const PxVec3& normal)
{
	m_normals.push_back(normal);
}

void IndexedModel::addTangent(const PxVec3& tangent)
{
	m_tangents.push_back(tangent);
}

IndexedModel IndexedModel::finalize()
{
	if (isValid())
	{
		return *this;
	}

	if (m_texCoords.size() == 0)
	{
		for (unsigned int i = m_texCoords.size(); i < m_positions.size(); i++)
		{
			m_texCoords.push_back(PxVec2(0.0f, 0.0f));
		}
	}

	if (m_normals.size() == 0)
	{
		calcNormals();
	}

	if (m_tangents.size() == 0)
	{
		calcTangents();
	}

	return *this;
}

void IndexedModel::addFace(unsigned int vertIndex0, unsigned int vertIndex1, unsigned int vertIndex2)
{
	m_indices.push_back(vertIndex0);
	m_indices.push_back(vertIndex1);
	m_indices.push_back(vertIndex2);
}

void IndexedModel::calcNormals()
{
	m_normals.clear();
	m_normals.reserve(m_positions.size());

	for (unsigned int i = 0; i < m_positions.size(); i++)
		m_normals.push_back(PxVec3(0, 0, 0));

	for (unsigned int i = 0; i < m_indices.size(); i += 3)
	{
		int i0 = m_indices[i];
		int i1 = m_indices[i + 1];
		int i2 = m_indices[i + 2];

		PxVec3 v1 = m_positions[i1] - m_positions[i0];
		PxVec3 v2 = m_positions[i2] - m_positions[i0];

		PxVec3 normal = v1.cross(v2).getNormalized();

		m_normals[i0] = m_normals[i0] + normal;
		m_normals[i1] = m_normals[i1] + normal;
		m_normals[i2] = m_normals[i2] + normal;
	}

	for (unsigned int i = 0; i < m_normals.size(); i++)
		m_normals[i] = m_normals[i].getNormalized();
}

void IndexedModel::calcTangents()
{
	m_tangents.clear();
	m_tangents.reserve(m_positions.size());

	for (unsigned int i = 0; i < m_positions.size(); i++)
		m_tangents.push_back(PxVec3(0, 0, 0));

	for (unsigned int i = 0; i < m_indices.size(); i += 3)
	{
		int i0 = m_indices[i];
		int i1 = m_indices[i + 1];
		int i2 = m_indices[i + 2];

		PxVec3 edge1 = m_positions[i1] - m_positions[i0];
		PxVec3 edge2 = m_positions[i2] - m_positions[i0];

		float deltaU1 = m_texCoords[i1].x - m_texCoords[i0].x;
		float deltaU2 = m_texCoords[i2].x - m_texCoords[i0].x;
		float deltaV1 = m_texCoords[i1].y - m_texCoords[i0].y;
		float deltaV2 = m_texCoords[i2].y - m_texCoords[i0].y;

		float dividend = (deltaU1 * deltaV2 - deltaU2 * deltaV1);
		float f = dividend == 0.0f ? 0.0f : 1.0f / dividend;

		PxVec3 tangent = PxVec3(0, 0, 0);

		tangent.x = (f * (deltaV2 * edge1.x - deltaV1 * edge2.x));
		tangent.y = (f * (deltaV2 * edge1.y - deltaV1 * edge2.y));
		tangent.z = (f * (deltaV2 * edge1.z - deltaV1 * edge2.z));

		//Bitangent example, in Java
		//		PxVec3 bitangent = new PxVec3(0,0,0);
		//		
		//		bitangent.setX(f * (-deltaU2 * edge1.x - deltaU1 * edge2.x));
		//		bitangent.setX(f * (-deltaU2 * edge1.y - deltaU1 * edge2.y));
		//		bitangent.setX(f * (-deltaU2 * edge1.getZ() - deltaU1 * edge2.getZ()));

		m_tangents[i0] += tangent;
		m_tangents[i1] += tangent;
		m_tangents[i2] += tangent;
	}

	for (unsigned int i = 0; i < m_tangents.size(); i++)
		m_tangents[i] = m_tangents[i].getNormalized();
}


MeshData::MeshData(const IndexedModel& model) :
ReferenceCounter(),
m_drawCount(model.getIndices().size())
{
	if (!model.isValid())
	{
		std::cout << "Error: Invalid mesh! Must have same number of positions, texCoords, normals, and tangents! "
			<< "(Maybe you forgot to Finalize() your IndexedModel?)" << std::endl;
		assert(0 != 0);
	}
	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.getPositions().size() * sizeof(model.getPositions()[0]), &model.getPositions()[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.getTexCoords().size() * sizeof(model.getTexCoords()[0]), &model.getTexCoords()[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.getNormals().size() * sizeof(model.getNormals()[0]), &model.getNormals()[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TANGENT_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.getTangents().size() * sizeof(model.getTangents()[0]), &model.getTangents()[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.getIndices().size() * sizeof(model.getIndices()[0]), &model.getIndices()[0], GL_STATIC_DRAW);

}

MeshData::~MeshData()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void MeshData::render() const
{
	glBindVertexArray(m_vertexArrayObject);
	glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);
}


Mesh::Mesh(const std::string& meshName, const IndexedModel& model) :
m_fileName(meshName)
{
	std::map<std::string, MeshData*>::const_iterator it = s_resourceMap.find(meshName);
	if (it != s_resourceMap.end())
	{
		m_meshData = it->second;
		m_meshData->addReference();
		//std::cout << "Error adding mesh " << meshName << ": Mesh already exists by the same name!" << std::endl;
		//assert(0 != 0);
	}
	else
	{
		m_meshData = new MeshData(model);
		s_resourceMap.insert(std::pair<std::string, MeshData*>(meshName, m_meshData));
	}
}

Mesh::Mesh(const std::string& fileName, float scale /*= 1.0f*/) :
m_fileName(fileName),
m_meshData(0)
{
	auto it = s_resourceMap.find(fileName);
	if (it != s_resourceMap.end())
	{
		m_meshData = it->second;
		m_meshData->addReference();
	}
	else
	{
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(("Assets/Models/" + fileName).c_str(),
			aiProcess_Triangulate |
			aiProcess_GenSmoothNormals |
			aiProcess_FlipUVs |
			aiProcess_CalcTangentSpace);

		if (!scene)
		{
			std::cout << "Mesh load failed!: " << fileName << std::endl;
			assert(0 == 0);
		}

		const aiMesh* model = scene->mMeshes[0];

		std::vector<PxVec3> positions;
		std::vector<PxVec2> texCoords;
		std::vector<PxVec3> normals;
		std::vector<PxVec3> tangents;
		std::vector<unsigned int> indices;

		const aiVector3D aiZeroVector(0.0f, 0.0f, 0.0f);
		for (unsigned int i = 0; i < model->mNumVertices; i++)
		{
			const aiVector3D pos = model->mVertices[i] * scale;
			const aiVector3D normal = model->mNormals[i];
			const aiVector3D texCoord = model->HasTextureCoords(0) ? model->mTextureCoords[0][i] : aiZeroVector;
			const aiVector3D tangent = model->mTangents[i];

			positions.push_back(PxVec3(pos.x, pos.y, pos.z));
			texCoords.push_back(PxVec2(texCoord.x, texCoord.y));
			normals.push_back(PxVec3(normal.x, normal.y, normal.z));
			tangents.push_back(PxVec3(tangent.x, tangent.y, tangent.z));
		}

		for (unsigned int i = 0; i < model->mNumFaces; i++)
		{
			const aiFace& face = model->mFaces[i];
			assert(face.mNumIndices == 3);
			indices.push_back(face.mIndices[0]);
			indices.push_back(face.mIndices[1]);
			indices.push_back(face.mIndices[2]);
		}

		m_meshData = new MeshData(IndexedModel(indices, positions, texCoords, normals, tangents));
		s_resourceMap.insert(std::make_pair(fileName, m_meshData));
	}
}

Mesh::Mesh(const Mesh& mesh) :
m_fileName(mesh.m_fileName),
m_meshData(mesh.m_meshData)
{
	m_meshData->addReference();
}

Mesh::~Mesh()
{
	if (m_meshData && m_meshData->removeReference())
	{
		if (m_fileName.length() > 0)
		{
			s_resourceMap.erase(m_fileName);
		}

		delete m_meshData;
	}
}

void Mesh::render() const
{
	m_meshData->render();
}