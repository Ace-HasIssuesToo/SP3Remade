#include "Game_System.h"
#include "Texture_PI.h"
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
	Camera_PI camera;
	camera.Init(Vector3(10, 0, 0), Vector3(), Vector3(0, 1, 0), 0, 0);
	Render_PI::pointer()->Camera_Set(camera);
	GameState::pointer()->Init();
	//Pokemon_Switch = 0;
}

void Game_System::Update(double dt)
{
	GameState::pointer()->Update(dt);
}

void Game_System::Render()
{
<<<<<<< HEAD
	PlayerClass::pointer()->Renderplayer();
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
	//if (state == INTRODUCTION)
	//{
	//	Render_PI::
	//}
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
=======
	GameState::pointer()->Render();
>>>>>>> 6b89acb7a3fa10edec97da3075947d2ef5d46132
}

void Game_System::Exit()
{
	if (c_pointer != nullptr)
	{
		delete c_pointer;
		c_pointer = nullptr;
	}
}
