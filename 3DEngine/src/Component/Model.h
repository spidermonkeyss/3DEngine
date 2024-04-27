#pragma once
#include "Mesh.h"
#include "Shader.h"
#include "Component.h"

class Model : public Component
{
private:
	Mesh* mesh;
	Shader* shader;
public:
	Model();

	void SetMesh(Mesh* mesh);
	void SetShader(Shader* shader);
	
	inline Mesh* GetMesh() { return mesh; }
	inline Shader* GetShader() { return shader; }
};

