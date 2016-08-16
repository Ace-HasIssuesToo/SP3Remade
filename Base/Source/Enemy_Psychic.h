#ifndef ENEMY_PSYCHIC_H
#define ENEMY_PSYCHIC_H

#include "Vector2.h"

class Enemy_Psychic
{
public:
	Enemy_Psychic();
	~Enemy_Psychic();

	static Enemy_Psychic* c_enemyPsychic;

	enum GEOMETRY_TYPE
	{
		//GEO_TILEENEMY_FRAME0,
		NUM_GEOMETRY,
	};

	void Init();
	void Update();
	void Render();
	void Exit();

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

private:
	static Enemy_Psychic* pointer() { return c_enemyPsychic; };

	// Enemy's Information
	Vector2 enemyPosition;
};

#endif