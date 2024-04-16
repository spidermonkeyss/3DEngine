#pragma once
#include "Mesh.h"
#include "Shader.h"
//#include "Vector3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera;
class GameObject;

class Model
{
private:
	GameObject* gameObject;
	Mesh* mesh;
	//Texture* texture
	Shader* shader;
	glm::mat4 transformMatrix = glm::mat4(1.0f);
	bool Bind();
public:
	Model(GameObject* gameObject);


	void SetMesh(Mesh* mesh);
	void SetShader(Shader* shader);

	void Draw(Camera* camera);
	
	inline Mesh* GetMesh() { return mesh; }
	inline Shader* GetShader() { return shader; }
};

