#pragma once
#include "Component/Script.h"

#include <unordered_map>
#include <iostream>

class ScriptHandlerTest
{
private:
	template<typename T> T* AddScript(unsigned int objectId, GameObject* _gameobject)
	{
		std::cout << typeid(T).name() << " is not a script" << std::endl;
	}
	template<typename T> void RemoveScript(unsigned int objectId)
	{
		std::cout << typeid(T).name() << " is not a script" << std::endl;
	}
	template<typename T> T* GetScript(unsigned int objectId)
	{
		std::cout << typeid(T).name() << " is not a script" << std::endl;
		return nullptr;
	}
	template<typename T> T* GetScriptUnSafe(unsigned int objectId)
	{
		std::cout << typeid(T).name() << " is not a script" << std::endl;
		return nullptr;
	}

	friend class Scene;

protected:
	/*Injected maps*/

	/*Injected template functions*/

};