#include "Texture_PI.h"
#include "GameState.h"
#include "Enemy_Poison.h"
#include "Enemy_Psychic.h"
#include "Enemy_Ghost.h"
#include "EnemyDark.h"
#include "Sensor.h"
#include "UI_PI.h"
#include "SoundEngine.h"
#include "Event.h"
#include "DecoText.h"
#include "Vector3.h"

GameState* GameState::c_pointer = new GameState();
GameState::GameState() : text(nullptr), startscreen(nullptr), winscreen(nullptr)
, losescreen(nullptr), helpscreen(nullptr), creditscreen(nullptr)
, Floor1(nullptr), Floor2(nullptr), Floor3(nullptr), Floor4(nullptr), Floor5(nullptr)
, pokemonCount(0), cageTimer(0), isReleased(false)
, D_Scare1(nullptr), P_Scare1(nullptr)
, ScareSound(nullptr), LoseSound(nullptr), scareTime(0), LoseSoundBool(false)
, levelTimer(0), PlayTheme(false), beforePointer(0)
{

}
GameState::~GameState()
{

}
void GameState::Init()
{
	GameInIt();
	state = START;
	if (state == FLOOR5)
	{
		Event::pointer()->Set_Multiplier(0);
	}
	PlayTheme = LoseSoundBool = false;
	Floor1 = new Map();
	Floor2 = new Map();
	Floor3 = new Map();
	Floor4 = new Map();
	Floor5 = new Map();
	if (!Floor1->Init("Data\\Map\\Floor1.csv"))
	{
		cout << "File Error" << endl;
	}

	if (!Floor2->Init("Data\\Map\\Floor2.csv"))
	{
		cout << "File Error" << endl;
	}

	if (!Floor3->Init("Data\\Map\\Floor3.csv"))
	{
		cout << "File Error" << endl;
	}

	if (!Floor4->Init("Data\\Map\\Floor4.csv"))
	{
		cout << "File Error" << endl;
	}

	if (!Floor5->Init("Data\\Map\\Floor5.csv"))
	{
		cout << "File Error" << endl;
	}

	text = MeshBuilder::GenerateText("text", 16, 16);
	text->textureArray[0] = LoadTGA("Data//Texture//calibri.tga");
	text->material.kAmbient.Set(1, 0, 0);

	startscreen = MeshBuilder::GenerateQuad("startscreen", Color(0, 0, 0), 1.f);
	startscreen->textureArray[0] = LoadTGA("Data//Texture//startscreen.tga");

	winscreen = MeshBuilder::GenerateQuad("winscreen", Color(0, 0, 0), 1.f);
	winscreen->textureArray[0] = LoadTGA("Data//Texture//winscreen.tga");

	losescreen = MeshBuilder::GenerateQuad("losescreen", Color(0, 0, 0), 1.f);
	losescreen->textureArray[0] = LoadTGA("Data//Texture//losescreen.tga");

	helpscreen = MeshBuilder::GenerateQuad("helpscreen", Color(0, 0, 0), 1.f);
	helpscreen->textureArray[0] = LoadTGA("Data//Texture//helpscreen2.tga");

	creditscreen = MeshBuilder::GenerateQuad("creditscreen", Color(0, 0, 0), 1.f);
	creditscreen->textureArray[0] = LoadTGA("Data//Texture//creditscreen.tga");

	D_Scare1 = MeshBuilder::GenerateQuad("creditscreen", Color(0, 0, 0), 1.f);
	D_Scare1->textureArray[0] = LoadTGA("Data//Texture//DScare1.tga");

	P_Scare1 = MeshBuilder::GenerateQuad("creditscreen", Color(0, 0, 0), 1.f);
	P_Scare1->textureArray[0] = LoadTGA("Data//Texture//PScare1.tga");


	

	ScareSound = SoundEngine::Use()->addSoundSourceFromFile("Data//Sound//Jumpscare.mp3");
	LoseSound = SoundEngine::Use()->addSoundSourceFromFile("Data//Sound//InvoLaugh.mp3");
	LoseSound = SoundEngine::Use()->addSoundSourceFromFile("Data//Sound//LosingSound.mp3");
	scareTime = 0;
	levelTimer = 180.f;
}

void GameState::GameInIt()
{
	UI::Init();
	PlayerClass::pointer()->Init();
	Enemy_Ghost::pointer()->Init();
	Enemy_Psychic::pointer()->Init();
	Enemy_Poison::pointer()->Init();
	Enemy_Dark::pointer()->Init();
	PokeballInfo::pointer()->Init();
	Sensor::pointer()->Init();
	ReadTxtFile::pointer()->Init();
	Event::pointer()->Init();
	ReadTxtFile::pointer()->ReadFromTextFile();
}

void GameState::GameReset()
{
	cageTimer = 0;
	pokemonCount = 0;
	levelTimer = 180.f;
	isReleased = false;
	PlayerClass::pointer()->clearPlayer();
	Enemy_Ghost::pointer()->ClearGhost();
	Enemy_Psychic::pointer()->clearPsychic();
	Enemy_Poison::pointer()->ClearPoison();
	Enemy_Dark::pointer()->clearEnemyDark();
	PokeballInfo::pointer()->ClearBallStatus();
	Event::pointer()->Clear();
	Event::pointer()->Set_Multiplier(100);
	if (state == FLOOR5)
	{
		Event::pointer()->Set_Multiplier(0);
	}
	EndLevel();
}

Mesh* GameState::GetText()
{
	return text;
}

void GameState::SetState(Game gamestate)
{
	state = gamestate;
}

void GameState::Update_Pokemon(double dt, Map* map)
{
	if (state == FLOOR1)
	{
		if (Pokemon_On_Loose[0])
		{
			Enemy_Ghost::pointer()->Update(dt, map);
		}
	}
	else if (state == FLOOR2)
	{
		if (Pokemon_On_Loose[0])
		{
			Enemy_Ghost::pointer()->Update(dt, map);
		}
		if (Pokemon_On_Loose[1])
		{
			Enemy_Psychic::pointer()->Update(dt, map);
		}
	}
	else if (state == FLOOR3)
	{
		if (Pokemon_On_Loose[0])
		{
			Enemy_Ghost::pointer()->Update(dt, map);
		}
		if (Pokemon_On_Loose[1])
		{
			Enemy_Psychic::pointer()->Update(dt, map);
		}
		if (Pokemon_On_Loose[2])
		{
			Enemy_Poison::pointer()->Update(dt, map);
		}
	}
	else if (state == FLOOR4)
	{
		if (Pokemon_On_Loose[0])
		{
			Enemy_Ghost::pointer()->Update(dt, map);
		}
		if (Pokemon_On_Loose[1])
		{
			Enemy_Psychic::pointer()->Update(dt, map);
		}
		if (Pokemon_On_Loose[2])
		{
			Enemy_Poison::pointer()->Update(dt, map);
		}
		if (Pokemon_On_Loose[3])
		{
			Enemy_Dark::pointer()->Update(dt, map);
		}
	}
	else if (state == FLOOR5)
	{
		if (Pokemon_On_Loose[0])
		{
			Enemy_Ghost::pointer()->Update(dt, map);
		}
		if (Pokemon_On_Loose[1])
		{
			Enemy_Psychic::pointer()->Update(dt, map);
		}
		if (Pokemon_On_Loose[2])
		{
			Enemy_Poison::pointer()->Update(dt, map);
		}
		if (Pokemon_On_Loose[3])
		{
			Enemy_Dark::pointer()->Update(dt, map);
		}
	}
}
void GameState::EndLevel()
{
	if (state == FLOOR1)
	{
		for (int i = 0; i < 1; i++)
		{
			Pokemon_On_Loose[i] = false;
		}
		for (int i = 0; i < 1; i++)
		{
			pokemonCount++;
			Pokemon_On_Loose[i] = true;
		}
	}
	else if (state == FLOOR2)
	{
		for (int i = 0; i < 2; i++)
		{
			Pokemon_On_Loose[i] = false;
		}
		for (int i = 0; i < 2; i++)
		{
			pokemonCount++;
			Pokemon_On_Loose[i] = true;
		}
	}
	else if (state == FLOOR3)
	{
		for (int i = 0; i < 3; i++)
		{
			Pokemon_On_Loose[i] = false;
		}
		for (int i = 0; i < 3; i++)
		{
			pokemonCount++;
			Pokemon_On_Loose[i] = true;
		}
	}
	else if (state == FLOOR4 || state == FLOOR5)
	{
		for (int i = 0; i < 4; i++)
		{
			Pokemon_On_Loose[i] = false;
		}
		for (int i = 0; i < 4; i++)
		{
			pokemonCount++;
			Pokemon_On_Loose[i] = true;
		}
	}
}

void GameState::Update_Stuffs(double dt, Map* map)
{
	levelTimer -= dt;

	if (levelTimer <= 0.f)
	{
		state = LOSE;
	}
	Sensor::pointer()->Update(dt);
	PlayerClass::pointer()->Update(dt, map);
	cageTimer += dt;
	if (cageTimer > Math::RandFloatMinMax(10.f, 20.f) && !isReleased)
	{
		isReleased = true;
		SoundEngine::Use()->play2D("Data//Sound//Crash.mp3", false);
		Enemy_Ghost::pointer()->Pos_Set(map->Map_Rand());
		Enemy_Psychic::pointer()->Pos_Set(map->Map_Rand());
		Enemy_Poison::pointer()->Pos_Set(map->Map_Rand());
		Enemy_Dark::pointer()->Pos_Set(map->Map_Rand());
	}
	Event::pointer()->Update(dt, map);
	Update_Pokemon(dt, map);
		
	PokeballInfo::pointer()->Update(dt, map);

	Vector3 Radius = Vector3();
	double range = 0;
	float min_range = 20;
	int catchrate = rand() % 101;
	int min_catchrate = 100;
	if (PokeballInfo::pointer()->getBallStatus())
	{
		if (Pokemon_On_Loose[0])
		{
			Radius = PokeballInfo::pointer()->getPokeballPos() - Enemy_Ghost::pointer()->GetGhostPos();
			range = (Radius.x*Radius.x) + (Radius.y*Radius.y);
			if (range <= min_range)
			{
				if (catchrate < min_catchrate)
				{
					LevelCheck(0);
				}
				PokeballInfo::pointer()->ClearBallStatus();
			}
		}
		if (Pokemon_On_Loose[1])
		{
			Radius = PokeballInfo::pointer()->getPokeballPos() - Enemy_Psychic::pointer()->GetPos();
			range = (Radius.x*Radius.x) + (Radius.y*Radius.y);
			if (range <= min_range)
			{
				if (catchrate < min_catchrate)
				{
					LevelCheck(1);
				}
				PokeballInfo::pointer()->ClearBallStatus();
			}
		}
		if (Pokemon_On_Loose[2])
		{
			Radius = PokeballInfo::pointer()->getPokeballPos() - Enemy_Poison::pointer()->GetPos();
			range = (Radius.x*Radius.x) + (Radius.y*Radius.y);
			if (range <= min_range)
			{
				if (catchrate < min_catchrate)
				{
					LevelCheck(2);
				}
				PokeballInfo::pointer()->ClearBallStatus();
			}
		}
		if (Pokemon_On_Loose[3])
		{
			Radius = PokeballInfo::pointer()->getPokeballPos() - Enemy_Dark::pointer()->getEnemyDarkPos();
			range = (Radius.x*Radius.x) + (Radius.y*Radius.y);
			if (range <= min_range)
			{
				if (catchrate < min_catchrate)
				{
					LevelCheck(3);
				}
				PokeballInfo::pointer()->ClearBallStatus();
			}
		}
	}
}

void GameState::LevelCheck(int i)
{
	Pokemon_On_Loose[i] = false;
	pokemonCount--;
	if (pokemonCount <= 0 && state == FLOOR1)
	{
		SoundEngine::Use()->stopAllSounds();
		PlayTheme = false;
		state = GAMEPLAY_BEFORE;
		ReadTxtFile::pointer()->SetStorage(FLOOR2);
		ReadTxtFile::pointer()->tempGameplayFunction();
	}
	else if (pokemonCount <= 0 && state == FLOOR2)
	{
		SoundEngine::Use()->stopAllSounds();
		PlayTheme = false;
		state = GAMEPLAY_BEFORE;
		ReadTxtFile::pointer()->SetStorage(FLOOR3);
		ReadTxtFile::pointer()->tempGameplayFunction();
	}
	else if (pokemonCount <= 0 && state == FLOOR3)
	{
		SoundEngine::Use()->stopAllSounds();
		PlayTheme = false;
		state = GAMEPLAY_BEFORE;
		ReadTxtFile::pointer()->SetStorage(FLOOR4);
		ReadTxtFile::pointer()->tempGameplayFunction();
	}
	else if (pokemonCount <= 0 && state == FLOOR4)
	{
		SoundEngine::Use()->stopAllSounds();
		PlayTheme = false;
		state = GAMEPLAY_BEFORE;
		ReadTxtFile::pointer()->SetStorage(FLOOR5);
		ReadTxtFile::pointer()->tempGameplayFunction();
	}
	else if (pokemonCount <= 0 && state == FLOOR5)
	{
		SoundEngine::Use()->stopAllSounds();
		PlayTheme = false;
		state = WIN;
	}
}

void GameState::GetState(double dt)
{
	switch (state)
	{
	case START:
	{
		if (Application::IsKeyPressed('S'))
		{
			state = INTRODUCTION;
		}
		else if (Application::IsKeyPressed('H'))
		{
			state = GUIDE;
		}
		else if (Application::IsKeyPressed('C'))
		{
			state = CREDIT;
		}
		break;
	}
	case GUIDE:
	{
		if (Application::IsKeyPressed('B'))
		{
			state = START;
		}
		break;
	}
	case INTRODUCTION:
	{
		ReadTxtFile::pointer()->TimerStart = true;
		ReadTxtFile::pointer()->Update(dt);
		if (Application::IsKeyPressed(VK_RETURN))
		{
			state = FLOOR1;
			for (int i = 0; i < 1; i++)
			{
				Pokemon_On_Loose[i] = false;
			}

			for (int i = 0; i < 1; i++)
			{
				pokemonCount++;
				Pokemon_On_Loose[i] = true;
			}
			static bool sceneSkipped = false;
			if (Input_PI::pointer()->HaveBeenPressed[Input_PI::IntroSkip] && !sceneSkipped)
			{
				sceneSkipped = true;
				ReadTxtFile::pointer()->sequence = 6;
				ReadTxtFile::pointer()->bgTimer = 15.f;
				SoundEngine::Use()->stopAllSounds();
			}

			else if (Input_PI::pointer()->HaveBeenPressed[Input_PI::IntroSkip])
			{
				state = FLOOR1;
				ReadTxtFile::pointer()->clearIntro();
				ReadTxtFile::pointer()->TimerStart = false;
				if (Application::IsKeyPressed(VK_RETURN))
				{
					state = FLOOR1;
					//EndLevel();
				}
				EndLevel();
			}
		}
	case GAMEPLAY_BEFORE:
	{
		ReadTxtFile::pointer()->EnterLoop();
		int temp = ReadTxtFile::pointer()->GetStorage();
		if (bool(temp) == true)
		{
			state = (Game)temp;
			GameReset();
		}
	}
	case CREDIT:
	{
		if (Application::IsKeyPressed('B'))
		{
			state = START;
		}
		break;
	}
	case FLOOR1:
	{
		if (!PlayTheme)
		{
			SoundEngine::Use()->play2D("Data//Sound//Theme.mp3", true);
			PlayTheme = true;
		}
		Update_Stuffs(dt, Floor1);
		break;
	}
	case FLOOR2:
	{
		if (!PlayTheme)
		{
			SoundEngine::Use()->play2D("Data//Sound//Theme.mp3", true);
			PlayTheme = true;
		}
		Update_Stuffs(dt, Floor2);
		break;
	}
	case FLOOR3:
	{
		if (!PlayTheme)
		{
			SoundEngine::Use()->play2D("Data//Sound//Theme.mp3", true);
			PlayTheme = true;
		}
		Update_Stuffs(dt, Floor3);
		break;
	}
	case FLOOR4:
	{
		if (!PlayTheme)
		{
			SoundEngine::Use()->play2D("Data//Sound//Theme.mp3", true);
			PlayTheme = true;
		}
		Update_Stuffs(dt, Floor4);
		break;
	}
	case FLOOR5:
	{
		if (!PlayTheme)
		{
			SoundEngine::Use()->play2D("Data//Sound//Theme.mp3", true);
			PlayTheme = true;
		}
		Update_Stuffs(dt, Floor5);
		break;
	}
	case WIN:
	{
		if (Application::IsKeyPressed(VK_RETURN))
		{
			GameReset();
			PlayerClass::pointer()->clearLights();
			PlayerClass::pointer()->clearItems();
			state = START;
		}
		break;
	}
	case LOSE:
	{
		if (Application::IsKeyPressed('R'))
		{
			GameReset();
			PlayerClass::pointer()->clearLights();
			PlayerClass::pointer()->clearItems();
		}
		if (LoseSoundBool)
		{
			SoundEngine::Use()->play2D(LoseSound, false);
			LoseSoundBool = false;
		}
		break;
	}
	case JUMPSCARE_D:
	{
		scareTime += (dt);
		if (scareTime > 5.f)
		{
			state = LOSE;
		}
		if (!LoseSoundBool)
		{
			SoundEngine::Use()->play2D(ScareSound, false);
			LoseSoundBool = true;
		}
		break;
	}
	case JUMPSCARE_P:
	{
		scareTime += (dt);
		if (scareTime >= 6)
		{
			state = LOSE;
		}
		if (!LoseSoundBool)
		{
			SoundEngine::Use()->play2D(ScareSound, false);
			LoseSoundBool = true;
		}
		break;
	}
	break;

	}
	}
}

void GameState::Update(double dt)
{
	GetState(dt);
	ReadTxtFile::pointer()->Update(dt);
	//cout <<  << endl;
}

void GameState::RenderScreens()
{
	if (state == START)
	{
		Render_PI::pointer()->modelStack_Set(true);
		Render_PI::pointer()->modelStack_Define(Vector3(Render_PI::Window_Scale().x * 0.5, Render_PI::Window_Scale().y * 0.5, 1), 0, 0, Vector3(150, 100, 1));
		Render_PI::pointer()->RenderMesh(startscreen, false);
		Render_PI::pointer()->modelStack_Set(false);
	}
	if (state == GUIDE)
	{
		Render_PI::pointer()->modelStack_Set(true);
		Render_PI::pointer()->modelStack_Define(Vector3(Render_PI::Window_Scale().x * 0.5, Render_PI::Window_Scale().y * 0.5, 1), 0, 0, Vector3(134, 100, 1));
		Render_PI::pointer()->RenderMesh(helpscreen, false);
		Render_PI::pointer()->modelStack_Set(false);
	}
	if (state == INTRODUCTION)
	{
		ReadTxtFile::pointer()->RenderForIntro();
		ReadTxtFile::pointer()->MusicInit();
	}
	if (state == GAMEPLAY_BEFORE)
	{
		ReadTxtFile::pointer()->RenderForGameplay();
	}
	if (state == CREDIT)
	{
		Render_PI::pointer()->modelStack_Set(true);
		Render_PI::pointer()->modelStack_Define(Vector3(Render_PI::Window_Scale().x * 0.5, Render_PI::Window_Scale().y * 0.5, 1), 0, 0, Vector3(140, 90, 1));
		Render_PI::pointer()->RenderMesh(creditscreen, false);
		Render_PI::pointer()->modelStack_Set(false);
	}
	if (state == WIN)
	{
	}
	if (state == LOSE)
	{
		Render_PI::pointer()->modelStack_Set(true);
		Render_PI::pointer()->modelStack_Define(Vector3(Render_PI::Window_Scale().x * 0.5, Render_PI::Window_Scale().y * 0.5, 1), 0, 0, Vector3(150, 100, 1));
		Render_PI::pointer()->RenderMesh(losescreen, false);
		Render_PI::pointer()->modelStack_Set(false);
	}
	if (state == JUMPSCARE_D)
	{
		Render_PI::pointer()->modelStack_Set(true);
		Render_PI::pointer()->modelStack_Define(Vector3(Render_PI::Window_Scale().x * 0.5, Render_PI::Window_Scale().y * 0.5, 1), 0, 0, Vector3(150, 100, 1));
		Render_PI::pointer()->RenderMesh(D_Scare1, false);
		Render_PI::pointer()->modelStack_Set(false);
	}
	if (state == JUMPSCARE_P)
	{
		Render_PI::pointer()->modelStack_Set(true);
		Render_PI::pointer()->modelStack_Define(Vector3(Render_PI::Window_Scale().x * 0.5, Render_PI::Window_Scale().y * 0.5, 1), 0, 0, Vector3(150, 100, 1));
		Render_PI::pointer()->RenderMesh(P_Scare1, false);
		Render_PI::pointer()->modelStack_Set(false);
	}
}

void  GameState::RenderFloorData(Map* map)
{
	if (Event::pointer()->check_Effect())
	{
		Event::pointer()->Render(Floor1, PlayerClass::pointer()->getPlayerPosOffSet());
	}
	else
	{
		map->Render(PlayerClass::pointer()->getPlayerPosOffSet(), false);

		if (state == FLOOR1 || state == FLOOR2 || state == FLOOR3 || state == FLOOR4 || state == FLOOR5)
		{
			if (Pokemon_On_Loose[0])
			{
				Enemy_Ghost::pointer()->RenderGhost();
			}
		}
		if (state == FLOOR2 || state == FLOOR3 || state == FLOOR4 || state == FLOOR5)
		{
			if (Pokemon_On_Loose[1])
			{
				Enemy_Psychic::pointer()->RenderPsychic();
			}
		}
		if (state == FLOOR3 || state == FLOOR4 || state == FLOOR5)
		{
			if (Pokemon_On_Loose[2])
			{
				Enemy_Poison::pointer()->render(PlayerClass::pointer()->getPlayerPosOffSet());
			}
		}
		if (state == FLOOR4 || state == FLOOR5)
		{
			if (Pokemon_On_Loose[3])
			{
				Enemy_Dark::pointer()->RenderEnemyDark();
			}
		}
		PokeballInfo::pointer()->Render();
		map->Render(PlayerClass::pointer()->getPlayerPosOffSet(), true);
	}
	
	PlayerClass::pointer()->Renderplayer();
	UI::Render();
}

void GameState::RenderFloors()
{
	if (state == FLOOR1)
	{
		
			RenderFloorData(Floor1);
	}
	else if (state == FLOOR2)
	{
			RenderFloorData(Floor2);
	}
	else if (state == FLOOR3)
	{
			RenderFloorData(Floor3);
	}
	else if (state == FLOOR4)
	{
			RenderFloorData(Floor4);
	}
	else if (state == FLOOR5)
	{
			RenderFloorData(Floor5);
	}
}

void GameState::Render()
{
	RenderScreens();
	RenderFloors();
	//cout << levelTimer << endl;
	//cout << pokemonCount << endl;
}

void GameState::Exit()
{
	if (c_pointer != nullptr)
	{
		UI::Exit();
		DecoText::pointer()->Exit();
		PlayerClass::pointer()->Exit();
		PokeballInfo::pointer()->Exit();
		Enemy_Psychic::pointer()->Exit();
		Enemy_Ghost::pointer()->Exit();
		Enemy_Poison::pointer()->Exit();
		Enemy_Dark::pointer()->Exit();
		Sensor::pointer()->Exit();
		ReadTxtFile::pointer()->Exit();
		Event::pointer()->Exit();
		if (text != nullptr)
		{
			delete text;
			text = nullptr;
		}
		if (startscreen != nullptr)
		{
			delete startscreen;
			startscreen = nullptr;
		}
		if (helpscreen != nullptr)
		{
			delete helpscreen;
			helpscreen = nullptr;
		}
		if (creditscreen != nullptr)
		{
			delete creditscreen;
			creditscreen = nullptr;
		}
		if (winscreen != nullptr)
		{
			delete winscreen;
			winscreen = nullptr;
		}
		if (losescreen != nullptr)
		{
			delete losescreen;
			losescreen = nullptr;
		}
		
		if (Floor1 != nullptr)
		{
			Floor1->Clear();
			delete Floor1;
			Floor1 = nullptr;
		}
		if (Floor2 != nullptr)
		{
			Floor2->Clear();
			delete Floor2;
			Floor2 = nullptr;
		}
		if (Floor3 != nullptr)
		{
			Floor3->Clear();
			delete Floor3;
			Floor3 = nullptr;
		}
		if (Floor4 != nullptr)
		{
			Floor4->Clear();
			delete Floor4;
			Floor4 = nullptr;
		}
		if (Floor5 != nullptr)
		{
			Floor5->Clear();
			delete Floor5;
			Floor5 = nullptr;
		}
		if (D_Scare1 != nullptr)
		{
			delete D_Scare1;
			D_Scare1 = nullptr;
		}
		if (P_Scare1 != nullptr)
		{
			delete P_Scare1;
			P_Scare1 = nullptr;
		}
		delete c_pointer;
		c_pointer = nullptr;
	}
}