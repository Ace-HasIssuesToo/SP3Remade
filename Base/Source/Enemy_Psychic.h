#ifndef ENEMY_PSYCHIC_H
#define ENEMY_PSYCHIC_H

#include "Support_Codes.h"
#include "Render_PI.h"
#include "Map_PI.h"

class Enemy_Psychic
{
public:
	Enemy_Psychic();
	~Enemy_Psychic();

	static Enemy_Psychic* pointer() { return c_enemyPsychic; };

	//enum GEOMETRY_TYPE
	//{
	//	//GEO_TILEENEMY_FRAME0,
	//	NUM_GEOMETRY,
	//};

	void Init();
	void Update(double dt, Map* map);
	void RenderPsychic();
	void Exit();

	//temporary death code
	bool tempKill;

private:
	static Enemy_Psychic* c_enemyPsychic;

	Vector3 psychicPos, psychicPosOffset;

	int counterFound;
	bool playerIntrude;
	bool defMechanism;
	bool lastResort;
};

#endif