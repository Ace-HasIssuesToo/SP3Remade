#ifndef LIGHT_SCENE
#define LIGHT_SCENE
#include "Game_Core.h"

class Light_Scene :public Scene
{
public:
	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

};

#endif