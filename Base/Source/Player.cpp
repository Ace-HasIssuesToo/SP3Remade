#include "Player.h"
#include "Input_PI.h"
#include "Render_PI.h"
#include "Texture_PI.h"
#include "Enemy_Poison.h"
#include "Enemy_Ghost.h"
#include "GameState.h"
#include "Additional_Functions.h"
#include "SoundEngine.h"
#include "DecoText.h"
#include "ReadTxtFile.h"
#include "Vector3.h"

PlayerClass* PlayerClass::m_pointer = new PlayerClass();

PlayerClass::PlayerClass()
	:movementSpeed(0)
	, PlayerPos(0, 0, 0)
	, PlayerPosOffSet(0, 0, 0)
	, playerShadow(0,0,0)
	, sc(0,0,0)
	, batteryTimer(0)
	, drinkTimer(0)
	, GetBattery(false)
	, GetDrink(false)
	, LightOn(false)
	, LightRange(0)
	, playerMeshRight(nullptr)
	, playerMeshLeft(nullptr)
	, playerMeshForward(nullptr)
	, playerMeshDownward(nullptr)
	, Battery(nullptr)
	, Drink(nullptr)
	, BatteryExists(false)
	, DrinkExists(false)
	, displayBattteryExists(false)
	, displayDrinkExists(false)
	, playerMeshIdle(nullptr)
{
}

PlayerClass::~PlayerClass()
{
}

void PlayerClass::Init()
{
	setPlayerMesh(Top);

	movementSpeed = 20;
	Stamina = 10.f;
	LightPower = 10.f;

	PlayerPosOffSet = PlayerPos = Render_PI::Window_Scale()*0.2 + Vector3(-10, 100, 0);
	PlayerPos = Render_PI::Window_Scale() * 0.2 + Vector3(-10, 100, 0);
	sc.Set(10.f, 10.f, 10.f);
	setPlayerMesh(Top);

	//PlayerPosOffSet = PlayerPos = Render_PI::Window_Scale()*0.5;
	//PlayerPos = Render_PI::Window_Scale() * 0.5;
	//sc.Set(10.f, 10.f, 10.f);
	//setPlayerMesh(Top);

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
	
	playerMeshIdle = MeshBuilder::GenerateQuad("playerMeshIdle", Color(0,0,0), 1.f);
	playerMeshIdle->textureArray[0] = LoadTGA("Data//Texture//playerIdle.tga");
	PickUp = SoundEngine::Use()->addSoundSourceFromFile("Data//Sound//Retrieval.mp3");
}

float PlayerClass::GetLightRange()
{
	/*if (LightOn == true)
	{
		LightRange = 3.f;
	}
	else if (LightOn == false)
	{
		LightRange = 1.f;
	}*/
	return LightRange;
}

void PlayerClass::clearItems()
{
	GetDrink = false;
	GetBattery = false;
}

void PlayerClass::Update(double dt, Map* map)
{
	Vector3 Movement = Vector3();
	playerShadow = PlayerPos;
	PlayerPos.z = 0;
	movementSpeed = 20;
	if (Input_PI::pointer()->IsBeingPressed[Input_PI::Run])
	{
		if (Stamina > 0.f)
		{
			Stamina -= dt;
			movementSpeed *= Math::Max(1.f, Stamina);
		}
	}
	else
	{
		if (Stamina <= 10.f)
		{
			Stamina += 0.5 * dt;
		}
	}
	if (Stamina > 10.f)
	{
		Stamina = 10.f;
	}
	else if (Stamina < 0.f)
	{
		Stamina = 0;
	}

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

	if (Input_PI::pointer()->HaveBeenPressed[Input_PI::Light_Switch] == true)
	{

		if (LightOn)
		{
			LightPower -= 0.1 * LightRange * dt;
			LightOn = false;
			LightRange = 0;
		}
		else
		{
			LightOn = true;
			LightRange = 10;
		}
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
	Movement = Enemy_Ghost::pointer()->Freeze(Movement);
	if (Movement == (0,0,0))
	{
		setPlayerMesh(Idle);
	}
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
	Vector3 size = Vector3(5, 5, 1);
	Vector3 DisplacedMovement = playerShadow + Functions::DisplaceWall(Movement, size);

	//Kind of Collision
	if (map->Get_Type(DisplacedMovement + PlayerPosOffSet) == "Wall")
	{
		Deco_interacted = "Wall";
	}
	else if (map->Get_Type(DisplacedMovement + PlayerPosOffSet) == "Floor")
	{
		PlayerPos = playerShadow;
	}
	else if (map->Get_Type(DisplacedMovement + PlayerPosOffSet) == "VendingMachine")
	{
		GetDrink = true;
		Deco_interacted = "VendingMachine";
	}
	else if (map->Get_Type(DisplacedMovement + PlayerPosOffSet) == "Treasure")
	{
		GetBattery = true;
		Deco_interacted = "Treasure";
	}
	else
	{
		Deco_interacted = map->Get_Type(DisplacedMovement + PlayerPosOffSet);
	}

	if (GetDrink == true)
	{
		if (drinkTimer < 10.f)
		{
			drinkTimer += dt;
		}
	}
	if (GetBattery == true)
	{
		if (batteryTimer < 10.f)
		{
			batteryTimer += dt;
		}
	}

	if (Input_PI::pointer()->IsBeingPressed[Input_PI::UseDrink] && GetDrink)
	{
		Stamina = 10.f;
		GetDrink = false;
		drinkTimer = 0.f;
	}
	if (Input_PI::pointer()->IsBeingPressed[Input_PI::UseBattery] && GetBattery)
	{
		LightPower = 10.f;
		GetBattery = false;
		batteryTimer = 0.f;
	}
	
	//Keep Player in window
	float Limitation_size = 30;
	if (PlayerPos.x > (Render_PI::Window_Scale().x - Limitation_size))
	{
		double difference = PlayerPos.x - (Render_PI::Window_Scale().x - Limitation_size);
		PlayerPosOffSet.x += difference;
		PlayerPos.x = (Render_PI::Window_Scale().x - Limitation_size);
	}
	else if (PlayerPos.x < Limitation_size)
	{
		double difference = PlayerPos.x - (Limitation_size);
		PlayerPosOffSet.x += difference;
		PlayerPos.x = (Limitation_size);
	}
	if (PlayerPos.y >(Render_PI::Window_Scale().y - Limitation_size))
	{
		double difference = PlayerPos.y - (Render_PI::Window_Scale().y - Limitation_size);
		PlayerPosOffSet.y += difference;
		PlayerPos.y = (Render_PI::Window_Scale().y - Limitation_size);
	}
	else if (PlayerPos.y < Limitation_size)
	{
		double difference = PlayerPos.y - (Limitation_size);
		PlayerPosOffSet.y += difference;
		PlayerPos.y = (Limitation_size);
	}
}

void PlayerClass::clearPlayer()
{
	movementSpeed = 20;
	Stamina = 10.f;
	PlayerPosOffSet = PlayerPos = Render_PI::Window_Scale()*0.5;
	PlayerPos = Render_PI::Window_Scale() * 0.5;
	sc.Set(10.f, 10.f, 10.f);
	PokeballInfo::pointer()->setNumOfBalls(100);
}
void PlayerClass::clearLights()
{
	LightOn = false;
	LightPower = 10.f;
	LightRange = 0.f;
}
void PlayerClass::Exit()
{
	if (m_pointer != nullptr)
	{
		if (playerMeshLeft != nullptr)
		{
			SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>(playerMeshLeft);
			if (sa)
			{
				delete sa->m_anim;
				sa->m_anim = nullptr;
			}
			delete playerMeshLeft;
			playerMeshLeft = nullptr;
		};
		if (playerMeshRight != nullptr)
		{
			SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>(playerMeshRight);
			if (sa)
			{
				delete sa->m_anim;
				sa->m_anim = nullptr;
			}
			delete playerMeshRight;
			playerMeshRight = nullptr;
		};
		if (playerMeshForward != nullptr)
		{
			SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>(playerMeshForward);
			if (sa)
			{
				delete sa->m_anim;
				sa->m_anim = nullptr;
			}
			delete playerMeshForward;
			playerMeshForward = nullptr;
		};
		if (playerMeshDownward != nullptr)
		{
			SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>(playerMeshDownward);
			if (sa)
			{
				delete sa->m_anim;
				sa->m_anim = nullptr;
			}
			delete playerMeshDownward;
			playerMeshDownward = nullptr;
		};

		if (playerMeshIdle != nullptr)
		{
			delete playerMeshIdle;
			playerMeshIdle = nullptr;
		};
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
	sc.z = 0;
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
	case Idle:
		return playerMeshIdle;
		break;
	}
}

void PlayerClass::Renderplayer()
{
	Render_PI::pointer()->modelStack_Set(true);
	Render_PI::pointer()->RenderMeshIn2D(PlayerClass::getPlayerMesh2(), false, Vector3(PlayerPos), Vector3(getPlayerScale()));
	Render_PI::pointer()->modelStack_Set(false);

	

}