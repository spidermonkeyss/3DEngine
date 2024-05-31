#pragma once
#include "Component/Script.h"

#include <unordered_map>
#include <iostream>

#include "../res/scripts/anotherScript.h"
#include "../res/scripts/MovementController.h"
class ScriptHandler
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
   friend class GameObject;

   std::unordered_map<unsigned int, anotherScript> anotherScript_map;
   template<> anotherScript* AddScript<anotherScript>(unsigned int objectId, GameObject* _gameobject)
   {
       anotherScript* comp = &anotherScript_map[objectId];
       comp->componentGameObjectId = objectId;
       comp->gameobject = _gameobject;
       return comp;
   }
   template<> void RemoveScript<anotherScript>(unsigned int objectId)
   {
       anotherScript_map.erase(objectId);
   }
   template<> anotherScript* GetScript<anotherScript>(unsigned int objectId)
   {
       if (anotherScript_map.count(objectId) == 1)
           return &anotherScript_map[objectId];
       return nullptr;
   }
   template<> anotherScript* GetScriptUnSafe<anotherScript>(unsigned int objectId)
   {
       return &anotherScript_map[objectId];
   }
   std::unordered_map<unsigned int, MovementController> MovementController_map;
   template<> MovementController* AddScript<MovementController>(unsigned int objectId, GameObject* _gameobject)
   {
       MovementController* comp = &MovementController_map[objectId];
       comp->componentGameObjectId = objectId;
       comp->gameobject = _gameobject;
       return comp;
   }
   template<> void RemoveScript<MovementController>(unsigned int objectId)
   {
       MovementController_map.erase(objectId);
   }
   template<> MovementController* GetScript<MovementController>(unsigned int objectId)
   {
       if (MovementController_map.count(objectId) == 1)
           return &MovementController_map[objectId];
       return nullptr;
   }
   template<> MovementController* GetScriptUnSafe<MovementController>(unsigned int objectId)
   {
       return &MovementController_map[objectId];
   }
   void CallScriptUpdates()
   {
       std::unordered_map<unsigned int, anotherScript>::iterator anotherScript_ittr;
       for (anotherScript_ittr = anotherScript_map.begin(); anotherScript_ittr != anotherScript_map.end(); ++anotherScript_ittr)
       {
           anotherScript_ittr->second.Update();
       }
       std::unordered_map<unsigned int, MovementController>::iterator MovementController_ittr;
       for (MovementController_ittr = MovementController_map.begin(); MovementController_ittr != MovementController_map.end(); ++MovementController_ittr)
       {
           MovementController_ittr->second.Update();
       }
   }
};