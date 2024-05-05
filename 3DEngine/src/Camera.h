#pragma once
#include "Transform.h"

class Camera
{
private:
	Transform transform;
public:
	Camera();

	inline Transform* Transform() { return &transform; }
};