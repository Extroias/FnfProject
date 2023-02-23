#include "UpdateThread.h"
#include "../Application.h"
#include "Util/Time.h"

void UpdateThread::ThreadTask()
{
	using frames = std::chrono::duration<int64_t, std::ratio<1, 120>>;
	auto nextFrame = std::chrono::steady_clock::now() + frames{ 0 };
	tracy::SetThreadName("Update");

	while (!Quit)
	{
		FrameMarkNamed("UpdateFrame");

		auto start = std::chrono::steady_clock::now();
		{
			ZoneScoped;
			Application::App->GetInputManager()->ReleaseInputs();
			auto& gameObjects = Application::App->GetGameObjects();
			for (auto& gameObject : gameObjects)
			{
				gameObject->Update();
			}
		}

		std::this_thread::sleep_until(nextFrame);
		nextFrame = std::chrono::steady_clock::now() + frames(1);

		std::chrono::duration<double> duration = std::chrono::steady_clock::now() - start;
		delta = duration;
		now = start.time_since_epoch();
	}
}
void UpdateThread::SetTimings()
{
	std::unique_lock lock(Time::timeMutex);
	Time::_deltad = delta;
	Time::_delta = (float)delta.count();
	Time::_now = now;
}
