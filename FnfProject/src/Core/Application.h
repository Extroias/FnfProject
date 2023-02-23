#ifndef Application_H
#define Application_H

#include <iostream>
#include <thread>
#include <SDL.h>
#include <tracy/Tracy.hpp>

#include "GameLoop/RendererThread.h"
#include "GameLoop/InputThread.h"
#include "GameObject/GameObject.h"
#include "GameObject/TestComponent.h"

class Application
{
private:

	const int windowHeight = 480;
	const int windowWidth = 640;
	SDL_Window*  window;
	RendererThread* thread;
	InputManager* manager;

	std::vector<MainPtr<GameObject>> gameObjects;

	void AddGameObject(GameObject* object);
	friend GameObject::GameObject(std::string name, Vector2 position);

public:
    static Application* App;
	Application();
	~Application();
	int Run();

	std::vector<MainPtr<GameObject>>& GetGameObjects() { return gameObjects; }
	InputManager* GetInputManager() { return manager; }
	RendererThread* GetRendererThread() { return thread; }
};
#endif //Application_H	

