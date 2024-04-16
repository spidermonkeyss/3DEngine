#pragma once
#include <string>
#include "FileLoader.h"

class Shader
{
private:
	unsigned int gl_ShaderId;
	int mvp_location;
	void LoadGlShader(const std::string& vertexShader, const std::string& fragmentShader);
public:
	
	~Shader();

	void Bind();

	void LoadShaderFile(const std::string& filePath);
	void SetMVP(const float* mvp);
};