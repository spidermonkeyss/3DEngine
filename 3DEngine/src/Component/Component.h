#pragma once

class GameObject;

class Component
{
private:
public:
	unsigned int componentGameObjectId;
	bool isEnabled = true;

	GameObject* GameObject();
};