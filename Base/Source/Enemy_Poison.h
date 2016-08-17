#ifndef ENEMY_POISON
#define ENEMY_POISON
#include "Input_PI.h"
#include "Map_PI.h"

class Enemy_Poison
{
public:
	static Enemy_Poison* pointer(){ return m_pointer; };
	void Init();
	void Update(float dt, Map* map);
	void render();
	void Exit();
	Vector3 Poison(Vector3 Movement);
private:
	static Enemy_Poison* m_pointer;
	Enemy_Poison(){};
	~Enemy_Poison(){};
	Vector3 Pos;
	Vector3 Vel;
	bool Poisonous;
	bool Toxicfied;
	float CoolDown;
	float LastTime;
	float ChangeEffect;
	bool FlipType[2];

};

#endif