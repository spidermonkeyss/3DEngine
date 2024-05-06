#pragma once
#include "Component/ComponentHandler.h"

class GameObject
{
private:
	unsigned int objectId;
	static unsigned int nextObjectId;
	Transform transform;

	GameObject();
	
	static GameObject* GetGameObjectByObjectId(unsigned int objectId);
public:
	~GameObject();

	template<typename T> T* AddComponent() { return Scene::currentScene->componentHandler.AddComponent<T>(objectId); }
	template<typename T> void RemoveComponent() { Scene::currentScene->componentHandler.RemoveComponent<T>(objectId); }
	template<typename T> T* GetComponent() { return Scene::currentScene->componentHandler.GetComponent<T>(objectId); }
	//WARNGING: This will add a component if one does not exist already, but is a little faster due to not checking if the component exists first before grabbing it
	template<typename T> T* GetComponentUnsafe() { return Scene::currentScene->componentHandler.GetComponentUnsafe<T>(objectId); }
	
	static GameObject* CreateGameObject();
	static void DestroyGameObject(GameObject* gameObject);

private:
	friend class Engine;
	friend class Component;
	friend class Physics;
	friend class Renderer;
	friend class Scene;
};