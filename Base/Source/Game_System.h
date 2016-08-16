#ifndef PARTICLE_SCENE
#define PARTICLE_SCENE
#include "Main_Shaft.h"
#include "Map_PI.h"
#include "Player.h"
<<<<<<< HEAD
#include "EnemyGhost.h"
#include "Enemy_Psychic.h"
=======
#include "Enemy_Ghost.h"
#include "EnemyDark.h"
>>>>>>> d9580da46056991b3e2d99efafe75d1ea16d6798

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