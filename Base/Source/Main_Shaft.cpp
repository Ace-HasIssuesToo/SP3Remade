#include"Main_Shaft.h"
#include "GameState.h"
#include "Input_PI.h"
#include "Texture_PI.h"
#include "Player.h"
#include "SoundEngine.h"


Main_Shaft* Main_Shaft::c_pointer = new Main_Shaft();




void Main_Shaft::Init()
{

	Render_PI::pointer()->Init();
	Camera_PI camera;
	camera.Init(Vector3(10, 0, 0), Vector3(), Vector3(0, 1, 0), 0, 0);
	Render_PI::pointer()->Camera_Set(camera);
	Texture::Init();
	SoundEngine::Init();
	Input_PI::pointer()->Init();
	GameState::pointer()->Init();
}

void Main_Shaft::Update(double dt)
{
	////std::cout << 1 / dt << std::endl;
	Input_PI::pointer()->Update(dt);
	GameState::pointer()->Update(dt);
}


void Main_Shaft::Render()
{ 
	Render_PI::pointer()->Render_Set();
	Render_PI::pointer()->Ortho_Set(true);
	GameState::pointer()->Render();
	Render_PI::pointer()->Ortho_Set(false);
}

void Main_Shaft::Exit()
{
	SoundEngine::Exit();
	Render_PI::pointer()->Exit();
	Input_PI::pointer()->Exit();
	Texture::Exit();
	GameState::pointer()->Exit();

	if (c_pointer != nullptr)
	{
		delete c_pointer;
		c_pointer = nullptr;
	};


}
