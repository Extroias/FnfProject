#ifndef Component_H
#define Component_H

#include <typeinfo>
#include <SDL.h>

#include "GamePointers.h"

class GameObject;
class Component
{
protected:
	GameObject* gameObject = nullptr;
	WeakPtr<Component> thisptr;

public:

	Component() {};
	virtual ~Component() = default;

	GameObject* GetGameObject() { return gameObject; }

	virtual void Update() {};
	virtual void Render(SDL_Renderer* renderer){}

	friend GameObject;
};
#endif //Component_H	
