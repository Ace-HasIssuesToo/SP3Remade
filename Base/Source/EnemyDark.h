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
	void Exit();
	void Pos_Set(Vector3 Pos){ EnemyDarkPos = Pos; };

	Vector3 getEnemyDarkPos();

	enum EnemyDarkMeshes
	{
		Left = 0,
		Right,
		Top,
		Down
	};

	void setEnemyDarkMesh(Enemy_Dark::EnemyDarkMeshes mesh);
	Mesh* getEnemyMesh();

	Vector3 getRadSq();
	Vector3 getDisSq();

	void clearEnemyDark();

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
	float distSq;
	float combinedRadSq;

	Vector3 EnemyDarkPos, EnemyDarkScale;
	Vector3 EnemyDarkShadow;

	EnemyDarkMeshes enemyDarkMesh;
	Mesh *enemyDarkMeshLeft, *enemyDarkMeshRight, *enemyDarkMeshForward, *enemyDarkMeshDownward;
	Mesh *Darkball_Mesh;

	Vector3 darkBallPos;
	Vector3 darkBallDirection;
	bool ballOnScreen;
};

#endif