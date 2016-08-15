#ifndef ENEMY_SCENE
#define ENEMY_SCENE
#include "Game_Core.h"

class Enemy_Scene :public Scene
{
public:
	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
};


#endif