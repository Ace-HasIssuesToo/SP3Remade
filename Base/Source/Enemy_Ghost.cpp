#include "Enemy_Ghost.h"
#include "Render_PI.h"
#include "Texture_PI.h"
#include "Player.h"
#include "GameState.h"
#include "SoundEngine.h"
Enemy_Ghost* Enemy_Ghost::c_Enemy_Ghost = new Enemy_Ghost();

Enemy_Ghost::Enemy_Ghost() : ghostTimer(0)
, ghostStayTimer(0)
, dirX(Math::RandFloatMinMax(-5.f, 5.f))
, dirY(Math::RandFloatMinMax(-5.f, 5.f))
, ghostPos(0, 0, 0)
, ghostShadow(0, 0, 0)
, ghostoffset(0, 0, 0)
{

}
Enemy_Ghost::~Enemy_Ghost()
{

}
void Enemy_Ghost::Init()
{
	ghostPos = (Render_PI::Window_Scale() * 0.8);
	//ghostoffset = (Math::RandFloatMinMax(5.f, 10.f), 0, Math::RandFloatMinMax(5.f, 10.f));
	ghostSprite = MeshBuilder::GenerateSpriteAnimation("gastly", 1, 8);
	ghostSprite->textureArray[0] = LoadTGA("Data//Texture//gastly.tga");
	SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>(ghostSprite);
	if (sa)
	{
		sa->m_anim = new Animation();
		sa->m_anim->Set(0, 7, 0, 1.f, true);
	}
	haunt = SoundEngine::Use()->addSoundSourceFromFile("Data//Sound//239-ghastly.mp3");
}
void Enemy_Ghost::ClearGhost()
{
	ghostTimer = ghostStayTimer = 0.0f;
	ghostPos = (Render_PI::Window_Scale() * 0.8);
	ghostShadow = Vector3(0, 0, 0);
	ghostoffset = Vector3(0, 0, 0);
	dirX = (Math::RandFloatMinMax(-5.f, 5.f));
	dirY = (Math::RandFloatMinMax(-5.f, 5.f));
}
Vector3 Enemy_Ghost::GetGhostPos()
{
	return Map::Pokemon_Offset(ghostPos);
}
Vector3 Enemy_Ghost::GetGhostOffSet()
{
	return ghostoffset;
}
Vector3 Enemy_Ghost::Freeze(Vector3 Movement)
{
	if (ghostStayTimer > 0.0f)
	{
		Movement = Vector3(0, 0, 0);
	}
	return Movement;
}
void Enemy_Ghost::Update(double dt, Map* map)
{
	ghostShadow = ghostPos;
	
	//ghost will move randomly until every 10 seconds
	ghostTimer += dt;
	ghostShadow.x += dirX * dt;
	ghostShadow.y += dirY * dt;
	Vector3 Shadows = ghostShadow;
	if (dirX > 0)
	{
		Shadows.x += 0.5;
	}
	if (dirX < 0)
	{
		Shadows.x -= 0.5;
	}
	if (dirY > 0)
	{
		Shadows.y += 0.5;
	}
	if (dirY < 0)
	{
		Shadows.y -= 0.5;
	}
	if (map->Get_Type(Shadows) == "Wall")
	{
		dirX = -dirX;
		dirY = -dirY;
		dirX += Math::RandFloatMinMax(-5, 5);
		dirY += Math::RandFloatMinMax(-5, 5);
	}
	else if (map->Get_Type(Shadows) == "Floor" )
	{
		ghostPos = ghostShadow;
	}
	if (ghostTimer > 30.f)
	{
		//teleport ghost to player position
		if (ghostStayTimer == 0.0f)
		{
			//teleport first time
			ghostPos = (PlayerClass::pointer()->getPlayerPosOffSet() + PlayerClass::pointer()->getPlayerPos());
			SoundEngine::Use()->play2D(haunt);
		}
		ghostStayTimer += dt;
		dirX = 0;
		dirY = 0;
		if (ghostStayTimer > 2.5f)
		{
			//ghost will move away again
			dirX += Math::RandFloatMinMax(-5, 5);
			dirY += Math::RandFloatMinMax(-5, 5);
			ghostShadow.x += dirX * dt;
			ghostShadow.y += dirY * dt;
			ghostTimer = 0.0f;
		}
	}
	else if (ghostTimer < 30.f)
	{
		ghostStayTimer = 0.0f;
	}
	SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>(ghostSprite);
	if (sa)
	{
		sa->Update(dt);
		sa->m_anim->animActive = true;
	}
}
void Enemy_Ghost::RenderGhost()
{
	//ghost will disppear when it is on top of the player
	if (ghostStayTimer == 0.0f)
	{
		Vector3 Diff = Render_PI::Window_Scale() - ghostPos;
		Render_PI::pointer()->modelStack_Set(true);
		Render_PI::pointer()->RenderMeshIn2D(ghostSprite, false, Map::Pokemon_Offset(ghostPos), Vector3(10, 10, 1));
		Render_PI::pointer()->modelStack_Set(false);
	}
	/*std::ostringstream ss;
	ss.precision(5);
	ss << "Life: " << life;
	Render_PI::pointer()->RenderTextOnScreen(Game_System::pointer()->GetText(), ss.str(), Color(1, 0.25f, 0), Render_PI::Window_Scale() * 0.3, Vector3(5, 5, 1));*/
}
void Enemy_Ghost::Exit()
{
	if (haunt != nullptr)
	{
		//haunt->drop();
		haunt = nullptr;
	}
	
	if (ghostSprite != nullptr)
	{
		SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>(ghostSprite);
		if (sa)
		{
			delete sa->m_anim;
			sa->m_anim = nullptr;
		}
		delete ghostSprite;
		ghostSprite = nullptr;
	}
	
	if (c_Enemy_Ghost != nullptr)
	{
		delete c_Enemy_Ghost;
		c_Enemy_Ghost = nullptr;
	}
}
