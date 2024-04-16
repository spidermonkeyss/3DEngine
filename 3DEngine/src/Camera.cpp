#include "Camera.h"

Camera::Camera(GLFWwindow* window)
	:transform()
{
	viewMatrix = glm::mat4(1.0f);
}

void Camera::CameraDraw(GLFWwindow* window)
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	projectionMatrix = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 150.0f);

	viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(transform.Position().x, transform.Position().y, transform.Position().z));
	viewMatrix = glm::inverse(viewMatrix);
}