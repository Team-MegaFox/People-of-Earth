// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Deroiche
// Created          : 09-15-2015
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 01-24-2016
// ***********************************************************************
// <copyright file="Mesh.cpp" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>

/// <summary>
/// The s_resource map{CC2D43FA-BBC4-448A-9D0B-7B57ADF2655C}
/// </summary>
std::map<std::string, MeshData*> Mesh::s_resourceMap;

bool IndexedModel::isValid() const
{
	return m_vertices.size() == m_texCoords.size() &&
		m_texCoords.size() == m_normals.size() &&
		m_normals.size() == m_tangents.size();
}

void IndexedModel::calcNormals()
{
	m_normals.clear();
	m_normals.reserve(m_vertices.size());

	for (size_t i = 0; i < m_vertices.size(); i++)
	{
		m_normals.push_back(glm::vec3(0.0f));
	}

	for (size_t i = 0; i < m_indices.size(); i += 3)
	{
		int i0 = m_indices[i];
		int i1 = m_indices[i + 1];
		int i2 = m_indices[i + 2];

		glm::vec3 v1 = m_vertices[i1] - m_vertices[i0];
		glm::vec3 v2 = m_vertices[i2] - m_vertices[i0];

		glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

		m_normals[i0] += normal;
		m_normals[i1] += normal;
		m_normals[i2] += normal;
	}

	for (size_t i = 0; i < m_normals.size(); i++)
	{
		m_normals[i] = glm::normalize(m_normals[i]);
	}
}

void IndexedModel::calcTangents()
{
	m_tangents.clear();
	m_tangents.reserve(m_vertices.size());

	for (size_t i = 0; i < m_vertices.size(); i++)
	{
		m_tangents.push_back(glm::vec3(0.0f));
	}

	for (size_t i = 0; i < m_indices.size(); i++)
	{
		int i0 = m_indices[i];
		int i1 = m_indices[i + 1];
		int i2 = m_indices[i + 2];

		glm::vec3 edge1 = m_vertices[i1] - m_vertices[i0];
		glm::vec3 edge2 = m_vertices[i2] - m_vertices[i0];

		float deltaU1 = m_texCoords[i1].x - m_texCoords[i0].x;
		float deltaU2 = m_texCoords[i2].x - m_texCoords[i0].x;
		float deltaV1 = m_texCoords[i1].y - m_texCoords[i0].y;
		float deltaV2 = m_texCoords[i2].y - m_texCoords[i0].y;

		float dividend = (deltaU1 * deltaV2 - deltaU2 * deltaV1);
		float f = dividend == 0.0f ? 0.0f : 1.0f / dividend;

		glm::vec3 tangent(0.0f);

		tangent.x = (f * (deltaV2 * edge1.x - deltaV1 * edge2.x));
		tangent.y = (f * (deltaV2 * edge1.y - deltaV1 * edge2.y));
		tangent.z = (f * (deltaV2 * edge1.z - deltaV1 * edge2.z));

		m_tangents[i0] += tangent;
		m_tangents[i1] += tangent;
		m_tangents[i2] += tangent;
	}

	for (size_t i = 0; i < m_tangents.size(); i++)
	{
		m_tangents[i] = glm::normalize(m_tangents[i]);
	}
}

IndexedModel IndexedModel::finalize()
{
	if (isValid())
	{
		return *this;
	}

	if (m_texCoords.empty())
	{
		for (size_t i = m_texCoords.size(); i < m_vertices.size(); i++)
		{
			m_texCoords.push_back(glm::vec2(0.0f));
		}
	}

	if (m_normals.empty())
	{
		calcNormals();
	}

	if (m_tangents.empty())
	{
		calcTangents();
	}

	return *this;
}

MeshData::MeshData(const IndexedModel& indexedModel) : 
ReferenceCounter(),
m_drawCount(indexedModel.getIndices().size())
{
	if (!indexedModel.isValid())
	{
		//Error check
		//Error: Invalid mesh! Must have same number of positions, texCoords, normals, and tangents!
		//(Maybe you forgot to Finalize() your IndexedModel?)
		assert(0 != 0);
	}
	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, indexedModel.getVertices().size() * sizeof(indexedModel.getVertices()[0]), &indexedModel.getVertices()[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, indexedModel.getTexCoords().size() * sizeof(indexedModel.getTexCoords()[0]), &indexedModel.getTexCoords()[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, indexedModel.getNormals().size() * sizeof(indexedModel.getNormals()[0]), &indexedModel.getNormals()[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TANGENT_VB]);
	glBufferData(GL_ARRAY_BUFFER, indexedModel.getTangents().size() * sizeof(indexedModel.getTangents()[0]), &indexedModel.getTangents()[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexedModel.getIndices().size() * sizeof(indexedModel.getIndices()[0]), &indexedModel.getIndices()[0], GL_STATIC_DRAW);
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

Mesh::Mesh(const std::string& fileName /*= "cube.obj"*/, float scale /*= 1.0f*/) : 
m_fileName(fileName),
m_meshData(nullptr)
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
			//Error
			//Mesh failed to load
			assert(0 == 0);
		}

		const aiMesh* mesh = scene->mMeshes[0];

		std::vector<unsigned int> indices;
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> texCoords;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec3> tangents;

		const aiVector3D aiZero(0.0f, 0.0f, 0.0f);
		for (size_t i = 0; i < mesh->mNumVertices; i++)
		{
			const aiVector3D vert = mesh->mVertices[i] * scale;
			const aiVector3D texCoord = mesh->HasTextureCoords(0) ? mesh->mTextureCoords[0][i] : aiZero;
			const aiVector3D normal = mesh->mNormals[i];
			const aiVector3D tangent = mesh->mTangents[i];

			vertices.push_back(glm::vec3(vert.x, vert.y, vert.z));
			texCoords.push_back(glm::vec2(texCoord.x, texCoord.y));
			normals.push_back(glm::vec3(normal.x, normal.y, normal.z));
			tangents.push_back(glm::vec3(tangent.x, tangent.y, tangent.z));
		}

		for (size_t i = 0; i < mesh->mNumFaces; i++)
		{
			const aiFace& face = mesh->mFaces[i];
			assert(face.mNumIndices == 3);
			indices.push_back(face.mIndices[0]);
			indices.push_back(face.mIndices[1]);
			indices.push_back(face.mIndices[2]);
		}

		m_meshData = new MeshData(IndexedModel(indices, vertices, texCoords, normals, tangents));
		if (m_meshData == nullptr)
		{
			assert(0 != 0);
		}
		s_resourceMap.insert(std::make_pair(m_fileName, m_meshData));
	}
}

Mesh::Mesh(const std::string& meshName, const IndexedModel& model) : 
m_fileName(meshName)
{
	auto it = s_resourceMap.find(meshName);
	if (it != s_resourceMap.end())
	{
		//Error
		//Adding mesh, could not add mesh
		assert(0 != 0);
	}
	else
	{
		m_meshData = new MeshData(model);
		s_resourceMap.insert(std::make_pair(meshName, m_meshData));
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
