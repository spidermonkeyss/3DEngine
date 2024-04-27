#pragma once
#include "GLCall.h"
#include "Camera.h"
#include "Component/Model.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Renderer
{
private:
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	void DrawModel(unsigned int objectId);

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
public:
	Renderer();

	static char keyPressed;

	GLFWwindow* window;
	Camera* camera;
	bool shouldWindowClose = false;

	int Init();
	void SetCamera(Camera* camera);
	void Clear();
	void Render();
};