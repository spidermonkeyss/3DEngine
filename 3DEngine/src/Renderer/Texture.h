#pragma once
#include "FileLoader.h"
#include "GLCall.h"
#include <string>

class Texture
{
private:
	std::string filePath;
	bool isLoaded;
	unsigned int gl_TextureId;
	unsigned char* localBuffer;
	int width, height, BPP;

	void Bind(unsigned int slot);
	void Unbind();

	void LoadGLTexture(const std::string& filePath);

	Texture();
public:
	static Texture* CreateTexture();
	bool LoadTextureFile(const std::string& filePath);

private:
	friend class Engine;
	friend class Renderer;
	friend class Model;
	friend class Shader;
	friend class Material;
};