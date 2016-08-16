#ifndef PARTICLE_SCENE
#define PARTICLE_SCENE
#include "Main_Shaft.h"
#include "Map_PI.h"
#include "Player.h"
<<<<<<< HEAD
#include "Enemy_Ghost.h"
=======
#include "EnemyGhost.h"
#include "EnemyDark.h"
>>>>>>> Added Dark Type Enemy Class

class Game_System :public Scene
{
public:
	static Game_System* pointer(){ return c_pointer; };
	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
private:
	Map Floor1;
	Map Floor2;
	Game_System();
	~Game_System();
	static Game_System* c_pointer;
	Vector3 Pos;
};


#endif