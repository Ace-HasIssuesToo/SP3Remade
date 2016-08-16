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
<<<<<<< HEAD
	PlayerClass::pointer()->Init();
=======
>>>>>>> ced28e260ab9fe57ed95bcf1860d7b5ecf02c9a3
}

void Main_Shaft::Update(double dt)
{
	//std::cout << 1 / dt << std::endl;
	Input_PI::pointer()->Update(dt);
	Game_System::pointer()->Update(dt);
<<<<<<< HEAD
	PlayerClass::pointer()->Update(dt);
=======
>>>>>>> ced28e260ab9fe57ed95bcf1860d7b5ecf02c9a3
}


void Main_Shaft::Render()
{
	Render_PI::pointer()->Render_Set();
	Render_PI::pointer()->Fog_Set(true);
	Game_System::pointer()->Render();
	Render_PI::pointer()->Fog_Set(false);
}

void Main_Shaft::Exit()
{
	Render_PI::pointer()->Exit();
	Input_PI::pointer()->Exit();
	Game_System::pointer()->Exit();
	Texture::Exit();
}
