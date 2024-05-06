#include "GameObject.h"
#include "Transform.h"
//#include "Component/Model.h"
//#include "Component/Rigidbody.h"
#include "Scene.h"

#include <iostream>

unsigned int GameObject::nextObjectId = 0;

GameObject::GameObject()
{
	std::cout << "GameObject created.\n";
}

GameObject::~GameObject()
{
	std::cout << "GameObject destroyed.\n";
}

GameObject* GameObject::CreateGameObject()
{
	unsigned int objectId = nextObjectId;
	nextObjectId++;
	std::unique_ptr<GameObject> wee(new GameObject());
	Scene::currentScene->gameObjects[objectId] = std::move(wee);
	Scene::currentScene->gameObjects[objectId]->objectId = objectId;
	return Scene::currentScene->gameObjects[objectId].get();
}

void GameObject::DestroyGameObject(GameObject* gameObject)
{
	std::cout << "GameObject deleted.\n";
	gameObject->RemoveComponent<Model>();
	gameObject->RemoveComponent<Rigidbody>();
	gameObject->RemoveComponent<BoxCollider>();
	Scene::currentScene->gameObjects.erase(gameObject->objectId);
}

GameObject* GameObject::GetGameObjectByObjectId(unsigned int objectId)
{
	if (Scene::currentScene->gameObjects.count(objectId) == 1)
		return Scene::currentScene->gameObjects[objectId].get();
	return nullptr;

}