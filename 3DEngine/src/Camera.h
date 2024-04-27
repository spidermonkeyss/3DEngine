#pragma once
#include "Component/Transform.h"

class Camera
{
private:
	Transform transform;
public:
	Camera();

	inline Transform* Transform() { return &transform; }
};