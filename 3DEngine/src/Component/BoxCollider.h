#pragma once
#include "Component.h"
#include "Vector3.h"
#include "Collision.h"

#include <vector>

class BoxCollider : public Component
{
public:
	std::vector<Collision> collisions;
	bool isTrigger = false;
	Vector3 offset;
	Vector3 lengths;
};

