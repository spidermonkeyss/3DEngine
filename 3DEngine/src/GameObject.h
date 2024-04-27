#pragma once
#include "Component/ComponentHandler.h"

class GameObject
{
private:
	unsigned int objectId;
	static unsigned int nextObjectId;
	inline static std::map<unsigned int, GameObject*> gameObjects;
public:

	GameObject();
	~GameObject();

	template<typename T> void AddComponent() { ComponentHandler::AddComponent<T>(objectId); }
	template<typename T> void RemoveComponent() { ComponentHandler::RemoveComponent<T>(objectId); }
	template<typename T> T* GetComponent() { return ComponentHandler::GetComponent<T>(objectId); }
	//WARNGING: This will add a component if one does not exist already, but is a little faster due to not checking if the component exists first before grabbing it
	template<typename T> T* GetComponentUnsafe() { return ComponentHandler::GetComponentUnsafe<T>(objectId); }
	

	static GameObject* GetGameObjectByObjectId(unsigned int objectId);
	inline unsigned int ID() { return objectId; }
	inline static unsigned int GetNextObjectId(){ return nextObjectId; }
};