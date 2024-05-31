#pragma once

#include <string>

class Texture
{
private:
	std::string filePath;
	unsigned int gl_TextureId;
	unsigned char* localBuffer;
	int width, height, BPP;

	void Bind(unsigned int slot);
	void Unbind();

	void LoadGLTexture(const std::string& filePath);

	Texture();
public:
	bool isLoaded;
	
	~Texture();
	
	bool LoadTextureFile(const std::string& filePath);

	static Texture* CreateTexture();

private:
	friend class Engine;
	friend class Renderer;
	friend class Model;
	friend class Shader;
	friend class Material;
	friend class Scene;
};