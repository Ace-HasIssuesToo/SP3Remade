#include "PokeInfo.h"

PokeballInfo* PokeballInfo::m_pointer = new PokeballInfo();

PokeballInfo::PokeballInfo()
	: ballPos(0,0,0)
	, ballDirection(0,0,0)
	, ballOnScreen(false)
	, sc(0, 0, 0)
	, vel(0, 0, 0)
	, throwSpeed(0)
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

	pokeballmesh = MeshBuilder::GenerateQuad("Pokeball", Color(0, 0, 0), 1.f);
	pokeballmesh->textureArray[0] = LoadTGA("Data//Texture//PokeBall.tga");

}
void PokeballInfo::Update(double dt, Map* map)
{
	if (ballOnScreen == false)
	{
		if (Input_PI::pointer()->IsBeingPressed[Input_PI::PokeThrowFront] == true)
		{
			ballOnScreen = true;
			ballDirection.y = throwSpeed;
		}
		else if (Input_PI::pointer()->IsBeingPressed[Input_PI::PokeThrowBack] == true)
		{
			ballOnScreen = true;
			ballDirection.y = -throwSpeed;
		}
		else if (Input_PI::pointer()->IsBeingPressed[Input_PI::PokeThrowLeft] == true)
		{
			ballOnScreen = true;
			ballDirection.x = -throwSpeed;
		}
		else if (Input_PI::pointer()->IsBeingPressed[Input_PI::PokeThrowRight] == true)
		{
			ballOnScreen = true;
			ballDirection.x = throwSpeed;
		}
		ballPos = PlayerClass::pointer()->getPlayerPos() + PlayerClass::pointer()->getPlayerPosOffSet();
		movementTime = 0;
	}
	else
	{
		ballPos += ballDirection * dt;
		movementTime += dt;
		if (movementTime >= 3)
		{
			ballOnScreen = false;
			ballDirection = Vector3(0, 0, 0);
		}
	}
}
Vector3 PokeballInfo::getPokeballPos()
{
	return ballPos;
}
Vector3 PokeballInfo::getPokeballScale()
{
	return sc;
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
		Render_PI::pointer()->RenderMeshIn2D(pokeballmesh, false, Map::Pokemon_Offset(ballPos), Vector3(getPokeballScale()));
		Render_PI::pointer()->modelStack_Set(false);
	}
}

void PokeballInfo::Exit()
{
	if (m_pointer != nullptr)
	{
		delete m_pointer;
		m_pointer = nullptr;
	};

}