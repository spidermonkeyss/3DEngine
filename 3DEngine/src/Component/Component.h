#pragma once

class GameObject;

class Component
{
private:
	unsigned int componentGameObjectId;
public:
	bool isEnabled = true;

	GameObject* gameobject;
private:
	friend class ComponentHandler;
	friend class ScriptHandler;
	friend class Physics;
};