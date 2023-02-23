#ifndef Renderer_H
#define Renderer_H

#include "GameObject.h"

class Renderer
{
public:
	Renderer(GameObject* ptr) : object(ptr){}

	virtual void Render(SDL_Renderer* renderer) = 0;
	virtual void SetTransform(Transform& transform) = 0;

	void SetBounds(Rect rect);
	Rect GetBounds();

	void SetSize(Vector2 size);
	Vector2 GetSize();

	void SetPosition(Vector2 position);
	Vector2 GetPosition();

	void SetColor(Color color);
	Color GetColor();
protected:
	GameObject* object;
	Rect rect;
	Color color;
};

#endif //Renderer_H	


