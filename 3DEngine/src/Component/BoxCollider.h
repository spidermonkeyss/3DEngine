#pragma once
#include "Component.h"
#include "Math/Vector3.h"
#include "Collision.h"

#include <vector>

class BoxCollider : public Component
{
private:
	std::vector<Collision> collisions;
public:
	bool isTrigger = false;
	Vector3 offset;
	Vector3 lengths;
private:
	friend class Physics;
};

