#pragma once
#include "Transform.h"
#include "Model.h"
#include "Rigidbody.h"
#include "BoxCollider.h"

#include <unordered_map>
#include <iostream>

class ComponentHandler
{
private:
	std::unordered_map<unsigned int, Model> modelComponents;
	std::unordered_map<unsigned int, Rigidbody> rigidbodyComponents;
	std::unordered_map<unsigned int, BoxCollider> boxColliderComponents;

	template<typename T> T* AddComponent(unsigned int objectId)
	{
		std::cout << typeid(T).name() <<  " is not a component" << std::endl;
	}
	template<> Model* AddComponent<Model>(unsigned int objectId)
	{
		Model* comp = &modelComponents[objectId];
		comp->componentGameObjectId = objectId;
		return comp;
	}
	template<> Rigidbody* AddComponent<Rigidbody>(unsigned int objectId)
	{
		Rigidbody* comp = &rigidbodyComponents[objectId];
		comp->componentGameObjectId = objectId;
		return comp;
	}
	template<> BoxCollider* AddComponent<BoxCollider>(unsigned int objectId)
	{
		BoxCollider* comp = &boxColliderComponents[objectId];
		comp->componentGameObjectId = objectId;
		return comp;
	}


	template<typename T> void RemoveComponent(unsigned int objectId) 
	{
		std::cout << typeid(T).name() << " is not a component" << std::endl;
	}
	template<> void RemoveComponent<Model>(unsigned int objectId)
	{
		modelComponents.erase(objectId);
	}
	template<> void RemoveComponent<Rigidbody>(unsigned int objectId)
	{
		rigidbodyComponents.erase(objectId);
	}
	template<> void RemoveComponent<BoxCollider>(unsigned int objectId)
	{
		boxColliderComponents.erase(objectId);
	}



	template<typename T> T* GetComponent(unsigned int objectId) 
	{ 
		std::cout << typeid(T).name() << " is not a component" << std::endl;
		return nullptr;
	}
	template<> Model* GetComponent<Model>(unsigned int objectId)
	{
		if (modelComponents.count(objectId) == 1)
			return &modelComponents[objectId];
		return nullptr;
	}
	template<> Rigidbody* GetComponent<Rigidbody>(unsigned int objectId)
	{
		if (rigidbodyComponents.count(objectId) == 1)
			return &rigidbodyComponents[objectId];
		return nullptr;
	}
	template<> BoxCollider* GetComponent<BoxCollider>(unsigned int objectId)
	{
		if (boxColliderComponents.count(objectId) == 1)
			return &boxColliderComponents[objectId];
		return nullptr;
	}

	

	template<typename T> T* GetComponentUnsafe(unsigned int objectId)
	{
		std::cout << typeid(T).name() << " is not a component" << std::endl;
		return nullptr; 
	}
	template<> Model* GetComponentUnsafe<Model>(unsigned int objectId)
	{
		return &modelComponents[objectId];
	}
	template<> Rigidbody* GetComponentUnsafe<Rigidbody>(unsigned int objectId)
	{
		return &rigidbodyComponents[objectId];
	}
	template<> BoxCollider* GetComponentUnsafe<BoxCollider>(unsigned int objectId)
	{
		return &boxColliderComponents[objectId];
	}

private:
	friend class Scene;
	friend class GameObject;
	friend class Physics;
	friend class Renderer;
};