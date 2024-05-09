#pragma once

#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

class Material
{
private:
	struct TextureProp
	{
		std::string uniformName;
		Texture* texture;
	};
	struct IntProp
	{
		std::string uniformName;
		int value;
	};
	struct FloatProp 
	{
		std::string uniformName;
		float value;
	};
	struct Float2Prop
	{
		std::string uniformName;
		float v1, v2;
	};
	struct Float3Prop
	{
		std::string uniformName;
		float v1, v2, v3;
	};
	struct Float4Prop
	{
		std::string uniformName;
		float v1, v2, v3, v4;
	};

	Shader* shader = nullptr;

	std::unordered_map<std::string, Texture*> textures;
	std::unordered_map<std::string, int> ints;
	std::unordered_map<std::string, float> floats;
	std::unordered_map<std::string, float[2]> float2s;
	std::unordered_map<std::string, float[3]> float3s;
	std::unordered_map<std::string, float[4]> float4s;

	void ApplyMaterialToShader();

public:
	void SetShader(Shader* shader);
	void SetTexture(std::string uniformName, Texture * _texture);

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