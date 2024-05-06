#include "Model.h"
#include "GameObject.h"
#include "GLCall.h"
#include "Camera.h"

Model::Model()
{
	mesh = nullptr;
	shader = nullptr;
	texture = nullptr;
}

void Model::SetMesh(Mesh* _mesh)
{
	mesh = _mesh;
}

void Model::SetShader(Shader* _shader)
{
	shader = _shader;
}

void Model::ApplyTexture(Texture* _texture, const std::string& shaderUniformName)
{
	texture = _texture;
	shader->SetTexture(shaderUniformName, 0, _texture);
}
