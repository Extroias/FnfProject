#include "GameObject/TestComponent.h"
#include "Application.h"
#include "Util/Time.h"
#include "SquareRenderer.h"

TestComponent::TestComponent()
{
	axisX = 0;
	axisY = 0;
	SquareRenderer* renderer = new SquareRenderer(gameObject, { 60,60 });
	gameObject->SetRenderer(renderer);
	renderer->SetColor(Color().White());
	Application::App->GetInputManager()->AddDelegate(MakeDelegate<1>(std::function([this](milliseconds m) {	axisX = -1;})),InputState::OnPressed,SDLK_a);
	Application::App->GetInputManager()->AddDelegate(MakeDelegate<1>(std::function([this](milliseconds m) {	axisX = 1;	})), InputState::OnPressed, SDLK_d);
	Application::App->GetInputManager()->AddDelegate(MakeDelegate<1>(std::function([this](milliseconds m) {	axisY = -1;})), InputState::OnPressed, SDLK_w);
	Application::App->GetInputManager()->AddDelegate(MakeDelegate<1>(std::function([this](milliseconds m) {	axisY = 1;})), InputState::OnPressed, SDLK_s);
}
void TestComponent::Render(SDL_Renderer* renderer)
{
	ZoneScoped;
	time += Time::delta();
	gameObject->transform.SetPosition(gameObject->transform.GetPosition() + Vector2(Time::delta() * 30.0f * axisX, Time::delta() * 30.0f * axisY));
    
	gameObject->GetComponent<Testerface>()->Test();
	if (time > 7) gameObject->RemoveComponent(thisptr);
}