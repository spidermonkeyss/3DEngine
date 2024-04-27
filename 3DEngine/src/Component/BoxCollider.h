#pragma once
#include "Component.h"

class BoxCollider : public Component
{
public:
	bool isTrigger = false;
	Vector3 offset;
	Vector3 lengths;
};