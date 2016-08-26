#ifndef PLAYER_H
#define PLAYER_H
#include "Support_Codes.h"
#include "Render_PI.h"
#include "Map_PI.h"
#include "PokeInfo.h"
#include "irrKlang.h"

class PlayerClass
{
public:
	virtual void Init();
	virtual void Update(double dt, Map* map);

	virtual void Renderplayer();
	void Exit();

	Vector3 getPlayerPos();
	Vector3 getPlayerScale();
	Vector3 getPlayerPosOffSet();
	float GetLightRange();
	enum PlayerMeshes
	{
		Left = 0,
		Right,
		Top, 
		Down,
		Idle,
	};
	void setPlayerMesh(PlayerClass::PlayerMeshes mesh);
	Mesh* getPlayerMesh2();
	void clearPlayer();
	void clearLights();
	void clearItems();
	static PlayerClass* pointer()
	{
		return m_pointer;
	}
	float return_LightPower(){ return LightPower; };
	float return_Runtime(){ return Stamina; };
	ISoundSource* Drink;
	ISoundSource* PickUp;
private:
	PlayerClass();
	~PlayerClass();

	static PlayerClass* m_pointer;

	int movementSpeed;

	Vector3 PlayerPos, PlayerPosOffSet;
	Vector3 playerShadow;
	Vector3 sc;

	PlayerMeshes playerMesh;
	Mesh* playerMeshLeft, *playerMeshRight, *playerMeshForward, *playerMeshDownward;
	Mesh* playerMeshIdle;
	float Stamina;
	float LightPower;
	float LightRange;
	float batteryTimer;
	float drinkTimer;
	bool LightOn;
	bool GetBattery;
	bool GetDrink;
	bool DrinkExists;
	bool BatteryExists;
	Mesh* RunBar;
	Mesh* LightBar;
	Mesh* Battery;
	Mesh* Drink;
};

const float Max_Speed = 6.f;
const float Max_LightRange = 4.f;
#endif