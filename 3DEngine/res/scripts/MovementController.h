#pragma once
#include "Component/Script.h"

class MovementController : public Script
{
public:
	float speed = 5.0f;
	float turnSpeed = 0.1f;

	void Update() override;
};