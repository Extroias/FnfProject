#ifndef RendererThread_H
#define RendererThread_H

#include <SDL.h>
#include <thread>
#include "TestObject.h"

class RendererThread
{
public:
	RendererThread(SDL_Window* window);
	~RendererThread();
	void Stop() {
		this->Quit = true;
		this->thread.join();
	}

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_GLContext context;
	std::thread thread;
	bool Quit;

	TestObject* object;

	void ThreadTask();

};

#endif //RendererThread_H	

