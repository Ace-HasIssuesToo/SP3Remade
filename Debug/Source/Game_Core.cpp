#include"Game_Core.h"
#include "Start_Scene.h"
#include "Enemy_Scene.h"
#include "Gun_Scene.h"
#include "Sound_Scene.h"

Game_Core* Game_Core::c_pointer = new Game_Core();

void Game_Core::Init()
{
	Game_Model::pointer()->Init();
	Input_Controller::pointer()->Init();
	Scene* pointer = nullptr;
	pointer = new Sound_Scene();
	pointer->Init();
	Game_Model::pointer()->Scene_Data.push_back(pointer);
	pointer = new Light_Scene;
	pointer->Init();
	Game_Model::pointer()->Scene_Data.push_back(pointer);
	pointer = new Room_Scene;
	pointer->Init();
	Game_Model::pointer()->Scene_Data.push_back(pointer);
	pointer = new Enemy_Scene;
	pointer->Init();
	Game_Model::pointer()->Scene_Data.push_back(pointer);
	pointer = new Start_Scene;
	pointer->Init();
	Game_Model::pointer()->Scene_Data.push_back(pointer);
	pointer = new Gun_Scene;
	pointer->Init();
	Game_Model::pointer()->Scene_Data.push_back(pointer);
	pointer = nullptr;
}

void Game_Core::Update(double dt)
{
	std::cout << 1 / dt << std::endl;
	Input_Controller::pointer()->Update(dt);
	for (std::vector<Scene *>::iterator X = Game_Model::pointer()->Scene_Data.begin(); X != Game_Model::pointer()->Scene_Data.end(); ++X)
	{
		((Scene*)*X)->Update(dt);
	}
}


void Game_Core::Render()
{
	Game_Model::pointer()->Render_Set();
	Game_Model::pointer()->Fog_Set(true);
	for (std::vector<Scene *>::iterator X = Game_Model::pointer()->Scene_Data.begin(); X != Game_Model::pointer()->Scene_Data.end(); ++X)
	{
		((Scene*)*X)->Render();
	}
	Game_Model::pointer()->Fog_Set(false);
}

void Game_Core::Exit()
{
	Game_Model::pointer()->Exit();
	Input_Controller::pointer()->Exit();
	while (!Game_Model::pointer()->Scene_Data.empty())
	{
		Scene * point = Game_Model::pointer()->Scene_Data.back();
		point->Exit();
		delete point;
		Game_Model::pointer()->Scene_Data.pop_back();
	}
}
