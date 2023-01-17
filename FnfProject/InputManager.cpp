#include "InputManager.h"
InputManager::InputManager()
{
	states = SDL_GetKeyboardState(&length);
}
void InputManager::TakeSnapshot()
{
	ZoneScoped;
	milliseconds time = std::chrono::steady_clock::now().time_since_epoch();
	std::vector<Uint8> snapshot;
	for (int i = 0; i < length; i++)
		snapshot.push_back(states[i]);

	for (auto& event : events)
	{
		Uint8 pressed = snapshot[event->GetCode()];
		event->ProcessInput(pressed, time);
	}

	prevSnapshot = snapshot;
}
void InputManager::ReleaseInputs()
{
	ZoneScoped;
	for (auto& event : events)
	{
		event->OnPressed.ReleaseCache();
		event->OnRelease.ReleaseCache();
		if (event->IsPressed()) event->OnStay.Invoke();
	}
}
void InputManager::AddDelegate(const Delegate<milliseconds>& del, InputState state, SDL_KeyCode code)
{  
	ZoneScoped;
	std::unique_ptr<InputEvent>* event;
	SDL_Scancode scode = SDL_GetScancodeFromKey(code);

	auto it = std::find_if(events.begin(), events.end(), 
		[&](std::unique_ptr<InputEvent>& even)
		{
			return even->GetCode() == scode;
		});
	if (it == events.end()) event = &events.emplace_back(std::make_unique<InputEvent>(scode));
	else event = &*it;

	if (state == InputState::OnPressed)
	{
		event->get()->OnPressed.AddDynamicListener(del);
	}
	if (state == InputState::OnRelease)
	{
		event->get()->OnRelease.AddDynamicListener(del);
	}
}
void InputManager::RemoveDelegate(const Delegate<milliseconds>& del, InputState state, SDL_KeyCode code)
{
	ZoneScoped;
	std::unique_ptr<InputEvent>* event;
	SDL_Scancode scode = SDL_GetScancodeFromKey(code);

	auto it = std::find_if(events.begin(), events.end(), [scode](std::unique_ptr<InputEvent>& even) {return even->GetCode() == scode;});
	if (it == events.end()) event = &events.emplace_back(std::make_unique<InputEvent>(scode));
	else event = &*it;

	if (state == InputState::OnPressed)
	{
		event->get()->OnPressed.RemoveDynamicListener(del);
	}
	if (state == InputState::OnRelease)
	{
		event->get()->OnRelease.RemoveDynamicListener(del);
	}
}
