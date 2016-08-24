#pragma once
#include "Support_Codes.h"
#include "Render_PI.h"
#include "Map_PI.h"
#include "irrKlang.h"

class Enemy_Ghost
{
	
public:
	static Enemy_Ghost* pointer(){ return c_Enemy_Ghost; };
	void Init();
	void Update(double dt, Map* map);
	void RenderGhost();
	void Exit();
	void ClearGhost();

	Vector3 GetGhostPos();
	Vector3 GetGhostOffSet();
	Vector3 Freeze(Vector3 Movement);
	ISoundSource* haunt;
private:
	Enemy_Ghost();
	~Enemy_Ghost();
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