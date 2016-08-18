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

	// Poison sprite
	Poison_Mesh = MeshBuilder::GenerateSpriteAnimation("Poison", 1, 8);
	Poison_Mesh->textureArray[0] = LoadTGA("Data//Texture//Poison.tga");
	SpriteAnimation *sa1 = dynamic_cast<SpriteAnimation*>(Poison_Mesh);
	if (sa1)
	{
		sa1->m_anim = new Animation();
		sa1->m_anim->Set(0, 7, 0, 1.f, true);
	}
}

void Enemy_Poison::Update(float dt, Map* map)
{
		SpriteAnimation *sa1 = dynamic_cast<SpriteAnimation*>(Poison_Mesh);
		if (sa1)
		{
			sa1->Update(dt);
			sa1->m_anim->animActive = true;
		}
	if (Vel == Vector3())
	{
		float Speed = 20;
		if (Poisonous)
		{
			Vel = (Pos - Map::Pokemon_Offset(PlayerClass::pointer()->getPlayerPos())).Normalize()*Speed;
		}
		else
		{
			Vel = (Map::Pokemon_Offset(PlayerClass::pointer()->getPlayerPos()) - Pos).Normalize()*Speed;
		}
	}
	Vector3 Shadow = Pos + Vel*dt;
	Vel *= 0.9;
	if (Vel.x > -1 && Vel.x < 1)
	{
		Vel.x = 0;
	}
	if (Vel.y > -1 && Vel.y < 1)
	{
		Vel.y = 0;
	}
	if (map->Get_Type(Shadow) == "Floor")
	{
		//Pos = Shadow;
	}
	else
	{
		Vel = Vector3();
	}

	if (CoolDown == 0)
	{
		Vector3 Range = Map::Pokemon_Offset(PlayerClass::pointer()->getPlayerPos()) - Pos;
		double radius = (Range.x*Range.x) + (Range.y*Range.y);

		if (radius < (10 * 10))
		{
			Vel = Vector3();
			CoolDown = 20;
			LastTime = 10;
			ChangeEffect = 0;
			Poisonous = true;
			for (int i = 0; i < All_debuff; i++)
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
	Vector3 Render_Pos = Map::Pokemon_Offset(Pos);
	Render_PI::pointer()->RenderMeshIn2D(Poison_Mesh, false, Render_Pos, Vector3(10, 10, 1));
	Render_PI::pointer()->modelStack_Set(false);
}

void Enemy_Poison::Exit()
{
	if (m_pointer != nullptr)
	{
		delete m_pointer;
		m_pointer = nullptr;
	}
}

Vector3 Enemy_Poison::Poison(Vector3 Movement)
{
	if (Poisonous)
	{
		if (ChangeEffect == 0)
		{
			if (rand() % 2 == 0)
			{
				FlipType[Debuff_Effects::MoonWalk] = true;
			}
			if (rand() % 2 == 0)
			{
				FlipType[Debuff_Effects::XY_swap] = true;
			}
			if (rand() % 2 == 0)
			{
				FlipType[Debuff_Effects::Speed] = true;
			}
			else if (rand() % 2 == 0)
			{
				FlipType[Debuff_Effects::Slow] = true;
			}
			ChangeEffect = 0.5;
		}


		bool No_Effects = true;
		if (FlipType[Debuff_Effects::MoonWalk])
		{
			Movement *= -1;
			No_Effects = false;
		}
		if (FlipType[Debuff_Effects::XY_swap])
		{
			float New_Y = Movement.y;
			Movement.y = Movement.x;
			Movement.x = New_Y;
			No_Effects = false;
		}
		if (FlipType[Debuff_Effects::Speed])
		{
			Movement.x *= 10 * (rand() % 3) + 2;
			Movement.y *= 10 * (rand() % 3) + 2;
			No_Effects = false;
		}
		if (FlipType[Debuff_Effects::Slow])
		{
			Movement.x *= 0.1f*float((rand() % 3) + 2);
			Movement.y *= 0.1f*float((rand() % 3) + 2);
			No_Effects = false;
		}
		if (No_Effects)
		{
			Movement *= -1;
			float New_Y = Movement.y;
			Movement.y = Movement.x;
			Movement.x = New_Y;
		}
	}

	return Movement;
}