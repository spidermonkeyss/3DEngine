#pragma once
//#include "Component/BoxCollider.h"
#include "Vector3.h"

class BoxCollider;

class Collision
{
public:
	BoxCollider* otherCollider;
	Vector3 collisionForceDirection;
	float penDepth;
};