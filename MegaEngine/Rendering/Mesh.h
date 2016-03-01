#pragma once
#include "..\Core\ReferenceCounter.h"
#include <string>
#include <vector>
#include <map>
#include <glew\glew.h>
#include <glm\glm.hpp>

class IndexedModel
{
public:
	IndexedModel() {}
	IndexedModel(const std::vector<unsigned int> indices, const std::vector<glm::vec3>& positions, const std::vector<glm::vec2>& texCoords,
		const std::vector<glm::vec3>& normals = std::vector<glm::vec3>(), const std::vector<glm::vec3>& tangents = std::vector<glm::vec3>()) :
		m_indices(indices),
		m_positions(positions),
		m_texCoords(texCoords),
		m_normals(normals),
		m_tangents(tangents) {}

	bool isValid() const;
	void calcNormals();
	void calcTangents();

	IndexedModel finalize();

	void addVertex(const glm::vec3& vert);
	inline void addVertex(float x, float y, float z) { addVertex(glm::vec3(x, y, z)); }

	void addTexCoord(const glm::vec2& texCoord);
	inline void addTexCoord(float x, float y) { addTexCoord(glm::vec2(x, y)); }

	void addNormal(const glm::vec3& normal);
	inline void addNormal(float x, float y, float z) { addNormal(glm::vec3(x, y, z)); }

	void addTangent(const glm::vec3& tangent);
	inline void addTangent(float x, float y, float z) { addTangent(glm::vec3(x, y, z)); }

	void addFace(unsigned int vertIndex0, unsigned int vertIndex1, unsigned int vertIndex2);

	inline const std::vector<unsigned int>& getIndices() const { return m_indices; }
	inline const std::vector<glm::vec3>& getPositions()   const { return m_positions; }
	inline const std::vector<glm::vec2>& getTexCoords()   const { return m_texCoords; }
	inline const std::vector<glm::vec3>& getNormals()     const { return m_normals; }
	inline const std::vector<glm::vec3>& getTangents()    const { return m_tangents; }
private:
	std::vector<unsigned int> m_indices;
	std::vector<glm::vec3> m_positions;
	std::vector<glm::vec2> m_texCoords;
	std::vector<glm::vec3> m_normals;
	std::vector<glm::vec3> m_tangents;
};

class MeshData : public ReferenceCounter
{
public:
	MeshData(const IndexedModel& model);
	virtual ~MeshData();

	void render() const;
protected:
private:
	MeshData(MeshData& other) {}
	void operator=(MeshData& other) {}

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

	void render() const;
protected:
private:
	static std::map<std::string, MeshData*> s_resourceMap;

	std::string m_fileName;
	MeshData* m_meshData;

	void operator=(Mesh& mesh) {}
};

//class MeshBuilder
//{
//public:
//	MeshBuilder() {}
//	
//	void AddVertex(const PxVec3& vert);
////	inline void AddVertex(float x, float y, float z) { AddVertex(PxVec3(x, y, z)); }
//	
//	void AddTexCoord(const PxVec2& texCoord);
////	inline void AddTexCoord(float x, float y) { AddTexCoord(PxVec2(x, y)); }
//	
//	void AddFace(unsigned int vertIndex0, unsigned int vertIndex1, unsigned int vertIndex2);
//	
//	Mesh FinalizeMesh(const std::string& meshName);
//	
//	inline IndexedModel* GetModel() { return &m_model; }
//protected:
//private:
//	IndexedModel m_model;
//};
