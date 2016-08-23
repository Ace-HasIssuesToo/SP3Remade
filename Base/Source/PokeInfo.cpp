#include "PokeInfo.h"

PokeballInfo* PokeballInfo::m_pointer = new PokeballInfo();

PokeballInfo::PokeballInfo()
	: ballPos(0,0,0)
	, ballDirection(0,0,0)
	, ballOnScreen(false)
	, sc(0, 0, 0)
	, vel(0, 0, 0)
	, throwSpeed(0)
	, numOfBalls(0)
{

}

PokeballInfo::~PokeballInfo()
{

}

void PokeballInfo::Init()
{
	ballPos = PlayerClass::pointer()->getPlayerPos();
	ballDirection = Vector3();
	ballOnScreen = false;
	throwSpeed = 40;
	movementTime = 0;
	sc.Set(3, 3, 3);
	numOfBalls = 100;
	pokeballmesh = MeshBuilder::GenerateQuad("Pokeball", Color(0, 0, 0), 1.f);
	pokeballmesh->textureArray[0] = LoadTGA("Data//Texture//PokeBall.tga");
}
void PokeballInfo::Update(double dt, Map* map)
{
	if (ballOnScreen == false)
	{
		if (Input_PI::pointer()->IsBeingPressed[Input_PI::PokeThrowFront] == true && numOfBalls >= 1)
		{
			ballOnScreen = true;
			ballDirection.y = throwSpeed;
			numOfBalls--;
		}
		else if (Input_PI::pointer()->IsBeingPressed[Input_PI::PokeThrowBack] == true && numOfBalls >= 1)
		{
			ballOnScreen = true;
			ballDirection.y = -throwSpeed;
			numOfBalls--;
		}
		else if (Input_PI::pointer()->IsBeingPressed[Input_PI::PokeThrowLeft] == true && numOfBalls >= 1)
		{
			ballOnScreen = true;
			ballDirection.x = -throwSpeed;
			numOfBalls--;
		}
		else if (Input_PI::pointer()->IsBeingPressed[Input_PI::PokeThrowRight] == true && numOfBalls >= 1)
		{
			ballOnScreen = true;
			ballDirection.x = throwSpeed;
			numOfBalls--;
		}
		ballPos = PlayerClass::pointer()->getPlayerPos() + PlayerClass::pointer()->getPlayerPosOffSet();
		movementTime = 0;
	}
	else
	{
		Vector3 Shadow = ballPos + (ballDirection * dt);
		if (map->Get_Type(Shadow) == "Floor")
		{
			ballPos = Shadow;
		}
		else
		{
			ballDirection *= -1;
		}
		ballDirection *= 0.989;
		if (ballDirection.x > -1 && ballDirection.x < 1)
		{
			ballDirection.x = 0;
		}
		if (ballDirection.y > -1 && ballDirection.y < 1)
		{
			ballDirection.y = 0;
		}
		if (ballDirection == Vector3())
		{
			ClearBallStatus();
		}
		else
		{
			Vector3 radius = (PlayerClass::pointer()->getPlayerPosOffSet() + PlayerClass::pointer()->getPlayerPos()) - ballPos;
			double range = radius.x*radius.x + radius.y*radius.y;
			Vector3 Scale = Render_PI::Window_Scale();
			float Max_Range = Scale.x*Scale.y*0.8;
			if (range > Max_Range)
			{
				ClearBallStatus();
			}
		}
	}
}
void PokeballInfo::setNumOfBalls(int balls)
{
	this->numOfBalls = balls;
}

Vector3 PokeballInfo::getPokeballPos()
{
	return Map::Pokemon_Offset(ballPos);
}
void PokeballInfo::ClearBallStatus()
{
	ballOnScreen = false;
	ballDirection = Vector3(0, 0, 0);
	ballPos = Vector3(-1000, -1000, 0);
}

int PokeballInfo::getNumOfBalls()
{
	return numOfBalls;
}

bool PokeballInfo::getBallStatus()
{
	return ballOnScreen;
}

void PokeballInfo::Render()
{
	if (ballOnScreen == true)
	{
		Render_PI::pointer()->modelStack_Set(true);
		Render_PI::pointer()->RenderMeshIn2D(pokeballmesh, false, Map::Pokemon_Offset(ballPos), Vector3(sc));
		Render_PI::pointer()->modelStack_Set(false);
	}
}

void PokeballInfo::Exit()
{
	if (pokeballmesh != nullptr)
	{
		delete pokeballmesh;
		pokeballmesh = nullptr;
	}
	if (m_pointer != nullptr)
	{
		delete m_pointer;
		m_pointer = nullptr;
	};

}