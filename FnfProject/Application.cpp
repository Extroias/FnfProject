#include "Application.h"

Application* Application::App = nullptr;
Application::Application()
{
	App = this;
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	manager = new InputManager();
	thread = new RendererThread(window);
}
Application::~Application()
{
	delete thread;
	delete manager;
}
int Application::Run()
{
	SDL_EventState(SDL_KEYDOWN, SDL_IGNORE);
	SDL_EventState(SDL_KEYUP, SDL_IGNORE);
	SDL_Event e; 
	bool quit = false; 
	using frames = std::chrono::duration<int64_t, std::ratio<1, 1000>>;
	auto nextFrame = std::chrono::steady_clock::now() + frames{ 0 };
	while (quit == false) 
	{ 
		{
			ZoneScoped;
			FrameMark;
			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT) quit = true;
			}
			manager->TakeSnapshot();
		}
		std::this_thread::sleep_until(nextFrame);
		nextFrame = std::chrono::steady_clock::now() + frames{ 1 };
	}

	thread->Stop();
	SDL_Quit();

	return 0;
}