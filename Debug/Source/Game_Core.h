#ifndef GAME_CORE
#define GAME_CORE

#include "Scene.h"
#include "Game_Model.h"
#include "Render_functions.h"
#include "Room_Scene.h"
#include "Light_Scene.h"

class Game_Core :public Scene
{
public:
	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	static Game_Core* pointer(){ return c_pointer; };
private:
	Game_Core(){};
	~Game_Core(){};
	static Game_Core* c_pointer;
};


#endif