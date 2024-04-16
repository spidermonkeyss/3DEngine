#include "Model.h"
#include "GameObject.h"
#include "GLCall.h"
#include "Camera.h"

Model::Model(GameObject* _gameObject)
{
	mesh = nullptr;
	shader = nullptr;
	gameObject = _gameObject;
}

bool Model::Bind()
{
	if (mesh == nullptr || shader == nullptr)
		return false;
	if (mesh->vertexTypeSize == 0)
		return false;
	mesh->Bind();
	shader->Bind();
	return true;
}

void Model::SetMesh(Mesh* _mesh)
{
	mesh = _mesh;
}

void Model::SetShader(Shader* _shader)
{
	shader = _shader;
}

void Model::Draw(Camera* camera)
{
	bool isBound = Bind();
	if (!isBound)
		return;
	transformMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(gameObject->Transform()->Position().x,
																gameObject->Transform()->Position().y,
																gameObject->Transform()->Position().z));

	glm::mat4 mvp = *camera->GetProjectionMatrix() * *camera->GetViewMatrix() * transformMatrix;
	shader->SetMVP(&mvp[0][0]);

	if (GetMesh()->hasIndexBuffer)
	{
		GLCall(glDrawElements(GL_TRIANGLES, GetMesh()->indexCount, GetMesh()->indexType, nullptr));
	}
	else
	{
		GLCall(glDrawArrays(GL_TRIANGLES, 0, GetMesh()->vertexCount));
	}
}