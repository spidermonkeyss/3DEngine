#pragma once
#include "Component.h"

class Script : public Component
{
private:
	virtual void Update();
public:
	Script();
	
private:
	friend class Scene;
	friend class ComponentHandler;
	friend class ScriptHandler;
};
