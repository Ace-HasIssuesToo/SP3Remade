#include "Game_System.h"
#include "Texture_PI.h"

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
	Pos = Vector3();
}

void Game_System::Update(double dt)
{

	PlayerClass::pointer()->Update(dt, Floor1);
	Enemy_Psychic::pointer()->Update(dt, Floor1);
	Enemy_Ghost::pointer()->Update(dt, Floor1);
<<<<<<< HEAD
=======
	//EnemyGhost::pointer()->Update(dt, Floor1);
>>>>>>> 83b28297b4a40a15afc409b60b47432c92a9e377
}

void Game_System::Render()
{
	Floor1.Render(PlayerClass::pointer()->getPlayerPosOffSet());
	PlayerClass::pointer()->Renderplayer();
	Enemy_Ghost::pointer()->RenderGhost();
	if (Enemy_Psychic::pointer()->tempKill == false)
		Enemy_Psychic::pointer()->RenderPsychic();
}

void Game_System::Exit()
{

}
