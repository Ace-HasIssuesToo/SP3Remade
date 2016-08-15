#ifndef SOUND_SCENE
#define SOUND_SCENE
#include "Game_Core.h"

class Sound_Scene :public Scene
{
public:
	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
};

#endif