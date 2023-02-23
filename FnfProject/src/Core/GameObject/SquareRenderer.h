#ifndef SquareRenderer_H
#define SquareRenderer_H

#include "Renderer.h"

class SquareRenderer : public Renderer
{
public:
	SquareRenderer(GameObject* object, Vector2 size) : Renderer(object) { rect.position = object->transform.GetPosition(); rect.size = size; }

	void Render(SDL_Renderer* renderer) override;
	void SetTransform(Transform& transform) override;
private:

};

#endif //SquareRenderer_H	


