#include "Model.h"
#include "GameObject.h"
#include "GLCall.h"
#include "Camera.h"

Model::Model()
{
	mesh = nullptr;
	material = nullptr;
}

void Model::SetMesh(Mesh* _mesh)
{
	mesh = _mesh;
}

void Model::SetMaterial(Material* _material)
{
	material = _material;
}
