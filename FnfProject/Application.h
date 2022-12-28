#ifndef Application_H
#define Application_H

#include <iostream>
#include <thread>
#include <SDL.h>
#include <tracy/Tracy.hpp>
#include "RendererThread.h"
#include "InputManager.h"

class Application
{
private:

	const int windowHeight = 480;
	const int windowWidth = 640;
	SDL_Window*  window;
	RendererThread* thread;
	InputManager* manager;

public:
    static Application* App;
	Application();
	~Application();
	int Run();
	InputManager* GetInputManager() { return manager; }
};
#endif //Application_H	

