#ifndef PLAYER_H
#define PLAYER_H
#include "Support_Codes.h"
#include "Render_PI.h"
#include "Map_PI.h"

class PlayerClass
{
public:
	virtual void Init();
	virtual void Update(double dt, Map* map);
	virtual void Renderplayer();
	virtual void RenderPokeball();
<<<<<<< HEAD

=======
	void Exit();
>>>>>>> 725b3b555616dd3994b19d0f9335df5f03ab3aa3
	Vector3 getPlayerPos();
	Vector3 getPlayerScale();
	Vector3 getPlayerPosOffSet();

	enum PlayerMeshes
	{
		Left = 0,
		Right,
		Top, 
		Down
	};

	void setPlayerMesh(PlayerClass::PlayerMeshes mesh);
	Mesh* getPlayerMesh2();

	static PlayerClass* pointer()
	{
		return m_pointer;
	}
private:
	PlayerClass();
	~PlayerClass();

	static PlayerClass* m_pointer;

	int movementSpeed;
	double throwSpeed;

	Vector3 PlayerPos, PokeballPos, PlayerPosOffSet;
	Vector3 playerShadow, pokeballShadow;
	Vector3 sc;

	PlayerMeshes playerMesh;
	PlayerMeshes playerMeshString;
	Mesh* playerMeshLeft, *playerMeshRight, *playerMeshForward, *playerMeshDownward;
};

#endif