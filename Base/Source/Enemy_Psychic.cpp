#include "Enemy_Psychic.h"
#include "Render_PI.h"

Enemy_Psychic* Enemy_Psychic::c_enemyPsychic = new Enemy_Psychic();

Enemy_Psychic::Enemy_Psychic()
{

}

Enemy_Psychic::~Enemy_Psychic()
{

}

void Enemy_Psychic::Init()
{
	enemyPosition.x = 0;
	enemyPosition.y = 0;
}

void Enemy_Psychic::Update()
{

}

int Enemy_Psychic::SetPos_x(int pos_x)
{
	enemyPosition.x = pos_x;
}

int Enemy_Psychic::SetPos_y(int pos_y)
{
	enemyPosition.y = pos_y;
}

int Enemy_Psychic::GetPos_x()
{
	return enemyPosition.x;
}

int Enemy_Psychic::GetPos_y()
{
	return enemyPosition.y;
}

bool Enemy_Psychic::detectionArea()
{
	// Tile size in world origin
	Vector3 tileSize = Render_PI::Window_Scale()*(1.f / 10.f);
	//if (enemyPosition.x)

	return true;
}

void Enemy_Psychic::enemyStrategy()
{

}

void Enemy_Psychic::Render()
{

}

void Enemy_Psychic::Exit()
{

}