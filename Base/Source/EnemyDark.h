#ifndef ENEMYDARK_H
#define ENEMY_DARK

#include "Support_Codes.h"
#include "Render_PI.h"
#include "Map_PI.h"
#include "Player.h"

class Enemy_Dark
{
public:
	virtual void Init();
	virtual void Update(double dt, Map map);
	virtual void RenderEnemyDark();
	virtual void RenderDarkball();
	Vector3 getEnemyDarkPos();
	Vector3 getEnemyDarkPosOffSet();
	Vector3 getEnemyDarkScale();
	static Enemy_Dark* pointer()
	{
		return m_pointer;
	}
private:
	Enemy_Dark();
	~Enemy_Dark();

	static Enemy_Dark* m_pointer;
	int movementSpeed;
	double throwSpeed;
	Vector3 EnemyDarkPos, DarkBall, EnemyDarkPosOffSet, EnemyDarkScale;
	Mesh* darkMesh;
	Vector3 EnemyDarkShadow, DarkBallShadow;
	double directionToPlayer;
};

#endif