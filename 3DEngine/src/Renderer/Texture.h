#pragma once
#include "FileLoader.h"
#include "GLCall.h"
#include <string>

class Texture
{
private:
	unsigned int gl_TextureId;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;

	void Bind(unsigned int slot);
	void Unbind();

	void LoadGLTexture(const std::string& filePath);

public:
	bool LoadTextureFile(const std::string& filePath);

private:
	friend class Renderer;
	friend class Model;
	friend class Shader;
};