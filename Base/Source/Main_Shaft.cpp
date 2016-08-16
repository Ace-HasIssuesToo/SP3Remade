#include"Main_Shaft.h"
#include "Game_System.h"
#include "Input_PI.h"
#include "Texture_PI.h"
#include "Player.h"

Main_Shaft* Main_Shaft::c_pointer = new Main_Shaft();

void Main_Shaft::Init()
{
	Texture::Init();
	Render_PI::pointer()->Init();
	Input_PI::pointer()->Init();
	Game_System::pointer()->Init();
	PlayerClass::pointer()->Init();
}

void Main_Shaft::Update(double dt)
{
	//std::cout << 1 / dt << std::endl;
	Input_PI::pointer()->Update(dt);
	Game_System::pointer()->Update(dt);
	PlayerClass::pointer()->Update(dt);
}


void Main_Shaft::Render()
{
	Render_PI::pointer()->Render_Set();
	Render_PI::pointer()->Fog_Set(true);
	Game_System::pointer()->Render();
	Render_PI::pointer()->Fog_Set(false);
	PlayerClass::pointer()->Renderplayer();
}

void Main_Shaft::Exit()
{
	Render_PI::pointer()->Exit();
	Input_PI::pointer()->Exit();
	Game_System::pointer()->Exit();
	Texture::Exit();
}
