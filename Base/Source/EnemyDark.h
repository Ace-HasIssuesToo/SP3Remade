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
	virtual void Update(double dt, Map* map);

	virtual void RenderEnemyDark();
	virtual void RenderDarkball();

	Vector3 getEnemyDarkPos();
	Vector3 getEnemyDarkPosOffSet();
	Vector3 getEnemyDarkScale();

	enum EnemyDarkMeshes
	{
		Left = 0,
		Right,
		Top,
		Down
	};

	void setEnemyDarkMesh(Enemy_Dark::EnemyDarkMeshes mesh);
	Mesh* getEnemyMesh();

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
	double directionToPlayer;

	Vector3 EnemyDarkPos, DarkBall, EnemyDarkPosOffSet, EnemyDarkScale;
	Vector3 EnemyDarkShadow, DarkBallShadow;

	EnemyDarkMeshes enemyDarkMesh;
	Mesh *enemyDarkMeshLeft, *enemyDarkMeshRight, *enemyDarkMeshForward, *enemyDarkMeshDownward;
};

#endif