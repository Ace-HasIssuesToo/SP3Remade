#ifndef ENEMY_POISON
#define ENEMY_POISON
#include "Input_PI.h"
#include "Map_PI.h"

class Enemy_Poison
{
public:
	static Enemy_Poison* pointer(){ return m_pointer; };
	void Init();
	void Update(double dt, Map* map);
	void render();
	void Exit();
	Vector3 Poison(Vector3 Movement);
	Vector3 GetPos();
private:
	enum Debuff_Effects
	{
		MoonWalk,
		XY_swap,
		Speed,
		Slow,
		ShadowClone,
		All_debuff,
	};
	static Enemy_Poison* m_pointer;
	Enemy_Poison(){};
	~Enemy_Poison(){};
	Vector3 Pos;
	Vector3 Vel;
	bool Poisonous;
	float CoolDown;
	float LastTime;
	float ChangeEffect;
	bool FlipType[All_debuff];
	Mesh* Poison_Mesh;
	Vector3 Clones[5];

};
const float Moving_Speed = 30;
#endif