#ifndef RendererThread_H
#define RendererThread_H

#include <SDL.h>
#include <tracy/Tracy.hpp>
#include <common/TracySystem.hpp>
#include <thread>
#include "GameObject.h"
#include "InputManager.h"
#include "TestComponent.h"

class RendererThread
{
public:
	RendererThread(SDL_Window* window);
	~RendererThread();
	

	void Stop() {
		this->Quit = true;
		this->thread.join();
	}
	void SetTimings();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_GLContext context;
	std::thread thread;
	bool Quit;

	std::chrono::duration<double> delta;
	milliseconds now;

	void ThreadTask();
};

#endif //RendererThread_H	

