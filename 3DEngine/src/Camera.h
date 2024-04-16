#pragma once
#include "Transform.h"
#include "GLCall.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
private:
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	Transform transform;
public:
	Camera(GLFWwindow* window);

	void CameraDraw(GLFWwindow* window);

	inline glm::mat4* GetViewMatrix() { return &viewMatrix; }
	inline glm::mat4* GetProjectionMatrix() { return &projectionMatrix; }
	inline Transform* Transform() { return &transform; }
};