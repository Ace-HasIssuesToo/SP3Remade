#include "Start_System.h"


void Start_System::Update(float dt)
{
	float x_dir = (Application::mouse_current_x / 600) * 160 - 80;
	float y_dir = ((600 - Application::mouse_current_y) / 400) * 120 - 60;
	Game_Model::pointer()->Mouse_Pos = { x_dir, y_dir, 0 };
	Light Temp = Game_Model::pointer()->Get_lights(0);
	Temp.spotDirection = Game_Model::pointer()->Start_cam.Get_camera().position - Game_Model::pointer()->Start_cam.Get_camera().target;
	Game_Model::pointer()->Set_lights(Temp, 0);
	float Speed = 1;
	if (Application::IsKeyPressed('W'))
	{
		Game_Model::pointer()->Start_cam.Move(dt * Speed, X->forward, false);
	}
	if (Application::IsKeyPressed('S'))
	{
		Game_Model::pointer()->Start_cam.Move(dt * Speed, X->backward, false);
	}
	if (Application::IsKeyPressed('A'))
	{
		Game_Model::pointer()->Start_cam.Move(dt * Speed, X->left, false);
	}
	if (Application::IsKeyPressed('D'))
	{
		Game_Model::pointer()->Start_cam.Move(dt * Speed, X->right, false);
	}
	Game_Model::pointer()->Start_cam.Update(dt);
	Game_Model::pointer()->Start_cam.View(dt);
}