#ifndef PARTICLE_SCENE
#define PARTICLE_SCENE
#include "Main_Shaft.h"
#include "Map_PI.h"
#include "Player.h"
#include "Enemy_Ghost.h"
#include "Enemy_Psychic.h"
#include "Enemy_Ghost.h"
#include "EnemyDark.h"

class Game_System :public Scene
{
	enum Game
	{
		START,
		GUIDE,
		FLOOR1,
		FLOOR2,
		FLOOR3,
		FLOOR4,
		FLOOR5,
		LOSE,
		WIN,
	};
public:
	static Game_System* pointer(){ return c_pointer; };
	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	void GameState(double dt);
	void LoadFloor1();
	void LoadFloor2();
	void LoadFloor3();
	void LoadFloor4();
	void LoadFloor5();
	Game state;
private:
	Map Floor1;
	Map Floor2;
	Map Floor3;
	Map Floor4;
	Map Floor5;
	Game_System();
	~Game_System();
	static Game_System* c_pointer;
	int Pokemon_Switch;
	int rest;
};


#endif