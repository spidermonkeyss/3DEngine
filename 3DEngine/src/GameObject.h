#pragma once
#include "Component/ComponentHandler.h"

class Model;

class GameObject
{
private:
	unsigned int objectId;
	static unsigned int nextObjectId;

public:
	GameObject();
	~GameObject();

	template<typename T> void AddComponent() { ComponentHandler::AddComponent<T>(objectId); }
	template<typename T> T* GetComponent() { return ComponentHandler::GetComponent<T>(objectId); }
	//WARNGING: This will add a component if one does not exist already, but is a little faster due to not checking if the component exists first before grabbing it
	template<typename T> T* GetComponentUnsafe() { return ComponentHandler::GetComponentUnsafe<T>(objectId); }
	
	inline unsigned int ID() { return objectId; }
	inline static unsigned int GetNextObjectId(){ return nextObjectId; }
};