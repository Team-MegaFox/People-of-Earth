// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Deroiche
// Created          : 09-15-2015
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 01-24-2016
// ***********************************************************************
// <copyright file="Shader.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once

#include <map>
#include <vector>
#include <string>

#include "..\Core\ReferenceCounter.h"
#include "..\Core\Transform.h"
#include "Material.h"
#include "Camera3D.h"

#include <glm/glm.hpp>

class RenderingEngine;
class DirectionalLight;
class PointLight;
class SpotLight;

/// <summary>
/// Stores two string values for the name and what type of object it is.
/// </summary>
/// <example>
/// <code>
/// TypedData uniform("C_MVP", "mat4");
/// </code>
/// </example>
class TypedData
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="TypedData"/> class.
	/// </summary>
	/// <param name="name">The name.</param>
	/// <param name="type">The type.</param>
	TypedData(const std::string & name, const std::string & type) :
		m_name(name),
		m_type(type) {}

	/// <summary>
	/// Gets the name.
	/// </summary>
	/// <returns>A const refernce to the name.</returns>
	inline const std::string & getName() const { return m_name; }
	/// <summary>
	/// Gets the type.
	/// </summary>
	/// <returns>A const reference to the type.</returns>
	inline const std::string & getType() const { return m_type; }
private:
	/// <summary>
	/// The name.
	/// </summary>
	std::string m_name;
	/// <summary>
	/// The type.
	/// </summary>
	std::string m_type;
};

/// <summary>
/// The Uniform Struct holds the individual values of a struct from the shader files
/// so it can go through each variable in the struct and apply values to them then send
/// them to the graphics card.
/// </summary>
class UniformStruct
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="UniformStruct"/> class.
	/// </summary>
	/// <param name="name">The struct's name.</param>
	/// <param name="memberNames">The member names.</param>
	UniformStruct(const std::string & name, const std::vector<TypedData> & memberNames) :
		m_name(name),
		m_memberNames(memberNames) {}

	/// <summary>
	/// Gets the struct's name.
	/// </summary>
	/// <returns>A const reference of the struct's name.</returns>
	inline const std::string & getName()                   const { return m_name; }
	/// <summary>
	/// Gets the member names.
	/// </summary>
	/// <returns>A const refernce of the vector of member names.</returns>
	inline const std::vector<TypedData> & getMemberNames() const { return m_memberNames; }
private:
	/// <summary>
	/// The struct's name
	/// </summary>
	std::string            m_name;
	/// <summary>
	/// The member names
	/// </summary>
	std::vector<TypedData> m_memberNames;
};

/// <summary>
/// The Shader Data class holds the program's ID and the uniforms that are inside its shader files.
/// It also links the vertex and fragment shaders to the shader program.
/// </summary>
/// <seealso cref="ReferenceCounter" />
class ShaderData : public ReferenceCounter
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="ShaderData"/> class with shader file's name.
	/// </summary>
	/// <param name="fileName">Name of the shader file.</param>
	ShaderData(const std::string & fileName);
	/// <summary>
	/// Finalizes an instance of the <see cref="ShaderData"/> class.
	/// </summary>
	virtual ~ShaderData();

	/// <summary>
	/// Gets the program ID.
	/// </summary>
	/// <returns>The shader program's ID.</returns>
	inline int getProgram()                                           const { return m_program; }
	/// <summary>
	/// Gets the shader IDs.
	/// </summary>
	/// <returns>A const reference to the vector of shader IDs.</returns>
	inline const std::vector<int> & getShaders()                       const { return m_shaders; }
	/// <summary>
	/// Gets the uniform names.
	/// </summary>
	/// <returns>A const reference to the vector of uniform names.</returns>
	inline const std::vector<std::string> & getUniformNames()          const { return m_uniformNames; }
	/// <summary>
	/// Gets the uniform types.
	/// </summary>
	/// <returns>A const reference to the vector of uniform types.</returns>
	inline const std::vector<std::string> & getUniformTypes()          const { return m_uniformTypes; }
	/// <summary>
	/// Gets the map of uniforms in the shader program.
	/// </summary>
	/// <returns>A const reference to the map of uniforms in the shader program.</returns>
	inline const std::map<std::string, unsigned int> & getUniformMap() const { return m_uniformMap; }
private:
	/// <summary>
	/// Adds the vertex shader.
	/// </summary>
	/// <param name="text">The vertex shader's source text.</param>
	void addVertexShader(const std::string & text);
	/// <summary>
	/// Adds the geometry shader.
	/// </summary>
	/// <param name="text">The geometry shader's source text.</param>
	void addGeometryShader(const std::string & text);
	/// <summary>
	/// Adds the fragment shader.
	/// </summary>
	/// <param name="text">The fragment shader's source text.</param>
	void addFragmentShader(const std::string & text);
	/// <summary>
	/// Adds a shader to the program.
	/// </summary>
	/// <param name="text">The shader's source text.</param>
	/// <param name="type">The type of shader.</param>
	/// <example>
	/// <code>
	/// addProgram(sourceText, GL_VERTEX_SHADER);
	/// </code>
	/// </example>
	void addProgram(const std::string & text, int type);
		 
	/// <summary>
	/// Adds all attributes to the program.
	/// </summary>
	/// <param name="vertexShaderText">The vertex shader's source text.</param>
	/// <param name="attributeKeyword">The attribute keyword.</param>
	void addAllAttributes(const std::string & vertexShaderText, const std::string & attributeKeyword);
	/// <summary>
	/// Adds the shader uniforms to this Shader Data from the graphics card.
	/// </summary>
	/// <param name="shaderText">The shader's source text.</param>
	void addShaderUniforms(const std::string & shaderText);
	/// <summary>
	/// Finds the uniform name and type from the struct and adds it to the map.
	/// </summary>
	/// <param name="uniformName">Name of the uniform.</param>
	/// <param name="uniformType">Type of the uniform.</param>
	/// <param name="structs">The struct of uniforms.</param>
	void addUniform(const std::string & uniformName, const std::string & uniformType, const std::vector<UniformStruct> & structs);
	/// <summary>
	/// Compiles the shader.
	/// </summary>
	void compileShader() const;
	/// <summary>
	/// Converts the vertex shader to GLSL 150.
	/// </summary>
	/// <param name="shaderText">The vertex shader's source text.</param>
	void convertVertexShaderToGLSL150(std::string * shaderText);
	/// <summary>
	/// Converts the fragment shader to GLSL 150.
	/// </summary>
	/// <param name="shaderText">The fragment shader's source text.</param>
	void convertFragmentShaderToGLSL150(std::string * shaderText);

	/// <summary>The supported level of OpenGL on the computer</summary>
	static int s_supportedOpenGLLevel;
	/// <summary>
	/// The shader program ID
	/// </summary>
	int m_program;
	/// <summary>
	/// The shaders in the program.
	/// </summary>
	std::vector<int>                    m_shaders;
	/// <summary>
	/// The uniform names in the program.
	/// </summary>
	std::vector<std::string>            m_uniformNames;
	/// <summary>
	/// The uniform types in the program.
	/// </summary>
	std::vector<std::string>            m_uniformTypes;
	/// <summary>
	/// The location of the uniforms based on the name.
	/// </summary>
	std::map<std::string, unsigned int> m_uniformMap;
};

/// <summary>
/// The Shader class stores the <see cref="ShaderData"/> and keeps refernce of the same shader.
/// </summary>
class Shader
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Shader"/> class from a shader file.
	/// </summary>
	/// <param name="fileName">Name of the file.</param>
	Shader(const std::string & fileName = "basicShader");
	/// <summary>
	/// Initializes a new instance of the <see cref="Shader"/> class from a shader object.
	/// </summary>
	/// <param name="other">The other.</param>
	Shader(const Shader & other);
	/// <summary>
	/// Finalizes an instance of the <see cref="Shader"/> class.
	/// </summary>
	virtual ~Shader();

	/// <summary>
	/// Binds this instance of the shader program to be used.
	/// </summary>
	void bind() const;
	/// <summary>
	/// Updates the uniforms. Automatically finds the uniforms of the shader 
	/// and sends the appriorpiate data to the graphics card.
	/// </summary>
	/// <param name="transform">The transform.</param>
	/// <param name="material">The material.</param>
	/// <param name="renderingEngine">The rendering engine.</param>
	/// <param name="camera">The main camera.</param>
	virtual void updateUniforms(const Transform & transform, const Material & material, const RenderingEngine & renderingEngine, const Camera3D & camera) const;

	/// <summary>
	/// Sets the integer uniform.
	/// </summary>
	/// <param name="uniformName">Name of the uniform.</param>
	/// <param name="value">The value of the uniform.</param>
	void setUniformi(const std::string & uniformName, int value) const;
	/// <summary>
	/// Sets the float uniform.
	/// </summary>
	/// <param name="uniformName">Name of the uniform.</param>
	/// <param name="value">The value of the uniform.</param>
	void setUniformf(const std::string & uniformName, float value) const;
	/// <summary>
	/// Sets the matrix4x4 uniform.
	/// </summary>
	/// <param name="uniformName">Name of the uniform.</param>
	/// <param name="value">The value of the uniform.</param>
	void setUniformMat4(const std::string & uniformName, const glm::mat4 & value) const;
	/// <summary>
	/// Sets the 3D vector uniform.
	/// </summary>
	/// <param name="uniformName">Name of the uniform.</param>
	/// <param name="value">The value of the uniform.</param>
	void setUniformVec3(const std::string & uniformName, const glm::vec3 & value) const;
protected:
private:
	/// <summary>The map of every <see cref="ShaderData"/>.</summary>
	static std::map<std::string, ShaderData *> s_resourceMap;

	/// <summary>
	/// The shader data.
	/// </summary>
	ShaderData * m_shaderData;
	/// <summary>
	/// The shader file name.
	/// </summary>
	std::string m_fileName;

	/// <summary>
	/// Sets the directional light uniform.
	/// </summary>
	/// <param name="uniformName">Name of the uniform.</param>
	/// <param name="value">The directional light to send to the graphics card.</param>
	void setUniformDirectionalLight(const std::string & uniformName, const DirectionalLight & value) const;
	/// <summary>
	/// Sets the point light uniform.
	/// </summary>
	/// <param name="uniformName">Name of the uniform.</param>
	/// <param name="value">The point light to send to the graphics card.</param>
	void setUniformPointLight(const std::string & uniformName, const PointLight & value) const;
	/// <summary>
	/// Sets the spot light uniform.
	/// </summary>
	/// <param name="uniformName">Name of the uniform.</param>
	/// <param name="value">The spot light to send to the graphics card.</param>
	void setUniformSpotLight(const std::string & uniformName, const SpotLight & value) const;

	/// <summary>
	/// Operator=s the specified other.
	/// </summary>
	/// <param name="other">The other.</param>
	void operator=(const Shader & other) {}
};