#pragma once
#include <string>
#include <vector>
#include <map>
#include <glew\glew.h>
#include <glm\glm.hpp>

#include "..\Core\ReferenceCounter.h"

class IndexedModel
{
public:
	IndexedModel() { }
	IndexedModel(const std::vector<unsigned int> indices, const std::vector<glm::vec3>& vertices, const std::vector<glm::vec2>& texCoords,
		const std::vector<glm::vec3>& normals = std::vector<glm::vec3>(), const std::vector<glm::vec3>& tangents = std::vector<glm::vec3>()) :
		m_indices(indices),
		m_vertices(vertices),
		m_texCoords(texCoords),
		m_normals(normals),
		m_tangents(tangents) { }
	~IndexedModel() { }

	bool isValid() const;
	void calcNormals();
	void calcTangents();

	IndexedModel finalize();

	void addVertex(const glm::vec3& vertex) { m_vertices.push_back(vertex); }
	inline void addVertex(float x, float y, float z) { addVertex(glm::vec3(x, y, z)); }

	void addTexCoord(const glm::vec2& texCoord) { m_texCoords.push_back(texCoord); }
	inline void addTexCoord(float u, float v) { addTexCoord(glm::vec2(u, v)); }

	void addNormal(const glm::vec3& normal) { m_normals.push_back(normal); }
	inline void addNormal(float x, float y, float z) { addNormal(glm::vec3(x, y, z)); }

	void addTangent(const glm::vec3& tangent) { m_tangents.push_back(tangent); }
	inline void addTangent(float x, float y, float z) { addTangent(glm::vec3(x, y, z)); }

	void addFace(unsigned int vertindex0, unsigned int vertindex1, unsigned int vertindex2) { m_indices.push_back(vertindex0); m_indices.push_back(vertindex1); m_indices.push_back(vertindex2); }

	inline const std::vector<unsigned int>& getIndices() const { return m_indices; }
	inline const std::vector<glm::vec3>& getVertices() const { return m_vertices; }
	inline const std::vector<glm::vec2>& getTexCoords() const { return m_texCoords; }
	inline const std::vector<glm::vec3>& getNormals() const { return m_normals; }
	inline const std::vector<glm::vec3>& getTangents() const { return m_tangents; }

private:
	std::vector<unsigned int> m_indices;
	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec2> m_texCoords;
	std::vector<glm::vec3> m_normals;
	std::vector<glm::vec3> m_tangents;

};

class MeshData : public ReferenceCounter
{
public:
	MeshData(const IndexedModel& indexedModel);	
	virtual ~MeshData();

	void render() const;

private:
	enum 
	{
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,
		TANGENT_VB,

		INDEX_VB,

		NUM_BUFFERS
	};

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	int m_drawCount;

};

class Mesh
{
public:
	Mesh(const std::string& fileName = "cube.obj", float scale = 1.0f);
	Mesh(const std::string& meshName, const IndexedModel& model);
	Mesh(const Mesh& mesh);
	virtual ~Mesh();
	//void operator=(const Mesh other) { m_fileName = other.m_fileName; m_meshData = other.m_meshData; }

	void render() const;

private:
	static std::map<std::string, MeshData*> s_resourceMap;

	std::string m_fileName;
	MeshData* m_meshData;

};
