#include "Transform.h"

Transform::Transform()
	:position()
{
	position.x = 0;
	position.y = 0;
	position.z = 0;
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
