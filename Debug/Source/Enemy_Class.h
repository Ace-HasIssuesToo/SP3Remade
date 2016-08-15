#ifndef ENEMY_CLASS_H
#define ENEMY_CLASS_H
#include "Vector3.h"

class Enemy_Class
{
public:
	Enemy_Class(){};
	~Enemy_Class(){};
	Vector3 Position;
	int state;
	void Create();
	void Teleport(int i);
	void AI_Movement(double dt);
	enum States
	{
		Shut_Down,
		Normal,
		Stunned,
		Targeted,
		Hunting,
		All_States,
	};
};

#endif