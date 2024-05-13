#include "Texture.h"
#include "Scene.h"
#include "FileLoader.h"

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
	localBuffer = FileLoader::Load_image_file(filePath, &width, &height, &BPP, 4);

	GLCall(glGenTextures(1, &gl_TextureId));
	GLCall(glBindTexture(GL_TEXTURE_2D, gl_TextureId));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (localBuffer)
		free(localBuffer);
}

Texture::Texture()
	:filePath(""), isLoaded(false), gl_TextureId(0), localBuffer(nullptr), height(0), width(0), BPP(0)
{
}

Texture::~Texture()
{
}

Texture* Texture::CreateTexture()
{
	return Scene::currentScene->CreateTexture();
}

bool Texture::LoadTextureFile(const std::string& _filePath)
{
    std::string extensionTypeStr = FileLoader::GetFileExtension(_filePath);

    if (extensionTypeStr == "png")
    {
        LoadGLTexture(_filePath);
		isLoaded = true;
		filePath = _filePath;
		return true;
    }
    else
    {
        std::cout << "File extension not supported\n";
    }
    return false;
}
