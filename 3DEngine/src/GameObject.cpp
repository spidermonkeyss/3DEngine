#include "GameObject.h"
#include "Transform.h"
#include "Component/Model.h"
#include "Component/Rigidbody.h"

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
	gameObjects[objectId] = std::move(wee);
	gameObjects[objectId]->objectId = objectId;
	return gameObjects[objectId].get();
}

void GameObject::DestroyGameObject(GameObject* gameObject)
{
	std::cout << "GameObject deleted.\n";
	gameObject->RemoveComponent<Model>();
	gameObject->RemoveComponent<Rigidbody>();
	gameObject->RemoveComponent<BoxCollider>();
	gameObjects.erase(gameObject->ID());
}

GameObject* GameObject::GetGameObjectByObjectId(unsigned int objectId)
{
	if (gameObjects.count(objectId) == 1)
		return gameObjects[objectId].get();
	return nullptr;

}