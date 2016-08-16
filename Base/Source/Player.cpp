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
	PokeballPos = PlayerPos;
	//playerMesh = MeshBuilder::GenerateSpriteAnimation();
}

void PlayerClass::Update(double dt)
{
	if (Input_PI::pointer()->IsBeingPressed[Input_PI::All_Control])
	{
		if (Input_PI::pointer()->IsBeingPressed[Input_PI::Forward] == true)
		{
			PlayerPos.y += movementSpeed * dt;
		}
		if (Input_PI::pointer()->IsBeingPressed[Input_PI::Backward] == true)
		{
			PlayerPos.y -= movementSpeed * dt;
		}
		if (Input_PI::pointer()->IsBeingPressed[Input_PI::Leftward] == true)
		{
			PlayerPos.x -= movementSpeed * dt;
		}
		if (Input_PI::pointer()->IsBeingPressed[Input_PI::Rightward] == true)
		{
			PlayerPos.x -= movementSpeed * dt;
		}
		if (Input_PI::pointer()->IsBeingPressed[Input_PI::PokeThrow] == true)
		{

		}
		//Bounds
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
}

void PlayerClass::Renderplayer()
{
	Render_PI::pointer()->modelStack_Set(true);
	Render_PI::pointer()->RenderMeshIn2D(Texture::Get("Something"), false, Vector3(PlayerPos), Vector3(1, 1, 1));
	Render_PI::pointer()->modelStack_Set(false);
}