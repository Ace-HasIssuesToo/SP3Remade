#pragma once
#include "Support_Codes.h"
#include "Render_PI.h"
#include "Map_PI.h"

class GameEnvironmentEvent
{
public:
	static GameEnvironmentEvent* pointer(){ return c_GameEnvironmentEvent; };

	void Init();
	void Update(double dt, Map map);
	void Render();
	void Exit();
private:
	GameEnvironmentEvent(){};
	~GameEnvironmentEvent(){};

	static GameEnvironmentEvent* c_GameEnvironmentEvent;
};