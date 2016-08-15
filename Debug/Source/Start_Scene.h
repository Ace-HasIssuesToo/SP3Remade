#ifndef START_SCENE
#define START_SCENE
#include "Game_Core.h"

class Start_Scene :public Scene
{
public:
	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
private:
};

#endif