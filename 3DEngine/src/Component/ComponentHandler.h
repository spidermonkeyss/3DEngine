#pragma once
#include "Transform.h"
#include "Model.h"
#include "Rigidbody.h"
#include "BoxCollider.h"

#include <map>
#include <vector>
#include <iostream>

class ComponentHandler
{
private:
	inline static std::map<unsigned int, Transform> tranformComponents;
	inline static std::map<unsigned int, Model> modelComponents;
	inline static std::map<unsigned int, Rigidbody> rigidbodyComponents;
	inline static std::map<unsigned int, BoxCollider> boxColliderComponents;
public:
	template<typename T> static void AddComponent(unsigned int objectId)
	{
		std::cout << typeid(T).name() <<  " is not a component" << std::endl;
	}
	template<> static void AddComponent<Transform>(unsigned int objectId) 
	{ 
		tranformComponents[objectId];
	}
	template<> static void AddComponent<Model>(unsigned int objectId)
	{
		modelComponents[objectId];
	}
	template<> static void AddComponent<Rigidbody>(unsigned int objectId)
	{
		rigidbodyComponents[objectId];
	}
	template<> static void AddComponent<BoxCollider>(unsigned int objectId)
	{
		boxColliderComponents[objectId];
	}


	template<typename T> static void RemoveComponent(unsigned int objectId) 
	{
		std::cout << typeid(T).name() << " is not a component" << std::endl;
	}
	template<> static void RemoveComponent<Transform>(unsigned int objectId)
	{
		tranformComponents.erase(objectId);
	}
	template<> static void RemoveComponent<Model>(unsigned int objectId)
	{
		modelComponents.erase(objectId);
	}
	template<> static void RemoveComponent<Rigidbody>(unsigned int objectId)
	{
		rigidbodyComponents.erase(objectId);
	}
	template<> static void RemoveComponent<BoxCollider>(unsigned int objectId)
	{
		boxColliderComponents.erase(objectId);
	}



	template<typename T> static T* GetComponent(unsigned int objectId) 
	{ 
		std::cout << typeid(T).name() << " is not a component" << std::endl;
		return nullptr;
	}
	template<> static Transform* GetComponent<Transform>(unsigned int objectId)
	{
		if (tranformComponents.count(objectId) == 1)
			return &tranformComponents[objectId];
		return nullptr;
	}
	
	template<> static Model* GetComponent<Model>(unsigned int objectId)
	{
		if (modelComponents.count(objectId) == 1)
			return &modelComponents[objectId];
		return nullptr;
	}
	template<> static Rigidbody* GetComponent<Rigidbody>(unsigned int objectId)
	{
		if (rigidbodyComponents.count(objectId) == 1)
			return &rigidbodyComponents[objectId];
		return nullptr;
	}
	template<> static BoxCollider* GetComponent<BoxCollider>(unsigned int objectId)
	{
		if (boxColliderComponents.count(objectId) == 1)
			return &boxColliderComponents[objectId];
		return nullptr;
	}

	

	template<typename T> static T* GetComponentUnsafe(unsigned int objectId) 
	{
		std::cout << typeid(T).name() << " is not a component" << std::endl;
		return nullptr; 
	}
	template<> static Transform* GetComponentUnsafe<Transform>(unsigned int objectId) 
	{
		return &tranformComponents[objectId];
	}
	template<> static Model* GetComponentUnsafe<Model>(unsigned int objectId)
	{
		return &modelComponents[objectId];
	}
	template<> static Rigidbody* GetComponentUnsafe<Rigidbody>(unsigned int objectId)
	{
		return &rigidbodyComponents[objectId];
	}
	template<> static BoxCollider* GetComponentUnsafe<BoxCollider>(unsigned int objectId)
	{
		return &boxColliderComponents[objectId];
	}

	inline static std::map<unsigned int, Transform>* GetTranformComponents() { return &tranformComponents; }
	inline static std::map<unsigned int, Model>* GetModelComponents() { return &modelComponents; }
	inline static std::map<unsigned int, Rigidbody>* GetRigidbodyComponents() { return &rigidbodyComponents; }
	inline static std::map<unsigned int, BoxCollider>* GetBoxColliderComponents() { return &boxColliderComponents; }
};