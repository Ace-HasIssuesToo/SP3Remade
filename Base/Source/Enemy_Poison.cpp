#include "Enemy_Poison.h"
#include "Texture_PI.h"
#include "Player.h"

Enemy_Poison* Enemy_Poison::m_pointer = new Enemy_Poison();
void Enemy_Poison::Init()
{
	Pos = Render_PI::Window_Scale()*0.25;
	Vel = Vector3();
	Poisonous = false;
	CoolDown = LastTime = ChangeEffect = 0;
}

void Enemy_Poison::Update(float dt, Map map)
{

	cout <<CoolDown<<" / "<< LastTime << " / " << ChangeEffect << endl;
	if (Vel == Vector3())
	{
		Vel = Vector3(Math::RandFloatMinMax(-10, 10), Math::RandFloatMinMax(-10, 10), 0);
	}
	Vector3 Shadow = Pos + Vel*dt;
	Vel *= 0.99;
	if (Vel.x > -1 && Vel.x < 1)
	{
		Vel.x = 0;
	}
	if (Vel.y > -1 && Vel.y < 1)
	{
		Vel.y = 0;
	}
	if (map.Get_Type(Shadow) == "Floor")
	{
		//Pos = Shadow;
	}
	else
	{
		//Vel = Vector3(Math::RandFloatMinMax(-10, 10), Math::RandFloatMinMax(-10, 10), 0);
	}

	if (CoolDown == 0)
	{
		Vector3 Range = PlayerClass::pointer()->getPlayerPos() - Pos;
		double radius = (Range.x*Range.x) + (Range.y*Range.y);
		if (radius < (20* 20))
		{
			CoolDown = 20;
			LastTime = 10;
			ChangeEffect = 0;
			Poisonous = true;
			for (int i = 0; i < 2; i++)
			{
				FlipType[i] = false;
			}
		}
	}
	else
	{
		if (CoolDown > 0)
		{
			CoolDown -= dt;
		}
		else
		{
			CoolDown = 0;
		}

		if (LastTime > 0)
		{
			LastTime -= dt;
		}
		else
		{
			LastTime = 0;
			Poisonous = false;
		}
		if (ChangeEffect > 0)
		{
			ChangeEffect -= dt;
		}
		else
		{
			ChangeEffect = 0;
		}
	}
}

void Enemy_Poison::render()
{
	Render_PI::pointer()->modelStack_Set(true);
	Render_PI::pointer()->RenderMeshIn2D(Texture::Get("Something"), false, Vector3(Pos), Vector3(10, 10, 1));
	Render_PI::pointer()->modelStack_Set(false);
}

void Enemy_Poison::exit()
{
}

Vector3 Enemy_Poison::Poison(Vector3 Movement)
{
	if (Poisonous)
	{
		if (ChangeEffect == 0)
		{
			if (rand() % 2 == 0)
			{
				FlipType[0] = true;
			}
			else if (rand() % 2 == 0)
			{
				FlipType[1] = true;
			}
			else
			{
				FlipType[0] = true;
				FlipType[1] = true;
			}
			ChangeEffect = 1;
		}

		if (FlipType[0])
		{
			Movement *= -1;
		}
		if (FlipType[1])
		{
			float Temp = Movement.x;
			Movement.x = Movement.y;
			Movement.y = Temp;
		}
	}

	return Movement;
}