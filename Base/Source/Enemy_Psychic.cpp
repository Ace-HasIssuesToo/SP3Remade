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
	// Position of enemy
	psychicPos = (Render_PI::Window_Scale() * 0.2);

	// Psychic camouflage image
	camou_psychic = MeshBuilder::GenerateQuad("camou_psychic", Color(1, 1, 1));
	camou_psychic->textureArray[0] = LoadTGA("Data//Texture//psychic-camou.tga");
	// Psychic run sprite
	run_psychic = MeshBuilder::GenerateSpriteAnimation("run_psychic", 1, 8);
	run_psychic->textureArray[0] = LoadTGA("Data//Texture//psychic-run.tga");
	SpriteAnimation *sa1 = dynamic_cast<SpriteAnimation*>(run_psychic);
	if (sa1)
	{
		sa1->m_anim = new Animation();
		sa1->m_anim->Set(0, 7, 0, 1.f, true);
	}
	// Psychic appearance sprite
	appear_psychic = MeshBuilder::GenerateSpriteAnimation("appear_psychic", 1, 2);
	appear_psychic->textureArray[0] = LoadTGA("Data//Texture//psychic-appear.tga");
	SpriteAnimation *sa2 = dynamic_cast<SpriteAnimation*>(appear_psychic);
	if (sa2)
	{
		sa2->m_anim = new Animation();
		sa2->m_anim->Set(0, 1, 0, 5.f, true);
	}
}

void Enemy_Psychic::Update(double dt, Map* map)
{
	// Psychic run sprite
	SpriteAnimation *sa1 = dynamic_cast<SpriteAnimation*>(run_psychic);
	if (sa1)
	{
		sa1->Update(dt);
		sa1->m_anim->animActive = true;
	}
	// Psychic appearance sprite
	SpriteAnimation *sa2 = dynamic_cast<SpriteAnimation*>(appear_psychic);
	if (sa2)
	{
		sa2->Update(dt);
		sa2->m_anim->animActive = true;
	}

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
	//cout << counterFound << endl;
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
}

void Enemy_Psychic::RenderPsychic()
{
	Render_PI::pointer()->modelStack_Set(true);
	//Render_PI::pointer()->RenderMeshIn2D(Texture::Get("psychic"), false, Vector3(psychicPos), Vector3(1, 1, 1));
	//Render_PI::pointer()->RenderMeshIn2D(camou_psychic, false, Vector3(psychicPos), Vector3(5, 5, 1));
	//Render_PI::pointer()->RenderMeshIn2D(run_psychic, false, Vector3(psychicPos), Vector3(5, 5, 1));
	Render_PI::pointer()->RenderMeshIn2D(appear_psychic, false, Vector3(psychicPos), Vector3(6, 6, 1));
	Render_PI::pointer()->modelStack_Set(false);
}

void Enemy_Psychic::Exit()
{
	/*
	NOTE:
	enemy spawn rand()
	enemy sound
	kill player strategy
	counter value change to 3, limit counter for last resort
	*/
	if (c_enemyPsychic != nullptr)
	{
		delete c_enemyPsychic;
		c_enemyPsychic = nullptr;
	}
}