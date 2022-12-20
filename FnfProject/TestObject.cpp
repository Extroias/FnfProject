#include "TestObject.h"

TestObject::TestObject() : x(0), y(0), counter(0.0f), radius(180.0f), offsetX(240), offsetY(180)
{
	this->square = { 60, 60, 60, 60 };
	
}
TestObject::~TestObject()
{

}
void TestObject::Render(SDL_Renderer* renderer, double delta)
{
	this->x = (int)std::floorf(std::sinf(this->counter) * this->radius) + this->offsetX;
	this->y = (int)std::floorf(std::cosf(this->counter) * this->radius) + this->offsetY;

	this->square.x = this->x;
	this->square.y = this->y;

	this->counter += delta*3;
	if (this->counter > M_PI * 2)
		this->counter = 0.0f;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
	SDL_RenderDrawRect(renderer, &this->square);
}