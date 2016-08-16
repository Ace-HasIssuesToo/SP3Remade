#include "Enemy_Ghost.h"
#include "Render_PI.h"
#include "Texture_PI.h"
#include "Player.h"
Enemy_Ghost* Enemy_Ghost::c_Enemy_Ghost = new Enemy_Ghost();

void Enemy_Ghost::Init()
{
	ghostPos = (Render_PI::Window_Scale() * 0.5);
	ghostoffset = (Math::RandFloatMinMax(10.f, 50.f), Math::RandFloatMinMax(10.f, 50.f), 0);
	ghostSprite = MeshBuilder::GenerateSpriteAnimation("cfire", 1, 8);
	ghostSprite->textureArray[0] = LoadTGA("Data//Texture//gastly.tga");
	SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>(ghostSprite);
	if (sa)
	{
		sa->m_anim = new Animation();
		sa->m_anim->Set(0, 7, 0, 1.f, true);
	}
}

Vector3 Enemy_Ghost::GetGhostOffSet()
{
	return ghostoffset;
}

void Enemy_Ghost::Update(double dt, Map map)
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
	if (map.Get_Type(Shadows) == "Wall")
	{
		dirX = -dirX;
		dirY = -dirY;
		dirX += Math::RandFloatMinMax(-5, 5);
		dirY += Math::RandFloatMinMax(-5, 5);
	}
	else if (map.Get_Type(Shadows) == "Floor")
	{
		ghostPos = ghostShadow;
	}
	if (ghostTimer > 15.f)
	{
		//teleport ghost to 1 tile before player position
		ghostPos = PlayerClass::pointer()->getPlayerPos() + GetGhostOffSet();
		ghostStayTimer += dt;
		dirX = 0;
		dirY = 0;
		
		if (ghostStayTimer > 5.f)
		{
			//ghost will move away again
			dirX += Math::RandFloatMinMax(-5, 5);
			dirY += Math::RandFloatMinMax(-5, 5);
			ghostShadow.x += dirX * dt;
			ghostShadow.y += dirY * dt;
			ghostTimer = 0.0f;
		}
	}
	else if (ghostTimer < 15.f)
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
	Vector3 Diff = Render_PI::Window_Scale() - ghostPos;
	Render_PI::pointer()->modelStack_Set(true);
	cout << Diff.x << " / " << Diff.y << endl;
	Render_PI::pointer()->RenderMeshIn2D(ghostSprite, false, Vector3(ghostPos), Vector3(10, 10, 1));
	Render_PI::pointer()->modelStack_Set(false);
}
void Enemy_Ghost::Exit()
{

}