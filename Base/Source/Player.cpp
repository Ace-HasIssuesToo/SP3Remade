#include "Player.h"
#include "Input_PI.h"
#include "Render_PI.h"
#include "Texture_PI.h"
#include "Enemy_Poison.h"

PlayerClass* PlayerClass::m_pointer = new PlayerClass();

PlayerClass::PlayerClass()
	:movementSpeed(0)
	, PlayerPos(0, 0, 0)
	, PlayerPosOffSet(0, 0, 0)
	, PokeballPos(0,0,0)
	, playerShadow(0,0,0)
	, pokeballShadow(0,0,0)
	, sc(0,0,0)
{
}

PlayerClass::~PlayerClass()
{
}

void PlayerClass::Init()
{
	movementSpeed = 20;
<<<<<<< HEAD
	throwSpeed = -9.8;
	PlayerPos = Render_PI::Window_Scale();
=======
	PlayerPos = Render_PI::Window_Scale() * 0.5;
>>>>>>> d8116b92ecf01aa631da0b85d8b3730eb0fb9411
	sc.Set(5.f, 5.f, 5.f);
	//sc.Set(10.f, 10.f, 10.f);

	setPlayerMesh(Top);
	SpriteAnimation *saL, *saR, *saF, *saB;
	//Left Texture
	playerMeshLeft = MeshBuilder::GenerateSpriteAnimation("playerMeshLeft", 1, 4);
	playerMeshLeft->textureArray[0] = LoadTGA("Data//Texture//playerLeft.tga");		
	saL = dynamic_cast<SpriteAnimation*>(playerMeshLeft);
	if (saL)
	{
		saL->m_anim = new Animation();
		saL->m_anim->Set(0, 3, 0, 1.f, true);
	}
	//Down Texture
	playerMeshDownward = MeshBuilder::GenerateSpriteAnimation("playerMeshDown", 1, 4);
	playerMeshDownward->textureArray[0] = LoadTGA("Data//Texture//playerDown.tga");
	saB = dynamic_cast<SpriteAnimation*>(playerMeshDownward);
	if (saB)
	{
		saB->m_anim = new Animation();
		saB->m_anim->Set(0, 3, 0, 1.f, true);
	}
	//Top Texture
	playerMeshForward = MeshBuilder::GenerateSpriteAnimation("playerMeshTop", 1, 4);
	playerMeshForward->textureArray[0] = LoadTGA("Data//Texture//playerTop.tga");
	saF = dynamic_cast<SpriteAnimation*>(playerMeshForward);
	if (saF)
	{
		saF->m_anim = new Animation();
		saF->m_anim->Set(0, 3, 0, 1.f, true);
	}
	//Right Texture
	playerMeshRight = MeshBuilder::GenerateSpriteAnimation("playerMeshRight", 1, 4);
	playerMeshRight->textureArray[0] = LoadTGA("Data//Texture//PlayerRight.tga");
	saR = dynamic_cast<SpriteAnimation*>(playerMeshRight);
	if (saR)
	{
		saR->m_anim = new Animation();
		saR->m_anim->Set(0, 3, 0, 1.f, true);
	}
	//playerMesh = nullptr;
}

void PlayerClass::Update(double dt, Map* map)
{
	playerShadow = PlayerPos;
	Vector3 Movement = Vector3();
	if (Input_PI::pointer()->IsBeingPressed[Input_PI::Forward] == true)
	{
		Movement.y += movementSpeed * dt;
	}
	else if (Input_PI::pointer()->IsBeingPressed[Input_PI::Backward] == true)
	{
		Movement.y -= movementSpeed * dt;
	}
	if (Input_PI::pointer()->IsBeingPressed[Input_PI::Leftward] == true)
	{
		Movement.x -= movementSpeed * dt;
	}
	else if (Input_PI::pointer()->IsBeingPressed[Input_PI::Rightward] == true)
	{
		Movement.x += movementSpeed * dt;
	}

	if (getPlayerMesh2() == playerMeshForward)
	{
		SpriteAnimation *saT = dynamic_cast<SpriteAnimation*>(playerMeshForward);
		if (saT)
		{
			saT->Update(dt);
			saT->m_anim->animActive = true;
		}
	}
	else if (getPlayerMesh2() == playerMeshDownward)
	{
		SpriteAnimation *saD = dynamic_cast<SpriteAnimation*>(playerMeshDownward);
		if (saD)
		{
			saD->Update(dt);
			saD->m_anim->animActive = true;
		}
	}
	else if (getPlayerMesh2() == playerMeshLeft)
	{
		SpriteAnimation *saL = dynamic_cast<SpriteAnimation*>(playerMeshLeft);
		if (saL)
		{
			saL->Update(dt);
			saL->m_anim->animActive = true;
		}
	}
	else if (getPlayerMesh2() == playerMeshRight)
	{
		SpriteAnimation *saR = dynamic_cast<SpriteAnimation*>(playerMeshRight);
		if (saR)
		{
			saR->Update(dt);
			saR->m_anim->animActive = true;
		}
	}


	Movement = Enemy_Poison::pointer()->Poison(Movement);
	if (Movement.y > 0)
	{
		setPlayerMesh(Top);
	}
	else if (Movement.y < 0)
	{
		setPlayerMesh(Down);
	}
	if (Movement.x < 0)
	{
		setPlayerMesh(Left);
	}
	else if (Movement.x > 0)
	{
		setPlayerMesh(Right);
	}
	playerShadow += Movement;
	//Kind of Collision
	if (map->Get_Type(playerShadow + PlayerPosOffSet) == "Wall")
	{

	}
	else if (map->Get_Type(playerShadow + PlayerPosOffSet) == "Floor")
	{
		PlayerPos = playerShadow;
	}

	//Keep Player in window
	if (PlayerPos.x > (Render_PI::Window_Scale().x - 10))
	{
		double difference = PlayerPos.x - (Render_PI::Window_Scale().x - 10);
		PlayerPosOffSet.x += difference;
		PlayerPos.x = (Render_PI::Window_Scale().x - 10);
	}
	else if (PlayerPos.x < 10)
	{
		double difference = PlayerPos.x - (10);
		PlayerPosOffSet.x += difference;
		PlayerPos.x = (10);
	}
	if (PlayerPos.y >(Render_PI::Window_Scale().y - 10))
	{
		double difference = PlayerPos.y - (Render_PI::Window_Scale().y - 10);
		PlayerPosOffSet.y += difference;
		PlayerPos.y = (Render_PI::Window_Scale().y - 10);
	}
	else if (PlayerPos.y < 10)
	{
		double difference = PlayerPos.y - (10);
		PlayerPosOffSet.y += difference;
		PlayerPos.y = (10);
	}
}

void PlayerClass::Exit()
{
	if (m_pointer != nullptr)
	{
		delete m_pointer;
		m_pointer = nullptr;
	};

}

Vector3 PlayerClass::getPlayerPos()
{
	return PlayerPos;
}
Vector3 PlayerClass::getPlayerPosOffSet()
{
	return PlayerPosOffSet;
}
Vector3 PlayerClass::getPlayerScale()
{
	return sc;
}

void PlayerClass::setPlayerMesh(PlayerClass::PlayerMeshes mesh)
{
	this->playerMesh = mesh;
}

Mesh* PlayerClass::getPlayerMesh2()
{
	switch (playerMesh)
	{
	case Left:
		return playerMeshLeft;
		break;
	case Right:
		return playerMeshRight;
		break;
	case Top:
		return playerMeshForward;
		break;
	case Down:
		return playerMeshDownward;
		break;
	}
}

void PlayerClass::Renderplayer()
{
	Render_PI::pointer()->modelStack_Set(true);
	Render_PI::pointer()->RenderMeshIn2D(PlayerClass::getPlayerMesh2(), false, Vector3(PlayerPos), Vector3(getPlayerScale()));
	Render_PI::pointer()->modelStack_Set(false);
}