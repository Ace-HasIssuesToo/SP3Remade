#include "Player.h"
#include "Input_PI.h"
#include "Render_PI.h"
#include "Texture_PI.h"
#include "Enemy_Poison.h"

PlayerClass* PlayerClass::m_pointer = new PlayerClass();

PlayerClass::PlayerClass()
	:movementSpeed(0)
	, throwSpeed(0)
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
	throwSpeed = -9.8;
	PlayerPos = Render_PI::Window_Scale() * 0.5;
	sc.Set(1, 1, 1);
	playerMesh = nullptr;
}

void PlayerClass::Update(double dt, Map map)
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
	Movement = Enemy_Poison::pointer()->Poison(Movement);
	playerShadow += Movement;
	//Kind of Collision
	if (map.Get_Type(playerShadow + PlayerPosOffSet) == "Wall")
	{

	}
	else if (map.Get_Type(playerShadow + PlayerPosOffSet) == "Floor")
	{
		PlayerPos = playerShadow;
	}

	PokeballPos = PlayerPos;
	pokeballShadow = PokeballPos;
	if (Input_PI::pointer()->IsBeingPressed[Input_PI::PokeThrowFront] == true)
	{
		pokeballShadow.y += throwSpeed * dt;
	}
	if (Input_PI::pointer()->IsBeingPressed[Input_PI::PokeThrowBack] == true)
	{

	}
	if (Input_PI::pointer()->IsBeingPressed[Input_PI::PokeThrowLeft] == true)
	{

	}
	if (Input_PI::pointer()->IsBeingPressed[Input_PI::PokeThrowRight] == true)
	{

	}

	//if (map.Get_Type(pokeballShadow) == "Wall")
	//{
	//	
	//}
	//else if (map.Get_Type(pokeballShadow) == "Floor")
	//{
	//	PokeballPos = pokeballShadow;
	//}

	//Keep Player in window
	if (PlayerPos.x > (Render_PI::Window_Scale().x - 5))
	{
		double difference = PlayerPos.x - (Render_PI::Window_Scale().x - 5);
		PlayerPosOffSet.x += difference;
		PlayerPos.x = (Render_PI::Window_Scale().x - 5);
	}
	else if (PlayerPos.x < 5)
	{
		double difference = PlayerPos.x - (5);
		PlayerPosOffSet.x += difference;
		PlayerPos.x = (5);
	}
	if (PlayerPos.y > (Render_PI::Window_Scale().y - 5))
	{
		double difference = PlayerPos.y - (Render_PI::Window_Scale().y - 5);
		PlayerPosOffSet.y += difference;
		PlayerPos.y = (Render_PI::Window_Scale().y - 5);
	}
	else if (PlayerPos.y < 5)
	{
		double difference = PlayerPos.y - (5);
		PlayerPosOffSet.y += difference;
		PlayerPos.y = (5);
	}
}

void PlayerClass::Exit()
{
	if (playerMesh != nullptr)
	{
		delete playerMesh;
		playerMesh = nullptr;
	};
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

void PlayerClass::Renderplayer()
{
	Render_PI::pointer()->modelStack_Set(true);
	Render_PI::pointer()->RenderMeshIn2D(Texture::Get("Something"), false, Vector3(PlayerPos), Vector3(getPlayerScale()));
	Render_PI::pointer()->modelStack_Set(false);
}

void PlayerClass::RenderPokeball()
{
	Render_PI::pointer()->modelStack_Set(true);
	Render_PI::pointer()->RenderMeshIn2D(Texture::Get("Something"), false, Vector3(PokeballPos), Vector3(getPlayerScale()));
	Render_PI::pointer()->modelStack_Set(false);
}