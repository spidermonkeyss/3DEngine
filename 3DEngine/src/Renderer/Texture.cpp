#include "Texture.h"
#include <stb_image.h>

void Texture::Bind(unsigned int slot)
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, gl_TextureId));
}

void Texture::Unbind()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::LoadGLTexture(const std::string& filePath)
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(filePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	GLCall(glGenTextures(1, &gl_TextureId));
	GLCall(glBindTexture(GL_TEXTURE_2D, gl_TextureId));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);
}

bool Texture::LoadTextureFile(const std::string& filePath)
{
    std::string extensionTypeStr = FileLoader::GetFileExtension(filePath);
	std::string _fileName = FileLoader::GetFileName(filePath);

    if (extensionTypeStr == "png")
    {
        LoadGLTexture(filePath);
		fileName = _fileName;
		return true;
    }
    else
    {
        std::cout << "File extension not supported\n";
    }
    return false;
}
