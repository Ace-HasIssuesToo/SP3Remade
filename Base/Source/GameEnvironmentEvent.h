#pragma once
#include "Support_Codes.h"
#include "Render_PI.h"
#include "Map_PI.h"

class GameEnvironmentEvent
{
public:
	static GameEnvironmentEvent* pointer(){ return c_GameEnvironmentEvent; };

	void Init();
	//void Update(double dt, Map* map);
	void Update(double dt);
	void Render();
	void Exit();
	float ChangeLightRange(float lightrange);
private:
	GameEnvironmentEvent()
		: lightTrigger(0)
		, debuffTimer(0)
	{};
	~GameEnvironmentEvent(){};
	float lightTrigger;
	float debuffTimer;

	static GameEnvironmentEvent* c_GameEnvironmentEvent;
};