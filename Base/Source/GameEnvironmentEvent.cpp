#include "GameEnvironmentEvent.h"

GameEnvironmentEvent* GameEnvironmentEvent::c_GameEnvironmentEvent = new GameEnvironmentEvent();

void GameEnvironmentEvent::Init()
{

}
float GameEnvironmentEvent::ChangeLightRange(float lightrange)
{
	if (lightTrigger > 5.f)
	{
		lightrange = 1.f;
	}
	if (debuffTimer > 5.f)
	{
		lightrange = 3.f;
	}
	return lightrange;
}
void GameEnvironmentEvent::Update(double dt)
{
	lightTrigger += dt;
	if (lightTrigger > 5.f)
	{
		debuffTimer += dt;
	}
}
void GameEnvironmentEvent::Render()
{

}
void GameEnvironmentEvent::Exit()
{
	if (c_GameEnvironmentEvent != nullptr)
	{
		delete c_GameEnvironmentEvent;
		c_GameEnvironmentEvent = nullptr;
	}
}