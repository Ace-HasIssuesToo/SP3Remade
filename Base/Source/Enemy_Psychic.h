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

	enum GEOMETRY_TYPE
	{
		//GEO_TILEENEMY_FRAME0,
		NUM_GEOMETRY,
	};

	void Init();
	void Update(double dt, Map map);
	void RenderPsychic();
	void Exit();

<<<<<<< HEAD
	//temporary death code
	bool tempKill;
=======
	// Set pos x of enemy
	void SetPos_x(int pos_x);
	// Set pos y of enemy
	void SetPos_y(int pos_y);

	// Get pos x of enemy
	int GetPos_x();
	// Get pos y of enemy
	int GetPos_y();
	// Get number of times enemy found by the player
	int counterFound;
	// Get bool for enemy detection area
	bool detectionArea();

	// Set enemy strategy
	void enemyStrategy();
>>>>>>> d9580da46056991b3e2d99efafe75d1ea16d6798

private:
	static Enemy_Psychic* c_enemyPsychic;

	Vector3 psychicPos, psychicPosOffset;

	int counterFound;
	bool playerIntrude;
	bool defMechanism;
	bool lastResort;
};

#endif