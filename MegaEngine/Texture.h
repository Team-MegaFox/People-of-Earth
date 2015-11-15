#pragma once
#include "ReferenceCounter.h"
#include <glew\glew.h>
#include <string>
#include <map>

class TextureData
{
public:
	TextureData(GLenum textureTarget, int width, int height, int numTextures, 
		unsigned char** data, GLfloat* filters, GLenum* internalFormat, 
		GLenum* format, bool clamp, GLenum* attachments);
	virtual ~TextureData();

	void bind(int textureNum) const;
	void bindToRenderTarget() const;

	inline int getWidth() { return m_width; }
	inline int getHeight() { return m_height; }

private:
	void initTextures(unsigned char** data, GLfloat* filters, GLenum* internalFormat,
		GLenum* format, bool clamp);
	void initRenderTarget(GLenum* attachments);

	GLuint* m_textureID;
	GLenum m_textureTarget;
	GLuint m_frameBuffer;
	GLuint m_renderBuffer;
	int m_numTextures;
	int m_width;
	int m_height;

};

class TextureImage
{
public:
	TextureImage(const std::string& fileName, GLenum textureTarget = GL_TEXTURE_2D,
		GLfloat filter = GL_LINEAR_MIPMAP_LINEAR, GLenum internalFormat = GL_RGBA, 
		GLenum format = GL_RGBA, bool clamp = false, GLenum attachment = GL_NONE);
	TextureImage(int width = 0, int height = 0, unsigned char* data = 0,
		GLenum textureTarget = GL_TEXTURE_2D, GLfloat filter = GL_LINEAR_MIPMAP_LINEAR, 
		GLenum internalFormat = GL_RGBA, GLenum format = GL_RGBA, bool clamp = false, 
		GLenum attachment = GL_NONE);
	TextureImage(const TextureImage& texture);
	virtual ~TextureImage();

	void bind(unsigned int unit = 0) const;
	void bindRenderTarget() const;

	inline int getWidth() const { return m_textureData->getWidth(); }
	inline int getHeight() const { return m_textureData->getHeight(); }

	bool operator==(const TextureImage& texture) const { return m_textureData == texture.m_textureData; }
	bool operator!=(const TextureImage& texture) const { return !operator==(texture); }

private:
	static std::map<std::string, TextureData*> s_resourceMap;

	TextureData* m_textureData;
	std::string m_fileName;
};

