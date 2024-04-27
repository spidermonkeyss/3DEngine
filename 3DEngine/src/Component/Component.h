#pragma once

class GameObject;

class Component
{
private:
	unsigned int componentGameObjectId;
public:
	bool isEnabled = true;

	GameObject* GameObject();
	unsigned int GetComponentGameObjectId() { return componentGameObjectId; }
};