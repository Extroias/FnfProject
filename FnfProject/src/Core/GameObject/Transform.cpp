#include "Transform.h"
Vector2 Transform::GetPosition()
{
	return position;
}
Vector2 Transform::GetScale()
{
	return scale;
}
float Transform::GetRotation()
{
	return rotation;
}
void Transform::SetPosition(Vector2 position)
{
	this->position = position;
}
void Transform::SetScale(Vector2 scale)
{
	this->scale = scale;
}
void Transform::SetRotation(float rotation)
{
	this->rotation = rotation;
}