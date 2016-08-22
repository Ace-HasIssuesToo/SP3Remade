#include "Game_System.h"
#include "Texture_PI.h"
#include "GameState.h"
#include "GameEnvironmentEvent.h"

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
	GameState::pointer()->Init();
	GameEnvironmentEvent::pointer()->Init();
}

void Game_System::Update(double dt)
{
	GameState::pointer()->Update(dt);
	GameEnvironmentEvent::pointer()->Update(dt); 
}

void Game_System::Render()
{
	GameState::pointer()->Render();
	GameEnvironmentEvent::pointer()->Render();
}

void Game_System::Exit()
{
	GameState::pointer()->Exit();
	GameEnvironmentEvent::pointer()->Exit();
	if (c_pointer != nullptr)
	{
		delete c_pointer;
		c_pointer = nullptr;
	}
}
