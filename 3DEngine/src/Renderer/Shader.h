#pragma once
#include "FileLoader.h"
#include "Texture.h"
#include "GLCall.h"

#include <string>
#include <unordered_map>

class Shader
{
private:
	struct ShaderProperity
	{
		int location;
		std::string name;
		GLenum type;
	};

	bool isLoaded;
	unsigned int gl_ShaderId;
	std::string filePath;
	
	std::unordered_map<std::string, ShaderProperity> attributies;
	std::unordered_map<std::string, ShaderProperity> uniforms;

	void LoadGlShader(const std::string& vertexShader, const std::string& fragmentShader);

	void SetMVP(const std::string& mvpUniformName, const float* mvp);
	bool SetTexture(const std::string& uniformName, int value, Texture* texture);

	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform2f(const std::string& name, float v1, float v2);
	void SetUniform3f(const std::string& name, float v1, float v2, float v3);
	void SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4);
	void SetUniformMat4(const std::string& name, const float* mat4);
	
	int GetAttributeLocation(const std::string& name);
	int GetUniformLocation(const std::string& name);

	void Bind();

	Shader();
public:
	~Shader();
	
	static Shader* CreateShader();

	bool LoadShaderFile(const std::string& filePath);
private:
	friend class Engine;
	friend class Scene;
	friend class Renderer;
	friend class Material;
};