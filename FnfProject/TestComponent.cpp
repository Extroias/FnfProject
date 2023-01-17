#include "TestComponent.h"
#include "Application.h"
#include "Time.h"

TestComponent::TestComponent()
{
	this->square = { 60, 60, 60, 60 };
	axisX = 0;
	axisY = 0;
	Application::App->GetInputManager()->AddDelegate(MakeDelegate<1>(std::function([this](milliseconds m) {	
		auto str = (std::to_string(m.count()) + "ms");
	    TracyMessage(str.c_str(), str.length());
		axisX = -1;
		})),InputState::OnPressed,SDLK_a);
	Application::App->GetInputManager()->AddDelegate(MakeDelegate<1>(std::function([this](milliseconds m) {
		auto str = (std::to_string(m.count()) + "ms");
	    TracyMessage(str.c_str(), str.length());
		axisX = 1;
		})), InputState::OnPressed, SDLK_d);
	Application::App->GetInputManager()->AddDelegate(MakeDelegate<1>(std::function([this](milliseconds m) {	axisY = -1;})), InputState::OnPressed, SDLK_w);
	Application::App->GetInputManager()->AddDelegate(MakeDelegate<1>(std::function([this](milliseconds m) {	axisY = 1;})), InputState::OnPressed, SDLK_s);
}
void TestComponent::Render(SDL_Renderer* renderer)
{
	ZoneScoped;
	time += Time::delta();
	gameObject->transform.SetPosition(gameObject->transform.GetPosition() + Vector2(Time::delta() * 30.0f * axisX, Time::delta() * 30.0f * axisY));
	
	square.x = (int)gameObject->transform.GetPosition().x;
	square.y = (int)gameObject->transform.GetPosition().y;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
	SDL_RenderDrawRect(renderer, &this->square);
    
	gameObject->GetComponent<Testerface>()->Test();
	if (time > 7) gameObject->RemoveComponent(thisptr);
}