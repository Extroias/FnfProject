#include "InputManager.h"
InputManager::InputManager()
{
	states = SDL_GetKeyboardState(&length); 
}
void InputManager::TakeSnapshot()
{
	SDL_PumpEvents();
	std::vector<bool> snapshot;
	for (int i = 0; i < length; i++)
		snapshot.push_back(states[i]);
	snapshots.push_back(snapshot);
}