#pragma once
#include "Vector3.h"
#include "Component.h"

class Rigidbody : public Component
{
public:
	bool doGravity = true;
	Vector3 velocity;
	float mass = 1;//in kilograms
	
	void SetVelocity(float x, float y, float z);
};