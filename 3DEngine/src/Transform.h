#pragma once
#include "Vector3.h"

class Transform
{
private:
	Vector3 position;
public:
	Transform();

	void SetPosition(float x, float y, float z);
	void SetPosition(Vector3 position);

	inline Vector3 Position() { return position; }
};