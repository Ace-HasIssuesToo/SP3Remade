#ifndef ENEMY_POISON
#define ENEMY_POISON
#include "Input_PI.h"

class Enemy_Poison
{
public:
	static Enemy_Poison* pointer(){ return m_pointer; };
	void Init();
	void Update(float dt);
	void render();
	void exit();
private:
	static Enemy_Poison* m_pointer;
	Enemy_Poison(){};
	~Enemy_Poison(){};
	Vector3 Pos;

};

#endif