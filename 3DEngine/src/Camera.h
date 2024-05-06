#pragma once
#include "Transform.h"

class Camera
{
private:
	Transform transform;
	Camera();
public:
	inline Transform* Transform() { return &transform; }
private:
	friend class Engine;
	friend class Renderer;
};