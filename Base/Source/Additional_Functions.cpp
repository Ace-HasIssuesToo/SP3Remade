#include "Additional_Functions.h"

Vector3 Functions::PathFinding(Vector3 Current_Pos, Vector3 Target_Pos, float Speed, Map* map)
{
	Vector3 Movement = Vector3();

	if (Current_Pos.x > Target_Pos.x)
	{
		Movement.x += Speed;
	}
	else
	{
		Movement.x -= Speed;
	}
	if (Current_Pos.y > Target_Pos.y)
	{
		Movement.y += Speed;
	}
	else
	{
		Movement.y -= Speed;
	}

	if (map->Get_Type(Current_Pos + Movement) == "Floor")
	{
		return Movement;
	}
	else
	{
		float X = Movement.x;
		Movement.x = 0;
		if (map->Get_Type(Current_Pos + Movement) == "Floor")
		{
			return Movement;
		}
		else
		{
			Movement.y = 0;
			Movement.x = X;
			if (map->Get_Type(Current_Pos + Movement) == "Floor")
			{
				return Movement;
			}
		}
	}

	return Vector3();
}