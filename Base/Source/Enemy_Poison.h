#ifndef ENEMY_POISON
#define ENEMY_POISON
#include "Input_PI.h"
#include "Map_PI.h"

class Enemy_Poison
{
public:
	void Clear();
	static Enemy_Poison* pointer(){ return m_pointer; };
	void Init();
	void Update(double dt, Map* map);
	void render(Vector3 Offset);
	void Exit();
	Vector3 Poison(Vector3 Movement);
	Vector3 GetPos();
	void ClearPoison();
	void render_Poison();
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
	Mesh* Poison_Mesh;
	Mesh* Poisoned_effect;
	Enemy_Poison(){};
	~Enemy_Poison(){};
	Vector3 Pos;
	Vector3 Vel;
	bool Poisonous;
	float CoolDown;
	float LastTime;
	float ChangeEffect;
	bool FlipType[All_debuff];
	Vector3 Clones[5];

};
const float Moving_Speed = 10;
#endif