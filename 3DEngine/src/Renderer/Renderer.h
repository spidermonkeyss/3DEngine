#pragma once
#include "Window/Window.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Renderer
{
private:
	static Renderer* currentRenderer;
	Window* window;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	Camera* camera;
	
	Renderer();

	void DrawModel(unsigned int objectId);
	void SetCamera(Camera* camera);
	void Render();
public:

private:
	friend class Engine;
};