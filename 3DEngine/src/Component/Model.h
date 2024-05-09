#pragma once
#include "Renderer/Mesh.h"
#include "Renderer/Material.h"
#include "Component.h"

class Model : public Component
{
private:
	Mesh* mesh;
	Material* material;

public:
	Model();

	void SetMesh(Mesh* mesh);
	void SetMaterial(Material* material);
	
private:
	friend class Engine;
	friend class Renderer;
};

