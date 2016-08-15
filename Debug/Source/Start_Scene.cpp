#include "Start_Scene.h"

void Start_Scene::Init()
{
	float scale = Game_Model::pointer()->Game_Scale;
	Game_Model::pointer()->Current_Camera->Angle = 180;
	Game_Model::pointer()->Current_Camera->camera.Init(Vector3(1.5 * scale, 0.5 * scale, 1.5 * scale), Vector3(), Vector3(0, 1, 0));
	Game_Model::pointer()->Current_Camera->camera.target = A_A_T::Target_Cal(Game_Model::pointer()->Current_Camera->camera.position, Game_Model::pointer()->Current_Camera->Angle, 0.1);

}

void Start_Scene::Update(double dt)
{
	float Speed = 0.1;

	if (Input_Controller::pointer()->IsBeingPressed[Input_Controller::pointer()->Run])
	{
		Speed = 0.5;
	}

	if (Input_Controller::pointer()->IsBeingPressed[Input_Controller::pointer()->Forward])
	{
		Vector3 pos = A_A_T::Target_Cal(Game_Model::pointer()->Current_Camera->camera.position, Game_Model::pointer()->Current_Camera->Angle, Speed * dt);
		if (Room_Scene::Collision_Check(pos))
		{
			Game_Model::pointer()->Current_Camera->camera.position = pos;
		}
		else
		{
			Vector3 X = pos;
			X.x = Game_Model::pointer()->Current_Camera->camera.position.x;
			if (Room_Scene::Collision_Check(X))
			{
				Game_Model::pointer()->Current_Camera->camera.position = X;
			}
			else
			{
				X = pos;
				X.z = Game_Model::pointer()->Current_Camera->camera.position.z;
				if (Room_Scene::Collision_Check(X))
				{
					Game_Model::pointer()->Current_Camera->camera.position = X;
				}
			}
		}
	}
	if (Input_Controller::pointer()->IsBeingPressed[Input_Controller::pointer()->Backward])
	{
		Vector3 pos = A_A_T::Target_Cal(Game_Model::pointer()->Current_Camera->camera.position, Game_Model::pointer()->Current_Camera->Angle + 180, Speed * dt);
		if (Room_Scene::Collision_Check(pos))
		{
			Game_Model::pointer()->Current_Camera->camera.position = pos;
		}
		else
		{
			Vector3 X = pos;
			X.x = Game_Model::pointer()->Current_Camera->camera.position.x;
			if (Room_Scene::Collision_Check(X))
			{
				Game_Model::pointer()->Current_Camera->camera.position = X;
			}
			else
			{
				X = pos;
				X.z = Game_Model::pointer()->Current_Camera->camera.position.z;
				if (Room_Scene::Collision_Check(X))
				{
					Game_Model::pointer()->Current_Camera->camera.position = X;
				}
			}
		}

	}
	if (Input_Controller::pointer()->IsBeingPressed[Input_Controller::pointer()->Leftward])
	{
		Vector3 pos = A_A_T::Target_Cal(Game_Model::pointer()->Current_Camera->camera.position, Game_Model::pointer()->Current_Camera->Angle + 270, Speed * dt);
		if (Room_Scene::Collision_Check(pos))
		{
			Game_Model::pointer()->Current_Camera->camera.position = pos;
		}
		else
		{
			Vector3 X = pos;
			X.x = Game_Model::pointer()->Current_Camera->camera.position.x;
			if (Room_Scene::Collision_Check(X))
			{
				Game_Model::pointer()->Current_Camera->camera.position = X;
			}
			else
			{
				X = pos;
				X.z = Game_Model::pointer()->Current_Camera->camera.position.z;
				if (Room_Scene::Collision_Check(X))
				{
					Game_Model::pointer()->Current_Camera->camera.position = X;
				}
			}
		}
	}
	if (Input_Controller::pointer()->IsBeingPressed[Input_Controller::pointer()->Rightward])
	{
		Vector3 pos = A_A_T::Target_Cal(Game_Model::pointer()->Current_Camera->camera.position, Game_Model::pointer()->Current_Camera->Angle + 90, Speed * dt);
		if (Room_Scene::Collision_Check(pos))
		{
			Game_Model::pointer()->Current_Camera->camera.position = pos;
		}
		else
		{
			Vector3 X = pos;
			X.x = Game_Model::pointer()->Current_Camera->camera.position.x;
			if (Room_Scene::Collision_Check(X))
			{
				Game_Model::pointer()->Current_Camera->camera.position = X;
			}
			else
			{
				X = pos;
				X.z = Game_Model::pointer()->Current_Camera->camera.position.z;
				if (Room_Scene::Collision_Check(X))
				{
					Game_Model::pointer()->Current_Camera->camera.position = X;
				}
			}
		}
	}

	if (Input_Controller::pointer()->HaveBeenPressed[Input_Controller::pointer()->Light_Switch])
	{
		if (Game_Model::pointer()->lights[0].power == 0)
		{
			Game_Model::pointer()->lights[0].power = 1;
		}
		else
		{
			Game_Model::pointer()->lights[0].power = 0;
		}
	}


	float Rotate_Speed = 50;
	float Rotate = ((((Application::mouse_current_x -100)- 300) / 600));
	if (Rotate <= -0.2 || Rotate >= 0.2)
	{
		Game_Model::pointer()->Current_Camera->Angle += Rotate_Speed *Rotate*dt;
	}

	Vector3 pos = A_A_T::Target_Cal(Game_Model::pointer()->Current_Camera->camera.position, Game_Model::pointer()->Current_Camera->Angle, 0.01);
	if (Room_Scene::Collision_Check(pos))
	{
		Game_Model::pointer()->Current_Camera->camera.target = pos;
	}

	Game_Model::pointer()->lights[0].position = Position(Game_Model::pointer()->Current_Camera->camera.position.x - Game_Model::pointer()->Current_Camera->camera.target.x, Game_Model::pointer()->Current_Camera->camera.position.y - Game_Model::pointer()->Current_Camera->camera.target.y, Game_Model::pointer()->Current_Camera->camera.position.z - Game_Model::pointer()->Current_Camera->camera.target.z);
	Game_Model::pointer()->lights[0].spotDirection = Game_Model::pointer()->Current_Camera->camera.position - Game_Model::pointer()->Current_Camera->camera.target;

}

void Start_Scene::Render()
{
}

void Start_Scene::Exit()
{
}
