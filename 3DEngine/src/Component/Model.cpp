#include "Model.h"
#include "GameObject.h"
#include "GLCall.h"
#include "Camera.h"

Model::Model()
{
	mesh = nullptr;
	shader = nullptr;
}

void Model::SetMesh(Mesh* _mesh)
{
	mesh = _mesh;
}

void Model::SetShader(Shader* _shader)
{
	shader = _shader;
}