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
	RandMultiplier = 100;
	FlashDelay = 0;
	LastTime = CurrentTime = 0;
}

void Event::Clear()
{
	current_Effect = No_Effect;
	Effect_Time = 0;
	RandMultiplier = 0;
	FlashDelay = 0;
	LastTime = CurrentTime = 0;
}

void Event::Update(double dt, Map* map)
{
	CurrentTime += dt;
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
	else if ((CurrentTime - LastTime) > 1.f)
	{
		LastTime = CurrentTime;
		Black = true;
		RandMultiplier = Math::Max(RandMultiplier, (int)All_Effect);
		int effect = rand() % RandMultiplier;
		if (effect >= All_Effect)
		{
			current_Effect = No_Effect;
			Black = false;
		}
		else
		{
			current_Effect = Effects(effect);
		}
		if (current_Effect == Lightning)
		{
			Effect_Time = Math::RandFloatMinMax(0.3f, 0.5f);
			FlashDelay = 0;
			SoundEngine::Use()->play2D("Data//Sound//Thunder.mp3", false);
		}
		else if (current_Effect == BlackOut)
		{
			Effect_Time = Math::RandFloatMinMax(2.f, 10.f);
			SoundEngine::Use()->play2D("Data//Sound//LightBulbCrashing.mp3", false);
		}
		else if (current_Effect == Stun)
		{
			SoundEngine::Use()->play2D("Data//Sound//RunningPokemon.mp3", false);
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

	
}

void Event::Render(Map* map, Vector3 pos)
{
	map->RenderEvent(pos, Black);
}

void Event::Exit()
{
	delete m_pointer;
}
