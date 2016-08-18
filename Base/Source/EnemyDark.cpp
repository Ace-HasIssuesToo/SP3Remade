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
	EnemyDarkScale.Set(5.f, 5.f, 5.f);
	//EnemyDarkScale.Set(10.f, 10.f, 10.f);

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
	float distSq = (getEnemyDarkPos() - player_position).LengthSquared();
	float combinedRadSq = (getEnemyDarkScale().x + PlayerClass::pointer()->getPlayerScale().x) * (getEnemyDarkScale().x + PlayerClass::pointer()->getPlayerScale().x);

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

	DarkBall = EnemyDarkPos;
	DarkBallShadow = DarkBall;

	if (distSq <= combinedRadSq)
	{
		Vector3 posToPlayer = PlayerClass::pointer()->getPlayerPos() - getEnemyDarkPos();
	}

	if (map->Get_Type(DarkBallShadow) == "Wall")
	{

	}
	else if (map->Get_Type(DarkBallShadow) == "Floor")
	{
		DarkBall = DarkBallShadow;
	}
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
	Render_PI::pointer()->RenderMeshIn2D(Enemy_Dark::getEnemyMesh(), false, Map::Pokemon_Offset(EnemyDarkPos), Vector3(getEnemyDarkScale()));
	Render_PI::pointer()->modelStack_Set(false);
}

void Enemy_Dark::RenderDarkball()
{
	Render_PI::pointer()->modelStack_Set(true);
	Render_PI::pointer()->RenderMeshIn2D(Darkball_Mesh, false, Vector3(DarkBall), Vector3(1, 1, 1));
	Render_PI::pointer()->modelStack_Set(false);
}

void Enemy_Dark::Exit()
{
	if (m_pointer != nullptr)
	{
		delete m_pointer;
		m_pointer = nullptr;
	};

}