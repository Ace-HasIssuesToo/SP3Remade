#ifndef ENEMY_PSYCHIC_H
#define ENEMY_PSYCHIC_H

#include "Support_Codes.h"
#include "Render_PI.h"
#include "Map_PI.h"
#include "irrKlang.h"

using namespace irrklang;

class Enemy_Psychic
{
public:
	Enemy_Psychic();
	~Enemy_Psychic();

	static Enemy_Psychic* pointer() { return c_enemyPsychic; };

	void Init();
	void Update(double dt, Map* map);
	void RenderPsychic();
	void Exit();

	void SpriteUpdate(double dt);
	Vector3 GetPos();

	void clearPsychic();

	enum STATE_TYPE
	{
		STATE_HIDE,
		STATE_APPEAR,
		STATE_KILL,
		STATE_GG,
		STATE_TOTAL,
	};
	STATE_TYPE currState;

	// Sound Engine
	ISoundSource* runScream;
	ISound* killScream;

private:
	static Enemy_Psychic* c_enemyPsychic;

	Vector3 psychicPos, psychicPosOffset, locationDir;

	bool psycho;
	bool finalScream;
	float screamTimer;

	int countFound;
	bool playerIntrude;
	bool defMechanism;
	bool lastResort;

	Mesh* hide_psychic;
	Mesh* appear_psychic;
	Mesh* kill_psychic;
};

#endif