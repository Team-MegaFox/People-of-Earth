// ***********************************************************************
// Author           : Pavan Jakhu and Jesse Derochie
// Created          : 09-15-2015
//
// Last Modified By : Pavan Jakhu
// Last Modified On : 01-24-2016
// ***********************************************************************
// <copyright file="Texture.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#pragma once
#include "..\Core\ReferenceCounter.h"
#include <glew\glew.h>
#include <string>
#include <map>

/// <summary>
/// The Texture Data class inherits <see cref="ReferenceCounter"/> and holds texture information such as
/// the image data, image height, image width, texture format, filters and GL attachments.
/// </summary>
/// <seealso cref="ReferenceCounter" />
class TextureData : public ReferenceCounter
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="TextureData"/> class.
	/// </summary>
	/// <param name="textureTarget">The texture target.</param>
	/// <param name="width">The width of the texture.</param>
	/// <param name="height">The height of the texture.</param>
	/// <param name="numTextures">The number textures.</param>
	/// <param name="data">The texture data.</param>
	/// <param name="filters">The filters.</param>
	/// <param name="internalFormat">The internal format.</param>
	/// <param name="format">The format.</param>
	/// <param name="clamp">The clamp.</param>
	/// <param name="attachments">The attachments for the texture.</param>
	TextureData(GLenum textureTarget, int width, int height, int numTextures,
		unsigned char** data, GLfloat* filters, GLenum* internalFormat, 
		GLenum* format, bool clamp, GLenum* attachments);
	/// <summary>
	/// Finalizes an instance of the <see cref="TextureData"/> class.
	/// </summary>
	virtual ~TextureData();

	/// <summary>
	/// Binds the texture data to be used in the graphics card.
	/// </summary>
	/// <param name="textureNum">The texture number.</param>
	void bind(int textureNum) const;
	/// <summary>
	/// Binds to render target to this instance of the texture.
	/// </summary>
	void bindToRenderTarget() const;

	/// <summary>
	/// Gets the texture width.
	/// </summary>
	/// <returns>The texture width.</returns>
	inline int getWidth() { return m_width; }
	/// <summary>
	/// Gets the texture height.
	/// </summary>
	/// <returns>The texture height.</returns>
	inline int getHeight() { return m_height; }

private:
	/// <summary>
	/// Initializes the texture(s).
	/// </summary>
	/// <param name="data">The texture data.</param>
	/// <param name="filters">The filters.</param>
	/// <param name="internalFormat">The internal format.</param>
	/// <param name="format">The format.</param>
	/// <param name="clamp">The clamp.</param>
	void initTextures(unsigned char** data, GLfloat* filters, GLenum* internalFormat,
		GLenum* format, bool clamp);
	/// <summary>
	/// Initializes the render target.
	/// </summary>
	/// <param name="attachments">The attachments.</param>
	void initRenderTarget(GLenum* attachments);

	/// <summary>
	/// The texture identifier in the graphics card.
	/// </summary>
	GLuint* m_textureID;
	/// <summary>
	/// The texture target.
	/// </summary>
	GLenum m_textureTarget;
	/// <summary>
	/// The frame buffer.
	/// </summary>
	GLuint m_frameBuffer;
	/// <summary>
	/// The render buffer.
	/// </summary>
	GLuint m_renderBuffer;
	/// <summary>
	/// The number of textures.
	/// </summary>
	int m_numTextures;
	/// <summary>
	/// The texture width.
	/// </summary>
	int m_width;
	/// <summary>
	/// The texture height.
	/// </summary>
	int m_height;

};

/// <summary>
/// The Texture class stores the <see cref='TextureData'/> and the image's file name, if used.
/// Also has a static map that stores all <see cref='TextureData'/>.
/// </summary>
class Texture
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Texture"/> class with a image file.
	/// </summary>
	/// <param name="fileName">Name of the image file.</param>
	/// <param name="textureTarget">The texture target.</param>
	/// <param name="filter">The filter.</param>
	/// <param name="internalFormat">The internal format.</param>
	/// <param name="format">The format.</param>
	/// <param name="clamp">The clamp.</param>
	/// <param name="attachment">The attachment.</param>
	Texture(const std::string& fileName, GLenum textureTarget = GL_TEXTURE_2D,
		GLfloat filter = GL_LINEAR_MIPMAP_LINEAR, GLenum internalFormat = GL_RGBA, 
		GLenum format = GL_RGBA, bool clamp = false, GLenum attachment = GL_NONE);
	/// <summary>
	/// Initializes a new instance of the <see cref="Texture"/> class with custom values.
	/// </summary>
	/// <param name="width">The texture width.</param>
	/// <param name="height">The texture height.</param>
	/// <param name="data">The texture data.</param>
	/// <param name="textureTarget">The texture target.</param>
	/// <param name="filter">The filter.</param>
	/// <param name="internalFormat">The internal format.</param>
	/// <param name="format">The format.</param>
	/// <param name="clamp">The clamp.</param>
	/// <param name="attachment">The attachment.</param>
	Texture(int width = 0, int height = 0, unsigned char* data = nullptr,
		GLenum textureTarget = GL_TEXTURE_2D, GLfloat filter = GL_LINEAR_MIPMAP_LINEAR, 
		GLenum internalFormat = GL_RGBA, GLenum format = GL_RGBA, bool clamp = false, 
		GLenum attachment = GL_NONE);
	/// <summary>
	/// Initializes a new instance of the <see cref="Texture"/> class with a texture object.
	/// </summary>
	/// <param name="texture">The texture.</param>
	Texture(const Texture& texture);
	/// <summary>
	/// Finalizes an instance of the <see cref="Texture"/> class.
	/// </summary>
	virtual ~Texture();
	/// <summary>
	/// Equal operator override.
	/// </summary>
	/// <param name="other">The texture to copy.</param>
	void operator=(Texture other);

	/// <summary>
	/// Binds the texture data to be used in the graphics card.
	/// </summary>
	/// <param name="unit">The texture unit.</param>
	void bind(unsigned int unit = 0) const;
	/// <summary>
	/// Binds to render target to this instance of the texture.
	/// </summary>
	void bindRenderTarget() const;

	/// <summary>
	/// Gets the texture width.
	/// </summary>
	/// <returns>int.</returns>
	inline int getWidth() const { return m_textureData->getWidth(); }
	/// <summary>
	/// Gets the texture height.
	/// </summary>
	/// <returns>int.</returns>
	inline int getHeight() const { return m_textureData->getHeight(); }

	/// <summary>
	/// Checks if this instance of a Texture is equal to another.
	/// </summary>
	/// <param name="texture">The texture.</param>
	/// <returnsIf the texture is the same as the other.</returns>
	bool operator==(const Texture& texture) const { return m_textureData == texture.m_textureData; }
	/// <summary>
	/// Checks if this instance of a Texture is not equal to another.
	/// </summary>
	/// <param name="texture">The texture.</param>
	/// <returns>If the texture is not the same as the other.</returns>
	bool operator!=(const Texture& texture) const { return !operator==(texture); }

private:	
	/// <summary>The map of every <see cref="TextureData"/>.</summary>
	static std::map<std::string, TextureData*> s_resourceMap;

	/// <summary>
	/// The texture data.
	/// </summary>
	TextureData* m_textureData;
	/// <summary>
	/// The image's file name.
	/// </summary>
	std::string m_fileName;
};

