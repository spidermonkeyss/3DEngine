#pragma once
#include "Vector3.h"
#include "Component.h"

class Transform : public Component
{
public:
	Vector3 position;

	Transform();
	
	void SetPosition(float x, float y, float z);
	void SetPosition(Vector3 position);
};