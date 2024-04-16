#pragma once
#include "Model.h"
#include "Transform.h"

class Model;

class GameObject
{
private:
	Model* model;
	Transform transform;
public:

	GameObject();
	~GameObject();

	void AddModel();
	void RemoveModel();

	inline Model* GetModel() { return model; }
	inline Transform* Transform() { return &transform; }
};