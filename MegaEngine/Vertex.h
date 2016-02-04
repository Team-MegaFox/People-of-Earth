#pragma once
#include <GLM/glm.hpp>

class Vertex
{
public:
	Vertex()
	{

	}

	Vertex(const glm::vec3 & position)
	{
		this->m_position = position;
	}

	Vertex(const glm::vec3 & position, const glm::vec3 & normals)
	{
		this->m_position = position;
		this->m_normals = normals;
	}

	Vertex(const glm::vec3 & position, const glm::vec2 & textureCoords, const glm::vec3 & normals)
	{
		this->m_position = position;
		this->m_textureCoords = textureCoords;
		this->m_normals = normals;
	}

	inline glm::vec3 * getPosition() { return &m_position; }
	inline glm::vec2 * getTextureCoords() { return &m_textureCoords; }
	inline glm::vec3 * getNormals() { return &m_normals; }

	inline void setPosition(glm::vec3 & pos) { m_position = pos; }
	inline void setTexCoords(glm::vec2 & texCoords) { m_textureCoords = texCoords; }
	inline void setNormals(glm::vec3 & normals) { m_normals = normals; }

private:
	//Vertex Attributes
	glm::vec3 m_position;
	glm::vec2 m_textureCoords;
	glm::vec3 m_normals;
};
