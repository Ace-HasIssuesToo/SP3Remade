#ifndef PLAYER_H
#define PLAYER_H
#include "Support_Codes.h"
#include "Render_PI.h"
#include "Map_PI.h"
#include "PokeInfo.h"

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
		Down
	};

	void setPlayerMesh(PlayerClass::PlayerMeshes mesh);
	Mesh* getPlayerMesh2();
	void clearPlayer();
	static PlayerClass* pointer()
	{
		return m_pointer;
	}
private:
	PlayerClass();
	~PlayerClass();

	static PlayerClass* m_pointer;

	int movementSpeed;

	Vector3 PlayerPos, PokeballPos, PlayerPosOffSet;
	Vector3 playerShadow, pokeballShadow;
	Vector3 sc;

	PlayerMeshes playerMesh;
	Mesh* playerMeshLeft, *playerMeshRight, *playerMeshForward, *playerMeshDownward;
	float Runtime;
	float LightPower;
	float LightRange;
	bool LightOn;
	Mesh* RunBar;
	Mesh* LightBar;
};

const float Max_Speed = 6.f;
#endif