#pragma once
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

#include <string>

class Material
{
protected:
	void CreateProperties();
private:
	unsigned int id;
	static unsigned int nextId;

	Shader* shader = nullptr;
	std::string filePath = "";

	std::unordered_map<std::string, Texture*> textures;
	std::unordered_map<std::string, int> ints;
	std::unordered_map<std::string, float> floats;
	std::unordered_map<std::string, float[2]> float2s;
	std::unordered_map<std::string, float[3]> float3s;
	std::unordered_map<std::string, float[4]> float4s;

	void ApplyMaterialToShader();

	Material();
public:
	static Material* CreateMaterial();

	void SetShader(Shader* shader);
	void SetShader(std::string filePath);
	void SetTexture(std::string uniformName, Texture * _texture);
	void SetTexture(std::string uniformName, std::string textureFilePath);

	void SetInt(std::string uniformName, int value);
	void SetFloat(std::string uniformName, float value);
	void SetFloat2(std::string uniformName, float v1, float v2);
	void SetFloat3(std::string uniformName, float v1, float v2, float v3);
	void SetFloat4(std::string uniformName, float v1, float v2, float v3, float v4);

private:
	friend class Engine;
	friend class Renderer;
	friend class Scene;
};