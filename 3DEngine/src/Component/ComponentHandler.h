#pragma once

#include "Transform.h"
#include "Model.h"

#include <map>
#include <iostream>

class ComponentHandler
{
public:
	inline static std::map<unsigned int, Transform> tranformComponents;
	inline static std::map<unsigned int, Model> modelComponents;


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



	template<typename T> static void RemoveComponent(unsigned int objectId) 
	{
		std::cout << typeid(T).name() << " is not a component" << std::endl;
	}
	template<> static void RemoveComponent<Transform>(unsigned int objectId)
	{

	}



	template<typename T> static T* GetComponent(unsigned int objectId) 
	{ 
		std::cout << typeid(T).name() << " is not a component" << std::endl;
		return nullptr;
	}
	template<> static Transform* GetComponent<Transform>(unsigned int objectId)
	{
		if (ComponentHandler::tranformComponents.count(objectId) == 1)
			return &ComponentHandler::tranformComponents[objectId];
		return nullptr;
	}
	template<> static Model* GetComponent<Model>(unsigned int objectId)
	{
		if (ComponentHandler::modelComponents.count(objectId) == 1)
			return &ComponentHandler::modelComponents[objectId];
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
	
};