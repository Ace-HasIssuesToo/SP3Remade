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
{
}

Enemy_Dark::~Enemy_Dark()
{
}

void Enemy_Dark::Init()
{
	movementSpeed = 10;
	throwSpeed = 30;
	EnemyDarkPos = Render_PI::Window_Scale() * 0.7f;
	EnemyDarkScale.Set(5.f, 5.f, 5.f);
	//EnemyDarkScale.Set(10.f, 10.f, 10.f);
	ballOnScreen = false;
	darkBallDirection = darkBallPos = Vector3();

	Darkball_Mesh = MeshBuilder::GenerateQuad("Pokeball", Color(0, 0, 0), 1.f);
	Darkball_Mesh->textureArray[0] = LoadTGA("Data//Texture//DarkBall.tga");

	SpriteAnimation *saL, *saR, *saF, *saB;
	//Left Texture
	enemyDarkMeshLeft = MeshBuilder::GenerateSpriteAnimation("enemyDarkMeshLeft", 1, 4);
	enemyDarkMeshLeft->textureArray[0] = LoadTGA("Data//Texture//EnemyDarkLeft.tga");
	saL = dynamic_cast<SpriteAnimation*>(enemyDarkMeshLeft);
	if (saL)
	{
		saL->m_anim = new Animation();
		saL->m_anim->Set(0, 3, 0, 1.f, true);
	}
	//Down Texture
	enemyDarkMeshDownward = MeshBuilder::GenerateSpriteAnimation("enemyDarkMeshDown", 1, 4);
	enemyDarkMeshDownward->textureArray[0] = LoadTGA("Data//Texture//EnemyDarkDown.tga");
	saB = dynamic_cast<SpriteAnimation*>(enemyDarkMeshDownward);
	if (saB)
	{
		saB->m_anim = new Animation();
		saB->m_anim->Set(0, 3, 0, 1.f, true);
	}
	//Top Texture
	enemyDarkMeshForward = MeshBuilder::GenerateSpriteAnimation("enemyDarkMeshTop", 1, 4);
	enemyDarkMeshForward->textureArray[0] = LoadTGA("Data//Texture//EnemyDarkTop.tga");
	saF = dynamic_cast<SpriteAnimation*>(enemyDarkMeshForward);
	if (saF)
	{
		saF->m_anim = new Animation();
		saF->m_anim->Set(0, 3, 0, 1.f, true);
	}
	//Right Texture
	enemyDarkMeshRight = MeshBuilder::GenerateSpriteAnimation("enemyDarkMeshRight", 1, 4);
	enemyDarkMeshRight->textureArray[0] = LoadTGA("Data//Texture//EnemyDarkRight.tga");
	saR = dynamic_cast<SpriteAnimation*>(enemyDarkMeshRight);
	if (saR)
	{
		saR->m_anim = new Animation();
		saR->m_anim->Set(0, 3, 0, 1.f, true);
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
	if (getEnemyMesh() == enemyDarkMeshForward)
	{
		SpriteAnimation *saT = dynamic_cast<SpriteAnimation*>(enemyDarkMeshForward);
		if (saT)
		{
			saT->Update(dt);
			saT->m_anim->animActive = true;
		}
	}
	else if (getEnemyMesh() == enemyDarkMeshDownward)
	{
		SpriteAnimation *saD = dynamic_cast<SpriteAnimation*>(enemyDarkMeshDownward);
		if (saD)
		{
			saD->Update(dt);
			saD->m_anim->animActive = true;
		}
	}
	else if (getEnemyMesh() == enemyDarkMeshLeft)
	{
		SpriteAnimation *saL = dynamic_cast<SpriteAnimation*>(enemyDarkMeshLeft);
		if (saL)
		{
			saL->Update(dt);
			saL->m_anim->animActive = true;
		}
	}
	else if (getEnemyMesh() == enemyDarkMeshRight)
	{
		SpriteAnimation *saR = dynamic_cast<SpriteAnimation*>(enemyDarkMeshRight);
		if (saR)
		{
			saR->Update(dt);
			saR->m_anim->animActive = true;
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
	if (map->Get_Type(EnemyDarkShadow) == "Wall")
	{

	}
	else if (map->Get_Type(EnemyDarkShadow) == "Floor")
	{
		EnemyDarkPos = EnemyDarkShadow;
	}


	if ((distSq <= combinedRadSq) && (ballOnScreen == false))
	{
		ballOnScreen = true;
		darkBallPos = EnemyDarkPos;
		darkBallDirection = (Vector3((PlayerClass::pointer()->getPlayerPos() + PlayerClass::pointer()->getPlayerPosOffSet()) - darkBallPos).Normalize()) * throwSpeed;
	}
	else if (ballOnScreen == true)
	{
		Vector3 shadow = darkBallPos + (darkBallDirection * dt);
		if (map->Get_Type(shadow) == "Floor")
		{
			darkBallPos = shadow;
		}
		else
		{
			ballOnScreen = false;
		}
		Vector3 radiusRange;
		radiusRange = (darkBallPos - (PlayerClass::pointer()->getPlayerPosOffSet() + PlayerClass::pointer()->getPlayerPos()));
		float radRange = radiusRange.x * radiusRange.x + radiusRange.y * radiusRange.y;
		if (radRange < 10.f)
		{
			GameState::pointer()->SetState(GameState::LOSE);
		}
	}
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
	switch (enemyDarkMesh)
	{
	case Left:
		return enemyDarkMeshLeft;
		break;
	case Right:
		return enemyDarkMeshRight;
		break;
	case Top:
		return enemyDarkMeshForward;
		break;
	case Down:
		return enemyDarkMeshDownward;
		break;

	}
}

void Enemy_Dark::RenderEnemyDark()
{
		Render_PI::pointer()->modelStack_Set(true);
		Render_PI::pointer()->RenderMeshIn2D(Enemy_Dark::getEnemyMesh(), false, Map::Pokemon_Offset(EnemyDarkPos), Vector3(EnemyDarkScale));
		Render_PI::pointer()->modelStack_Set(false); 
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

void Enemy_Dark::Exit()
{
	if (m_pointer != nullptr)
	{
		delete m_pointer;
		m_pointer = nullptr;
	};
	if (enemyDarkMeshLeft != nullptr)
	{
		delete enemyDarkMeshLeft;
		enemyDarkMeshLeft = nullptr;
	};
	if (enemyDarkMeshRight != nullptr)
	{
		delete enemyDarkMeshRight;
		enemyDarkMeshRight = nullptr;
	};
	if (enemyDarkMeshForward != nullptr)
	{
		delete enemyDarkMeshForward;
		enemyDarkMeshForward = nullptr;
	};
	if (enemyDarkMeshDownward != nullptr)
	{
		delete enemyDarkMeshDownward;
		enemyDarkMeshDownward = nullptr;
	};
	if (Darkball_Mesh != nullptr)
	{
		delete Darkball_Mesh;
		Darkball_Mesh = nullptr;
	};
}