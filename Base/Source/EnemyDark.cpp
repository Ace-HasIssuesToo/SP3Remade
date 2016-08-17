#include "EnemyDark.h"
#include "Input_PI.h"
#include "Render_PI.h"
#include "Texture_PI.h"

Enemy_Dark* Enemy_Dark::m_pointer = new Enemy_Dark();

Enemy_Dark::Enemy_Dark()
	:movementSpeed(0)
	, throwSpeed(0)
	, EnemyDarkPos(0, 0, 0)
	, EnemyDarkPosOffSet(0, 0, 0)
	, DarkBall(0, 0, 0)
	, EnemyDarkShadow(0, 0, 0)
	, DarkBallShadow(0, 0, 0)
{
}

Enemy_Dark::~Enemy_Dark()
{
}

void Enemy_Dark::Init()
{
	movementSpeed = 10;
	throwSpeed = -9.8;
	EnemyDarkPos = Render_PI::Window_Scale() * 0.7f;
	EnemyDarkScale.Set(1.1f, 1.1f, 1.1f);
	//Enemy_DarkMesh = MeshBuilder::GenerateSpriteAnimation();
}

void Enemy_Dark::Update(double dt, Map map)
{
	EnemyDarkShadow = EnemyDarkPos;
	//Kind of Collision
	if (map.Get_Type(EnemyDarkShadow) == "Wall")
	{

	}
	else if (map.Get_Type(EnemyDarkShadow) == "Floor")
	{
		EnemyDarkPos = EnemyDarkShadow;
	}

	DarkBall = EnemyDarkPos;
	DarkBallShadow = DarkBall;

	if (map.Get_Type(DarkBallShadow) == "Wall")
	{

	}
	else if (map.Get_Type(DarkBallShadow) == "Floor")
	{
		DarkBall = DarkBallShadow;
	}

	float distSq = (getEnemyDarkPos() - PlayerClass::pointer()->getPlayerPos()).LengthSquared();
	float combinedRadSq = (getEnemyDarkScale().x + PlayerClass::pointer()->getPlayerScale().x) * (getEnemyDarkScale().x + PlayerClass::pointer()->getPlayerScale().x);

	if ((distSq >= combinedRadSq) && (PlayerClass::pointer()->getPlayerPos().x > EnemyDarkShadow.x))
	{
		EnemyDarkPos.x += movementSpeed * dt;
	}
	else if (distSq >= combinedRadSq && (PlayerClass::pointer()->getPlayerPos().x < EnemyDarkShadow.x))
	{
		EnemyDarkPos.x -= movementSpeed * dt;
	}
	if (distSq >= combinedRadSq && (PlayerClass::pointer()->getPlayerPos().y < EnemyDarkShadow.y))
	{
		EnemyDarkPos.y -= movementSpeed * dt;
	}
	else if (distSq >= combinedRadSq && (PlayerClass::pointer()->getPlayerPos().y > EnemyDarkShadow.y))
	{
		EnemyDarkPos.y += movementSpeed * dt;
	}

	if (distSq <= combinedRadSq)
	{

	}
	//Keep Enemy_Dark in window
	/*if (EnemyDarkPos.x > Render_PI::Window_Scale().x - 5)
	{
		double difference = EnemyDarkPos.x - (Render_PI::Window_Scale().x - 5);
		EnemyDarkPosOffSet.x += difference;
		EnemyDarkPos = (Render_PI::Window_Scale().x - 5);
	}
	else if (EnemyDarkPos.x < 5)
	{
		double difference = EnemyDarkPos.x - (5);
		EnemyDarkPosOffSet.x += difference;
		EnemyDarkPos = (5);
	}
	if (EnemyDarkPos.y > Render_PI::Window_Scale().y - 5)
	{
		double difference = EnemyDarkPos.y - (Render_PI::Window_Scale().y - 5);
		EnemyDarkPosOffSet.y += difference;
		EnemyDarkPos = (Render_PI::Window_Scale().y - 5);
	}
	else if (EnemyDarkPos.y < 5)
	{
		double difference = EnemyDarkPos.y - (5);
		EnemyDarkPosOffSet.y += difference;
		EnemyDarkPos = (5);
	}*/
}

Vector3 Enemy_Dark::getEnemyDarkPos()
{
	return EnemyDarkPos;
}
Vector3 Enemy_Dark::getEnemyDarkPosOffSet()
{
	return EnemyDarkPosOffSet;
}
Vector3 Enemy_Dark::getEnemyDarkScale()
{
	return EnemyDarkScale;
}

void Enemy_Dark::RenderEnemyDark()
{
	Render_PI::pointer()->modelStack_Set(true);
	Render_PI::pointer()->RenderMeshIn2D(Texture::Get("Something"), false, Map::Pokemon_Offset(EnemyDarkPos), Vector3(getEnemyDarkScale()));
	Render_PI::pointer()->modelStack_Set(false);
}

void Enemy_Dark::RenderDarkball()
{
	Render_PI::pointer()->modelStack_Set(true);
	Render_PI::pointer()->RenderMeshIn2D(Texture::Get("Something"), false, Vector3(DarkBall), Vector3(1, 1, 1));
	Render_PI::pointer()->modelStack_Set(false);
}