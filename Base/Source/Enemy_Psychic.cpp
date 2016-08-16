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