#ifndef Component_H
#define Component_H

#include <typeinfo>
#include <SDL.h>

#include "Util/GamePointers.h"

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

	friend GameObject;
};
#endif //Component_H	
