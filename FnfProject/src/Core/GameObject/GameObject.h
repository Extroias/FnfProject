#ifndef GameObject_H
#define GameObject_H

#include <SDL.h>
#include <string>
#include <vector>
#include <memory>
#include <concepts>

#include "Util/Shapes.h"
#include "Util/GamePointers.h"
#include "Transform.h"
#include "Component.h"

class Renderer;
class GameObject
{
private:
	std::string name;

	std::vector<MainPtr<Component>> components;
	Renderer* renderer;

public:

	Transform transform;

	GameObject(const std::string name, const Vector2 position);

	void Update();
	void SetRenderer(Renderer* renderer);

	template<class Return>
	WeakPtr<Return> GetComponent()
	{
		for (int i = 0; i < components.size(); i++)
		{
			Return* ptr = dynamic_cast<Return*>(components[i].get());
			if (ptr) return WeakPtr<Return>(components[i]);
		}
		return WeakPtr<Return>();
	}
	
	void AddComponent(Component* component);
	void RemoveComponent(WeakPtr<Component>& component);
};

#endif //GameObject_H	