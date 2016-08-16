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
<<<<<<< HEAD
	Enemy_Ghost::pointer()->Init();
=======
	EnemyGhost::pointer()->Init();
	Enemy_Dark::pointer()->Init();
>>>>>>> Added Dark Type Enemy Class
	Pos = Vector3();
}

void Game_System::Update(double dt)
{

	PlayerClass::pointer()->Update(dt, Floor1);
<<<<<<< HEAD
	Enemy_Ghost::pointer()->Update(dt, Floor1);
	//EnemyGhost::pointer()->Update(dt, Floor1);
=======
	EnemyGhost::pointer()->Update(dt, Floor1);
	Enemy_Dark::pointer()->Update(dt, Floor1);
>>>>>>> Added Dark Type Enemy Class
	
}

void Game_System::Render()
{
	Floor1.Render(PlayerClass::pointer()->getPlayerPosOffSet());
	PlayerClass::pointer()->Renderplayer();
<<<<<<< HEAD
	Enemy_Ghost::pointer()->RenderGhost();
=======
	PlayerClass::pointer()->RenderPokeball();
	EnemyGhost::pointer()->RenderGhost();
	Enemy_Dark::pointer()->RenderEnemyDark();
>>>>>>> Added Dark Type Enemy Class
}

void Game_System::Exit()
{

}
