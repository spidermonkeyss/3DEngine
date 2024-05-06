#pragma once
#include "Math/Vector3.h"

class BoxCollider;

class Collision
{
private:
	BoxCollider* otherCollider;
	Vector3 collisionForceDirection;
	float penDepth;
public:
	inline BoxCollider* OtherCollider() { return otherCollider; }

private:
	friend class Physics;
};