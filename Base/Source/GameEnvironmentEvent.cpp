#include "GameEnvironmentEvent.h"

GameEnvironmentEvent* GameEnvironmentEvent::c_GameEnvironmentEvent = new GameEnvironmentEvent();

void GameEnvironmentEvent::Init()
{

}
void GameEnvironmentEvent::Update(double dt, Map map)
{

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