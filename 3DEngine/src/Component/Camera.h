#pragma once
#include "Transform.h"
#include "Component.h"

class Camera : public Component
{
public:
	Camera();
private:
	friend class Engine;
	friend class Renderer;
};