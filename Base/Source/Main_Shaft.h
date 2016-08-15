#ifndef MAIN_SHAFT
#define MAIN_SHAFT

#include "Scene.h"
#include "Render_PI.h"

class Main_Shaft :public Scene
{
public:
	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	static Main_Shaft* pointer(){ return c_pointer; };
private:
	Main_Shaft(){};
	~Main_Shaft(){};
	static Main_Shaft* c_pointer;
};


#endif