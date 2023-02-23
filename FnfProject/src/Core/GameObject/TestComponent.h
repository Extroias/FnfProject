#ifndef TestObject_H
#define TestObject_H

#include <SDL.h>
#include <cmath>
#include <tracy/Tracy.hpp>
#include "GameLoop/InputThread.h"
#include "Component.h"

class Testerface
{
public:
	virtual void Test() = 0;
};

class TestComponent : public Component, public Testerface
{
public:
	TestComponent();
	virtual ~TestComponent() = default;

	void Render(SDL_Renderer* renderer) override;
	void Test() {
	}
private:

	float time = 0;
	int axisX;
	int axisY;

};


#endif //TestObject_H	

