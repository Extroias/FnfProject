#ifndef TestObject_H
#define TestObject_H

#include <SDL.h>
#include <cmath>
#include <tracy/Tracy.hpp>
#include "InputManager.h"

class TestObject
{
public:
	TestObject();
	~TestObject();

	void Render(SDL_Renderer* renderer, double delta);
	

private:

	float counter;
	float radius;
	int offsetX;
	int offsetY;
	double x;
	double y;
	int axisX;
	int axisY;
	SDL_Rect square;


};


#endif //TestObject_H	

