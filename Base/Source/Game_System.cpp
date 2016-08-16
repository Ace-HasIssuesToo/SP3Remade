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
	Pos = Vector3();
}

void Game_System::Update(double dt)
{
	if (Application::IsKeyPressed('W'))
	{
		Pos.x += 10 * dt;
	}
	if (Application::IsKeyPressed('S'))
	{
		Pos.x -= 10 * dt;
	}
	if (Application::IsKeyPressed('D'))
	{
		Pos.y += 10 * dt;
	}
	if (Application::IsKeyPressed('A'))
	{
		Pos.y -= 10 * dt;
	}
}

void Game_System::Render()
{
	Floor1.Render(Pos);
}

void Game_System::Exit()
{

}
