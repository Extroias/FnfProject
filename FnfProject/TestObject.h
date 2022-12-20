#ifndef TestObject_H
#define TestObject_H

#include <SDL.h>
#include <cmath>

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
	int x;
	int y;
	SDL_Rect square;


};


#endif //TestObject_H	

