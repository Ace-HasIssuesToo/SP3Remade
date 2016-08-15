#include "Enemy_Class.h"
#include "Game_Model.h"

void Enemy_Class::Create()
{
	this->Position = Vector3();
	this->state = Shut_Down;
}

void Enemy_Class::Teleport(int i)
{
	int Start = Math::Max((i*10)+1, 1);
	int X = Math::RandIntMinMax(i, i+8);
	int Z = Math::RandIntMinMax(i, i+8);
	while (Game_Model::pointer()->BluePrint[X][Z] != char(' '))
	{
		if (Z < 98)
		{
			Z++;
		}
		else if (X < 98)
		{
			X++;
			Z = 0;
		}
		else
		{
			X = Z = 0;
		}
	}
	this->Position.Set(X*Game_Model::pointer()->Game_Scale, 0.5*Game_Model::pointer()->Game_Scale, Z*Game_Model::pointer()->Game_Scale);
}

void Enemy_Class::AI_Movement(double dt)
{
	if (this->state != Shut_Down)
	{
		Vector3 Target =Game_Model::Current_Camera->camera.target;
		float New_X = 0;
		float New_Z = 0;
		if (this->state == Hunting)
		{
			if ( Target.x < this->Position.x)
			{
				this->Position.x -= (1.5* dt);
			}
			else if (Target.x > this->Position.x)
			{
				this->Position.x += (1.5* dt);
			}


			if (Target.z < this->Position.z)
			{
				this->Position.z -= (1.5* dt);
			}
			else if (Target.z > this->Position.z)
			{
				this->Position.x += (1.5* dt);
			}
		}
		else if (this->state != Stunned)
		{
			if (Target.x < this->Position.x)
			{
				 this->Position.x -= (0.5* dt);
			}
			else if (Target.x > this->Position.x)
			{
				this->Position.x += (0.5* dt);
			}


			if (Target.z < this->Position.z)
			{
				this->Position.z -= (0.5* dt);
			}
			else if (Target.z > this->Position.z)
			{
				this->Position.x += (0.5* dt);
			}
		}

	}
}