#include "Sensor.h"
#include "Player.h"
#include "Enemy_Poison.h"
#include "Enemy_Psychic.h"
#include "Enemy_Ghost.h"
#include "EnemyDark.h"
#include "GameState.h"


Sensor* Sensor::m_pointer = new Sensor();

void Sensor::Init()
{
	float Speed = 1.f;
	Save = MeshBuilder::GenerateSpriteAnimation("Save", 1, 8);
	Save->textureArray[0] = LoadTGA("Data//Texture//Save.tga");
	SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>(Save);
	if (sa)
	{
		sa->m_anim = new Animation();
		sa->m_anim->Set(0, 7, 0, Speed, true);
	}

	Danger = MeshBuilder::GenerateSpriteAnimation("Danger", 1, 8);
	Danger->textureArray[0] = LoadTGA("Data//Texture//Danger.tga");
	sa = dynamic_cast<SpriteAnimation*>(Danger);
	if (sa)
	{
		sa->m_anim = new Animation();
		sa->m_anim->Set(0, 7, 0, Speed, true);
	}

	dead = MeshBuilder::GenerateSpriteAnimation("Dead", 1, 8);
	dead->textureArray[0] = LoadTGA("Data//Texture//Dead.tga");
	sa = dynamic_cast<SpriteAnimation*>(dead);
	if (sa)
	{
		sa->m_anim = new Animation();
		sa->m_anim->Set(0, 7, 0, Speed, true);
	}
	Range = INT_MAX;
	Player_Pos = Vector3();
}

void Sensor::Mesh_Update(Mesh* mesh, double dt)
{
	SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>(mesh);
	if (sa)
	{
		sa->Update(dt);
		sa->m_anim->animActive = true;
	}
}

void Sensor::Range_Cal(Vector3 Enemy_Pos)
{
	Vector3 Dir = Player_Pos - (Enemy_Pos);
	float Temp_Range = (Dir.x*Dir.x) + (Dir.y + Dir.y);
	if (Temp_Range < Range)
	{
		Range = Temp_Range;
	}
}

void Sensor::Update(double dt)
{
	Player_Pos = PlayerClass::pointer()->getPlayerPos();
	Mesh_Update(Save, dt);
	Mesh_Update(Danger, dt);
	Mesh_Update(dead, dt);

	Range = INT_MAX;
	int state = GameState::pointer()->current_State();
	if (state == GameState::FLOOR1)
	{
		Range_Cal(Enemy_Ghost::pointer()->GetGhostPos());
	}
	else if (state == GameState::FLOOR2)
	{
		Range_Cal(Enemy_Psychic::pointer()->GetPos());
		Range_Cal(Enemy_Ghost::pointer()->GetGhostPos());
	}
	else if (state == GameState::FLOOR3)
	{
			Range_Cal(Enemy_Poison::pointer()->GetPos());
		Range_Cal(Enemy_Psychic::pointer()->GetPos());
		Range_Cal(Enemy_Ghost::pointer()->GetGhostPos());
	}
	else
	{
		Range_Cal(Enemy_Poison::pointer()->GetPos());
		Range_Cal(Enemy_Psychic::pointer()->GetPos());
		Range_Cal(Enemy_Ghost::pointer()->GetGhostPos());
		Range_Cal(Enemy_Dark::pointer()->getEnemyDarkPos());
	}
}

void Sensor::Render()
{
	int Min_Range = 50;
	Vector3 Pos = Render_PI::Window_Scale();
	Pos.y = 15;
	Pos.x *= 0.9;
	Render_PI::pointer()->modelStack_Set(true);
	if (Range > Min_Range*100)
	{
		Render_PI::pointer()->RenderMeshIn2D(Save, false, Pos, Vector3(20, 20, 1));
	}
	else if (Range > Min_Range*5)
	{
		Render_PI::pointer()->RenderMeshIn2D(Danger, false, Pos, Vector3(20, 20, 1));
	}
	else
	{
		Render_PI::pointer()->RenderMeshIn2D(dead, false, Pos, Vector3(20, 20, 1));
	}
	Render_PI::pointer()->modelStack_Set(false);
}

void Sensor::Exit()
{
	if (Save != nullptr)
	{
		SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>(Save);
		if (sa)
		{
			delete sa->m_anim;
		}
		delete Save;
		Save = nullptr;
	}
	if (Danger != nullptr)
	{
		SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>(Danger);
		if (sa)
		{
			delete sa->m_anim;
		}
		delete Danger;
		Danger = nullptr;
	}
	if (dead != nullptr)
	{
		SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>(dead);
		if (sa)
		{
			delete sa->m_anim;
		}
		delete dead;
		dead = nullptr;
	}
	if (m_pointer != nullptr)
	{
		delete m_pointer;
		m_pointer = nullptr;
	}
}
