#pragma once
#include "Main_Shaft.h"
#include "Map_PI.h"
#include "Player.h"
#include "PokeInfo.h"
#include "Support_Codes.h"
#include "ReadTxtFile.h"
#include "irrKlang.h"

using namespace irrklang;

class GameState
{
public:
	enum Game
	{
		START,
		GUIDE,
		FLOOR1,
		FLOOR2,
		FLOOR3,
		FLOOR4,
		FLOOR5,
		LOSE,
		WIN,
		INTRODUCTION,
		GAMEPLAY,
		JUMPSCARE_D,
		JUMPSCARE_P,
		CREDIT,
	};
	Game state;
	//Game GetState(double dt);
	void GameInIt();
	void GameReset();
	void GetState(double dt);
	void SetState(Game gamestate);
	void RenderFloors();
	void RenderScreens();
	void RenderFloorData(Map* map);

	void Init();
	void Update(double dt);
	void Update_Stuffs(double dt, Map* map);
	void Update_Pokemon(double dt, Map* map);
	void Render();
	void Exit();
	bool checkcaged(){ return !isReleased; };
	Game current_State(){ return state; };
	static GameState* pointer(){ return c_pointer; };

	Mesh* text;
	Mesh* startscreen;
	Mesh* winscreen;
	Mesh* losescreen;
	Mesh* helpscreen;
	Mesh* creditscreen;

	Mesh* D_Scare1;
	Mesh* P_Scare1;

	ISoundSource* ScareSound;
	ISoundSource* LoseSound;

	Mesh* GetText();
private:
	bool LoseSoundBool;
	GameState();
	~GameState();
	Map* Floor1;
	Map* Floor2;
	Map* Floor3;
	Map* Floor4;
	Map* Floor5;
	bool Pokemon_On_Loose[4];
	
	int pokemonCount;
	float cageTimer;
	float levelTimer;
	static GameState* c_pointer;
	bool isReleased;
	float scareTime;
};