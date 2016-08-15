#ifndef GUN_SCENE
#define GUN_SCENE
#include "Game_Core.h"

class Gun_Scene :public Scene
{
public:
	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
private:
};

#endif