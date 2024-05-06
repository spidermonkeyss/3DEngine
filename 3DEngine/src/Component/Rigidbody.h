#pragma once
#include "Math/Vector3.h"
#include "Component.h"

class Rigidbody : public Component
{
private:
	Vector3 forceVector;
public:
	bool doGravity = true;
	Vector3 velocity;
	float mass = 1;//in kilograms
	
	void SetVelocity(float x, float y, float z);
	//void AddForce(float x, float y, float z);
	//void AddForce(Vector3 forceVec3);
};