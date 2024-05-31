#pragma once
#include "Transform.h"
#include "Scene.h"

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

	template<typename T> T* AddComponent() { return Scene::currentScene->componentHandler.AddComponent<T>(objectId, this); }
	template<typename T> void RemoveComponent() { Scene::currentScene->componentHandler.RemoveComponent<T>(objectId); }
	template<typename T> T* GetComponent() { return Scene::currentScene->componentHandler.GetComponent<T>(objectId); }
	//WARNGING: This will add a component if one does not exist already, but is a little faster due to not checking if the component exists first before grabbing it
	template<typename T> T* GetComponentUnsafe() { return Scene::currentScene->componentHandler.GetComponentUnsafe<T>(objectId); }
	
	template<typename T> T* AddScript() { return Scene::currentScene->scriptHandler.AddScript<T>(objectId, this); }
	template<typename T> void RemoveScript() { return Scene::currentScene->scriptHandler.RemoveScript<T>(objectId); }
	template<typename T> T* GetScript() { return Scene::currentScene->scriptHandler.GetScript<T>(objectId); }
	//WARNGING: This will add a script if one does not exist already, but is a little faster due to not checking if the script exists first before grabbing it
	template<typename T> T* GetScriptUnsafe() { return Scene::currentScene->scriptHandler.GetScriptUnsafe<T>(objectId); }

	static GameObject* CreateGameObject();
	static void DestroyGameObject(GameObject* gameObject);

	Transform* Transform() { return &transform; }

private:
	friend class Engine;
	friend class Component;
	friend class Physics;
	friend class Renderer;
	friend class Scene;
};