#pragma once
#include "Window/Window.h"
#include "Component/Camera.h"

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
	void Render();
public:
	void SetCamera(Camera* camera);

private:
	friend class Engine;
	friend class Scene;
};