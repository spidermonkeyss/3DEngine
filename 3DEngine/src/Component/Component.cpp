#include "Component.h"
#include "GameObject.h"

GameObject* Component::GameObject()
{
	return GameObject::GetGameObjectByObjectId(this->componentGameObjectId);
}
