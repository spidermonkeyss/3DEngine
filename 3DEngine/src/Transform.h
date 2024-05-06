#pragma once
#include "Math/Vector3.h"

class Transform
{
public:
	Vector3 position;

	Transform();
	
	void SetPosition(float x, float y, float z);
	void SetPosition(Vector3 position);
};