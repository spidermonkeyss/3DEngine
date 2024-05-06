#include "Rigidbody.h"

void Rigidbody::SetVelocity(float x, float y, float z)
{
	velocity.x = x;
	velocity.y = y;
	velocity.z = z;
}

/*
void Rigidbody::AddForce(float x, float y, float z)
{
	forceVector.x += x;
	forceVector.y += y;
	forceVector.z += z;
}

void Rigidbody::AddForce(Vector3 forceVec3)
{
	forceVector.x += forceVec3.x;
	forceVector.y += forceVec3.y;
	forceVector.z += forceVec3.z;
}
*/