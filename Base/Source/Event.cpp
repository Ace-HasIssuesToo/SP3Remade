#include "Event.h"
#include "GameState.h"
#include "Enemy_Poison.h"
#include "Enemy_Psychic.h"
#include "Enemy_Ghost.h"
#include "EnemyDark.h"
#include "SoundEngine.h"

Event* Event::m_pointer = new Event();

void Event::Init()
{
	current_Effect = No_Effect;
	Effect_Time = 0;
	RandMultiplier =100;
	FlashDelay = 0;
}

void Event::Clear()
{
	current_Effect = No_Effect;
	Effect_Time = 0;
	RandMultiplier = 100;
	FlashDelay = 0;
}

void Event::Update(double dt, Map* map)
{
	if (bool(current_Effect))
	{
		Effect_Time -= dt;
		if (current_Effect == Lightning)
		{
			if (FlashDelay <= 0)
			{
			Black = !Black;
			FlashDelay = 0.1f;
			}
			FlashDelay -= dt;
		}
		if (Effect_Time <= 0)
		{
			Effect_Time = 0;
			current_Effect = No_Effect;
		}
	}
	else
	{
		Black = true;
		RandMultiplier = Math::Max(RandMultiplier, (int)All_Effect);
		Effect_Time = rand() % RandMultiplier;
		if (Effect_Time >= All_Effect)
		{
			Effect_Time = 0;
		}
		else if (current_Effect == Lightning)
		{
			Effect_Time = Math::RandFloatMinMax(0.3f, 0.5f);
			FlashDelay = 0;
			SoundEngine::Use()->play2D("Data//Sound//Thunder.mp3", false);
		}
		else if (current_Effect == BlackOut)
		{
			Effect_Time = Math::RandFloatMinMax(2.f, 10.f);
		}
		else if (current_Effect == Stun)
		{
			Effect_Time = Math::RandFloatMinMax(2.f, 4.f);
			if (!GameState::pointer()->checkcaged())
			{
				Enemy_Ghost::pointer()->Pos_Set(map->Map_Rand());
				Enemy_Psychic::pointer()->Pos_Set(map->Map_Rand());
				Enemy_Poison::pointer()->Pos_Set(map->Map_Rand());
				Enemy_Dark::pointer()->Pos_Set(map->Map_Rand());
			}
		}
	}

	if (!bool(current_Effect))
	{
		if (Application::IsKeyPressed('I'))
		{
			current_Effect = Lightning;
			Effect_Time = Math::RandFloatMinMax(0.3f, 0.5f);
			FlashDelay = 0;
		}
		else if (Application::IsKeyPressed('O'))
		{
			current_Effect = BlackOut;
			Effect_Time = Math::RandFloatMinMax(2.f, 4.f);
		}
		else if (Application::IsKeyPressed('P'))
		{
			current_Effect = BlackOut;
			Effect_Time = Math::RandFloatMinMax(2.f, 10.f);
		}
	}
}

void Event::Render(Map* map, Vector3 pos)
{
	map->RenderEvent(pos, Black);
}

void Event::Exit()
{
	delete m_pointer;
}
