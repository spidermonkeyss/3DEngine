#include "GameObject.h"
#include "Model.h"
#include <iostream>

GameObject::GameObject()
	:transform(), model(nullptr)
{
	std::cout << "GameObject created.\n";
}

GameObject::~GameObject()
{
	RemoveModel();
	std::cout << "GameObject deleted.\n";
}

void GameObject::AddModel()
{
	model = new Model(this);
}

void GameObject::RemoveModel()
{
	if (model != nullptr)
		delete model;
}