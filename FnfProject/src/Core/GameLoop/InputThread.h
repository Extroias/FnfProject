#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL.h>
#include <vector>
#include <chrono>
#include <memory>
#include <tracy/Tracy.hpp>

#include "Util/Event.h"

using milliseconds = std::chrono::duration<double, std::milli>;

enum class InputState
{
	OnPressed,
	OnRelease,
	OnStay,
};

struct InputEvent
{
	InputEvent(SDL_Scancode code) :code(code){
		OnStay.AddListener(MakeDelegate(std::function([&]() {})));
	}

	CachedEvent<milliseconds> OnPressed;
	CachedEvent<milliseconds> OnRelease;
	Event<> OnStay;
	void TestFunc(){}
	void ProcessInput(Uint8  input, milliseconds time)
	{
		if (currentlyPressed && !input)
		{
			OnRelease.Invoke(time);
			currentlyPressed = false;
		}
		else if (!currentlyPressed && input)
		{
			OnPressed.Invoke(time);
			currentlyPressed = true;
		}
	}
	bool IsPressed() { return currentlyPressed; }
	SDL_Scancode GetCode() { return code; }
private:
	SDL_Scancode code;
	bool currentlyPressed = false;
};
class InputManager
{
public:
	InputManager();
	void TakeSnapshot();
	void ReleaseInputs();

	void AddDelegate(const Delegate<milliseconds>& del, InputState state, SDL_KeyCode code);
	void RemoveDelegate(const Delegate<milliseconds>& del, InputState state, SDL_KeyCode code);
private:

	const Uint8* states;
	int length;
	std::vector<Uint8> prevSnapshot;
	std::vector<std::unique_ptr<InputEvent>> events;

};

#endif //INPUTMANAGER_H	
