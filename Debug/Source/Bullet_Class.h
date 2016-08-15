#ifndef BULLET_CLASS
#define BULLET_CLASS
#include "Vector3.h"

class Bullet
{
public :
	Vector3 Pos;
	float Angle;
	bool Active;
	int Effect;
	float Fly_Time;

	enum Effect
	{
		None = 0,
		Teleport,
		Marked,
	};

	void Clear()
	{
		this->Pos = Vector3();
		this->Angle = 0;
		this->Active = false;
		this->Effect = None;
		Fly_Time = 0;
	};
	void Shot(Vector3 Pos, float Angle, int Effect)
	{
		this->Pos = Pos;
		this->Angle = Angle;
		this->Active = true;
		this->Effect = Effect;
		this->Fly_Time = 2;
	}
};
#endif