#include "RendererThread.h"
RendererThread::RendererThread(SDL_Window* window)
{
	this->window = window;
	context = SDL_GL_GetCurrentContext();
	object = new TestObject();

	SDL_GL_MakeCurrent(window, nullptr);
	this->thread = std::thread(&RendererThread::ThreadTask, this);
}
RendererThread::~RendererThread()
{
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
}
void RendererThread::ThreadTask()
{
	using frames = std::chrono::duration<int64_t, std::ratio<1, 120>>;
	auto nextFrame = std::chrono::steady_clock::now() + frames{ 0 };

	double delta = 0;

	SDL_GL_MakeCurrent(window, context);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	while (!Quit)
	{
		auto start = std::chrono::steady_clock::now();

		object->Render(renderer, delta);
		SDL_RenderPresent(renderer);

		std::this_thread::sleep_until(nextFrame);
		nextFrame += frames{ 1 };
		std::chrono::duration<double> duration = std::chrono::steady_clock::now() - start;
		delta = duration.count();
	}
}