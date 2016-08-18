#include "Game_System.h"
#include "Texture_PI.h"
#include "Enemy_Poison.h"
#include "GameState.h"

Game_System* Game_System::c_pointer = new Game_System();

Game_System::Game_System()
{

}

Game_System::~Game_System()
{

}

void Game_System::Init()
{
	Camera_PI camera;
	camera.Init(Vector3(10, 0, 0), Vector3(), Vector3(0, 1, 0), 0, 0);
	Render_PI::pointer()->Camera_Set(camera);
	state = FLOOR2;
	Floor1 = new Map();
	Floor2 = new Map();
	Floor3 = new Map();
	Floor4 = new Map();
	Floor5 = new Map();
	if (!Floor1->Init("Data\\Map\\Floor1.csv"))
	{
		cout << "File Error" << endl;
	}

	if (!Floor2->Init("Data\\Map\\Floor2.csv"))
	{
		cout << "File Error" << endl;
	}

	if (!Floor3->Init("Data\\Map\\Floor3.csv"))
	{
		cout << "File Error" << endl;
	}

	if (!Floor4->Init("Data\\Map\\Floor4.csv"))
	{
		cout << "File Error" << endl;
	}

	if (!Floor5->Init("Data\\Map\\Floor5.csv"))
	{
		cout << "File Error" << endl;
	}
	PlayerClass::pointer()->Init();
	Enemy_Psychic::pointer()->Init();
	Enemy_Ghost::pointer()->Init();
	Enemy_Poison::pointer()->Init();
	Enemy_Dark::pointer()->Init();
	PokeballInfo::pointer()->Init();
	Pokemon_Switch = 0;

	text = MeshBuilder::GenerateText("text", 16, 16);
	text->textureArray[0] = LoadTGA("Data//Texture//calibri.tga");
	text->material.kAmbient.Set(1, 0, 0);
}
Mesh* Game_System::GetText()
{
	return text;
}
void Game_System::GameState(double dt)
{
	switch (state)
	{
		/*case START:
		{
			if (Application::IsKeyPressed('S'))
			{
				state = FLOOR1;
				LoadFloor1();
			}
			break;
		}*/
		case GUIDE:
		{
			Render_PI::pointer()->modelStack_Set(true);

			Render_PI::pointer()->modelStack_Set(false);
			break;
		}
		case FLOOR1:
		{
			PlayerClass::pointer()->Update(dt, Floor1);
			Enemy_Psychic::pointer()->Update(dt, Floor1);
			Enemy_Ghost::pointer()->Update(dt, Floor1);
			Enemy_Poison::pointer()->Update(dt, Floor1);
			Enemy_Dark::pointer()->Update(dt, Floor1);
			PokeballInfo::pointer()->Update(dt, Floor1);
			break;
		}
		case FLOOR2:
		{
			PlayerClass::pointer()->Update(dt, Floor2);
			Enemy_Psychic::pointer()->Update(dt, Floor2);
			Enemy_Ghost::pointer()->Update(dt, Floor2);
			Enemy_Poison::pointer()->Update(dt, Floor2);
			Enemy_Dark::pointer()->Update(dt, Floor2);
			PokeballInfo::pointer()->Update(dt, Floor2);
			break;
		}
		case FLOOR3:
		{
			PlayerClass::pointer()->Update(dt, Floor3);
			Enemy_Psychic::pointer()->Update(dt, Floor3);
			Enemy_Ghost::pointer()->Update(dt, Floor3);
			Enemy_Poison::pointer()->Update(dt, Floor3);
			Enemy_Dark::pointer()->Update(dt, Floor3);
			PokeballInfo::pointer()->Update(dt, Floor3);
			break;
		}
		case FLOOR4:
		{
			PlayerClass::pointer()->Update(dt, Floor4);
			Enemy_Psychic::pointer()->Update(dt, Floor4);
			Enemy_Ghost::pointer()->Update(dt, Floor4);
			Enemy_Poison::pointer()->Update(dt, Floor4);
			Enemy_Dark::pointer()->Update(dt, Floor4);
			PokeballInfo::pointer()->Update(dt, Floor4);
			break;
		}
		case FLOOR5:
		{
			PlayerClass::pointer()->Update(dt, Floor5);
			Enemy_Psychic::pointer()->Update(dt, Floor5);
			Enemy_Ghost::pointer()->Update(dt, Floor5);
			Enemy_Poison::pointer()->Update(dt, Floor5);
			Enemy_Dark::pointer()->Update(dt, Floor5);
			PokeballInfo::pointer()->Update(dt, Floor5);
			break;
		}
		case WIN:
		{
			Render_PI::pointer()->modelStack_Set(true);

			Render_PI::pointer()->modelStack_Set(false);
			break;
		}
		case LOSE:
		{
			Render_PI::pointer()->modelStack_Set(true);

			Render_PI::pointer()->modelStack_Set(false);
			break;
		}
		break;
	}
}
void Game_System::Update(double dt)
{
	GameState(dt);
}

void Game_System::Render()
{
	Floor1->Render(PlayerClass::pointer()->getPlayerPosOffSet());
	Floor2->Render(PlayerClass::pointer()->getPlayerPosOffSet());
	PlayerClass::pointer()->Renderplayer();
	Enemy_Ghost::pointer()->RenderGhost();
	Enemy_Psychic::pointer()->RenderPsychic();
	Enemy_Poison::pointer()->render();
	Enemy_Dark::pointer()->RenderEnemyDark();
	if (PokeballInfo::pointer()->getBallStatus() == true)
		PokeballInfo::pointer()->Render();
}

void Game_System::Exit()
{

	PlayerClass::pointer()->Exit();
	Enemy_Psychic::pointer()->Exit();
	Enemy_Ghost::pointer()->Exit();
	Enemy_Poison::pointer()->Exit();
	Enemy_Dark::pointer()->Exit();
	PokeballInfo::pointer()->Exit();
	
	if (Floor1 != nullptr)
	{
		delete Floor1;
		Floor1 = nullptr;
	}
	if (Floor2 != nullptr)
	{
		delete Floor2;
		Floor2 = nullptr;
	}
	if (Floor3 != nullptr)
	{
		delete Floor3;
		Floor3 = nullptr;
	}
	if (Floor4 != nullptr)
	{
		delete Floor4;
		Floor4 = nullptr;
	}
	if (Floor5 != nullptr)
	{
		delete Floor5;
		Floor5 = nullptr;
	}
	if (c_pointer != nullptr)
	{
		delete c_pointer;
		c_pointer = nullptr;
	}
}
