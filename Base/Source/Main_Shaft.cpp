#include"Main_Shaft.h"
#include "Debug_PI.h"
#include "Input_PI.h"
#include "Texture_PI.h"

Main_Shaft* Main_Shaft::c_pointer = new Main_Shaft();

void Main_Shaft::Init()
{
	Texture::Init();
	Render_PI::pointer()->Init();
	Input_PI::pointer()->Init();
	Debug_PI::pointer()->Init();
}

void Main_Shaft::Update(double dt)
{
	//std::cout << 1 / dt << std::endl;
	Input_PI::pointer()->Update(dt);
	Debug_PI::pointer()->Update(dt);
}


void Main_Shaft::Render()
{
	Render_PI::pointer()->Render_Set();
	Render_PI::pointer()->Fog_Set(true);
	Debug_PI::pointer()->Render();
	Render_PI::pointer()->Fog_Set(false);
}

void Main_Shaft::Exit()
{
	Render_PI::pointer()->Exit();
	Input_PI::pointer()->Exit();
	Debug_PI::pointer()->Exit();
	Texture::Exit();
}
