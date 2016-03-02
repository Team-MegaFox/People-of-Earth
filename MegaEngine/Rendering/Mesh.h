// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 03-01-2016
// ***********************************************************************
// <copyright file="Mesh.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once
#include "..\Core\ReferenceCounter.h"
#include <string>
#include <vector>
#include <map>
#include <glew\glew.h>
#include <PhysX/PxPhysicsAPI.h>
using namespace physx;

/// <summary>
/// Stores the vertices, texture coordinates, face normals and vertice tangents. 
/// Also stores the indices on how to draw the faces on the model.
/// </summary>
class IndexedModel
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="IndexedModel"/> class.
	/// </summary>
	IndexedModel() {}
	/// <summary>
	/// Initializes a new instance of the <see cref="IndexedModel"/> class.
	/// </summary>
	/// <param name="indices">The indices.</param>
	/// <param name="vertices">The vertices.</param>
	/// <param name="texCoords">The texture coordinates.</param>
	/// <param name="normals">The face normals.</param>
	/// <param name="tangents">The vertices tangents.</param>
	IndexedModel(const std::vector<unsigned int> indices, const std::vector<PxVec3>& positions, const std::vector<PxVec2>& texCoords,
		const std::vector<PxVec3>& normals = std::vector<PxVec3>(), const std::vector<PxVec3>& tangents = std::vector<PxVec3>()) :
		m_indices(indices),
		m_positions(positions),
		m_texCoords(texCoords),
		m_normals(normals),
		m_tangents(tangents) {}

	/// <summary>
	/// Determines whether this instance is valid by checking if the sizes of the arrays are the same.
	/// </summary>
	/// <returns>If the model is valid.</returns>
	bool isValid() const;
	/// <summary>
	/// Calculates the normals.
	/// </summary>
	void calcNormals();
	/// <summary>
	/// Calculates the tangents.
	/// </summary>
	void calcTangents();

	/// <summary>
	/// Validates the model. If the normals and tangents aren't calculated then they are calculated.
	/// </summary>
	/// <returns>The validated model.</returns>
	IndexedModel finalize();

	// <summary>
	/// Adds a vertex.
	/// </summary>
	/// <param name="vertex">The vertex.</param>
	void addVertex(const PxVec3& vertex);
	/// <summary>
	/// Adds a vertex.
	/// </summary>
	/// <param name="x">The x value.</param>
	/// <param name="y">The y value.</param>
	/// <param name="z">The z value.</param>
	inline void addVertex(float x, float y, float z) { addVertex(PxVec3(x, y, z)); }

	/// <summary>
	/// Adds the texture coordinates.
	/// </summary>
	/// <param name="texCoord">The texture coordinates.</param>
	void addTexCoord(const PxVec2& texCoord);
	/// <summary>
	/// Adds the texture coordinates.
	/// </summary>
	/// <param name="u">The u value.</param>
	/// <param name="v">The v value.</param>
	inline void addTexCoord(float u, float v) { addTexCoord(PxVec2(u, v)); }

	/// <summary>
	/// Adds a normal vector.
	/// </summary>
	/// <param name="normal">The normal vector.</param>
	void addNormal(const PxVec3& normal);
	/// <summary>
	/// Adds a normal vector.
	/// </summary>
	/// <param name="x">The x value.</param>
	/// <param name="y">The y value.</param>
	/// <param name="z">The z value.</param>
	inline void addNormal(float x, float y, float z) { addNormal(PxVec3(x, y, z)); }

	/// <summary>
	/// Adds a tangent vector.
	/// </summary>
	/// <param name="tangent">The tangent vector.</param>
	void addTangent(const PxVec3& tangent);
	/// <summary>
	/// Adds a tangent vector.
	/// </summary>
	/// <param name="x">The x value.</param>
	/// <param name="y">The y value.</param>
	/// <param name="z">The z value.</param>
	inline void addTangent(float x, float y, float z) { addTangent(PxVec3(x, y, z)); }

	/// <summary>
	/// Adds a face tp the mesh.
	/// </summary>
	/// <param name="vertindex0">The first vertex index.</param>
	/// <param name="vertindex1">The second vertex index.</param>
	/// <param name="vertindex2">The third vertex index.</param>
	void addFace(unsigned int vertIndex0, unsigned int vertIndex1, unsigned int vertIndex2);

	/// <summary>
	/// Gets the indices.
	/// </summary>
	/// <returns>The indices of the model.</returns>
	inline const std::vector<unsigned int>& getIndices() const { return m_indices; }
	/// <summary>
	/// Gets the vertices.
	/// </summary>
	/// <returns>The vertices of the model.</returns>
	inline const std::vector<PxVec3>& getPositions()   const { return m_positions; }
	/// <summary>
	/// Gets the texture coordinates.
	/// </summary>
	/// <returns>The texture coordinates of the model.</returns>
	inline const std::vector<PxVec2>& getTexCoords()   const { return m_texCoords; }
	/// <summary>
	/// Gets the normals.
	/// </summary>
	/// <returns>The normals of the model.</returns>
	inline const std::vector<PxVec3>& getNormals()     const { return m_normals; }
	/// <summary>
	/// Gets the tangents.
	/// </summary>
	/// <returns>The tangents of the model.</returns>
	inline const std::vector<PxVec3>& getTangents()    const { return m_tangents; }
private:
	/// <summary>
	/// The indices.
	/// </summary>
	std::vector<unsigned int> m_indices;
	/// <summary>
	/// The vertices.
	/// </summary>
	std::vector<PxVec3> m_positions;
	/// <summary>
	/// The texture coordinates.
	/// </summary>

	std::vector<PxVec2> m_texCoords;
	/// <summary>
	/// The normals.
	/// </summary>

	std::vector<PxVec3> m_normals;
	/// <summary>
	/// The tangents.
	/// </summary>
	std::vector<PxVec3> m_tangents;
};

/// <summary>
/// Initializes the indexed model and sends the data to the graphics card.
/// </summary>
/// <seealso cref="ReferenceCounter" />
class MeshData : public ReferenceCounter
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="MeshData"/> class.
	/// </summary>
	/// <param name="indexedModel">The indexed model.</param>
	MeshData(const IndexedModel& model);
	/// <summary>
	/// Finalizes an instance of the <see cref="MeshData"/> class.
	/// </summary>
	virtual ~MeshData();

	/// <summary>
	/// Renders the model.
	/// </summary>
	void render() const;
protected:
private:
	MeshData(MeshData& other) {}
	void operator=(MeshData& other) {}

	/// <summary>
	/// Holds the values for where to send the data in the graphics card.
	/// </summary>
	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,
		TANGENT_VB,

		INDEX_VB,

		NUM_BUFFERS
	};

	/// <summary>
	/// The vertex array object.
	/// </summary>
	GLuint m_vertexArrayObject;
	/// <summary>
	/// The number of buffers to have to send to the graphics card.
	/// </summary>
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	/// <summary>
	/// The draw count.
	/// </summary>
	int m_drawCount;
};

/// <summary>
/// The Mesh class holds <see cref="MeshData"/> and can be initalized 
/// by a model file or by a manually made indexed model.
/// </summary>
class Mesh
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Mesh"/> class by passing a model file.
	/// </summary>
	/// <param name="fileName">Name of the file.</param>
	/// <param name="scale">The scale factor.</param>
	Mesh(const std::string& fileName = "Environment/cube.obj");
	/// <summary>
	/// Initializes a new instance of the <see cref="Mesh"/> class by passing a indexed model object.
	/// </summary>
	/// <param name="meshName">Name of the mesh.</param>
	/// <param name="model">The indexed model.</param>
	Mesh(const std::string& meshName, const IndexedModel& model);
	/// <summary>
	/// Initializes a new instance of the <see cref="Mesh"/> class by reference from another Mesh object.
	/// </summary>
	/// <param name="mesh">A reference to a mesh object.</param>
	Mesh(const Mesh& mesh);
	/// <summary>
	/// Finalizes an instance of the <see cref="Mesh"/> class.
	/// </summary>
	virtual ~Mesh();

	/// <summary>
	/// Renders the mesh.
	/// </summary>
	void render() const;
protected:
private:
	/// <summary>
	/// A static map of MeshData pointers that stores all Meshes by their file name or given name.
	/// </summary>
	static std::map<std::string, MeshData*> s_resourceMap;

	/// <summary>
	/// The file name.
	/// </summary>
	std::string m_fileName;
	/// <summary>
	/// The mesh data.
	/// </summary>
	MeshData* m_meshData;

	void operator=(Mesh& mesh) {}
};
