#pragma once

class GameObject;

class Component
{
private:
	unsigned int componentGameObjectId;
public:
	bool isEnabled = true;

	GameObject* GameObject();
private:
	friend class ComponentHandler;
	friend class Physics;
};