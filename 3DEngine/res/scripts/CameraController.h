#pragma once
#include "Component/Script.h"

class CameraController : public Script
{
public:
	GameObject* gameObjectToFollow;

	void Update() override;
	void OnStart() override;
};