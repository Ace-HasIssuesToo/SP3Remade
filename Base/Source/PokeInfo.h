#pragma once

#include "Support_Codes.h"
#include "Render_PI.h"
#include "Map_PI.h"
#include "Player.h"
#include "Input_PI.h"

class PokeballInfo
{
public:
	virtual void Init();
	virtual void Update(double dt, Map* map);
	virtual void Render();
	virtual void Exit();

	Vector3 getPokeballPos();
	bool getBallStatus();
	void ClearBallStatus();

	static PokeballInfo* pointer()
	{
		return m_pointer;
	}
private:
	PokeballInfo();
	~PokeballInfo();
	static PokeballInfo* m_pointer;

	Vector3 ballPos;
	Vector3 ballDirection;
	bool ballOnScreen;
	Vector3 sc;
	Vector3 vel;

	float movementTime;
	int numOfBalls;

	double throwSpeed;

	Mesh* pokeballmesh;
};