#pragma once
#include "Math/Vector3.h"

class Transform
{
private:
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

public:

	Transform();
	
	void SetPosition(float x, float y, float z);
	void SetPosition(Vector3 position);
	void SetRotation(float x, float y, float z);
	void SetRotation(Vector3 rotation);
	void SetScale(float x, float y, float z);
	void SetScale(Vector3 scale);

	inline Vector3 Position() { return position; }
	inline Vector3 Rotation() { return rotation; }
	inline Vector3 Scale() { return scale; }

	Vector3 Forward();
	Vector3 Right();
	Vector3 Up();

private:
	friend class Renderer;
	friend class Engine;
	friend class Physics;
};