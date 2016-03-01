#include "Texture.h"

#include "..\Core\Utility.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb\stb_image.h>
#include <iostream>
#include <cassert>
#include <cstring>
#include <glm\glm.hpp>

std::map<std::string, TextureData*> Texture::s_resourceMap;

TextureData::TextureData(GLenum textureTarget, int width, int height, int numTextures, unsigned char** data, GLfloat* filters, GLenum* internalFormat, GLenum* format, bool clamp, GLenum* attachments)
{
	m_textureID = new GLuint[numTextures];
	m_textureTarget = textureTarget;
	m_numTextures = numTextures;
	m_width = width;
	m_height = height;
	m_frameBuffer = 0;
	m_renderBuffer = 0;

	initTextures(data, filters, internalFormat, format, clamp);
	initRenderTargets(attachments);
}

TextureData::~TextureData()
{
	if (*m_textureID) glDeleteTextures(m_numTextures, m_textureID);
	if (m_frameBuffer) glDeleteFramebuffers(1, &m_frameBuffer);
	if (m_renderBuffer) glDeleteRenderbuffers(1, &m_renderBuffer);
	if (m_textureID) delete[] m_textureID;
}

void TextureData::initTextures(unsigned char** data, GLfloat* filters, GLenum* internalFormat, GLenum* format, bool clamp)
{
	glGenTextures(m_numTextures, m_textureID);
	for (int i = 0; i < m_numTextures; i++)
	{
		glBindTexture(m_textureTarget, m_textureID[i]);

		glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, filters[i]);
		glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, filters[i]);

		if (clamp)
		{
			glTexParameterf(m_textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameterf(m_textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			if (m_textureTarget == GL_TEXTURE_CUBE_MAP)
			{
				glTexParameterf(m_textureTarget, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			}
		}

		if (m_textureTarget == GL_TEXTURE_CUBE_MAP)
		{
			for (size_t cu = 0; cu < 6; cu++)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + cu, 0, internalFormat[i], m_width, m_height, 0, format[i], GL_UNSIGNED_BYTE, data[cu]);
			}
		}
		else
		{
			glTexImage2D(m_textureTarget, 0, internalFormat[i], m_width, m_height, 0, format[i], GL_UNSIGNED_BYTE, data[i]);
		}

		if (filters[i] == GL_NEAREST_MIPMAP_NEAREST ||
			filters[i] == GL_NEAREST_MIPMAP_LINEAR ||
			filters[i] == GL_LINEAR_MIPMAP_NEAREST ||
			filters[i] == GL_LINEAR_MIPMAP_LINEAR)
		{
			glGenerateMipmap(m_textureTarget);
			GLfloat maxAnisotropy;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
			glTexParameterf(m_textureTarget, GL_TEXTURE_MAX_ANISOTROPY_EXT, glm::clamp(0.0f, 8.0f, maxAnisotropy));
		}
		else if (m_textureTarget != GL_TEXTURE_CUBE_MAP)
		{
			glTexParameterf(m_textureTarget, GL_TEXTURE_BASE_LEVEL, 0);
			glTexParameterf(m_textureTarget, GL_TEXTURE_MAX_LEVEL, 0);
		}
	}
}

void TextureData::initRenderTargets(GLenum* attachments)
{
	if (attachments == 0)
		return;

	GLenum drawBuffers[32];      //32 is the max number of bound textures in OpenGL
	assert(m_numTextures <= 32); //Assert to be sure no buffer overrun should occur

	bool hasDepth = false;
	for (int i = 0; i < m_numTextures; i++)
	{
		if (attachments[i] == GL_DEPTH_ATTACHMENT)
		{
			drawBuffers[i] = GL_NONE;
			hasDepth = true;
		}
		else
			drawBuffers[i] = attachments[i];

		if (attachments[i] == GL_NONE)
			continue;

		if (m_frameBuffer == 0)
		{
			glGenFramebuffers(1, &m_frameBuffer);
			glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
		}

		glFramebufferTexture2D(GL_FRAMEBUFFER, attachments[i], m_textureTarget, m_textureID[i], 0);
	}

	if (m_frameBuffer == 0)
		return;

	if (!hasDepth)
	{
		glGenRenderbuffers(1, &m_renderBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, m_renderBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_width, m_height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_renderBuffer);
	}

	glDrawBuffers(m_numTextures, drawBuffers);

	//glDrawBuffer(GL_NONE);
	//glReadBuffer(GL_NONE);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cerr << "Framebuffer creation failed!" << std::endl;
		assert(false);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void TextureData::bind(int textureNum) const
{
	glBindTexture(m_textureTarget, m_textureID[textureNum]);
}

void TextureData::bindAsRenderTarget() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
	glViewport(0, 0, m_width, m_height);
}

Texture::Texture(const std::string& fileName, GLenum textureTarget, GLfloat filter, GLenum internalFormat, GLenum format, bool clamp, GLenum attachment)
{
	m_fileName = fileName;

	std::map<std::string, TextureData*>::const_iterator it = s_resourceMap.find(fileName);
	if (it != s_resourceMap.end())
	{
		m_textureData = it->second;
		m_textureData->addReference();
	}
	else
	{
		std::string filePath = "Assets/Textures/" + fileName;
		int x, y, bytesPerPixel;
		if (textureTarget != GL_TEXTURE_CUBE_MAP)
		{
			unsigned char* data = stbi_load(filePath.c_str(), &x, &y, &bytesPerPixel, 4);
			if (data == nullptr)
			{
				//error check
				assert(false);
			}

			m_textureData = new TextureData(textureTarget, x, y, 1, &data, &filter, &internalFormat, &format, clamp, &attachment);
			stbi_image_free(data);
		}
		else
		{
			unsigned char** dataArr = new unsigned char*[6];
			for (size_t i = 0; i < 6; i++)
			{
				std::string file = Utility::split(filePath, '.')[0] + std::to_string(i) + "." + Utility::split(filePath, '.')[1];
				unsigned char* data = stbi_load(file.c_str(), &x, &y, &bytesPerPixel, 4);
				dataArr[i] = data;

				if (dataArr[i] == nullptr)
				{
					//error check
					assert(false);
				}
			}

			m_textureData = new TextureData(textureTarget, x, y, 1, dataArr, &filter, &internalFormat, &format, clamp, &attachment);
			for (size_t i = 0; i < 6; i++)
			{
				stbi_image_free(dataArr[i]);
			}
		}

		s_resourceMap.insert(std::make_pair(fileName, m_textureData));
	}
}

Texture::Texture(int width, int height, unsigned char* data, GLenum textureTarget, GLfloat filter, GLenum internalFormat, GLenum format, bool clamp, GLenum attachment)
{
	m_fileName = "";
	m_textureData = new TextureData(textureTarget, width, height, 1, &data, &filter, &internalFormat, &format, clamp, &attachment);
}

Texture::Texture(const Texture& texture) :
m_textureData(texture.m_textureData),
m_fileName(texture.m_fileName)
{
	m_textureData->addReference();
}

void Texture::operator=(Texture texture)
{
	char* temp[sizeof(Texture) / sizeof(char)];
	memcpy(temp, this, sizeof(Texture));
	memcpy(this, &texture, sizeof(Texture));
	memcpy(&texture, temp, sizeof(Texture));
}

Texture::~Texture()
{
	if (m_textureData && m_textureData->removeReference())
	{
		if (m_fileName.length() > 0)
			s_resourceMap.erase(m_fileName);

		delete m_textureData;
	}
}

void Texture::bind(unsigned int unit) const
{
	assert(unit >= 0 && unit <= 31);
	glActiveTexture(GL_TEXTURE0 + unit);
	m_textureData->bind(0);
}

void Texture::bindAsRenderTarget() const
{
	m_textureData->bindAsRenderTarget();
}