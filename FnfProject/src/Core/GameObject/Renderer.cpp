#include "Renderer.h"
void Renderer::SetBounds(Rect rect)
{
	this->rect = rect;
}
Rect Renderer::GetBounds()
{
	return rect;
}
void Renderer::SetSize(Vector2 size)
{
	rect.size = size;
}
Vector2 Renderer::GetSize()
{
	return rect.size;
}
void Renderer::SetPosition(Vector2 position)
{
	rect.position = position;
}
Vector2 Renderer::GetPosition()
{
	return rect.position;
}
void Renderer::SetColor(Color color)
{
	this->color = color;
}
Color Renderer::GetColor()
{
	return color;
}