#pragma once
#include "Renderer/Shader.h"

#include <vector>

class Material
{
protected:
	void CreateProperties();
private:

	struct MaterialFileProperties
	{
		struct TexturePair { std::string propertyName; std::string filePath; };
		struct IntPair { std::string propertyName; int value; };
		struct FloatPair { std::string propertyName; float value; };
		struct Float2Pair { std::string propertyName; float value[2]; };
		struct Float3Pair { std::string propertyName; float value[3]; };
		struct Float4Pair { std::string propertyName; float value[4]; };

		std::string shaderFilePath = "";

		std::vector<TexturePair> textures;
		std::vector<IntPair> ints;
		std::vector<FloatPair> floats;
		std::vector<Float2Pair> float2s;
		std::vector<Float3Pair> float3s;
		std::vector<Float4Pair> float4s;
	};

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
	bool isLoaded;

	void SetShader(Shader* shader);
	void SetShader(std::string filePath);
	void SetTexture(std::string uniformName, Texture * _texture);
	void SetTexture(std::string uniformName, std::string textureFilePath);

	void SetInt(std::string uniformName, int value);
	void SetFloat(std::string uniformName, float value);
	void SetFloat2(std::string uniformName, float v1, float v2);
	void SetFloat3(std::string uniformName, float v1, float v2, float v3);
	void SetFloat4(std::string uniformName, float v1, float v2, float v3, float v4);

	bool LoadMaterialFile(const std::string& _filePath);
	
	static Material* CreateMaterial();

private:
	friend class Engine;
	friend class Renderer;
	friend class Scene;
	friend class FileLoader;
	friend class Model;
};