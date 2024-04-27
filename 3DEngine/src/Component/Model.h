#pragma once
#include "Mesh.h"
#include "Shader.h"

class Camera;
class GameObject;

class Model
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

