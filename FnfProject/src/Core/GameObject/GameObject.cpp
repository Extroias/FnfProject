#include "GameObject/GameObject.h"
#include "Application.h"
#include "Component.h"
GameObject::GameObject(const std::string name, const Vector2 position) : name(name)
{
	Application::App->AddGameObject(this);
	transform.SetPosition(position);
}

void GameObject::AddComponent(Component* component)
{
	auto& comp = components.emplace_back(component);
	component->thisptr = comp;
	component->gameObject = this;
}

void GameObject::RemoveComponent(WeakPtr<Component>& component)
{
	std::erase(components, component);
}
void GameObject::Update()
{
	for (auto& component : components)
	{
		component->Update();
	}
}