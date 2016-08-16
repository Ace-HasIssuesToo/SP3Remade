#pragma once
#include "Support_Codes.h"
#include "Render_PI.h"
#include "Map_PI.h"

class EnemyGhost
{
public:
	static EnemyGhost* pointer(){ return c_enemyGhost; };
	void Init();
	void Update(double dt, Map map);
	void RenderGhost();
	void Exit();
private:
	EnemyGhost() : ghostTimer(0), ghostStayTimer(0), dirX(Math::RandFloatMinMax(-10.f, 10.f)), dirY(Math::RandFloatMinMax(-10.f, 10.f)){};
	~EnemyGhost(){};
	static EnemyGhost* c_enemyGhost;

	float dirX;
	float dirY;
	float ghostTimer;
	float ghostStayTimer;
	Vector3 ghostPos;
	Vector3 ghostShadow;
};