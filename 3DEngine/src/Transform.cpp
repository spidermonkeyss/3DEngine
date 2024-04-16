#include "Transform.h"

Transform::Transform()
	:position()
{
}

void Transform::SetPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void Transform::SetPosition(Vector3 _position)
{
	position.x = _position.x;
	position.y = _position.y;
	position.z = _position.z;
}
