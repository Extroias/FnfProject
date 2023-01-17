#include "Transform.h"
Vector2 Transform::GetPosition()
{
	std::lock_guard lock(posMutex);
	return position;
}
Vector2 Transform::GetScale()
{
	std::lock_guard lock(scaleMutex);
	return scale;
}
float Transform::GetRotation()
{
	std::lock_guard lock(rotationMutex);
	return rotation;
}
void Transform::SetPosition(Vector2 position)
{
	std::lock_guard lock(posMutex);
	this->position = position;
}
void Transform::SetScale(Vector2 scale)
{
	std::lock_guard lock(scaleMutex);
	this->scale = scale;
}
void Transform::SetRotation(float rotation)
{
	std::lock_guard lock(rotationMutex);
	this->rotation = rotation;
}