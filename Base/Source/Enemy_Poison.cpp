#include "Enemy_Poison.h"
#include "Texture_PI.h"
#include "Player.h"
#include "Additional_Functions.h"

Enemy_Poison* Enemy_Poison::m_pointer = new Enemy_Poison();

void  Enemy_Poison::Clear()
{
	Pos = Render_PI::Window_Scale()*0.25;
	Vel = Vector3();
	Poisonous = false;
	CoolDown = LastTime = ChangeEffect = 0;
}

void Enemy_Poison::ClearPoison()
{
	Poisonous = false;
}

void Enemy_Poison::Init()
{
	Pos = Render_PI::Window_Scale()*0.25;
	Vel = Vector3();
	Poisonous = false;
	CoolDown = LastTime = ChangeEffect = 0;
	Poisoned_effect = MeshBuilder::GenerateQuad("Poisoned", Color());
	Poisoned_effect->textureArray[0] = LoadTGA("Data//Texture//Poisoned.tga");
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

void Enemy_Poison::Update(double dt, Map* map)
{
	if (Poisonous && FlipType[ShadowClone])
	{
		for (int i = 0; i < 5; i++)
		{

			Vector3 Range = (PlayerClass::pointer()->getPlayerPosOffSet() + PlayerClass::pointer()->getPlayerPos()) - Clones[i];
			double radius = (Range.x*Range.x) + (Range.y*Range.y);
			Vector3 Velocity = (Pos - (PlayerClass::pointer()->getPlayerPosOffSet() + PlayerClass::pointer()->getPlayerPos())).Normalize()*Moving_Speed;
			if (radius > 10 * 10)
			{
				if (i % 2)
				{
					Velocity.x *= -1;
				}
				if (i % 3)
				{
					Velocity.y *= -1;
				}
				Vector3 Shadows = Clones[i] + Velocity*dt;
				if (map->Get_Type(Shadows) == "Floor")
				{
					Clones[i] = Shadows;
				}
				else
				{
					int random = rand() % 5;
					if (i == random)
					{
						Clones[i] = Pos + Velocity;
						Pos = Clones[rand() % 5] + Velocity;
					}
					else
					{
						Clones[i] = Clones[random];
					}
				}
			}
			else
			{
				int random = rand() % 5;
				if (i == random)
				{
					Clones[i] = Pos + Velocity;
					Pos = Clones[rand() % 5] + Velocity;
				}
				else
				{
					Clones[i] = Clones[random];
				}
			}
		}
	}
	SpriteAnimation *sa1 = dynamic_cast<SpriteAnimation*>(Poison_Mesh);
	if (sa1)
	{
		sa1->Update(dt);
		sa1->m_anim->animActive = true;
	}

	if (Poisonous)
	{
		//Vel = (Pos - (PlayerClass::pointer()->getPlayerPosOffSet() + PlayerClass::pointer()->getPlayerPos())).Normalize()*Moving_Speed;
		Vel = Functions::PathFinding(Pos, (PlayerClass::pointer()->getPlayerPosOffSet() + PlayerClass::pointer()->getPlayerPos()), Moving_Speed*dt, map);
	}
	else
	{
		//Vel = ((PlayerClass::pointer()->getPlayerPosOffSet() + PlayerClass::pointer()->getPlayerPos()) - Pos).Normalize()*Moving_Speed;
		Vel = Functions::PathFinding(Pos, (PlayerClass::pointer()->getPlayerPosOffSet() + PlayerClass::pointer()->getPlayerPos()), -Moving_Speed*dt, map);
	}
	cout << Pos.x << " / " << Pos.y << endl;
	if (Vel != Vector3())
	{
		Pos += Vel;
	}
	else
	{
		if (Poisonous && FlipType[ShadowClone])
		{
			int random = rand() % 5;
			Pos = Clones[random];
		}
		else
		{
			Vector3 offset = (Pos - (PlayerClass::pointer()->getPlayerPosOffSet() + PlayerClass::pointer()->getPlayerPos())).Normalize()*Moving_Speed;
			if (rand() % 2)
			{
				offset.x *= -1;
			}
			if (rand() % 3)
			{
				offset.y *= -1;
			}
			Pos = (PlayerClass::pointer()->getPlayerPosOffSet() + PlayerClass::pointer()->getPlayerPos()) + offset;
		}
	}
	/*Vector3 Shadow = Pos + Vel*dt;
	if (map->Get_Type(Shadow) == "Floor")
	{
	Pos = Shadow;
	}
	Vel *= 0.9f;
	if (Vel.x > -1 && Vel.x < 1)
	{
	Vel.x = 0;
	}
	if (Vel.y > -1 && Vel.y < 1)
	{
	Vel.y = 0;
	}

	else
	{
	if (Poisonous && FlipType[ShadowClone])
	{
	int random = rand() % 5;
	Pos = Clones[random];
	}
	else
	{
	Vector3 offset = (Pos - (PlayerClass::pointer()->getPlayerPosOffSet() + PlayerClass::pointer()->getPlayerPos())).Normalize()*Moving_Speed;
	if (rand()% 2)
	{
	offset.x *= -1;
	}
	if (rand() % 3)
	{
	offset.y *= -1;
	}
	Pos = (PlayerClass::pointer()->getPlayerPosOffSet() + PlayerClass::pointer()->getPlayerPos()) + offset;
	}
	}
	*/
	if (CoolDown == 0)
	{
		Vector3 Range = (PlayerClass::pointer()->getPlayerPosOffSet() + PlayerClass::pointer()->getPlayerPos()) - Pos;
		double radius = (Range.x*Range.x) + (Range.y*Range.y);

		if (radius < (10 * 10))
		{
			Vel = Vector3();
			CoolDown = 20;
			LastTime = 10;
			ChangeEffect = 0;
			//Poisonous = true;
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

void Enemy_Poison::render_Poison()
{
	if (Poisonous)
	{
		Render_PI::pointer()->modelStack_Set(true);
		Vector3 Render_Pos = Render_PI::Window_Scale()*0.5 + Vector3(Math::RandFloatMinMax(-4, 4), Math::RandFloatMinMax(-4, 4), 0);
		Render_PI::pointer()->RenderMeshIn2D(Poisoned_effect, false, Render_Pos, Render_PI::Window_Scale()*1.1);
		Render_PI::pointer()->modelStack_Set(false);
	}
}

void Enemy_Poison::render(Vector3 Offset)
{
		Render_PI::pointer()->modelStack_Set(true);
		Render_PI::pointer()->RenderMeshIn2D(Poison_Mesh, false, Map::Pokemon_Offset(Pos), Vector3(10, 10, 1));
		Render_PI::pointer()->modelStack_Set(false);
	if (Poisonous)
	{
		if (FlipType[ShadowClone])
		{
			for (int i = 0; i < 5; i++)
			{
				if (Map::In_Range(Clones[i], Offset))
				{
					Render_PI::pointer()->modelStack_Set(true);
					Render_PI::pointer()->RenderMeshIn2D(Poison_Mesh, false, Map::Pokemon_Offset(Clones[i]), Vector3(10, 10, 1));
					Render_PI::pointer()->modelStack_Set(false);
				}
			}
		}
	}
}

void Enemy_Poison::Exit()
{
	if (Poison_Mesh != nullptr)
	{
		delete Poison_Mesh;
		Poison_Mesh = nullptr;
	}
	if (Poisoned_effect != nullptr)
	{
		delete Poisoned_effect;
		Poisoned_effect = nullptr;
	}
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
		bool ShadowClonesBool = FlipType[ShadowClone];
		for (int i = 0; i < All_debuff; i++)
		{
			FlipType[i] = false;
		}
		FlipType[ShadowClone] = ShadowClonesBool;
		if (ChangeEffect == 0)
		{
			int random = rand() % Debuff_Effects::All_debuff;
			if (!FlipType[Debuff_Effects::ShadowClone])
			{
				random = Debuff_Effects::ShadowClone;
			}
			if (random == Debuff_Effects::ShadowClone)
			{
				if (!FlipType[Debuff_Effects::ShadowClone])
				{
					FlipType[Debuff_Effects::ShadowClone] = true;
					for (int i = 0; i < 5; i++)
					{
						Clones[i] = Pos;
					}
				}
				else
				{
					while (random = rand() % Debuff_Effects::All_debuff != ShadowClone)
					{
						FlipType[random] = true;
					}
				}
			}
			else
			{
				FlipType[random] = true;
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

Vector3 Enemy_Poison::GetPos()
{
	return Map::Pokemon_Offset(Pos);
}