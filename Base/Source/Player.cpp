#include "Player.h"
#include "Input_PI.h"
#include "Render_PI.h"
#include "Texture_PI.h"

PlayerClass* PlayerClass::m_pointer = new PlayerClass;

PlayerClass::PlayerClass()
	:movementSpeed(0)
	, throwSpeed(0)
	, PlayerPos(0, 0, 0)
	, PlayerPosOffSet(0, 0, 0)
	, PokeballPos(0,0,0)
	, playerShadow(0,0,0)
	, pokeballShadow(0,0,0)
{
}

PlayerClass::~PlayerClass()
{
}

void PlayerClass::Init()
{
	movementSpeed = 10;
	throwSpeed = -9.8;
	PlayerPos = Render_PI::Window_Scale() * 0.5;
	//playerMesh = MeshBuilder::GenerateSpriteAnimation();
}

void PlayerClass::Update(double dt, Map map)
{
	playerShadow = PlayerPos;
	if (Input_PI::pointer()->IsBeingPressed[Input_PI::Forward] == true)
	{
		playerShadow.y += movementSpeed * dt;
	}
	else if (Input_PI::pointer()->IsBeingPressed[Input_PI::Backward] == true)
	{
		playerShadow.y -= movementSpeed * dt;
	}
	if (Input_PI::pointer()->IsBeingPressed[Input_PI::Leftward] == true)
	{
		playerShadow.x -= movementSpeed * dt;
	}
	else if (Input_PI::pointer()->IsBeingPressed[Input_PI::Rightward] == true)
	{
		playerShadow.x += movementSpeed * dt;
	}

	//Kind of Collision
	if (map.Get_Type(playerShadow) == "Wall")
	{

	}
	else if (map.Get_Type(playerShadow) == "Floor")
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

	if (map.Get_Type(pokeballShadow) == "Wall")
	{
		
	}
	else if (map.Get_Type(pokeballShadow) == "Floor")
	{
		PokeballPos = pokeballShadow;
	}

	//Keep Player in window
	if (PlayerPos.x > Render_PI::Window_Scale().x - 5)
	{
		double difference = PlayerPos.x - (Render_PI::Window_Scale().x - 5);
		PlayerPosOffSet += difference;
		PlayerPos = (Render_PI::Window_Scale().x - 5);
	}
	else if (PlayerPos.x < 5)
	{
		double difference = PlayerPos.x - (5);
		PlayerPosOffSet += difference;
		PlayerPos = (5);
	}
	if (PlayerPos.y > Render_PI::Window_Scale().y - 5)
	{
		double difference = PlayerPos.y - (Render_PI::Window_Scale().y - 5);
		PlayerPosOffSet += difference;
		PlayerPos = (Render_PI::Window_Scale().y - 5);
	}
	else if (PlayerPos.y < 5)
	{
		double difference = PlayerPos.y - (5);
		PlayerPosOffSet += difference;
		PlayerPos = (5);
	}
}

Vector3 PlayerClass::getPlayerPos()
{
	return PlayerPos;
}
Vector3 PlayerClass::getPlayerPosOffSet()
{
	return PlayerPosOffSet;
}

void PlayerClass::Renderplayer()
{
	Render_PI::pointer()->modelStack_Set(true);
	Render_PI::pointer()->RenderMeshIn2D(Texture::Get("Something"), false, Vector3(PlayerPos), Vector3(1, 1, 1));
	Render_PI::pointer()->modelStack_Set(false);
}

void PlayerClass::RenderPokeball()
{
	Render_PI::pointer()->modelStack_Set(true);
	Render_PI::pointer()->RenderMeshIn2D(Texture::Get("Something"), false, Vector3(PokeballPos), Vector3(1, 1, 1));
	Render_PI::pointer()->modelStack_Set(false);
}