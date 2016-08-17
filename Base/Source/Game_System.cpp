#include "Game_System.h"
#include "Texture_PI.h"
#include "Enemy_Poison.h"

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
	state = FLOOR1;
	if (!Floor1.Init("Data\\Map\\Floor1.csv"))
	{
		cout << "File Error" << endl;
	}
	PlayerClass::pointer()->Init();
	Enemy_Psychic::pointer()->Init();
	Enemy_Ghost::pointer()->Init();
	Enemy_Poison::pointer()->Init();
	Pos = Vector3();
}
void Game_System::LoadFloor1()
{
	
}
void Game_System::LoadFloor2()
{
	if (!Floor2.Init("Data\\Map\\Floor2.csv"))
	{
		cout << "File Error" << endl;
	}
	PlayerClass::pointer()->Init();
	Enemy_Psychic::pointer()->Init();
	Enemy_Ghost::pointer()->Init();
	Enemy_Poison::pointer()->Init();
	Pos = Vector3();
}
void Game_System::LoadFloor3()
{
	if (!Floor3.Init("Data\\Map\\Floor3.csv"))
	{
		cout << "File Error" << endl;
	}
	PlayerClass::pointer()->Init();
	Enemy_Psychic::pointer()->Init();
	Enemy_Ghost::pointer()->Init();
	Enemy_Poison::pointer()->Init();
	Pos = Vector3();
}
void Game_System::LoadFloor4()
{
	if (!Floor4.Init("Data\\Map\\Floor4.csv"))
	{
		cout << "File Error" << endl;
	}
	PlayerClass::pointer()->Init();
	Enemy_Psychic::pointer()->Init();
	Enemy_Ghost::pointer()->Init();
	Enemy_Poison::pointer()->Init();
	Pos = Vector3();
}
void Game_System::LoadFloor5()
{
	if (!Floor5.Init("Data\\Map\\Floor5.csv"))
	{
		cout << "File Error" << endl;
	}
	PlayerClass::pointer()->Init();
	Enemy_Psychic::pointer()->Init();
	Enemy_Ghost::pointer()->Init();
	Enemy_Poison::pointer()->Init();
	Pos = Vector3();
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
		case FLOOR1:
		{
			PlayerClass::pointer()->Update(dt, Floor1);
			Enemy_Psychic::pointer()->Update(dt, Floor1);
			Enemy_Ghost::pointer()->Update(dt, Floor1);
			Enemy_Poison::pointer()->Update(dt, Floor1);
			break;
		}
		case FLOOR2:
		{
			PlayerClass::pointer()->Update(dt, Floor2);
			Enemy_Psychic::pointer()->Update(dt, Floor2);
			Enemy_Ghost::pointer()->Update(dt, Floor2);
			Enemy_Poison::pointer()->Update(dt, Floor2);
			break;
		}
		case FLOOR3:
		{
			PlayerClass::pointer()->Update(dt, Floor3);
			Enemy_Psychic::pointer()->Update(dt, Floor3);
			Enemy_Ghost::pointer()->Update(dt, Floor3);
			Enemy_Poison::pointer()->Update(dt, Floor3);
			break;
		}
		case FLOOR4:
		{
			PlayerClass::pointer()->Update(dt, Floor4);
			Enemy_Psychic::pointer()->Update(dt, Floor4);
			Enemy_Ghost::pointer()->Update(dt, Floor4);
			Enemy_Poison::pointer()->Update(dt, Floor4);
			break;
		}
		case FLOOR5:
		{
			PlayerClass::pointer()->Update(dt, Floor5);
			Enemy_Psychic::pointer()->Update(dt, Floor5);
			Enemy_Ghost::pointer()->Update(dt, Floor5);
			Enemy_Poison::pointer()->Update(dt, Floor5);
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
	Floor1.Render(PlayerClass::pointer()->getPlayerPosOffSet());
	PlayerClass::pointer()->Renderplayer();
	Enemy_Ghost::pointer()->RenderGhost();
	if (Enemy_Psychic::pointer()->tempKill == false)
		Enemy_Psychic::pointer()->RenderPsychic();
	Enemy_Poison::pointer()->render();
}

void Game_System::Exit()
{

}
