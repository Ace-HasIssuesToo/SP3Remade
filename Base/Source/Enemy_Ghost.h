#pragma once
#include "Support_Codes.h"
#include "Render_PI.h"
#include "Map_PI.h"

class Enemy_Ghost
{
	
public:
	static Enemy_Ghost* pointer(){ return c_Enemy_Ghost; };
	void Init();
	void Update(double dt, Map* map);
	void RenderGhost();
	void Exit();

	Vector3 GetGhostPos();
	Vector3 GetGhostOffSet();
	Vector3 Freeze(Vector3 Movement);
private:
	int life = 1;
	Enemy_Ghost()
		: ghostTimer(0)
		, ghostStayTimer(0)
		, dirX(Math::RandFloatMinMax(-5.f, 5.f))
		, dirY(Math::RandFloatMinMax(-5.f, 5.f))
		, ghostPos(0, 0, 0)
		, ghostShadow(0, 0, 0)
		, ghostoffset(0, 0, 0)
	{
	}
	~Enemy_Ghost()
	{
	}
	static Enemy_Ghost* c_Enemy_Ghost;
	float dirX;
	float dirY;
	float ghostTimer;
	float ghostStayTimer;
	Vector3 ghostPos;
	Vector3 ghostShadow;
	Vector3 ghostoffset;
	Mesh* ghostSprite;
};