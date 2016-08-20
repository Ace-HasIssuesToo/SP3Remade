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
	for (int i = 0; i < 3; i++)
	{
		Pokemon_On_Loose[i] = false;
	}
	Camera_PI camera;
	camera.Init(Vector3(10, 0, 0), Vector3(), Vector3(0, 1, 0), 0, 0);
	Render_PI::pointer()->Camera_Set(camera);
	state = START;
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

	startscreen = MeshBuilder::GenerateQuad("startscreen", Color(0, 0, 0), 1.f);
	startscreen->textureArray[0] = LoadTGA("Data//Texture//startscreen.tga");

	winscreen = MeshBuilder::GenerateQuad("winscreen", Color(0, 0, 0), 1.f);
	winscreen->textureArray[0] = LoadTGA("Data//Texture//winscreen.tga");

	losescreen = MeshBuilder::GenerateQuad("losescreen", Color(0, 0, 0), 1.f);
	losescreen->textureArray[0] = LoadTGA("Data//Texture//losescreen.tga");

	helpscreen = MeshBuilder::GenerateQuad("helpscreen", Color(0, 0, 0), 1.f);
	helpscreen->textureArray[0] = LoadTGA("Data//Texture//helpscreen.tga");

	for (int i = 0; i < 3; i++)
	{
		Pokemon_On_Loose[i] = true;
	}
}

Mesh* Game_System::GetText()
{
	return text;
}

void Game_System::Update_Stuffs(double dt, Map* map)
{
	PlayerClass::pointer()->Update(dt, map);
	if (Pokemon_On_Loose[0])
	{
		Enemy_Psychic::pointer()->Update(dt, map);
	}
	if (Pokemon_On_Loose[1])
	{
		Enemy_Ghost::pointer()->Update(dt, map);
	}
	if (Pokemon_On_Loose[2])
	{
		Enemy_Poison::pointer()->Update(dt, map);
	}
	if (Pokemon_On_Loose[3])
	{
		Enemy_Dark::pointer()->Update(dt, map);
	}
	PokeballInfo::pointer()->Update(dt, map);

	Vector3 Radius = Vector3();
	double range = 0;
	float min_range = 10;
	int catchrate = rand() % 101; 
	int min_catchrate = 50;
	if (PokeballInfo::pointer()->getBallStatus())
	{
		if (Pokemon_On_Loose[0])
		{
			Radius = PokeballInfo::pointer()->getPokeballPos() - Enemy_Psychic::pointer()->GetPos();
			range = (Radius.x*Radius.x) + (Radius.y*Radius.y);
			if (range <= min_range)
			{
				if (catchrate > min_catchrate)
				{
					Pokemon_On_Loose[0] = false;
				}
				PokeballInfo::pointer()->ClearBallStatus();
			}
		}
		if (Pokemon_On_Loose[1])
		{
			Radius = PokeballInfo::pointer()->getPokeballPos() - Enemy_Ghost::pointer()->GetGhostPos();
			range = (Radius.x*Radius.x) + (Radius.y*Radius.y);
			if (range <= min_range)
			{
				if (catchrate > min_catchrate)
				{
					Pokemon_On_Loose[1] = false;
				}
				PokeballInfo::pointer()->ClearBallStatus();
			}
		}
		if (Pokemon_On_Loose[2])
		{
			Radius = PokeballInfo::pointer()->getPokeballPos() - Enemy_Poison::pointer()->GetPos();
			range = (Radius.x*Radius.x) + (Radius.y*Radius.y);
			if (range <= min_range)
			{
				if (catchrate > min_catchrate)
				{
					Pokemon_On_Loose[2] = false;
				}
				PokeballInfo::pointer()->ClearBallStatus();
			}
		}
		if (Pokemon_On_Loose[3])
		{
			Radius = PokeballInfo::pointer()->getPokeballPos() - Enemy_Dark::pointer()->getEnemyDarkPos();
			range = (Radius.x*Radius.x) + (Radius.y*Radius.y);
			if (range <= min_range)
			{
				if (catchrate > min_catchrate)
				{
					Pokemon_On_Loose[3] = false;
				}
				PokeballInfo::pointer()->ClearBallStatus();
			}
		}
	}
}

void Game_System::GameState(double dt)
{
	switch (state)
	{
		case START:
		{
			if (Application::IsKeyPressed('S'))
			{
				state = FLOOR1;
			}
			else if (Application::IsKeyPressed('H'))
			{
				state = GUIDE;
			}
			break;
		}
		case GUIDE:
		{
			if (Application::IsKeyPressed('B'))
			{
				state = START;
			}
			break;
		}
		case FLOOR1:
		{
					   Update_Stuffs(dt, Floor1);
			break;
		}
		case FLOOR2:
		{
					   Update_Stuffs(dt, Floor2);
			break;
		}
		case FLOOR3:
		{
					   Update_Stuffs(dt, Floor3);
			break;
		}
		case FLOOR4:
		{
					   Update_Stuffs(dt, Floor4);
			break;
		}
		case FLOOR5:
		{
					   Update_Stuffs(dt, Floor5);
			break;
		}
		case WIN:
		{
			if (Application::IsKeyPressed(VK_SPACE))
			{
				state = START;
			}
			break;
		}
		case LOSE:
		{
			if (Application::IsKeyPressed('R'))
			{
				state = START;
			}
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
	if (state == START)
	{
		Render_PI::pointer()->modelStack_Set(true);
		Render_PI::pointer()->modelStack_Define(Vector3(Render_PI::Window_Scale().x * 0.5, Render_PI::Window_Scale().y * 0.5, 1), 0, 0, Vector3(150, 100, 1));
		Render_PI::pointer()->RenderMesh(startscreen, false);
		Render_PI::pointer()->modelStack_Set(false);
	}
	if (state == GUIDE)
	{
		Render_PI::pointer()->modelStack_Set(true);
		Render_PI::pointer()->modelStack_Define(Vector3(Render_PI::Window_Scale().x * 0.5, Render_PI::Window_Scale().y * 0.5, 1), 0, 0, Vector3(134, 100, 1));
		Render_PI::pointer()->RenderMesh(helpscreen, false);
		Render_PI::pointer()->modelStack_Set(false);
	}
	if (state == FLOOR1)
	{
		Floor1->Render(PlayerClass::pointer()->getPlayerPosOffSet());
		PlayerClass::pointer()->Renderplayer();
		if (Pokemon_On_Loose[0])
		{
			Enemy_Psychic::pointer()->RenderPsychic();
		}
		if (Pokemon_On_Loose[1])
		{
			Enemy_Ghost::pointer()->RenderGhost();
		}
		if (Pokemon_On_Loose[2])
		{
			Enemy_Poison::pointer()->render();
		}
		if (Pokemon_On_Loose[3])
		{
			Enemy_Dark::pointer()->RenderEnemyDark();
		}
		PokeballInfo::pointer()->Render();
		PlayerClass::pointer()->Renderplayer();
	}
	if (state == WIN)
	{
		Render_PI::pointer()->modelStack_Set(true);
		Render_PI::pointer()->modelStack_Define(Vector3(Render_PI::Window_Scale().x * 0.5, Render_PI::Window_Scale().y * 0.5, 1), 0, 0, Vector3(150, 100, 1));
		Render_PI::pointer()->RenderMesh(winscreen, false);
		Render_PI::pointer()->modelStack_Set(false);
	}
	if (state == LOSE)
	{
		Render_PI::pointer()->modelStack_Set(true);
		Render_PI::pointer()->modelStack_Define(Vector3(Render_PI::Window_Scale().x * 0.5, Render_PI::Window_Scale().y * 0.5, 1), 0, 0, Vector3(150, 100, 1));
		Render_PI::pointer()->RenderMesh(losescreen, false);
		Render_PI::pointer()->modelStack_Set(false);
	}

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
