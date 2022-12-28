#include "TestObject.h"
#include "Application.h"
TestObject::TestObject() : x(0), y(0), counter(0.0f), radius(180.0f), offsetX(240), offsetY(180)
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
TestObject::~TestObject()
{

}
void TestObject::Render(SDL_Renderer* renderer, double delta)
{
	ZoneScoped;
	x += delta * 30.0 * (double)axisX;
	y += delta * 30.0 * (double)axisY;
	square.x = (int)x;
	square.y = (int)y;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
	SDL_RenderDrawRect(renderer, &this->square);
}