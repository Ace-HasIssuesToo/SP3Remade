#ifndef PARTICLE_SCENE
#define PARTICLE_SCENE
#include "Main_Shaft.h"

class Debug_PI :public Scene
{
public:
	static Debug_PI* pointer(){ return c_pointer; };
	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
private:
	Debug_PI();
	~Debug_PI();
	static Debug_PI* c_pointer;
};


#endif