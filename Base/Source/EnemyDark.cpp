#include "EnemyDark.h"
#include "Input_PI.h"
#include "Render_PI.h"
#include "Texture_PI.h"
#include "GameState.h"

Enemy_Dark* Enemy_Dark::m_pointer = new Enemy_Dark();

Enemy_Dark::Enemy_Dark()
	:movementSpeed(0)
	, throwSpeed(0)
	, EnemyDarkPos(0, 0, 0)
	, EnemyDarkPosOffSet(0, 0, 0)
	, darkBallPos(0, 0, 0)
	, EnemyDarkShadow(0, 0, 0)
	, enemyDarkMeshLeft(nullptr)
	, enemyDarkMeshRight(nullptr)
	, enemyDarkMeshForward(nullptr)
	, enemyDarkMeshDownward(nullptr)
	, Darkball_Mesh(nullptr)
{
}

Enemy_Dark::~Enemy_Dark()
{
}

void Enemy_Dark::Init()
{
	movementSpeed = 10;
	throwSpeed = 30;
	//EnemyDarkPos = Render_PI::Window_Scale() * 0.7f;
	EnemyDarkPos = (Render_PI::Window_Scale() * 0.25f) + Vector3(0, 320, 0);
	EnemyDarkScale.Set(5.f, 5.f, 5.f);
	//EnemyDarkScale.Set(10.f, 10.f, 10.f);
	ballOnScreen = false;
	darkBallDirection = darkBallPos = Vector3();

	Darkball_Mesh = MeshBuilder::GenerateQuad("Pokeball", Color(0, 0, 0), 1.f);
	Darkball_Mesh->textureArray[0] = LoadTGA("Data//Texture//DarkBall.tga");

	SpriteAnimation *sa;
	//Left Texture
	enemyDarkMeshLeft = MeshBuilder::GenerateSpriteAnimation("enemyDarkMeshLeft", 1, 4);
	enemyDarkMeshLeft->textureArray[0] = LoadTGA("Data//Texture//EnemyDarkLeft.tga");
	sa = dynamic_cast<SpriteAnimation*>(enemyDarkMeshLeft);
	if (sa)
	{
		sa->m_anim = new Animation();
		sa->m_anim->Set(0, 3, 0, 1.f, true);
	}
	//Down Texture
	enemyDarkMeshDownward = MeshBuilder::GenerateSpriteAnimation("enemyDarkMeshDown", 1, 4);
	enemyDarkMeshDownward->textureArray[0] = LoadTGA("Data//Texture//EnemyDarkDown.tga");
	sa = dynamic_cast<SpriteAnimation*>(enemyDarkMeshDownward);
	if (sa)
	{
		sa->m_anim = new Animation();
		sa->m_anim->Set(0, 3, 0, 1.f, true);
	}
	//Top Texture
	enemyDarkMeshForward = MeshBuilder::GenerateSpriteAnimation("enemyDarkMeshTop", 1, 4);
	enemyDarkMeshForward->textureArray[0] = LoadTGA("Data//Texture//EnemyDarkTop.tga");
	sa = dynamic_cast<SpriteAnimation*>(enemyDarkMeshForward);
	if (sa)
	{
		sa->m_anim = new Animation();
		sa->m_anim->Set(0, 3, 0, 1.f, true);
	}
	//Right Texture
	enemyDarkMeshRight = MeshBuilder::GenerateSpriteAnimation("enemyDarkMeshRight", 1, 4);
	enemyDarkMeshRight->textureArray[0] = LoadTGA("Data//Texture//EnemyDarkRight.tga");
	sa = dynamic_cast<SpriteAnimation*>(enemyDarkMeshRight);
	if (sa)
	{
		sa->m_anim = new Animation();
		sa->m_anim->Set(0, 3, 0, 1.f, true);
	}
}

void Enemy_Dark::Update(double dt, Map* map)
{
	EnemyDarkShadow = EnemyDarkPos;
	Vector3 Movement = Vector3();
	Vector3 player_position = (PlayerClass::pointer()->getPlayerPosOffSet() + PlayerClass::pointer()->getPlayerPos());
	distSq = (EnemyDarkPos - player_position).LengthSquared();
	combinedRadSq = (EnemyDarkScale.x + PlayerClass::pointer()->getPlayerScale().x) * (EnemyDarkScale.x + PlayerClass::pointer()->getPlayerScale().x);

	if ((distSq >= combinedRadSq) && (player_position.x > EnemyDarkShadow.x))
	{
		Movement.x += movementSpeed * dt;
	}
	else if (distSq >= combinedRadSq && (player_position.x < EnemyDarkShadow.x))
	{
		Movement.x -= movementSpeed * dt;
	}
	if (distSq >= combinedRadSq && (player_position.y < EnemyDarkShadow.y))
	{
		Movement.y -= movementSpeed * dt;
	}
	else if (distSq >= combinedRadSq && (player_position.y > EnemyDarkShadow.y))
	{
		Movement.y += movementSpeed * dt;
	}
	SpriteAnimation *sa;
	if (getEnemyMesh() == enemyDarkMeshForward)
	{
		sa = dynamic_cast<SpriteAnimation*>(enemyDarkMeshForward);
		if (sa)
		{
			sa->Update(dt);
			sa->m_anim->animActive = true;
		}
	}
	else if (getEnemyMesh() == enemyDarkMeshDownward)
	{
		sa = dynamic_cast<SpriteAnimation*>(enemyDarkMeshDownward);
		if (sa)
		{
			sa->Update(dt);
			sa->m_anim->animActive = true;
		}
	}
	else if (getEnemyMesh() == enemyDarkMeshLeft)
	{
		sa = dynamic_cast<SpriteAnimation*>(enemyDarkMeshLeft);
		if (sa)
		{
			sa->Update(dt);
			sa->m_anim->animActive = true;
		}
	}
	else if (getEnemyMesh() == enemyDarkMeshRight)
	{
		sa = dynamic_cast<SpriteAnimation*>(enemyDarkMeshRight);
		if (sa)
		{
			sa->Update(dt);
			sa->m_anim->animActive = true;
		}
	}
	if (Movement.y > 0)
	{
		setEnemyDarkMesh(Top);
	}
	else if (Movement.y < 0)
	{
		setEnemyDarkMesh(Down);
	}
	if (Movement.x < 0)
	{
		setEnemyDarkMesh(Left);
	}
	else if (Movement.x > 0)
	{
		setEnemyDarkMesh(Right);
	}
	EnemyDarkShadow += Movement;

	//Kind of Collision
	
	//if (map->Get_Type(EnemyDarkShadow) == "Floor") // imma hot ass nigga mang
	//{
	//	EnemyDarkPos = EnemyDarkShadow;
	//}
	//else
	//{
	//	Vector3 offset = (EnemyDarkPos - (PlayerClass::pointer()->getPlayerPosOffSet() + PlayerClass::pointer()->getPlayerPos())).Normalize() * 50;
	//	if (rand() % 2)
	//	{
	//		offset.x *= -1;
	//	}
	//	if (rand() % 3)
	//	{
	//		offset.y *= -1;
	//	}
	//	EnemyDarkPos = (PlayerClass::pointer()->getPlayerPosOffSet() + PlayerClass::pointer()->getPlayerPos()) + offset;
	//}

	//if ((distSq <= combinedRadSq) && (ballOnScreen == false))
	//{
	//	ballOnScreen = true;
	//	darkBallPos = EnemyDarkPos;
	//	darkBallDirection = (Vector3((PlayerClass::pointer()->getPlayerPos() + PlayerClass::pointer()->getPlayerPosOffSet()) - darkBallPos).Normalize()) * throwSpeed;
	//}
	//else if (ballOnScreen == true)
	//{
	//	Vector3 shadow = darkBallPos + (darkBallDirection * dt);
	//	if (map->Get_Type(shadow) == "Floor")
	//	{
	//		darkBallPos = shadow;
	//	}
	//	else
	//	{
	//		ballOnScreen = false;
	//	}
	//	Vector3 radiusRange;
	//	radiusRange = (darkBallPos - (PlayerClass::pointer()->getPlayerPosOffSet() + PlayerClass::pointer()->getPlayerPos()));
	//	float radRange = radiusRange.x * radiusRange.x + radiusRange.y * radiusRange.y;
	//	if (radRange < 10.f)
	//	{
	//		GameState::pointer()->SetState(GameState::LOSE);
	//	}
	//}
}

Vector3 Enemy_Dark::getRadSq()
{
	return combinedRadSq;
}
Vector3 Enemy_Dark::getDisSq()
{
	return distSq;
}


Vector3 Enemy_Dark::getEnemyDarkPos()
{
	return Map::Pokemon_Offset(EnemyDarkPos);
}

void Enemy_Dark::setEnemyDarkMesh(Enemy_Dark::EnemyDarkMeshes mesh)
{
	this->enemyDarkMesh = mesh;
}

Mesh* Enemy_Dark::getEnemyMesh()
{
	if (enemyDarkMesh == Left)
	{
		Render_PI::pointer()->modelStack_Set(true);
		Render_PI::pointer()->RenderMeshIn2D(enemyDarkMeshLeft, false, Map::Pokemon_Offset(EnemyDarkPos), Vector3(EnemyDarkScale));
		Render_PI::pointer()->modelStack_Set(false);
	}
	else if (enemyDarkMesh == Right)
	{
		Render_PI::pointer()->modelStack_Set(true);
		Render_PI::pointer()->RenderMeshIn2D(enemyDarkMeshRight, false, Map::Pokemon_Offset(EnemyDarkPos), Vector3(EnemyDarkScale));
		Render_PI::pointer()->modelStack_Set(false);
	}
	else if (enemyDarkMesh == Top)
	{
		Render_PI::pointer()->modelStack_Set(true);
		Render_PI::pointer()->RenderMeshIn2D(enemyDarkMeshForward, false, Map::Pokemon_Offset(EnemyDarkPos), Vector3(EnemyDarkScale));
		Render_PI::pointer()->modelStack_Set(false);
	}
	else if (enemyDarkMesh == Down)
	{
		Render_PI::pointer()->modelStack_Set(true);
		Render_PI::pointer()->RenderMeshIn2D(enemyDarkMeshDownward, false, Map::Pokemon_Offset(EnemyDarkPos), Vector3(EnemyDarkScale));
		Render_PI::pointer()->modelStack_Set(false);
	}
	return nullptr;
}

void Enemy_Dark::RenderEnemyDark()
{
	getEnemyMesh();
	RenderDarkball();
}

void Enemy_Dark::RenderDarkball()
{
	if (ballOnScreen == true)
	{
		Render_PI::pointer()->modelStack_Set(true);
		Render_PI::pointer()->RenderMeshIn2D(Darkball_Mesh, false, Map::Pokemon_Offset(darkBallPos), Vector3(1, 1, 1));
		Render_PI::pointer()->modelStack_Set(false);
	}
	else
	{

	}
}

void Enemy_Dark::clearEnemyDark()
{
	movementSpeed = 10;
	throwSpeed = 30;
	EnemyDarkPos = (Render_PI::Window_Scale() * 0.25f) + Vector3(0, 325, 0);
	//EnemyDarkPos = Render_PI::Window_Scale() * 0.7f;
	EnemyDarkScale.Set(5.f, 5.f, 5.f);
	//EnemyDarkScale.Set(10.f, 10.f, 10.f);
	ballOnScreen = false;
	darkBallDirection = darkBallPos = Vector3();
}

void Enemy_Dark::Exit()
{
	if (m_pointer != nullptr)
	{
		if (enemyDarkMeshLeft != nullptr)
		{
			SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>(enemyDarkMeshLeft);
			if (sa)
			{
				delete sa->m_anim;
				sa->m_anim = nullptr;
			}
			delete enemyDarkMeshLeft;
			enemyDarkMeshLeft = nullptr;
		};
		if (enemyDarkMeshRight != nullptr)
		{
			SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>(enemyDarkMeshRight);
			if (sa)
			{
				delete sa->m_anim;
				sa->m_anim = nullptr;
			}
			delete enemyDarkMeshRight;
			enemyDarkMeshRight = nullptr;
		};
		if (enemyDarkMeshForward != nullptr)
		{
			SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>(enemyDarkMeshForward);
			if (sa)
			{
				delete sa->m_anim;
				sa->m_anim = nullptr;
			}
			delete enemyDarkMeshForward;
			enemyDarkMeshForward = nullptr;
		};
		if (enemyDarkMeshDownward != nullptr)
		{
			SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>(enemyDarkMeshDownward);
			if (sa)
			{
				delete sa->m_anim;
				sa->m_anim = nullptr;
			}
			delete enemyDarkMeshDownward;
			enemyDarkMeshDownward = nullptr;
		};
		if (Darkball_Mesh != nullptr)
		{
			delete Darkball_Mesh;
			Darkball_Mesh = nullptr;
		};
		delete m_pointer;
		m_pointer = nullptr;
	};
}