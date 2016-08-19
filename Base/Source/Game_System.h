#ifndef PARTICLE_SCENE
#define PARTICLE_SCENE
#include "Main_Shaft.h"
#include "Map_PI.h"

class Game_System :public Scene
{
	
	
public:
	
	static Game_System* pointer(){ return c_pointer; };
	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	
	
private:
	
	Game_System();
	~Game_System();
	static Game_System* c_pointer;
	int Pokemon_Switch;
	/*bool Pokemon_On_Loose[4];
	void Update_Stuffs(double dt, Map* map);*/
	//int rest;
	
};


#endif