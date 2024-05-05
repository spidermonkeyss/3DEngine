#pragma once
#include "Component/ComponentHandler.h"

#include <memory>

class GameObject
{
private:
	unsigned int objectId;
	static unsigned int nextObjectId;
	inline static std::map<unsigned int, std::unique_ptr<GameObject>> gameObjects;
	Transform _transform;

	GameObject();
public:
	~GameObject();

	template<typename T> T* AddComponent() { return ComponentHandler::AddComponent<T>(objectId); }
	template<typename T> void RemoveComponent() { ComponentHandler::RemoveComponent<T>(objectId); }
	template<typename T> T* GetComponent() { return ComponentHandler::GetComponent<T>(objectId); }
	//WARNGING: This will add a component if one does not exist already, but is a little faster due to not checking if the component exists first before grabbing it
	template<typename T> T* GetComponentUnsafe() { return ComponentHandler::GetComponentUnsafe<T>(objectId); }

	static GameObject* CreateGameObject();
	static void DestroyGameObject(GameObject* gameObject);
	
	inline Transform* transform() { return &_transform; }
	inline unsigned int ID() { return objectId; }

	static GameObject* GetGameObjectByObjectId(unsigned int objectId);
	inline static unsigned int GetNextObjectId(){ return nextObjectId; }

	//inline static std::map<unsigned int, GameObject>* DEBUG_GetGameObjectsMap() { return &gameObjects; }
};