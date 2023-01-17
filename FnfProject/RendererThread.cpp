#include "RendererThread.h"
#include "Application.h"
#include "Time.h"

RendererThread::RendererThread(SDL_Window* window)
{
	this->window = window;
	context = SDL_GL_GetCurrentContext();

	GameObject* object = new GameObject("Test", { 120,120 });
	object->AddComponent(new TestComponent());

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

	SDL_GL_MakeCurrent(window, context);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	tracy::SetThreadName("Rendering");

	while (!Quit)
	{
		auto start = std::chrono::steady_clock::now();
		{
			ZoneScoped;
			FrameMarkNamed("RendererThread");
			Application::App->GetInputManager()->ReleaseInputs();
			auto& gameObjects = Application::App->GetGameObjects();
			for (auto& gameObject : gameObjects)
			{
				gameObject->Update(renderer);
			}
			SDL_RenderPresent(renderer);
		}
		std::this_thread::sleep_until(nextFrame);
		nextFrame = std::chrono::steady_clock::now() + frames(1) ;
		std::chrono::duration<double> duration = std::chrono::steady_clock::now() - start;
		delta = duration;
		now = start.time_since_epoch();
		SetTimings();
	}
}
void RendererThread::SetTimings()
{
	std::unique_lock lock(Time::timeMutex);
	Time::_deltad = delta;
	Time::_delta = (float)delta.count();
	Time::_now = now;
}
