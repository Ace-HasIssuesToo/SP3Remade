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
	if (!Floor1.Init("Data\\Map\\Floor1.csv"))
	{
		cout << "File Error" << endl;
	}
	PlayerClass::pointer()->Init();
	Enemy_Psychic::pointer()->Init();
	Enemy_Ghost::pointer()->Init();
	Enemy_Poison::pointer()->Init();
	Pokemon_Switch = 0;
	rest = 5;
}

void Game_System::Update(double dt)
{
<<<<<<< 5e9bcfdbfd83bc335b5ceafce3a75045d8717e22
	PlayerClass::pointer()->Update(dt, Floor1);
	Enemy_Psychic::pointer()->Update(dt, Floor1);
	Enemy_Ghost::pointer()->Update(dt, Floor1);
<<<<<<< HEAD
	//EnemyGhost::pointer()->Update(dt, Floor1);
=======
>>>>>>> 97834170ff795d8ae20d0d0a403c9d85cbcda03c
=======
	//PlayerClass::pointer()->Update(dt, Floor1);
	//Enemy_Psychic::pointer()->Update(dt, Floor1);
		//Enemy_Ghost::pointer()->Update(dt, Floor1);
>>>>>>> Solved Memory Leak Problem
	Enemy_Poison::pointer()->Update(dt, Floor1);
	if (Pokemon_Switch == 0)
	{
	}
	else if (Pokemon_Switch ==(rest))
	{
	}
	else if (Pokemon_Switch == (rest*2))
	{
	}
	else if (Pokemon_Switch == (rest*3))
	{
	}
	else if(Pokemon_Switch > (rest * 3))
	{
		Pokemon_Switch = 0;
	}
	Pokemon_Switch++;
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

	PlayerClass::pointer()->Exit();
	Enemy_Psychic::pointer()->Exit();
	Enemy_Ghost::pointer()->Exit();
	Enemy_Poison::pointer()->Exit();
	if (c_pointer != nullptr)
	{
		delete c_pointer;
		c_pointer = nullptr;
	}
}
