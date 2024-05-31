#include "Transform.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Transform::Transform()
	: position(), rotation(), scale(1,1,1)
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

void Transform::SetRotation(float x, float y, float z)
{
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
}

void Transform::SetRotation(Vector3 _rotation)
{
	rotation.x = _rotation.x;
	rotation.y = _rotation.y;
	rotation.z = _rotation.z;
}

void Transform::SetScale(float x, float y, float z)
{
	scale.x = x;
	scale.y = y;
	scale.z = z;
}

void Transform::SetScale(Vector3 _scale)
{
	scale.x = _scale.x;
	scale.y = _scale.y;
	scale.z = _scale.z;
}

Vector3 Transform::Forward()
{
	/*
	//https://stackoverflow.com/questions/14607640/rotating-a-vector-in-3d-space
	//YXZ Rotation
	Vector3 yRotation;
	float theta = glm::radians(rotation.y);
	yRotation.x = 0 * cos(theta) + -1 * sin(theta);
	yRotation.y = 0;
	yRotation.z = -0 * sin(theta) + -1 * cos(theta);
	yRotation = yRotation.Normal();

	Vector3 yxRotation;
	theta = glm::radians(rotation.x);
	yxRotation.x = yRotation.x;
	yxRotation.y = yRotation.y * cos(theta) - yRotation.z * sin(theta);
	yxRotation.z = yRotation.y * sin(theta) + yRotation.z * cos(theta);
	yxRotation = yxRotation.Normal();

	Vector3 yxzRotation;
	theta = glm::radians(rotation.z);
	yxzRotation.x = yxRotation.x * cos(theta) - yxRotation.y * sin(theta);
	yxzRotation.y = yxRotation.x * sin(theta) + yxRotation.y * cos(theta);
	yxzRotation.z = yxRotation.z;
	yxzRotation = yxzRotation.Normal();

	Vector3 yRotation;
	float theta = glm::radians(rotation.y);
	yRotation.x = -sin(theta);
	yRotation.y = 0;
	yRotation.z = -cos(theta);
	yRotation = yRotation.Normal();

	Vector3 yxRotation;
	theta = glm::radians(rotation.x);
	yxRotation.x = yRotation.x;
	yxRotation.z = yRotation.z;
	float y = sin(theta);
	float x = cos(theta);
	float magnitudeRatio = 1.0f / x;
	yxRotation.y = y * magnitudeRatio;
	yxRotation = yxRotation.Normal();

	return yxRotation;
	*/

	//https://math.stackexchange.com/questions/1385137/calculate-3d-vector-out-of-two-angles-and-vector-length
	Vector3 forward;
	float xTheta = rotation.x;
	float yTheta = rotation.y;
	forward.x = -(cos(xTheta) * sin(yTheta));
	forward.y = cos(yTheta) * sin(xTheta);
	forward.z = -(cos(yTheta) * cos(xTheta));
	return forward.Normal();
}

Vector3 Transform::Right()
{
	return Vector3::Cross(Forward(), Up()).Normal();
}

Vector3 Transform::Up()
{
	return Vector3::Up();
}
