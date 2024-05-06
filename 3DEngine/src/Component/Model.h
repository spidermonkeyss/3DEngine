#pragma once
#include "Renderer/Mesh.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Component.h"

class Model : public Component
{
private:
	Mesh* mesh;
	Shader* shader;
	Texture* texture;
public:
	Model();

	void SetMesh(Mesh* mesh);
	void SetShader(Shader* shader);
	void ApplyTexture(Texture* texture, const std::string& shaderUniformName);
	
private:
	friend class Renderer;
};

