#include "GameObject.h"
#include "Component/Transform.h"
#include "Component/Model.h"
#include "Component/Rigidbody.h"

#include <iostream>

unsigned int GameObject::nextObjectId = 0;

GameObject::GameObject()
{
	std::cout << "GameObject created.\n";
	objectId = nextObjectId;
	gameObjects[objectId] = this;
	AddComponent<Transform>();
	nextObjectId++;
}

GameObject::~GameObject()
{
	std::cout << "GameObject deleted.\n";
	RemoveComponent<Transform>();
	RemoveComponent<Model>();
	RemoveComponent<Rigidbody>();
	RemoveComponent<BoxCollider>();
	gameObjects.erase(objectId);
}

GameObject* GameObject::GetGameObjectByObjectId(unsigned int objectId)
{
	if (gameObjects.count(objectId) == 1)
		return gameObjects[objectId];
	return nullptr;
}