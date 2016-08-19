#pragma once
#include "Main_Shaft.h"
#include "Map_PI.h"
#include "Player.h"
#include "PokeInfo.h"
#include "StoryPlot.h"

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
	};
	Game state;
	//Game GetState(double dt);
	void GetState(double dt);
	void SetState(Game gamestate);
	void RenderFloors();
	void RenderScreens();

	void Init();
	void Update(double dt);
	void Render();
	void Exit();
	static GameState* pointer(){ return c_pointer; };

	Mesh* text;
	Mesh* startscreen;
	Mesh* winscreen;
	Mesh* losescreen;
	Mesh* helpscreen;

	Mesh* GetText();
private:
	GameState();
	~GameState();
	Map* Floor1;
	Map* Floor2;
	Map* Floor3;
	Map* Floor4;
	Map* Floor5;
	bool Pokemon_On_Loose[4];
	void Update_Stuffs(double dt, Map* map);
	int pokemonCount = 0;
	static GameState* c_pointer;
};