#ifndef PLAYER_H
#define PLAYER_H
#include "Support_Codes.h"
#include "Render_PI.h"
#include "Map_PI.h"

class PlayerClass
{
public:
	virtual void Init();
	virtual void Update(double dt, Map map);
	virtual void Renderplayer();
	virtual void RenderPokeball();
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
	Mesh* playerMesh;
	Vector3 playerShadow, pokeballShadow;
};

#endif