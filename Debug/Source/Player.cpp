#include "Player.h"
#include "Application.h"
#include <iostream>
#include "Game_Model.h"

const float Jump_Force = 5;
const float Terminal_Vel = -10;
const float Max_force = 30;

void Player::Still()
{
	Angle_XZ = 0;
	Angle_Y = 0;
	Move_Vel = 0;
	Jump_Vel = 0;
	dt_check = 0;
	camera.position.y = 5 * Game_Model::pointer()->Get_Terrin_Height(camera.position.x / 100, camera.position.z / 100);
}

Vector3 Fictionlise(Vector3 Input, float fiction)
{
	if (fiction < 0)
	{
		fiction = 0;
	}
	Vector3 Output = Input;
	if (Output.x > fiction)
	{
		Output.x -= fiction;
	}
	else if (Output.x < -fiction)
	{
		Output.x += fiction;
	}
	else
	{
		Output.x = 0;
	}
	if (Output.z > fiction)
	{
		Output.z -= fiction;
	}
	else if (Output.z < -fiction)
	{
		Output.z += fiction;
	}
	else
	{
		Output.z = 0;
	}
	return Output;
};

void Player::Update(float dt)
{
	//Move Update
	//Rock Tree Log Bush

	Vector3 New_Pos = camera.position + Move_Vel;
	Move_Vel = Fictionlise(Move_Vel, 0.5);
	int i = floor(New_Pos.x);
	int j = floor(New_Pos.z);
	if (Game_Model::pointer()->Get_Forest(i, j) == char(' ') || (Game_Model::pointer()->Get_Forest(i, j) == char('B')))
	{
		camera.position = New_Pos;
	}
	else if (Game_Model::pointer()->Get_Forest(i, j) == char('L') && camera.position.y > 0.5 + 5 * Game_Model::pointer()->Get_Terrin_Height(i / 100, j / 100))
	{
		camera.position = New_Pos;
	}
	else if (Game_Model::pointer()->Get_Forest(i, j) != char('W') && camera.position.y > 1 + 5 * Game_Model::pointer()->Get_Terrin_Height(i / 100, j / 100))
	{
		camera.position = New_Pos;
	}

	//Jump Update

	//Height Update
	i = floor(camera.position.x);
	j = floor(camera.position.z);
	float Min_Height = 5 * Game_Model::pointer()->Get_Terrin_Height(camera.position.x / 100, camera.position.z / 100);
	if (Game_Model::pointer()->Get_Forest(i, j) == char(' ') || (Game_Model::pointer()->Get_Forest(i, j) == char('B')))
	{
		if (camera.position.y <= Min_Height)
		{
			camera.position.y = Min_Height;
			Jump_Vel = 0;
		}



	}
	else if (Game_Model::pointer()->Get_Forest(i, j) == char('L'))
	{
		if (camera.position.y <= Min_Height + 0.5)
		{
			camera.position.y = Min_Height + 0.5;
			Jump_Vel = 0;
		}
	}
	else if (Game_Model::pointer()->Get_Forest(i, j) != char('W'))
	{
		if (camera.position.y <= Min_Height + 1)
		{
			camera.position.y = Min_Height + 1;
			Jump_Vel = 0;
		}
	}
}

void Player::View(float dt)
{
	float x_dir = (Application::mouse_current_x / 600) * 160 - 80;
	float y_dir = ((600 - Application::mouse_current_y) / 400) * 120 - 60;
	Set_AngleXZ(x_dir * 2);
	Vector3 Calculate_View = Game_Model::pointer()->target_calculator(camera.position, 0.1, Angle_XZ, Angle_Y);
	camera.target.Set(Calculate_View.x, Calculate_View.y, Calculate_View.z);
}

void Player::Jump(float dt)
{
	if (camera.position.y == Game_Model::pointer()->Get_Terrin_Height(camera.position.x / 100, camera.position.z / 100))
	{
		Jump_Vel = Jump_Force;
	}
}

void Player::Move(float speed, int Direction, bool Run)
{
	bool collision = true;
	if (Direction == forward)
	{
		Move_Vel += Game_Model::pointer()->target_calculator(Vector3(), speed, Angle_XZ, Angle_Y);
	}
	if (Direction == backward)
	{
		Move_Vel += Game_Model::pointer()->target_calculator(Vector3(), speed, Angle_XZ + 180, Angle_Y);
	}
	if (Direction == left)
	{
		Move_Vel += Game_Model::pointer()->target_calculator(Vector3(), speed, Angle_XZ - 90, Angle_Y);
	}
	if (Direction == right)
	{
		Move_Vel += Game_Model::pointer()->target_calculator(Vector3(), speed, Angle_XZ + 90, Angle_Y);
	}

}