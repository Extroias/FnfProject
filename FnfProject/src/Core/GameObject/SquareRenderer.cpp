#include "SquareRenderer.h"
void SquareRenderer::SetTransform(Transform& transform)
{
	this->SetPosition(transform.GetPosition());
}
void SquareRenderer::Render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(renderer, &rect.ToSDLRect());
}