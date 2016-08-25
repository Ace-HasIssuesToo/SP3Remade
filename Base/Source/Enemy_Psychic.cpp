#include "Enemy_Psychic.h"
#include "Texture_PI.h"
#include "Player.h"
#include "GameState.h"
#include "SoundEngine.h"

Enemy_Psychic* Enemy_Psychic::c_enemyPsychic = new Enemy_Psychic();

Enemy_Psychic::Enemy_Psychic()
: psychicPos(Vector3(0, 0, 0)), countFound(0), playerIntrude(false), defMechanism(false), lastResort(true), locationDir(Vector3(0, 0, 0)), screamTimer(0), finalScream(false), psycho(false),
runScream(nullptr), killScream(nullptr), hide_psychic(nullptr), appear_psychic(nullptr), kill_psychic(nullptr)
{

}

Enemy_Psychic::~Enemy_Psychic()
{

}

Vector3 Enemy_Psychic::GetPos()
{
	return Map::Pokemon_Offset(psychicPos);
}

void Enemy_Psychic::clearPsychic()
{
	psycho = finalScream = screamTimer = countFound = playerIntrude = defMechanism = lastResort = 0;
	currState = STATE_HIDE;
	psychicPos = (Render_PI::Window_Scale() * 0.8);
	//psychicPos = (Render_PI::Window_Scale() * 0.25) + Vector3(0, 30, 0);
}

void Enemy_Psychic::Init()
{
	// Position of enemy
	//psychicPos = (Render_PI::Window_Scale() * 0.25) + Vector3(0, 30, 0);
	psychicPos = (Render_PI::Window_Scale() * 0.8);
	// Psychic camouflage image
	hide_psychic = MeshBuilder::GenerateQuad("hide_psychic", Color(1, 1, 1));
	hide_psychic->textureArray[0] = LoadTGA("Data//Texture//psychicHide.tga");
	// Psychic appearance sprite
	appear_psychic = MeshBuilder::GenerateSpriteAnimation("appear_psychic", 1, 2);
	appear_psychic->textureArray[0] = LoadTGA("Data//Texture//psychicAppear.tga");
	SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>(appear_psychic);
	if (sa)
	{
		sa->m_anim = new Animation();
		sa->m_anim->Set(0, 1, 0, 5.f, true);
	}
	// Psychic kill image
	kill_psychic = MeshBuilder::GenerateQuad("kill_psychic", Color(1, 1, 1));
	kill_psychic->textureArray[0] = LoadTGA("Data//Texture//psychicKill.tga");

	// Enemy State
	currState = STATE_APPEAR;
	// Sound Engine
	runScream = SoundEngine::Use()->addSoundSourceFromFile("Data//Sound//psychic_461.mp3");
}

void Enemy_Psychic::SpriteUpdate(double dt)
{
	// Psychic appearance sprite
	SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>(appear_psychic);
	if (sa)
	{
		sa->Update(dt);
		sa->m_anim->animActive = true;
	}
}

void Enemy_Psychic::Update(double dt, Map* map)
{
	SpriteUpdate(dt);

	Vector3 radiusRange;
	radiusRange = (psychicPos - (PlayerClass::pointer()->getPlayerPosOffSet() + PlayerClass::pointer()->getPlayerPos()));

	float radRange = radiusRange.x * radiusRange.x + radiusRange.y * radiusRange.y;
	
	if (radRange < 200.f)
	{
		playerIntrude = true;
		psycho = true;
		countFound++;
	}

	if (psycho)
	{
		if (playerIntrude && currState == STATE_HIDE)
		{
			defMechanism = true;
		}

		Vector3 colliDetect = psychicPos + (locationDir * dt);
		if (map->Get_Type(colliDetect) == "Floor")
		{
			psychicPos = colliDetect;
			locationDir *= 0.99;
			if (locationDir.x > -0.1 && locationDir.x < 0.1)
				locationDir.x = 0;
			if (locationDir.y > -0.1 && locationDir.y < 0.1)
				locationDir.y = 0;
		}

		// State of enemy: HIDE to APPEAR
		if (defMechanism)
		{
			currState = STATE_APPEAR;

			// Runs to another location
			locationDir = (psychicPos - (PlayerClass::pointer()->getPlayerPosOffSet() + PlayerClass::pointer()->getPlayerPos())).Normalize()*100.0;

			// Plays enemy sound: RUN
			SoundEngine::Use()->play2D(runScream);
		}

		// State of enemy: APPEAR to KILL
		if (currState == STATE_APPEAR)
		{
			playerIntrude = false;
			defMechanism = false;
			lastResort = true;

			if (lastResort && countFound > 2)
			{
				currState = STATE_KILL;

				// Plays enemy sound: KILL
				killScream = SoundEngine::Use()->play2D("Data//Sound//psychic_468.mp3", false, false, false, ESM_AUTO_DETECT, true);
				finalScream = true;

			}
		}
		//cout << lastResort << "     " << counterFound << endl;
		// Kill the player or be caught by player
		if (finalScream)
			screamTimer += (dt);
		if (screamTimer > 3.f)
		{
			//currState = STATE_GG;	//TEMP KILL/ CAUGHT
			GameState::pointer()->SetState(GameState::LOSE);
		}
	}
}

void Enemy_Psychic::RenderPsychic()
{
		Render_PI::pointer()->modelStack_Set(true);
		//if (currState == STATE_HIDE)
		//Render_PI::pointer()->RenderMeshIn2D(hide_psychic, false, Map::Pokemon_Offset(psychicPos), Vector3(6, 6, 1));
		if (currState == STATE_APPEAR)
			Render_PI::pointer()->RenderMeshIn2D(appear_psychic, false, Map::Pokemon_Offset(psychicPos), Vector3(7, 7, 1));
		if (currState == STATE_KILL)
			Render_PI::pointer()->RenderMeshIn2D(kill_psychic, false, Map::Pokemon_Offset(psychicPos), Vector3(7, 7, 1));
		if (currState == STATE_GG)
			Render_PI::pointer()->RenderMeshIn2D(hide_psychic, false, Map::Pokemon_Offset(psychicPos), Vector3(6, 6, 1));

		Render_PI::pointer()->modelStack_Set(false);
	}

void Enemy_Psychic::Exit()
{
	if (c_enemyPsychic != nullptr)
	{
		/*
		if (runScream != nullptr)
		{
		runScream->drop();
		runScream = nullptr;
		}
		if (killScream != nullptr)
		{
		killScream->drop();
		killScream = nullptr;
		}*/

		if (hide_psychic != nullptr)
		{
			SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>(hide_psychic);
			if (sa)
			{
				delete sa->m_anim;
				sa->m_anim = nullptr;
			}
			delete hide_psychic;
			hide_psychic = nullptr;
		}

		if (appear_psychic != nullptr)
		{
			SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>(appear_psychic);
			if (sa)
			{
				delete sa->m_anim;
				sa->m_anim = nullptr;
			}
			delete appear_psychic;
			appear_psychic = nullptr;
		}

		if (kill_psychic != nullptr)
		{
			SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>(kill_psychic);
			if (sa)
			{
				delete sa->m_anim;
				sa->m_anim = nullptr;
			}
			delete kill_psychic;
			kill_psychic = nullptr;
		}

		delete c_enemyPsychic;
		c_enemyPsychic = nullptr;
	}

}