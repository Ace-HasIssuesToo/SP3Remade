#include "Enemy_Psychic.h"
#include "Texture_PI.h"
#include "Player.h"

Enemy_Psychic* Enemy_Psychic::c_enemyPsychic = new Enemy_Psychic();

Enemy_Psychic::Enemy_Psychic()
: psychicPos(0, 0, 0), counterFound(0), playerIntrude(false),
defMechanism(false), lastResort(false), tempKill(false)
{

}

Enemy_Psychic::~Enemy_Psychic()
{

}

void Enemy_Psychic::Init()
{
	psychicPos = (Render_PI::Window_Scale() * 0.2);
}

void Enemy_Psychic::Update(double dt, Map map)
{
<<<<<<< HEAD
	Vector3 radiusRange;
	radiusRange = (psychicPos - PlayerClass::pointer()->getPlayerPos());

	float radRange = radiusRange.x * radiusRange.x + radiusRange.y * radiusRange.y;
	if (radRange < 10.f)
		playerIntrude = true;

	if (playerIntrude)
	{
		counterFound += 1;
		defMechanism = true;
		playerIntrude = false;
	}
	cout << counterFound << endl;
	if (defMechanism && counterFound < 2)
	{
		// Runs to another location
		psychicPos = (Render_PI::Window_Scale() * 0.5);

		//play enemy sound

		defMechanism = false;
	}

	if (counterFound == 2)
	{
		//kill player
		tempKill = true;
	}

	// NOTE : defMech run instead of teleport, counter change to 3, rng PsychicPos
=======

}

void Enemy_Psychic::SetPos_x(int pos_x)
{
	this->enemyPosition.x = pos_x;
}

void Enemy_Psychic::SetPos_y(int pos_y)
{
	this->enemyPosition.y = pos_y;
}

int Enemy_Psychic::GetPos_x()
{
	return enemyPosition.x;
}

int Enemy_Psychic::GetPos_y()
{
	return enemyPosition.y;
}

bool Enemy_Psychic::detectionArea()
{
	// Tile size in world origin
	Vector3 tileSize = Render_PI::Window_Scale()*(1.f / 10.f);
	//if (enemyPosition.x)

	return true;
>>>>>>> d9580da46056991b3e2d99efafe75d1ea16d6798
}

void Enemy_Psychic::RenderPsychic()
{
	Render_PI::pointer()->modelStack_Set(true);
	Render_PI::pointer()->RenderMeshIn2D(Texture::Get("psychic"), false, Vector3(psychicPos), Vector3(1, 1, 1));
	Render_PI::pointer()->modelStack_Set(false);
}

void Enemy_Psychic::Exit()
{

}