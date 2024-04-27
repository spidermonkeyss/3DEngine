#include "GameObject.h"
#include "Component/Model.h"
#include <iostream>

unsigned int GameObject::nextObjectId = 0;

GameObject::GameObject()
{
	std::cout << "GameObject created.\n";
	objectId = nextObjectId;
	nextObjectId++;
}

GameObject::~GameObject()
{
	std::cout << "GameObject deleted.\n";
}