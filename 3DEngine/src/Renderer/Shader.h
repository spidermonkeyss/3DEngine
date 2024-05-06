#pragma once
#include "FileLoader.h"
#include "Texture.h"

#include <string>
#include <unordered_map>

class Shader
{
private:
	unsigned int gl_ShaderId;
	//int mvp_location;
	std::unordered_map<std::string, int> uniformLocationCache;

	void LoadGlShader(const std::string& vertexShader, const std::string& fragmentShader);

	void SetMVP(const std::string& mvpUniformName, const float* mvp);
	bool SetTexture(const std::string& uniformName, int value, Texture* texture);
	void SetUniform1i(const std::string& name, int value);
	
	int GetUniformLocation(const std::string& name);

	void Bind();
public:
	~Shader();

	bool LoadShaderFile(const std::string& filePath);
private:
	friend class Renderer;
	friend class Model;
};