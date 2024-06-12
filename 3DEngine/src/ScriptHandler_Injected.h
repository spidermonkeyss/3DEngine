#pragma once
#include "Component/Script.h"

#include <unordered_map>
#include <iostream>

#include "../res/scripts/anotherScript.h"
#include "../res/scripts/CameraController.h"
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
   std::unordered_map<unsigned int, CameraController> CameraController_map;
   template<> CameraController* AddScript<CameraController>(unsigned int objectId, GameObject* _gameobject)
   {
       CameraController* comp = &CameraController_map[objectId];
       comp->componentGameObjectId = objectId;
       comp->gameobject = _gameobject;
       return comp;
   }
   template<> void RemoveScript<CameraController>(unsigned int objectId)
   {
       CameraController_map.erase(objectId);
   }
   template<> CameraController* GetScript<CameraController>(unsigned int objectId)
   {
       if (CameraController_map.count(objectId) == 1)
           return &CameraController_map[objectId];
       return nullptr;
   }
   template<> CameraController* GetScriptUnSafe<CameraController>(unsigned int objectId)
   {
       return &CameraController_map[objectId];
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
           if (anotherScript_ittr->second.isEnabled)
               anotherScript_ittr->second.Update();
       }
       std::unordered_map<unsigned int, CameraController>::iterator CameraController_ittr;
       for (CameraController_ittr = CameraController_map.begin(); CameraController_ittr != CameraController_map.end(); ++CameraController_ittr)
       {
           if (CameraController_ittr->second.isEnabled)
               CameraController_ittr->second.Update();
       }
       std::unordered_map<unsigned int, MovementController>::iterator MovementController_ittr;
       for (MovementController_ittr = MovementController_map.begin(); MovementController_ittr != MovementController_map.end(); ++MovementController_ittr)
       {
           if (MovementController_ittr->second.isEnabled)
               MovementController_ittr->second.Update();
       }
   }
   void StartScripts()
   {
       std::unordered_map<unsigned int, anotherScript>::iterator anotherScript_ittr;
       for (anotherScript_ittr = anotherScript_map.begin(); anotherScript_ittr != anotherScript_map.end(); ++anotherScript_ittr)
       {
           if (anotherScript_ittr->second.isEnabled)
               anotherScript_ittr->second.OnStart();
       }
       std::unordered_map<unsigned int, CameraController>::iterator CameraController_ittr;
       for (CameraController_ittr = CameraController_map.begin(); CameraController_ittr != CameraController_map.end(); ++CameraController_ittr)
       {
           if (CameraController_ittr->second.isEnabled)
               CameraController_ittr->second.OnStart();
       }
       std::unordered_map<unsigned int, MovementController>::iterator MovementController_ittr;
       for (MovementController_ittr = MovementController_map.begin(); MovementController_ittr != MovementController_map.end(); ++MovementController_ittr)
       {
           if (MovementController_ittr->second.isEnabled)
               MovementController_ittr->second.OnStart();
       }
   }
};